using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;
using System.IO;
using System.Windows.Forms;

namespace BlueStar
{
    public partial class UpdateForm : Form
    {
        private string strServerPath = "\\\\server1\\Update\\BlueStar\\";
        private string strLocalPath = "C:\\BlueStar";
        private string strExeFile = "C:\\BlueStar\\Vod.exe";
        public UpdateForm()
        {
            InitializeComponent();
        }
        private void Copy(string sourceDirName, string destDirName)
        {           
            destDirName = destDirName + "\\";         
            if (Directory.Exists(sourceDirName))
            {
                if (!Directory.Exists(destDirName))
                {
                    Directory.CreateDirectory(destDirName);
                }
                foreach (string item in Directory.GetFiles(sourceDirName))
                {
                    string strDestFile = destDirName + Path.GetFileName(item);
                    File.Copy(item, strDestFile, true);
                    lblFileName.Text = "Update:  " + strDestFile;
                    lblFileName.Refresh();                 
                }
                foreach (string item in Directory.GetDirectories(sourceDirName))
                {
                    Copy(item, destDirName + item.Substring(item.LastIndexOf("\\") + 1));
                }
            }
        }

        private void UpdateForm_Shown(object sender, EventArgs e)
        {
           
            Copy(strServerPath, strLocalPath);
            System.Diagnostics.Process.Start(strExeFile);
            Application.Exit();      
        }
    }
}
