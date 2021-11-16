using System;
using System.Net;

namespace TestCS
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.Write("Client (0) or Server (1): ");
            bool isServer = Convert.ToInt32(Console.ReadLine()) == 1;

            string IP = "127.0.0.1";
            string port = "4004";
            if (!isServer)
            {
                Console.Write("Enter IP and port in IPv4:port format: ");
                //string[] temp = Console.ReadLine().Split(":");
                //IP = temp[0];
                //port = temp[1];
                port = Console.ReadLine();
            }

            try
            {
                ClientServer clientServer = new();
                clientServer.Open(IP, port, 3, isServer, Console.WriteLine);

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

        public static void TestCallback(Tuple<string, IPEndPoint> package)
        {

        }
    }
}
