using System;
using System.Net;

namespace TestCS
{
    internal class Program
    {
        static ClientServer clientServer = new();
        static void Main(string[] args)
        {
            AppDomain.CurrentDomain.ProcessExit += new EventHandler(CurrentDomain_ProcessExit);

            Console.Write("Client (0) or Server (1): ");
            bool isServer = Convert.ToInt32(Console.ReadLine()) == 1;

            string IP = "127.0.0.1";
            string port = "4004";
            if (!isServer)
            {
                Console.Write("Enter IP and port in IPv4:port format: ");
                string[] temp = Console.ReadLine().Split(":");
                IP = temp[0];
                port = temp[1];
            }
            else
            {
                Console.Write("Enter port: ");
                port = Console.ReadLine();
            }

            try
            {
                clientServer.Open(IP, port, 3, isServer, (Tuple<string, IPEndPoint> package) =>
                {
                    string message = "";
                    string sender = package.Item2.ToString();
                    if (sender == IP + ":" + port)
                    {
                        sender = "server";
                    }

                    if (!string.IsNullOrWhiteSpace(package.Item1))
                    {
                        message = package.Item1;
                    }

                    if (package.Item1 == int.MinValue.ToString())
                    {
                        message = "connected";
                    }
                    else if (package.Item1 == int.MaxValue.ToString())
                    {
                        message = "disconnected";
                    }

                    Console.WriteLine("{0}: {1}", sender, message);
                });

                while (clientServer.IsRunning)
                {
                    clientServer.SendMessage(Console.ReadLine());
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        static void CurrentDomain_ProcessExit(object sender, EventArgs e)
        {
            clientServer.Close();
        }
    }
}
