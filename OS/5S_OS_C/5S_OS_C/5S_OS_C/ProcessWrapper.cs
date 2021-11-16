using Microsoft.Management.Infrastructure;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Security.Principal;
using System.Text;
using System.Threading.Tasks;

namespace _5S_OS_C
{
    public class ProcessData : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        public string Name { get; set; }
        public string PID { get; set; }
        public string UserName { get; set; }
        public string CPU { get; set; }
        public string Memory { get; set; }

        public bool IsRunning()
        {
            return true;
        }

        public void Update()
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(Name)));
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(PID)));
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(UserName)));
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(CPU)));
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(Memory)));
        }
    }

    public class ProcessWrapper : ProcessData
    {
        Process process_;
        PerformanceCounter ram_;
        PerformanceCounter cpu_;
        bool isRunning;

        public new string Name
        {
            get
            {
                try
                {
                    return process_.ProcessName;
                }
                catch (Exception)
                {
                    return "Unknown";
                }
            }
        }
        public new string PID
        {
            get
            {
                try
                {
                    return process_.Id.ToString();
                }
                catch (Exception)
                {
                    return "Unknown";
                }
            }
        }
        public new string UserName
        {
            get
            {
                try
                {
                    return Utils.GetProcessUser(process_);
                }
                catch (Exception)
                {
                    return "Unknown";
                }
            }
        }
        public new string CPU
        {
            get
            {
                try
                {
                    return Math.Round((cpu_.NextValue() / Environment.ProcessorCount)).ToString();
                }
                catch (Exception)
                {
                    return "";
                }
            }
        }
        public new string Memory
        {
            get
            {
                try
                {
                    return Math.Round((ram_.NextValue() / 1024)).ToString() + " K";
                }
                catch (Exception)
                {
                    return "";
                }
            }
        }

        public ProcessWrapper(Process process)
        {
            process_ = process;
            process_.Exited += Process__Exited;
            ram_ = new PerformanceCounter("Process", "Working Set - Private", process_.ProcessName, true);
            cpu_ = new PerformanceCounter("Process", "% Processor Time", process_.ProcessName, true);
            isRunning = true;
        }

        private void Process__Exited(object sender, EventArgs e)
        {
            isRunning = false;
        }

        public new void Update()
        {
            process_?.Refresh();
            base.Update();
        }

        public new bool IsRunning()
        {
            return isRunning;
        }
    }

    public static class Utils
    {
        public static string GetProcessUser(Process process)
        {
            IntPtr processHandle = IntPtr.Zero;
            try
            {
                OpenProcessToken(process.Handle, 8, out processHandle);
                WindowsIdentity wi = new(processHandle);
                string user = wi.Name;
                return user.Contains(@"\") ? user.Substring(user.IndexOf(@"\") + 1) : user;
            }
            catch
            {
                return null;
            }
            finally
            {
                if (processHandle != IntPtr.Zero)
                {
                    CloseHandle(processHandle);
                }
            }
        }

        [DllImport("advapi32.dll", SetLastError = true)]
        private static extern bool OpenProcessToken(IntPtr ProcessHandle, uint DesiredAccess, out IntPtr TokenHandle);
        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static extern bool CloseHandle(IntPtr hObject);
    }
}
