using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Timers;

namespace TestCS
{
    public class ClientServer
    {
        private readonly int BufferSize = 65535;
        private readonly int HandshakeSequence = int.MinValue;

        private Socket socket_;

        private string ip_;

        private int receivePort_ = 0;
        private int sendPort_ = -1;

        private readonly SortedSet<Tuple<string, int>> clients = new();

        private bool isHost_;
        private bool isTimeout = true;
        private CancellationTokenSource cancellationToken = new();
        private Task listener_;
        private Action<Tuple<string, IPEndPoint>> callback_;
        private EndPoint lastRecievePoint;
        private EndPoint lastSendPoint;

        public int Timeout { get; set; }

        public bool IsRunning
        {
            get
            {
                return socket_ != null;
            }
        }
        public void Open(string IP, string port, int timeout, bool isHost, Action<Tuple<string, IPEndPoint>> callback)
        {
            clients.Clear();
            OpenWithoutClearClient(IP, port, timeout, isHost, callback);
        }

        private void OpenWithoutClearClient(string IP, string port, int timeout, bool isHost, Action<Tuple<string, IPEndPoint>> callback)
        {
            Timeout = timeout;

            RecreateSocket();
            isHost_ = isHost;
            SetListenPort(port);

            if (!isHost_)
            {
                SetDestinationAddress(IP, port);
                CheckConnection();
            }

            SetListener(callback);
            StartListener();
        }

        public void ReOpen()
        {
            OpenWithoutClearClient(ip_, receivePort_.ToString(), Timeout, isHost_, callback_);
        }

        private void Close()
        {
            if (socket_ != null)
            {
                try
                {
                    socket_.Shutdown(SocketShutdown.Both);
                    socket_.Close();
                    socket_ = null;
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.Message);
                }
            }
        }

        private void RecreateSocket()
        {
            Close();
            const int SIO_UDP_CONNRESET = -1744830452;
            socket_ = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
            //socket_.IOControl((IOControlCode)SIO_UDP_CONNRESET, new byte[] { 0, 0, 0, 0 }, null);
        }

        private void CheckConnection()
        {
            System.Timers.Timer fullTimeout = new();
            fullTimeout.Interval = Timeout * 1e3;
            fullTimeout.Elapsed += (object sender, ElapsedEventArgs e) =>
            {
                if (isTimeout)
                {
                    Close();
                    Console.WriteLine("Connection timeout");
                }
            };

            System.Timers.Timer retryTimeout = new();
            retryTimeout.Interval = 500;
            retryTimeout.Elapsed += (object sender, ElapsedEventArgs e) =>
            {
                if (isTimeout && socket_ != null)
                {
                    SendMessage(HandshakeSequence);
                }
                else
                {
                    retryTimeout.Stop();
                }
            };

            SendMessage(HandshakeSequence);
            retryTimeout.Start();

            fullTimeout.Start();
            var message = ReceiveMessage();

            if (message == null)
            {
                Close();
                throw new Exception("Connection error");
            }
        }

        public void SetListener(Action<Tuple<string, IPEndPoint>> callback)
        {
            //if (listener_ != null && listener_.Status != TaskStatus.Created)
            //{
            //}
            callback_ = callback;
            listener_ = new Task(() => Listen(callback_));
        }

        public void StartListener()
        {
            listener_.Start();
        }

        public void StopListener()
        {
            SetListener(callback_);
        }

        public void SetDestinationAddress(string IP, string port)
        {
            ip_ = IP;
            sendPort_ = int.Parse(port);
        }

        public void SetListenPort(string port)
        {
            socket_.Bind(new IPEndPoint(IPAddress.Any, isHost_ ? int.Parse(port) : 0));
            receivePort_ = (socket_.LocalEndPoint as IPEndPoint).Port;
        }

        public void SetHost(bool isHost)
        {
            Close();
            Open(ip_, sendPort_.ToString(), Timeout, isHost, callback_);
        }

        public void SendMessage(object msg, string ip = null, int? port = null)
        {
            if (socket_ == null)
            {
                return;
            }

            try
            {
                string message = msg.ToString();

                if (string.IsNullOrWhiteSpace(message))
                {
                    return;
                }

                byte[] data = Encoding.Unicode.GetBytes(message);

                if (isHost_ && ip == null && port == null)
                {
                    foreach (var client in clients)
                    {
                        try
                        {
                            lastSendPoint = new IPEndPoint(IPAddress.Parse(client.Item1), client.Item2);
                            socket_.SendTo(data, lastSendPoint);
                        }
                        catch (SocketException)
                        {
                            clients.Remove(client);
                        }
                    }
                }
                else
                {
                    lastSendPoint = new IPEndPoint(IPAddress.Parse(ip ?? ip_), port ?? sendPort_);
                    socket_.SendTo(data, lastSendPoint);
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                Close();
                throw ex.GetBaseException();
            }
        }

        public Tuple<string, IPEndPoint> ReceiveMessage()
        {
            if (socket_ == null)
            {
                return null;
            }

            try
            {
                StringBuilder builder = new();

                int bytes = 0;
                byte[] data = new byte[BufferSize];

                lastRecievePoint = new IPEndPoint(IPAddress.Any, 0);
                do
                {
                    bytes = socket_.ReceiveFrom(data, BufferSize, 0, ref lastRecievePoint);
                    builder.Append(Encoding.Unicode.GetString(data, 0, bytes));
                }
                while (socket_.Available > 0);
                IPEndPoint remoteFullIp = lastRecievePoint as IPEndPoint;

                if (builder.ToString() == HandshakeSequence.ToString())
                {
                    if (isHost_)
                    {
                        clients.Add(Tuple.Create(remoteFullIp.Address.ToString(), remoteFullIp.Port));
                        SendMessage(HandshakeSequence, remoteFullIp.Address.ToString(), remoteFullIp.Port);
                        return Tuple.Create("", remoteFullIp);
                    }
                    else
                    {
                        isTimeout = false;
                    }
                }

                return Tuple.Create(builder.ToString(), remoteFullIp);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                Close();
                if (isHost_)
                {
                    StopListener();
                    ReOpen();
                }
                throw ex.GetBaseException();
            }
        }

        private void Listen(Action<Tuple<string, IPEndPoint>> callback)
        {
            while (true)
            {
                if (socket_ != null)
                {
                    Tuple<string, IPEndPoint> message = ReceiveMessage();
                    callback?.Invoke(message);
                    if (message.Item1 == "clients")
                    {
                        foreach (var client in clients)
                        {
                            Console.WriteLine(client);
                        }
                    }
                }
            }
        }
    }
}