using System;
using System.IO;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Data;
using System.Data.OleDb;
using System.Drawing;
using System.Drawing.Imaging;
using System.Text;
using System.Windows.Forms;
using BlueStar;
using DirectShowLib;


namespace BlueStar
{
    public partial class TestForm : Form
    {


        private RMPlayer player = null;
        private License lic = null;
      //  private Player player = null;

        private Mpg2Wav m2w = null;

        private bool isPause = false;
        private double starttime;
        
        private const string strPassword = "bl2160635";
        private string strConn = License.strConn + strPassword;
       // string strSQL = "SELECT CODE, Filepath1,Singer1, Song_name,Init_Speaker,kscfile.Filename FROM Songs, kscfile WHERE ((Filepath1 Like '%AA4%') AND (Singer1=[kscfile].[Singer]) AND ((Songs.Lang)=1) AND copydest = 1 AND ((kscfile.songName)=[Songs].[song_name])) AND matchpoint is null ORDER by Filepath1";
        //string strSQLPatch = "SELECT CODE, adddate, Filepath1,Singer1, Song_name,Init_Speaker,kscfile.Filename FROM Songs, kscfile WHERE Singer1=[kscfile].[Singer]  AND kscfile.songName=[Songs].[song_name] AND Matchpoint = 0 ORDER BY code";// ORDER by Filepath1";
        string strSQLKscByCode = "select filename,init_speaker from kscfile,songs where kscfile.songName=[Songs].[song_name] and Songs.[Singer1]=[kscfile].[Singer] AND code = '{0}'";
        string strSQLUpdate = "UPDATE Songs SET AddDate = Now,AudioMatch = Yes,YwtFile ='{0}',MatchPoint = {1} WHERE CODE='{2}'";
       //string strSQLUpdate = "UPDATE Songs SET AddDate = Now,YwtFile ='{0}',MatchPoint = {1} WHERE CODE='{2}'";
     //   
        string strshowtime = "karaoke.ShowTime := {0:000.000};   ";

        string strcode;
        OleDbConnection conn;
        OleDbCommand command;
        OleDbCommand command2;
        OleDbDataReader reader;
        int count = 0;

        private bool bBatchStart = false;
        string strfilename;
        string KSCFileFilter = "Audio files (*.ksc)|*.ksc|All Files (*.*)|*.*";
        string WaveFileFilter = "Audio files (*.wav; *.mpg)|*.wav; *.mpg|All Files (*.*)|*.*";
        string VideoFileFilter = "Video Files (*.avi; *.mpg; *.dat; *.mp4; *.vob)|*.avi; *.mpg; *.dat; *.mp4; *.vob|All Files (*.*)|*.*";

        //    private double ptime;
        private FileStream fsWav = null;
        private FileStream fsywt = null;//保存的文件流
        //        private FileStream fsksc = null;

        private const int WMGraphNotify = 0x0400 + 13;
        private const int WMConvertNotify = 0x0400 + 14;

        // private  int iSampleRate = 11025;
        //   private  short iSamples = 2048;
        //    private short iBytesPerSample = 1;
        //   private short iChannels = 1;
        private short iBeatRate;
        // private long istartPosition;

        //   private int iSampleSize = 0;//所采集到的数据大小
        //     private int iDataSize = 0;//Wave的数据大小

        // private BinaryWriter mWriter;
        private BinaryReader mReader;
        private BinaryReader mReaderywt;
        //        private StreamReader mReaderKsc;


        public TestForm()
        {
            InitializeComponent();
        }



        /*
        private void ConvertYWFbyKsc()
        {
            fsksc = new FileStream(textKSCFile.Text, FileMode.Open, FileAccess.Read);
            mReaderKsc = new StreamReader(fsksc, Encoding.GetEncoding("GB2312"));
            string strline;
            int findadd = -1;
            byte[] mFreqPair = new byte[4];  //test  4 
            byte[] mbyte;
            int count = 0;
            while ((strline = mReaderKsc.ReadLine()) != null)
            {                
                findadd = strline.IndexOf("karaoke.add('");
                if (findadd != -1)
                {
                    string strBegin, strEnd, strWords, strTimes;
                    int intBegin, intEnd = 0;
                    char ch = '\'';
                    intBegin = strline.IndexOf(ch, intEnd + 1)+1;
                    intEnd = strline.IndexOf(ch, intBegin);
                    strBegin = strline.Substring(intBegin, intEnd - intBegin);//strbegin = strline.Substring(12,9);
                    intBegin = strline.IndexOf(ch, intEnd + 1) + 1;
                    intEnd = strline.IndexOf(ch, intBegin);
                    strEnd = strline.Substring(intBegin, intEnd - intBegin);//strEnd = strline.Substring(25,9);
                    intBegin = strline.IndexOf(ch, intEnd + 1) + 1;
                    intEnd = strline.IndexOf(ch, intBegin);
                    strWords = strline.Substring(intBegin, intEnd - intBegin);
                    intBegin = strline.IndexOf(ch, intEnd + 1) + 1;
                    intEnd = strline.IndexOf(ch, intBegin);
                    strTimes = strline.Substring(intBegin, intEnd - intBegin);

                    intBegin = strTimes.IndexOf(',');
                    if (intBegin != -1)
                    {
                        long intfrom = (long)((int.Parse(strBegin.Substring(0, 2)) * 60 + double.Parse(strBegin.Substring(3))) * iSampleRate * iBytesPerSample * iChannels + 44);
                        long intto = (long)((int.Parse(strEnd.Substring(0, 2)) * 60 + double.Parse(strEnd.Substring(3))) * iSampleRate * iBytesPerSample * iChannels + 44);
                        long intfrompos = (intfrom - istartPosition) / iBeatRate;
                        long inttopos = (intto - istartPosition) / iBeatRate;
                        mReader.BaseStream.Position = istartPosition + intfrompos * iBeatRate;
                        mWriter.BaseStream.Position = 14 + intfrompos * 4;
                        for (long i = intfrompos; i < inttopos; i++)
                        {
                            mbyte = mReader.ReadBytes(iBeatRate);
                            if (mbyte.Length < iBeatRate)
                                break;
                            else
                            {
                                AudioMatch.GetMainFreq(ref mbyte, ref mFreqPair,iBytesPerSample, checkMore.Checked);
                                if (mFreqPair[2] > 0) { count++; }
                                mWriter.Write(mFreqPair);
                            }

                        }
                    }
                }
            }
            mWriter.Seek(12, SeekOrigin.Begin);
            mWriter.Write(count);
            MessageBox.Show("Match point : " + count);
        }

        private void ConvertYWFbyLRC()
        {
                int iHeadTo = 0, iMiddleFrom = 0, iMiddleTo = 0, iMiddleFrom2 = 0, iMiddleTo2 = 0;//, iTailFrom = 0;
            /*
            try
            {
                iHeadTo = (int)((int.Parse(textHeadTo.Text.Substring(0, 2)) * 60 + double.Parse(textHeadTo.Text.Substring(3))) * iSampleRate * iChannels + 44);            
                iMiddleFrom = (int)((int.Parse(textMiddleFrom.Text.Substring(0, 2)) * 60 + double.Parse(textMiddleFrom.Text.Substring(3))) * iSampleRate * iChannels + 44);                
                iMiddleTo = (int)((int.Parse(textMiddleTo.Text.Substring(0, 2)) * 60 + double.Parse(textMiddleTo.Text.Substring(3))) * iSampleRate * iChannels + 44);
                iMiddleFrom2 = (int)((int.Parse(textMiddleFrom2.Text.Substring(0, 2)) * 60 + double.Parse(textMiddleFrom2.Text.Substring(3))) * iSampleRate * iChannels + 44);
                iMiddleTo2 = (int)((int.Parse(textMiddleTo2.Text.Substring(0, 2)) * 60 + double.Parse(textMiddleTo2.Text.Substring(3))) * iSampleRate * iChannels + 44);
                iTailFrom = (int)((int.Parse(textKSCFile.Text.Substring(0, 2)) * 60 + double.Parse(textKSCFile.Text.Substring(3))) * iSampleRate * iChannels + 44);
            }
            catch { }
            *
            
            byte[] mFreqPair = new byte[4];  //test  4 

            byte[] mbyte;
            int count = 0;
            while (true)
            {
                //iHz = AudioMatch.GetHz(mbyte);
                //mWriter.Write(iHz);
                //byte nFirstHZ, nSecondHZ,nFirstAmp,nSecondAmp;
                //AudioMatch.GetMainFreq(ref mbyte, out nFirstHZ, out nSecondHZ, out nFirstAmp,out nSecondAmp);                
                //AudioMatch.GetMainFreq(ref mbyte, ref mFreqPair,iBytesPerSample,iChannels);
                long pos = mReader.BaseStream.Position;
              //  if (pos >= iTailFrom)
              //      break;
                //else
                if (pos < iHeadTo || pos >= iMiddleFrom && pos < iMiddleTo || pos >= iMiddleFrom2 && pos < iMiddleTo2)
                {
                    mFreqPair[0] = mFreqPair[1] = mFreqPair[3] = mFreqPair[2] = 0;
                    mWriter.Write(mFreqPair);
                    mReader.BaseStream.Position += iBeatRate;
                }
                else
                {                   
                    mbyte = mReader.ReadBytes(iBeatRate);
                    if (mbyte.Length < iBeatRate)
                        break;
                    else
                    {
                        AudioMatch.GetMainFreq(ref mbyte, ref mFreqPair, iBytesPerSample,checkMore.Checked);
                        if (mFreqPair[2] > 0) { count++; }
                        
                        mWriter.Write(mFreqPair);                        
                    }
                }                                
            }
            mWriter.Seek(12, SeekOrigin.Begin);
            mWriter.Write(count);
            MessageBox.Show("Time :" + (DateTime.Now - dtstart).TotalSeconds.ToString());
            MessageBox.Show("Match point : " + count);
        } */
        private void button1_Click(object sender, EventArgs e)
        {
            openFileDialog1.Filter = WaveFileFilter;
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                strfilename = openFileDialog1.FileName;
            }
            else
                return;
            
            if (strfilename.EndsWith(".mpg"))
            {
                int inindex = strfilename.LastIndexOf('\\') + 1;   
                strcode = strfilename.Substring(inindex, strfilename.Length - inindex - 4);
                if (checkToWav.Checked)
                {
                    string strWav = License.BaseDirectory + "Wav\\" + strcode + ".wav";
                    m2w = new Mpg2Wav(strfilename, strWav, textKSCFile.Text, checkInvert.Checked, ref lic);
                }
                else
                {
                    bool Binvert = false;
                    string strKSC = "";
                    if (textKSCFile.Text == string.Empty)
                    {

                        conn = new OleDbConnection(strConn);
                        conn.Open();
                        command2 = new OleDbCommand(string.Format(strSQLKscByCode, strcode), conn);
                        OleDbDataReader dbreader = command2.ExecuteReader();
                        if (dbreader.Read())
                        {
                            strKSC = License.BaseDirectory + "Ksc\\" + dbreader["Filename"].ToString();
                            Binvert = (bool)dbreader["init_speaker"];
                        }
                        conn.Close();
                    }
                    else
                    {
                        strKSC = textKSCFile.Text;
                        Binvert =  checkInvert.Checked;
                    }
                    string strYwt = License.BaseDirectory + "Ywt\\" + strcode +  ".ywt";
                    m2w = new Mpg2Wav(strfilename, strYwt, strKSC, Binvert, ref lic);
                }
                if (lic.isValid)
                {
                    m2w.SetNotifyWindow(this.Handle, WMConvertNotify);
                  //  m2w.bMoreData = chkMoreData.Checked;
                    m2w.Start();                    
                }
                else                    
                    m2w = null;
            }
            else
            {
                fsWav = new FileStream(strfilename, FileMode.Open, FileAccess.Read);
                int iSampleSize;
                string strYwt = License.BaseDirectory + "Ywt" + strfilename.Substring(strfilename.LastIndexOf('\\')).Replace(".wav", ".ywt");
                Mpg2Wav.Wave2Ywf(fsWav, null,strYwt, textKSCFile.Text, out iSampleSize);
                MessageBox.Show("match point is " + iSampleSize.ToString());
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string strfilename;
            openFileDialog1.Filter = WaveFileFilter;
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                strfilename = openFileDialog1.FileName;
            }
            else
                return;

            float mTotalScore = 0;
            int iBeatCount = 0;

            //return;           

            string strYwt = strfilename.Remove(strfilename.IndexOf("_")) + ".ywt";
            strYwt = strYwt.Replace("Wav", "Ywt");
            fsywt = new FileStream(strYwt, FileMode.Open, FileAccess.Read);
            mReaderywt = new BinaryReader(fsywt);
            YwtFormat ywtF = AudioMatch.PreReadYwtFile(mReaderywt);
            mReaderywt.BaseStream.Seek(ywtF.SentenceCount * 8, SeekOrigin.Current);

            fsWav = new FileStream(strfilename, FileMode.Open, FileAccess.Read);
            mReader = new BinaryReader(fsWav);
            WaveFormatEx wave=  Mpg2Wav.PreReadWaveFile(mReader,ywtF.Version);

            int iBeatRate = (short)(AudioMatch.iSamples * ywtF.BytesPerSample);
            byte[] mbyte;
            int index = -1;
            do
            {
                mbyte = mReader.ReadBytes(iBeatRate);
                if (mbyte.Length < iBeatRate)
                    return;
                index = AudioMatch.GetFirstFreq(ref mbyte, ref ywtF, wave.nChannels);
            }
            while (index == -1);

            //     iBeatRate = iSampleRate * 30 / iBpm;
            
            //   int iDataSize = iSampleSize / iBeatRate;
            byte[] OriFreqPair = null;
            byte[] NewFreqPair = new byte[2];
            double[] newAmp = new double[2];
            
            Single mCurScore = 0;
            while (true)
            {
                OriFreqPair = mReaderywt.ReadBytes(4);
                if (OriFreqPair.Length < 4) break;
                if (OriFreqPair[2] > 0) //if (nFirstHZ >= 16 && nFirstAmp > 0)   // >=80hz
                {
                    mbyte = mReader.ReadBytes(iBeatRate);
                    if (mbyte.Length < iBeatRate) break;
                    AudioMatch.GetMainFreq(ref mbyte, ref NewFreqPair, ref newAmp, ywtF.BytesPerSample);

                    mCurScore = AudioMatch.GetScore2(ref OriFreqPair, ref NewFreqPair);
                    if (mCurScore >= short.Parse(textGrade.Text))
                        mTotalScore += mCurScore;
                    iBeatCount++;
                }
                else
                    mReader.BaseStream.Position += iBeatRate;
            }

            float AveScore = mTotalScore / iBeatCount;
            MessageBox.Show("AveScore is " + AveScore.ToString());

            mReader.Close();
            mReaderywt.Close();
            fsWav.Close();
            fsywt.Close();

        }


        
        protected override void WndProc(ref Message m)
        {
            switch (m.Msg)
            {
                case WMGraphNotify:
                    {
                        if (player != null && player.IsComplete())
                        {
                            timer1.Stop();
                            player.Stop();
                            player = null;
                        }
                        break;
                    }
                case WMConvertNotify:
                    {
                        if (m2w != null && m2w.Complete())
                        {
                            if (checkToWav.Checked)
                            {
                                m2w = null;
                                MessageBox.Show("done");
                            }
                            else if (bBatchStart)
                            {
                                // iDataSize = m2w.iDataSize;
                                
                                    string strSQL = string.Format(strSQLUpdate, strcode + ".ywt", m2w.iDataSize, strcode);
                                    m2w = null;
                                    command2 = new OleDbCommand(strSQL, conn);
                                    int intLow = command2.ExecuteNonQuery();
                                
                                //File.Copy(strFilename, strFilename2);
                                count++;
                                lblPosition.Text = count.ToString();
                                processnextSongs();
                            }
                            else
                            {
                                string strSQL = string.Format(strSQLUpdate, strcode + ".ywt", m2w.iDataSize, strcode);
                                conn = new OleDbConnection(strConn);
                                conn.Open();
                                command2 = new OleDbCommand(strSQL, conn);
                                int intLow = command2.ExecuteNonQuery();                               
                                conn.Close();
                                MessageBox.Show("Match point :" + m2w.iDataSize.ToString());
                                m2w = null;
                            }                            
                        }
                        break;
                    }
            }

            base.WndProc(ref m);
        }
        
        private void button3_Click(object sender, EventArgs e)
        {

            openFileDialog1.Filter = VideoFileFilter;
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                strfilename = openFileDialog1.FileName;
            }
            else
                return;

            playvod(strfilename, checkMatch.Checked);

        }
        private void playvod(string strfilename, bool bmatch)
        {
            if (player != null)
            {
                player.Stop();
                player = null;
            }
            string strywtfile = string.Empty;

            if (bmatch)
            {
                int inindex = strfilename.LastIndexOf('\\') + 1;
                strcode = strfilename.Substring(inindex, strfilename.Length - inindex - 4);
                strywtfile = License.BaseDirectory + "Ywt\\" + strcode + ".ywt";
            }

          //  player = new RMPlayer(strfilename, strywtfile, checkInvert.Checked);
             player = new RMPlayer();
            // player.iMode = bmatch ? 1 : 0;
             player.Initialize2(strfilename,bmatch,checkInvert.Checked);

            player.SetNotifyWindow(this.Handle.ToInt32(), WMGraphNotify);
            if (checkVisible.Checked)
                player.SetOwner(panel1.Handle.ToInt32(), panel1.Width, panel1.Height);
            else
                player.SetOwner(0, 0, 0);

            // if (bmatch)
            ///  {
            //   am = new AudioMatch(strywtfile, checkRecord.Checked);
            //   am.Grade = short.Parse(textGrade.Text);

            //      player.Start();
            //   timer1.Interval = am.Interval;
            //   timer1.Enabled = true;
            //   am.Start();
            //  }
            //  else
            player.Start();
            isPause = false;
            timer1.Start();
            //player.Balance = -1;
           // checkVocal.Checked = false;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            timer1.Stop();
            if (player != null)
            {
                if (checkMatch.Checked)
                {
                    player.Cut();
                    //player.UpdateScore(am.CurTone, -1, am.AveScore);
                    //timer1.Enabled = false;
                    //am.Stop();
                    //MessageBox.Show("score is " + am.AveScore.ToString());
                    //am = null;
                }
                else
                    player.Stop();
              
                player = null;
            }
        }
     

        private void timer1_Tick(object sender, EventArgs e)
        {
            lblPosition.Text = player.CurrentPosition.ToString();
        /*    if (checkMatch.Checked)
            {
                if (!player.UpdateScore(am.CurTone, am.CurScore, am.AveScore))
                    timer1.Enabled = false;

            }*/
        }

        private void FFTNext()
        {
            byte[] mbyte = mReader.ReadBytes(iBeatRate);
            int iSamples = mbyte.Length >> 1;

            Bitmap bitmapOverlay = new Bitmap(640, 480,
               System.Drawing.Imaging.PixelFormat.Format32bppArgb);
            Graphics g;
            g = Graphics.FromImage(bitmapOverlay);
            g.Clear(System.Drawing.Color.AntiqueWhite);
            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            Pen pen = new Pen(Color.Blue);

            double[] pRealIn = new double[iSamples];
            byte[] bytes = new byte[2]; double[] pAmp = new double[2];
            //left channel
            for (int i = 0; i < iSamples; i++)
            {
                pRealIn[i] = mbyte[i << 1];
            }
            AudioMatch.GetAmp_Freq(ref pRealIn, ref bytes, ref pAmp);
            lblFreq.Text = ((byte)bytes[0]).ToString() + "  |  " + ((byte)bytes[1]).ToString();

            Point p1 = new Point(0, 230);
            Point p2 = new Point(0, 0);

            for (int i = 1; i <= 320; i++)
            {
                p1.X += 2;
                p2.Y = (int)(230 - pRealIn[i] * 5);
                p2.X += 2;
                g.DrawLine(pen, p1, p2);
            }


            //right

            for (int i = 0; i < iSamples; i++)
            {
                pRealIn[i] = mbyte[(i << 1) + 1];
            }
            AudioMatch.GetAmp_Freq(ref pRealIn, ref bytes, ref pAmp);
            lblFreq.Text += "  |  " + ((byte)bytes[0]).ToString() + "  |  " + ((byte)bytes[1]).ToString();


            p1 = new Point(0, 470);
            p2 = new Point(0, 0);

            for (int i = 1; i <= 320; i++)
            {
                p1.X += 2;
                p2.Y = (int)(470 - pRealIn[i] * 5);
                p2.X += 2;
                g.DrawLine(pen, p1, p2);
            }
            g.Dispose();

            panel1.BackgroundImage = bitmapOverlay;
            //  panel1.DrawToBitmap(bitmapOverlay, panel1.ClientRectangle);        

        }


        private void FFTTest()
        {
            string strfilename;
            openFileDialog1.Filter = WaveFileFilter;
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                strfilename = openFileDialog1.FileName;
            }
            else
                return;
            //   short iHz = 0;
            fsWav = new FileStream(strfilename, FileMode.Open, FileAccess.Read);
            mReader = new BinaryReader(fsWav);

            WaveFormatEx wave = Mpg2Wav.PreReadWaveFile(mReader,1);

            //  iBpm = short.Parse(textBox1.Text);         
            //  iBeatRate = iSampleRate * 30 / iBpm;
            iBeatRate = (short)(AudioMatch.iSamples * 1);

            //iDataSize = iSampleSize / iBeatRate;

            int iHeadTo = 0, iMiddleFrom = 0, iMiddleTo = 0, iMiddleFrom2 = 0, iMiddleTo2 = 0;//, iTailFrom = 0;
            /*     try
                 {
                     iHeadTo = (int)((int.Parse(textHeadTo.Text.Substring(0, 2)) * 60 + double.Parse(textHeadTo.Text.Substring(3))) * iSampleRate * iChannels + 44);
                     iMiddleFrom = (int)((int.Parse(textMiddleFrom.Text.Substring(0, 2)) * 60 + double.Parse(textMiddleFrom.Text.Substring(3))) * iSampleRate * iChannels + 44);
                     iMiddleTo = (int)((int.Parse(textMiddleTo.Text.Substring(0, 2)) * 60 + double.Parse(textMiddleTo.Text.Substring(3))) * iSampleRate * iChannels + 44);
                     iMiddleFrom2 = (int)((int.Parse(textMiddleFrom2.Text.Substring(0, 2)) * 60 + double.Parse(textMiddleFrom2.Text.Substring(3))) * iSampleRate * iChannels + 44);
                     iMiddleTo2 = (int)((int.Parse(textMiddleTo2.Text.Substring(0, 2)) * 60 + double.Parse(textMiddleTo2.Text.Substring(3))) * iSampleRate * iChannels + 44);
                     iTailFrom = (int)((int.Parse(textKSCFile.Text.Substring(0, 2)) * 60 + double.Parse(textKSCFile.Text.Substring(3))) * iSampleRate * iChannels + 44);
                 }
                 catch { }
                 */
            byte[] mFreqPair = new byte[4];  //test  4 



            while (true)
            {
                long pos = mReader.BaseStream.Position;
                //   if (pos >= iTailFrom)
                //     break;
                if (pos < iHeadTo || pos >= iMiddleFrom && pos < iMiddleTo || pos >= iMiddleFrom2 && pos < iMiddleTo2)
                {
                    mFreqPair[0] = mFreqPair[1] = mFreqPair[3] = mFreqPair[2] = 0;
                    mReader.BaseStream.Position += iBeatRate;
                }
                else
                {
                    break;
                }
            }
        }

        private void FFTClose()
        {

            mReader.Close();
            fsWav.Close();
        }

        private void butKSCFile_Click(object sender, EventArgs e)
        {
            openFileDialog1.Filter = KSCFileFilter;
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                textKSCFile.Text = openFileDialog1.FileName;
            }
            else
                return;
        }
        private void processnextSongs()
        {
            
            while (reader.Read())
            {
                string strFileMpg, strFileYwt, strFileKSc;
                // lblPosition.Text = count.ToString();   
//                Environment.MachineName 
                
                strFileMpg = reader["Filepath1"].ToString();
                int index = strFileMpg.LastIndexOf('\\');
                //int index = strFileMpg.IndexOf('\\', 2);
                strFileMpg = "\\\\C112\\VOD" + strFileMpg.Substring(index);
                strcode = reader["CODE"].ToString();
                strFileYwt = License.BaseDirectory + "Ywt\\" + strcode + ".ywt";
                //.Replace("\\\\Vod1", );
                // strFileMpg = reader["Filepath1"].ToString().Replace("\\\\vod1\\AA2", "G:\\MV\\Download");

                command2 = new OleDbCommand(string.Format(strSQLKscByCode, strcode), conn);
                OleDbDataReader dbreader = command2.ExecuteReader();
                dbreader.Read();
                
                    strFileKSc = License.BaseDirectory + "Ksc\\" + dbreader["Filename"].ToString();                   
                
                dbreader.Close();                
                              
                bool bInvert = (bool)reader["Init_Speaker"];

                if (File.Exists(strFileMpg) && File.Exists(strFileKSc))
                {
                    m2w = new Mpg2Wav(strFileMpg, strFileYwt, strFileKSc, bInvert, ref lic);
                    if (m2w.IsInitialized)
                    {
                        m2w.SetNotifyWindow(this.Handle, WMConvertNotify);
                      //  m2w.bMoreData = chkMoreData.Checked;
                        m2w.Start();
                        return;
                    }
                    else
                    {
                        m2w.Stop();
                        m2w = null;
                        continue;
                    }
                }
                else
                    continue ;
            }

            bBatchStart = false;
            reader.Close();
            conn.Close();
            MessageBox.Show("done");

        }

        private void button8_Click(object sender, EventArgs e)
        {
//            string strSQLPatch = "SELECT distinct(CODE), Filepath1,Singer1, Song_name,Init_Speaker FROM Songs, kscfile WHERE ((Filepath1 Like '%AA4%') AND (Singer1=[kscfile].[Singer]) AND ((Songs.Lang)=1) AND copydest = 1 AND ((kscfile.songName)=[Songs].[song_name])) AND matchpoint is null ORDER by Filepath1";
            string strSQLPatch = "SELECT CODE, Filepath1,Singer1, Song_name,Init_Speaker FROM Songs WHERE adddate > #2010/07/27# and matchpoint > 0 ORDER by Filepath1";
            conn = new OleDbConnection(strConn);
            conn.Open();
            command = new OleDbCommand(strSQLPatch, conn);

            reader = command.ExecuteReader();//
            count = 0;
            bBatchStart = true;
            processnextSongs();

        }
        private void copyfile()
        {
           // string strSQL = "SELECT distinct kscfile.filename FROM kscfile, songs WHERE ((kscfile.songName)=[Songs].[song_name]) AND ((songs.Singer1)=[kscfile].[Singer]) AND songs.matchpoint >= 0";
            //string strSQL = "SELECT distinct(code), filePath1 FROM Songs, kscfile WHERE (((Songs.[Filepath1]) Like '%AA4%') AND ((Songs.[Singer1])=[kscfile].[Singer]) AND (Songs.Lang)=1 AND copydest = 1 AND ((kscfile.songName)=[Songs].[song_name]))  and matchpoint is null ORDER BY filepath1";
            string strSQL = "SELECT code, filePath1 FROM Songs";
            //string strSQL = "SELECT code, filePath1 FROM Songs WHERE audiomatch = yes ORDER BY code";
            conn = new OleDbConnection(strConn);
            conn.Open();
            command = new OleDbCommand(strSQL, conn);
            reader = command.ExecuteReader();//
          /*  int iPast = int.Parse(textSQL.Text);
            for (int i = 0; i < iPast; i++)
            {
                reader.Read();
            }
            for (int i = iPast; i < iPast + 100; i++)*/
            //count = iPast; 
            while(reader.Read())
                {
                    string strFileMpg = reader["filePath1"].ToString();
                    int index = strFileMpg.IndexOf('\\',2);
                    string strdest = "F:\\VOD" + strFileMpg.Substring(index);
                   // index = strFileMpg.IndexOf('\\', 2);
                    strFileMpg = "H:" + strFileMpg.Substring(index);
                    if (File.Exists(strFileMpg))
                    {
                        File.Copy(strFileMpg, strdest);
                      //  count++;
                      //  if (count >= 150)
                        //    break;
                    }
                }
            
            conn.Close();
            MessageBox.Show("done");

        }
        private void exeSQL()
        {
            conn = new OleDbConnection(strConn);
            conn.Open();
            string strSQL = textSQL.Text;
            command = new OleDbCommand(strSQL, conn);
            int intret = command.ExecuteNonQuery();
            conn.Close();
            MessageBox.Show(intret.ToString());
        }
        private void button9_Click(object sender, EventArgs e)
        {
            //exeSQL();                                                        
        }

        private void checkVocal_CheckedChanged(object sender, EventArgs e)
        {
            if (player != null)
                player.Balance = checkVocal.Checked ? 1 : -1;

        }

        private void button10_Click(object sender, EventArgs e)
        {
            if (player == null)
                return;
            isPause = !isPause;            
            if (isPause)
            {
              //  am.Pause();
                starttime = player.CurrentPosition - 0.5;
                player.Pause();
                timer1.Stop();
            }
            else
            {
              //  am.Start();
                player.Start();
                timer1.Start();
            }
        }
        private void processBitmap()
        {
            string strOsdBmp = "Images\\ADBack.png";
            string strOsdpng = "Images\\ADBack2.png";
            //string strOsdpng2 = "Images\\OSDBackNew2.bmp";               
          //  Bitmap bitmapOrigin = new Bitmap(License.BaseDirectory + strOsdBmp);
            Bitmap bitmapOrigin = new Bitmap("H:\\Users\\Yaka\\Pictures\\Logo.png");
          //  bitmapOrigin.Save(strOsdpng);
           //  bitmapOrigin.MakeTransparent(Color.White);
            //  Graphics g = Graphics.FromImage(bitmapback);
            //   g.DrawImageUnscaled(bitmapOrigin, new Point());

              for (int x = 0;x < bitmapOrigin.Width;x++)
                  for (int y = 0; y < bitmapOrigin.Height; y++)
                  {
                      Color oldcol = bitmapOrigin.GetPixel(x, y);
                      Color newcol;
                        if (oldcol.R >= 240 && oldcol.G >= 240 && oldcol.B >= 240)
                      //    newcol = Color.FromArgb(0, oldcol.R, oldcol.G, oldcol.B);
                     // if (oldcol.R == 51 && oldcol.G == 51 && oldcol.B == 51 && oldcol.A == 255)
                      {
                         // if (y >= 15)
                         //     newcol = Color.FromArgb(80, 51, 51, 51);
                       //   else
                              newcol = Color.FromArgb(0, 0, 0, 0);
                          bitmapOrigin.SetPixel(x, y, newcol);

                      }
                    //  else if (oldcol.R < 102 && oldcol.G < 102 && oldcol.B < 102)                      
                         // newcol = Color.FromArgb(255, 102, 102, 102);
                        //  bitmapOrigin.SetPixel(x, y, newcol);                                            
                  }
            //bitmapOrigin.Save(License.BaseDirectory + strOsdpng);
              bitmapOrigin.Save("H:\\Users\\Yaka\\Pictures\\Logo2.png");
        }
        private void patchButton_Click(object sender, EventArgs e)
        {
            if (player != null)
            {
                timer1.Stop();
                player.Stop();
                player = null;
            }
            bool Binvert = false;
            string strKSC = "";
            conn = new OleDbConnection(strConn);
            conn.Open();
            command2 = new OleDbCommand(string.Format(strSQLKscByCode, strcode), conn);
            OleDbDataReader dbreader = command2.ExecuteReader();
            if (dbreader.Read())
            {
                strKSC = License.BaseDirectory + "Ksc\\" + dbreader["Filename"].ToString();
                Binvert = (bool)dbreader["init_speaker"];
            }
            conn.Close();

            FileStream fsksc = new FileStream(strKSC, FileMode.Open, FileAccess.Write);
            StreamWriter mWriteKsc = new StreamWriter(fsksc, Encoding.GetEncoding("GB2312"));
            mWriteKsc.WriteLine(string.Format(strshowtime, starttime));
            mWriteKsc.Flush();
            fsksc.Close();


            string strYwt = License.BaseDirectory + "Ywt\\" + strcode + ".ywt";
            m2w = new Mpg2Wav(strfilename, strYwt, strKSC, Binvert, ref lic);            
            m2w.SetNotifyWindow(this.Handle, WMConvertNotify);
           // m2w.bMoreData = chkMoreData.Checked;
            m2w.Start();

        }

        private void button11_Click(object sender, EventArgs e)
        {
            if (player != null)
            player.CurrentPosition = player.CurrentPosition - 1;
        }

        private void button12_Click(object sender, EventArgs e)
        {
            if (player != null)
            player.CurrentPosition = player.CurrentPosition + 1;
        }

        private void btnCopyFile_Click(object sender, EventArgs e)
        {
            copyfile();
        }

        private void btnBMP_Click(object sender, EventArgs e)
        {
            processBitmap();
        }

        private void btnUpdateYwt_Click(object sender, EventArgs e)
        {
            string strSQL = "SELECT ywtfile,kscfile.filename FROM kscfile, songs WHERE ((kscfile.songName)=[Songs].[song_name]) AND ((songs.Singer1)=[kscfile].[Singer]) AND audiomatch = yes";
         
            conn = new OleDbConnection(strConn);
            conn.Open();
            command = new OleDbCommand(strSQL, conn);
            reader = command.ExecuteReader();//        

            while (reader.Read())
            {                
                string strKsc = License.BaseDirectory + "Ksc\\" + reader["filename"].ToString();
                string strywtSource = License.BaseDirectory + "Ywt\\" + reader["ywtfile"].ToString();
                string strywtNew = License.BaseDirectory + "YwtNew\\" + reader["ywtfile"].ToString();
                FileStream fsywt = new FileStream(strywtSource, FileMode.Open, FileAccess.Read);
                BinaryReader  mReaderywt = new BinaryReader(fsywt);
                YwtFormat ywt = AudioMatch.PreReadYwtFile(mReaderywt);
                mReaderywt.BaseStream.Seek(ywt.SentenceCount * 8, SeekOrigin.Current);

                float interval = (float)AudioMatch.iSamples / ywt.SampleRate;
                Collection<Single> colSingle;
                Mpg2Wav.ConvertYWFbyKsc(interval, strKsc, out colSingle);
                ywt.SentenceCount = colSingle.Count / 2;


                FileStream fsywt2 = new FileStream(strywtNew, FileMode.Create);
                BinaryWriter mWriter = new BinaryWriter(fsywt2);
                AudioMatch.CreateYwtFile(mWriter, ywt);

                for (int i = 0; i < colSingle.Count; i++)
                {
                    mWriter.Write(colSingle[i]);
                }
                int data;
                while (mReaderywt.BaseStream.Position < mReaderywt.BaseStream.Length)
                {
                    data = mReaderywt.ReadInt32();
                    mWriter.Write(data);
                }

                mWriter.Close();
                fsywt2.Close();
                mReaderywt.Close();
                fsywt.Close();                
            }

            conn.Close();
            MessageBox.Show("done");
        }

        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            string str = e.ToString();
        }

       
       
    }
}
