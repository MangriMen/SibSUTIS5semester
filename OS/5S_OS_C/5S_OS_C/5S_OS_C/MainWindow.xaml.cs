using CommunityToolkit.WinUI.UI.Controls;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Controls.Primitives;
using Microsoft.UI.Xaml.Data;
using Microsoft.UI.Xaml.Input;
using Microsoft.UI.Xaml.Media;
using Microsoft.UI.Xaml.Navigation;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Storage.Streams;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace _5S_OS_C
{
    /// <summary>
    /// An empty window that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainWindow : Window
    {
        public MyViewModel MyViewModel { get; set; } = new MyViewModel();

        public MainWindow()
        {
            this.InitializeComponent();

            //DispatcherTimer timer = new DispatcherTimer();
            //timer.Tick += MyViewModel.RefreshProcesses;
            //timer.Interval = new TimeSpan(0, 0, 0, 0, 1000);
            //timer.Start();
        }

        private void TextBox_KeyDown(object sender, KeyRoutedEventArgs e)
        {
            if (e.Key == Windows.System.VirtualKey.Enter)
            {
                MyViewModel.Port = 12000;
                MyViewModel.IP = (sender as TextBox).Text;
                MyViewModel.ConnectToServer();
            }
            else
            {
                MyViewModel.GetProcesses();
                DispatcherTimer timer = new DispatcherTimer();
                timer.Tick += MyViewModel.RefreshProcesses;
                timer.Interval = new TimeSpan(0, 0, 0, 0, 1000);
                timer.Start();
                MyViewModel.StartListener();
            }
        }
    }

    public class MyViewModel : INotifyPropertyChanged
    {

        public string Data { get; set; }
        short port_ = 0;
        public Int32 Port
        {
            get
            {
                return port_;
            }
            set
            {
                port_ = (short)value;
                if (client.Connected)
                {
                    client.Close();
                    client.Connect(new IPEndPoint(IPAddress.Parse(ip_), port_));
                }
            }
        }

        string ip_ = IPAddress.Loopback.ToString();
        public string IP
        {
            get
            {
                return ip_;
            }
            set
            {
                ip_ = value;
                if (client.Connected)
                {
                    client.Close();
                }
                client.Connect(new IPEndPoint(IPAddress.Parse(ip_), port_));
            }
        }

        TcpListener listner = new TcpListener(new IPEndPoint(IPAddress.Any, 12000));
        Thread listnerThread;
        TcpClient client = new TcpClient();
        Thread clientThread;

        public event PropertyChangedEventHandler PropertyChanged;
        public ObservableCollection<ProcessData> Processes { get; set; } = new ObservableCollection<ProcessData>();

        public void ConnectToServer()
        {
            clientThread = new(new ThreadStart(WhileConnected));
            clientThread.Start();
        }

        public void DisconnectFromServer()
        {
            if (clientThread != null)
            {
                ;
            }
            client.Dispose();
        }

        public void WhileConnected()
        {
            try
            {
                NetworkStream stream = client.GetStream();

                byte[] buffer = new byte[64000];
                int bytes = stream.Read(buffer, 0, buffer.Length);

                var stringObj = Encoding.UTF8.GetString(buffer);

                // proper way to Deserialize object
                ProcessData[] temp = JsonConvert.DeserializeObject<ProcessData[]>(stringObj);
                foreach (var pw in temp)
                {
                    _ = Processes.Append(pw);
                }

                stream.Close();
            }
            catch (Exception ex)
            {
                Debug.WriteLine("EXCEPTION:" + ex.ToString()); 
            }
        }

        public void StartListener()
        {
            listner.Start();

            listnerThread = new(new ThreadStart(WhileListen));
            listnerThread.Start();
        }
        public void StopListener()
        {
            if (listnerThread != null)
            {
                ;
            }
            listner.Stop();
        }

        public void WhileListen()
        {
            TcpClient client = listner.AcceptTcpClient();

            NetworkStream stream = client.GetStream();

            //var objToString = System.Text.Json.JsonSerializer.Serialize(Processes.ToArray());
            string objToString = JsonConvert.SerializeObject(Processes, Formatting.None);
            byte[] data = Encoding.UTF8.GetBytes(objToString);
            stream.Write(data, 0, data.Length);

            stream.Close();
            client.Close();
        }

        public void GetProcesses()
        {
            var allProcesses = Process.GetProcesses();
            foreach (var process in allProcesses)
            {
                Processes.Add(new ProcessWrapper(process));
            }
        }

        public void UpdateProcessList()
        {
            var allProcesses = Process.GetProcesses();
            var temp = new ObservableCollection<ProcessData>();
            foreach (var process in allProcesses)
            {
                temp.Add(new ProcessWrapper(process));
            }
            Processes.Concat(temp);
        }

        public void RefreshProcesses(object sender, object e)
        {
            //UpdateProcessList();

            foreach (var process in Processes)
            {
                process.Update();
                if (!process.IsRunning())
                {
                    Processes.Remove(process);
                }
            }
        }

        public void Sorting(object sender, CommunityToolkit.WinUI.UI.Controls.DataGridColumnEventArgs e)
        {
            var dg = (DataGrid)sender;
            ObservableCollection<ProcessData> temp = Processes;

            if (e.Column.Header.ToString() == "Name")
            {
                if (e.Column.SortDirection == null || e.Column.SortDirection == DataGridSortDirection.Descending)
                {
                    temp = new ObservableCollection<ProcessData>(from item in Processes
                                                                    orderby item.Name ascending
                                                                    select item);
                    e.Column.SortDirection = DataGridSortDirection.Ascending;
                }
                else
                {
                    temp = new ObservableCollection<ProcessData>(from item in Processes
                                                                    orderby item.Name descending
                                                                    select item);
                    e.Column.SortDirection = DataGridSortDirection.Descending;
                }
            }
            else if (e.Column.Header.ToString() == "PID")
            {
                if (e.Column.SortDirection == null || e.Column.SortDirection == DataGridSortDirection.Descending)
                {
                    temp = new ObservableCollection<ProcessData>(from item in Processes
                                                                    orderby item.PID ascending
                                                                    select item);
                    e.Column.SortDirection = DataGridSortDirection.Ascending;
                }
                else
                {
                    temp = new ObservableCollection<ProcessData>(from item in Processes
                                                                    orderby item.PID descending
                                                                    select item);
                    e.Column.SortDirection = DataGridSortDirection.Descending;
                }
            }
            else if (e.Column.Header.ToString() == "CPU")
            {
                if (e.Column.SortDirection == null || e.Column.SortDirection == DataGridSortDirection.Descending)
                {
                    temp = new ObservableCollection<ProcessData>(from item in Processes
                                                                    orderby item.CPU ascending
                                                                    select item);
                    e.Column.SortDirection = DataGridSortDirection.Ascending;
                }
                else
                {
                    temp = new ObservableCollection<ProcessData>(from item in Processes
                                                                    orderby item.CPU descending
                                                                    select item);
                    e.Column.SortDirection = DataGridSortDirection.Descending;
                }
            }
            else if (e.Column.Header.ToString() == "Memory")
            {
                if (e.Column.SortDirection == null || e.Column.SortDirection == DataGridSortDirection.Descending)
                {
                    temp = new ObservableCollection<ProcessData>(from item in Processes
                                                                    orderby item.Memory ascending
                                                                    select item);
                    e.Column.SortDirection = DataGridSortDirection.Ascending;
                }
                else
                {
                    temp = new ObservableCollection<ProcessData>(from item in Processes
                                                                    orderby item.Memory descending
                                                                    select item);
                    e.Column.SortDirection = DataGridSortDirection.Descending;
                }
            }

            Processes.Clear();
            foreach (var sortedProcess in temp)
            {
                Processes.Add(sortedProcess);
            }

            // add code to handle sorting by other columns as required

            //Remove sorting indicators from other columns
            foreach (var dgColumn in dg.Columns)
            {
                if (dgColumn.Header.ToString() != e.Column.Header.ToString())
                {
                    dgColumn.SortDirection = null;
                }
            }
        }
    }
}
