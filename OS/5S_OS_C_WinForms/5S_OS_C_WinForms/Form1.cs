using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Security.Principal;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _5S_OS_C_WinForms
{
    public partial class Form1 : Form
    {
        Process[] processes;
        public Form1()
        {
            InitializeComponent();
            GetNewProcesses();
        }

        public class ProcessWrapper
        {
            Process process_;
            PerformanceCounter ram_;
            PerformanceCounter cpu_;
            public bool isRunning;

            public string Name
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
            public string PID
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
            public string UserName
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
            public string CPU
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
            public string Memory
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
                this.process_ = process;
                this.process_.Exited += Process__Exited;
                ram_ = new PerformanceCounter("Process", "Working Set - Private", process_.ProcessName, true);
                cpu_ = new PerformanceCounter("Process", "% Processor Time", process_.ProcessName, true);
                isRunning = true;
            }

            private void Process__Exited(object sender, EventArgs e)
            {
                isRunning = false;
            }

            public void Refresh()
            {
                this.process_?.Refresh();
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
                    WindowsIdentity wi = new WindowsIdentity(processHandle);
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

        void GetNewProcesses()
        {
            processes = Process.GetProcesses();
            ProcessWrapper[] processWrappers = new ProcessWrapper[processes.Length];
            foreach (Process process in processes)
            {
                processWrappers.Append(new ProcessWrapper(process));
            }
            dgvProcesses.DataSource = processWrappers;
        }
    }
}
