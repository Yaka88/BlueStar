using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.OleDb;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace BlueStar
{
    public partial class ADForm : Form
    {
        private const string strConnSQL = "Provider=SQLOLEDB;Data Source={0},1433;Initial Catalog=BlueStar;User ID=BlueStar;Password={1}";
        private const string strPassword = "bl2160635";
        private const string strServer = "192.168.1.2";
        private OleDbDataAdapter adapter;
        private DataTable dt;
        private OleDbCommandBuilder cb;
        public ADForm()
        {
            InitializeComponent();
        }

        private void ADForm_Load(object sender, EventArgs e)
        {
            adapter = new OleDbDataAdapter("SELECT * FROM AD Order BY ID", string.Format(strConnSQL, strServer, strPassword));            
            dt = new DataTable();
            cb = new OleDbCommandBuilder(adapter);   
            FillLogData();
        }
        private void FillLogData()
        {                        
            adapter.Fill(dt);
            gridAD.DataSource = dt;
            gridAD.Columns[0].Width = 60;
            gridAD.Columns[0].HeaderText = "序号";
            gridAD.Columns[1].Width = 70;
            gridAD.Columns[1].HeaderText = "包厢号";
            gridAD.Columns[2].Width = 520;
            gridAD.Columns[2].HeaderText = "字幕内容";
            gridAD.Columns[3].Width = 100;
            gridAD.Columns[3].HeaderText = "有效期";
        }

        private void btnUpdate_Click(object sender, EventArgs e)
        {                       
            adapter.Update(dt);
        }

        private void btnDelete_Click(object sender, EventArgs e)
        {
            gridAD.Rows.Remove(gridAD.CurrentRow);            
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void ADForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            adapter.Update(dt);
            GC.Collect();
        }
    }
}
