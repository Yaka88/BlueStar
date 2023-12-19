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
    public partial class ClientForm : Form
    {
        private string strSQL = "SELECT CODE,Singer1, Song_name,Init_Speaker,INIT_VOLBC,Filepath1,YwtFile,Songs.PINYIN,Singer.PINYIN,Has_Local FROM Songs,Singer WHERE AudioMatch = Yes AND gx_name=Singer1 ORDER by Code";
        private string strSQLQuery = "(song_name like '{0}%' or Singer1 like '{0}%' or Songs.PINYIN like '{0}%' or Singer.PINYIN like '{0}%')";
        private string strCode;
        private const string strPassword = "bl2160635";
      //  private const string strLocalPath = "\\\\C112\\VOD";
        private const string strLocalPath = "\\\\127.0.0.1\\VOD";   
        //private const string strLocalPath = "E:\\VOD";   
        private const string strKey = "Images\\Key.jpg";    
        private RMPlayer player = null;
        private bool isPause;
        private OleDbDataAdapter adapter = null;
        private DataTable dt = null;
  
        public ClientForm()
        {
            InitializeComponent();
        }
        private void PlayVod(int RowIndex)
        {
            if (player != null)
            {
                player.Cut();
                player = null;
            }
            strCode = SongGridView.Rows[RowIndex].Cells[0].Value.ToString();
            string strFileName = SongGridView.Rows[RowIndex].Cells["FilePath1"].Value.ToString();
          //  if ((bool)SongGridView.Rows[RowIndex].Cells["Has_Local"].Value)
            {
                int index = strFileName.LastIndexOf('\\');
                strFileName = strLocalPath + strFileName.Substring(index);
            }
            string strYwt = SongGridView.Rows[RowIndex].Cells["YwtFile"].Value.ToString();
            if (strYwt != string.Empty)
                strYwt = License.BaseDirectory + License.strYwtPath + strYwt;
            bool bInvert = (bool)SongGridView.Rows[RowIndex].Cells["Init_Speaker"].Value;
           // player = new RMPlayer();
           // player.Initialize(strCode);
            if (chkVocal.Checked)
                bInvert = !bInvert; //for test
            player = new RMPlayer(strFileName, strYwt, bInvert);
            short intVol = (short)SongGridView.Rows[RowIndex].Cells["INIT_VOLBC"].Value;
            player.Volume = intVol;
            player.SetOwner(panel1.Handle.ToInt32(), panel1.Width, panel1.Height);           
            player.Start();
          //  player.Balance = -1;
            //chkVocal.Checked = false;
            isPause = false;
        }
        private void SongGridView_CellContentDoubleClick(object sender, DataGridViewCellEventArgs e)
        {           
            PlayVod(e.RowIndex);
        }

        private void ClientForm_Load(object sender, EventArgs e)
        {
            adapter = new OleDbDataAdapter(strSQL, License.strConn + strPassword);
            dt = new DataTable();
            adapter.Fill(dt);
            FillGrid("");
            pictureBox1.Image = new Bitmap(License.BaseDirectory + strKey);
        }
        private void FillGrid(string strQuery)
        {          
            DataView dv= new DataView(dt,strQuery,"Code",DataViewRowState.OriginalRows);        
            SongGridView.DataSource = dv;
            SongGridView.Font = new Font(FontFamily.GenericSerif, 12);
            SongGridView.Columns[0].Width = 100;
            SongGridView.Columns[1].Width = 120;
            SongGridView.Columns[2].Width = 250;
            SongGridView.Columns[3].Visible = false;
            SongGridView.Columns[4].Visible = false;
            SongGridView.Columns[5].Visible = false;
            SongGridView.Columns[6].Visible = false;
            SongGridView.Columns[7].Visible = false;
            SongGridView.Columns[8].Visible = false;
            SongGridView.Columns[9].Visible = false; 
        }
        private void btnStart_Click(object sender, EventArgs e)
        {
            if (SongGridView.CurrentRow != null)
                PlayVod(SongGridView.CurrentRow.Index);
        }

        private void btnCut_Click(object sender, EventArgs e)
        {
            if (player != null)
            {
                player.Cut();
                player = null;
            }
        }

        private void btnPause_Click(object sender, EventArgs e)
        {
            if (player != null)
            {
                isPause = !isPause;
                if (isPause)
                    player.Pause();
                else
                    player.Start();
            }
        }

        private void chkVocal_CheckedChanged(object sender, EventArgs e)
        {
            if (player != null)
                player.Balance = chkVocal.Checked ? 1 : -1;
        }

        private void ClientForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (player != null)
            {
                player.Cut();
                player = null;
            }
            dt.Clear();
            adapter.Dispose();
        }

        private void btnQuery_Click(object sender, EventArgs e)
        {
            string strsql = string.Format(strSQLQuery, textName.Text.ToUpper());
            FillGrid(strsql);
        }

        private void pictureBox1_MouseClick(object sender, MouseEventArgs e)
        {
            //textName.Text += e.X.ToString(); 
            int istepx = 65,isetpy = 42;
            char ch = 'A';
            ch += (char)(e.X / istepx);
            if (e.Y >= isetpy)
                ch += (char)13;
            textName.Text += ch.ToString();          
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            textName.Text = string.Empty;
        }

        private void btnScale_Click(object sender, EventArgs e)
        {
            if (player == null)
                return;
            bool isNormal = panel1.Width == 360;
            if (isNormal)
            {
                panel1.Left -= panel1.Width;
                panel1.Width *= 2;
                panel1.Height  *= 2;                
            }
            else
            {
                panel1.Width /= 2;
                panel1.Height  /= 2;
                panel1.Left += panel1.Width;
            }
            player.SetOwner(panel1.Handle.ToInt32(), panel1.Width, panel1.Height);
        }
        
    }
}
