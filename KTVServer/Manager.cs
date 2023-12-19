using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Net.Sockets;
using System.Net;
using System.Management;
using System.Threading;
using System.Security.Cryptography;

namespace BlueStar
{
    public partial class KTVServer: Form
    {
        private Thread thListener = null;
        private TcpListener tcpServer = null;
        private string strCPUSQL = "SELECT ProcessorId FROM Win32_Processor";
      //  private string strNetSQL = "SELECT MACAddress FROM Win32_NetworkAdapterConfiguration WHERE IPEnabled = true";
        private string strNetSQL = "SELECT MACAddress,Description  FROM Win32_NetworkAdapter WHERE AdapterTypeID = 0 AND PNPDeviceID LIKE 'PCI%'"; // PhysicalAdapter = true";
        private string strDate;
        private const string strDateFormat = "yyyyMMdd";
        private byte[] bytePass;
        private int port = 8868;
     //   private string strIP = "192.168.8.112";

        public KTVServer()
        {
            InitializeComponent();
        }

        private void GetUniqCode(string strTime)
        {
            string strCPU = string.Empty, strNet = string.Empty;
            try
            {
                ManagementObjectSearcher cimobject = new ManagementObjectSearcher(strCPUSQL);
                ManagementObjectCollection moc = cimobject.Get();
                foreach (ManagementObject mo in moc)
                {
                    strCPU = mo.Properties["ProcessorId"].Value.ToString().Trim();
                    if (strCPU.Length > 0)
                        break;
                }
                cimobject.Dispose();                             
                cimobject = new ManagementObjectSearcher(strNetSQL);
                moc = cimobject.Get();
                foreach (ManagementObject mo in moc)
                {
                    strNet = mo.Properties["MACAddress"].Value.ToString();
                    break;
                }
            }
            catch (Exception)
            { }
            
            StringBuilder strUniq = new StringBuilder(strCPU);
            strUniq.Append(strNet);//
         //   txtCode.Text = strUniq.ToString();

            MD5 md5 = MD5.Create();
            bytePass = md5.ComputeHash(Encoding.ASCII.GetBytes(strUniq.ToString()));
            strUniq.Length = 0;
            for (int i = 0; i < bytePass.Length; i++)
            {
                strUniq.Append(bytePass[i].ToString("X2"));
            }
            txtCode.Text = strUniq.ToString();
            strUniq.Append(strTime);
            bytePass = md5.ComputeHash(Encoding.ASCII.GetBytes(strUniq.ToString()));            
        }
        private void btnStart_Click(object sender, EventArgs e)
        {
            strDate = DateTime.Now.ToString(strDateFormat);
            GetUniqCode(strDate);
            thListener = new Thread(LicMonitor);
            thListener.Start();
            btnStart.Enabled = false;
            btnStop.Enabled = true;
            ListAddItem(" Service started.");
        }
        private void ListAddItem(string strList)
        {
            if (listClient.Items.Count >= 20)
            {
                listClient.Items.RemoveAt(0);
            }
            listClient.Items.Add(DateTime.Now.ToString() + strList);            
        }
        private void LicMonitor()
        {
            
            tcpServer = new TcpListener(IPAddress.Any, port);           
            tcpServer.Start();
            Byte[] bytes = new Byte[8];
            String data = null;
            while (true)
            {
                TcpClient client = tcpServer.AcceptTcpClient();
                NetworkStream stream = client.GetStream();                
                int i = stream.Read(bytes, 0, bytes.Length);
                if (i < 8) continue;
                data = Encoding.ASCII.GetString(bytes, 0, 8);              
                if (data != strDate)                
                {
                    GetUniqCode(data);
                    strDate = data;
                }
                // Send back a response.
                string Ipaddress = ((IPEndPoint)client.Client.RemoteEndPoint).Address.ToString();
                ListAddItem(" Client " + Ipaddress + " connected.");
                stream.Write(bytePass, 0, bytePass.Length);
                
            }
        }

        private void btnStop_Click(object sender, EventArgs e)
        {
            btnStart.Enabled = true;
            btnStop.Enabled = false;
            if (thListener != null)
            {               
                thListener.Abort();
                tcpServer.Stop();
                thListener = null;
            }
            ListAddItem(" Service stoped.");            
        }

        private void KTVServer_Load(object sender, EventArgs e)
        {
            btnStart_Click(this, null);
        }

        private void KTVServer_FormClosing(object sender, FormClosingEventArgs e)
        {
            btnStop_Click(this, null);
        }
    }
}
