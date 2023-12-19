//#define TV
#define TESTVocal
using System;
using Microsoft.Win32;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Text;
using System.IO;
using System.Threading;
using System.Data.OleDb;
using System.Runtime.InteropServices;
using DirectShowLib;

namespace BlueStar
{
     //[ClassInterface(ClassInterfaceType.AutoDual)]
    [ClassInterface(ClassInterfaceType.AutoDispatch)]
    public class RMPlayer
    {
        private const long S_OK = 0;
        private const long S_FALSE = 1;
        public const int MinFreq = 185;
        public const int MaxFreq = 660;

        private const string strSQL = "SELECT FilePath1,init_speaker,INIT_VOLBC,ywtfile,Mode,Has_Local from songs where Code = '{0}'";
        private const string strSQLAD = "SELECT [Content] from AD where (EndTime is null OR EndTime >= '{0}') AND (Room = 'ALL' OR Room = '{1}')";
        private const string strSQlUpdate = "UPDATE Songs SET clickcount = clickcount + 1 WHERE code = '{0}'";
        private const string strSQLInsertSing = "INSERT INTO SingInfo(Code,Room,Score,SingTime) VALUES('{0}','{1}',{2},'{3}')";
        private const string strSQLInsertLogin = "INSERT INTO LoginInfo(Room,LoginTime) VALUES('{0}','{1}')";
        private const string strPassword = "bl2160635";
        private const string strAC3Registry = "Software\\AC3Filter\\preset\\Default";
        private const string strLocalPath = "\\\\127.0.0.1\\BL";
        private const string strTestSong = "00000001";
        private const string strSpace = "          ";  
        private const string strSourceFilter = "Source Filter";
        private const string strMPGSplitter = "MPEG Stream Splitter";
        private const string strSampleGrabber = "Sample Grabber";
        private const string strXCARDFilter = "Sigma Designs MPEG-2 hardware decoder";
        private const string strAVIDecFilter = "AVI Decompressor";
        private const string strMMSwFilter = "MMSwitcher Filter";
        private const string strTeeFilter = "Pin Tee Filter";
        private const string strSPCMFilter = "Sigma Designs PCM Swapper";

        private const string strMainMpegGuid = "B4951392-7D41-4E7A-AA60-CEAD5615E672";
        //  private const string strSigmaMpegGuid = "BD6FD780-B1DC-11D1-8BE4-00A0768008A8";
        private const string strSigmaDecGuid = "4E3ABD41-458E-11D1-917E-00001B4F006F";
        private const string strMMSwGuid = "D3CD7858-971A-4838-ACEC-40CA5D529DC8";//"2583025B-F1AD-46A1-91F3-314B8C2AAC28";//
        private const string strPCMSwapGuid = "1236F6AF-1A72-4A62-9B2B-C5F7B62C6B1C";
        //  private const string strAC3Guid = "A753A1EC-973E-4718-AF8E-A3F554D45C44";  


        private string strHuanhu = "Images\\Huanhu.wav";    //0
        private string strGuzhang = "Images\\Guzhang.wav";  //1
        private string strDaocai = "Images\\Daocai.wav";    //2

        private int intVolumn = 30;
        
        private Collection<byte[]> colWaveData;

        public int iMode = 1; //0 普通 1， line ,2 Note ,3 dash  //4   roll          
        private static object oLock = new object();
        private static int m_iFinaly = 0;//0 not, 1  show score, 2 ,stoped 
        private bool m_bCutted = false;
        private bool IsInitialized = false;
        private bool m_bOverHalf = false;
        private bool m_bUpdateOriFreq = true;
        private bool m_bInvert = false;      
        private bool m_bDoubleTrack = false;     
        private int m_Balance = 0;
        private string m_strCode;
        private double pLength = 0;
        private double m_fCutPosition;
        private const double fDelayTime = 5;
        private string strHostName;
        
        private License lic = null;
        private DirectOSD gOSD = null;
        private AVGrabber AudioGrabber = null;
        private AudioMatch gAm = null;
        private YwtFormat ywtF;
        private System.Timers.Timer timer = null;
       
#if TV
        private CRmOSD TVOsd = null;
        private IBaseFilter pXcardFilter = null;
#else
        private IBaseFilter pAVIDecFilter = null;   
        private IBaseFilter pVideoGrabFilter = null;
#endif
        private IGraphBuilder graphBuilder = null;

        private IMediaControl mediaControl = null;
        private IMediaEventEx mediaEventEx = null;
        private IBasicAudio basicAudio = null;
        private IVideoWindow videoWin = null;
        private IMediaPosition mediaPosition = null;

        private Collection<Single> colSingle;
        private Collection<string> colAD;
        private int iColADindex = 0;
        private int ColPointer = 0;
        private long iYwfStartPos;
        private FileStream fsYWT = null;
        private BinaryReader mReader = null;

        private IBaseFilter pMPEGSplitter = null;
        private IBaseFilter pAudioGrabFilter = null;
        private ISampleGrabber sampleGrabber = null;
        private IBaseFilter pSwitchFilter = null;
        private IBaseFilter pSourceFilter = null;
        //   private IBaseFilter pAC3Filter = null;      
       
        public RMPlayer()
        {
            LoginServer();
        }
        public RMPlayer(string FileName, string strYwtFile, bool Invert)
        {
            LoginServer();
            m_bInvert = Invert;
            GetCode(FileName);
            PlayVod(FileName, strYwtFile);
        }
        private void ReadWaveData(string strFileName)
        {
            FileStream fs = new FileStream(strFileName, FileMode.Open, FileAccess.Read);
            BinaryReader mReader = new BinaryReader(fs);
            mReader.BaseStream.Position = 40;
            int size = mReader.ReadInt32();
            byte[] wavedata = mReader.ReadBytes(size);
            colWaveData.Add(wavedata);
            mReader.Close();
            fs.Close();
        }
        private void LoginServer()
        {
      //      System.Diagnostics.Trace.Listeners.Clear();
        //    System.Diagnostics.Trace.AutoFlush = true;
          //  System.Diagnostics.Trace.Listeners.Add(new System.Diagnostics.TextWriterTraceListener("app.log"));
           
            strHostName = System.Net.Dns.GetHostName();
            lic = new License();
#if TV
            TVOsd = new CRmOSD(ref lic);
            TVOsd.SetOSDSize(0, 0, 640, 80);
#endif
            OleDbConnection connSQL = new OleDbConnection(License.strConnSQL + strPassword);
            connSQL.Open();
            OleDbCommand command = new OleDbCommand(string.Format(strSQLInsertLogin, strHostName, DateTime.Now.ToString()), connSQL);
            command.ExecuteNonQuery();
            connSQL.Close();
            
            RegistryKey reg = Registry.CurrentUser.OpenSubKey(strAC3Registry, true);
            reg.SetValue("mask", 5, RegistryValueKind.DWord);
            reg.Close();

            colWaveData = new Collection<byte[]>();
            ReadWaveData(License.BaseDirectory + strHuanhu);
            ReadWaveData(License.BaseDirectory + strGuzhang);
            ReadWaveData(License.BaseDirectory + strDaocai);
        }
        private void GetCode(string FileName)
        {
            int inindex = FileName.LastIndexOf('\\') + 1;
            m_strCode = FileName.Substring(inindex, FileName.Length - inindex - 4);
        }
        private void InitializeValue()
        {
            if (IsInitialized)
                Stop();
            m_bOverHalf = false;
            m_bUpdateOriFreq = true;
            m_bInvert = false;
            m_bDoubleTrack = false;
            m_Balance = 0;            
            m_iFinaly = 0;
            m_bCutted = false;
            m_fCutPosition = 0;          
        }

        public bool Initialize2(string FileName, bool AudioMatch, bool Invert)
        {
            InitializeValue();
            GetCode(FileName);
            string strYwt = string.Empty;
            if (AudioMatch || m_strCode == strTestSong)
            {
                OleDbCommand command = new OleDbCommand(string.Format(strSQL, m_strCode), License.connMdb);
                OleDbDataReader reader = command.ExecuteReader();
                if (reader.Read())
                {
                    if (m_strCode == strTestSong)
                        iMode = new Random().Next(1, 5);
                    else
                        iMode = (short)reader["Mode"];
                    strYwt = License.BaseDirectory + License.strYwtPath + reader["YwtFile"].ToString();
                    m_bInvert = (bool)reader["Init_Speaker"];               //test
                    intVolumn = (short)reader["INIT_VOLBC"];
                }
                else
                {
                    iMode = 0;
                    intVolumn = 30;
                }
                reader.Close();
            }
            else
            {
                iMode = 0;
                m_bInvert = Invert;
            }
            //  System.Diagnostics.Trace.WriteLine(DateTime.Now.ToString("HH:mm:ss.fff") + ":Initialize:" + m_strCode);
                                           
            PlayVod(FileName, strYwt);           
            return IsInitialized;
        }
        public bool Initialize(string FileName)
        {            
            InitializeValue();
            GetCode(FileName);
            string strYwt = string.Empty;
            if (iMode !=0 || m_strCode == strTestSong)
            {
                OleDbCommand command = new OleDbCommand(string.Format(strSQL, m_strCode), License.connMdb);
                OleDbDataReader reader = command.ExecuteReader();
                if (reader.Read())
                {
                    if (m_strCode == strTestSong)
                        iMode = new Random().Next(1, 5);
                    else
                        iMode = (short)reader["Mode"];
                    strYwt = License.BaseDirectory + License.strYwtPath + reader["YwtFile"].ToString();
                    m_bInvert = (bool)reader["Init_Speaker"];               //test
                    intVolumn = (short)reader["INIT_VOLBC"];
                }
                else
                {
                    iMode = 0;
                    intVolumn = 30;
                }
                reader.Close();
            }          
          //  System.Diagnostics.Trace.WriteLine(DateTime.Now.ToString("HH:mm:ss.fff") + ":Initialize:" + m_strCode);
         
            PlayVod(FileName, strYwt);
            if (m_strCode == strTestSong)
            {
                Volume = 28;
            }
            return IsInitialized;
        }
     
        private void PlayVod(string FileName, string strYwtFile)
        {
            IPin iPinOutSource = null;
            IPin iPinInVideo = null;
            IPin iPinOutVideo = null, iPinInMPG = null, iPinOutAudio = null, iPinInAudio = null;
            if (lic == null || !lic.isValid)
                lic = new License();
            if (lic.isValid)
                IsInitialized = true;
            else
                return;
#if TESTVocal
            if (m_strCode != strTestSong)
                m_bInvert = !m_bInvert;
#endif

            if (iMode != 0)      //set ywt
            {
                gAm = new AudioMatch(strYwtFile, false, ref lic); //for record
                SetYwtFile(strYwtFile);
                timer = new System.Timers.Timer(gAm.Interval);
            }
            else
                timer = new System.Timers.Timer(200);
            timer.Elapsed += new System.Timers.ElapsedEventHandler(Timer_Tick);
            timer.Enabled = false;

            graphBuilder = (IGraphBuilder)new FilterGraph();
            mediaControl = (IMediaControl)graphBuilder;
            mediaPosition = mediaControl as IMediaPosition;
            mediaEventEx = mediaControl as IMediaEventEx;

            basicAudio = mediaControl as IBasicAudio;
               //m_rot = new DsROTEntry(graphBuilder);
            graphBuilder.AddSourceFilter(FileName, strSourceFilter, out pSourceFilter);  //1. add source
            iPinOutSource = DsFindPin.ByDirection(pSourceFilter, PinDirection.Output, 0);

            pMPEGSplitter = (IBaseFilter)(Activator.CreateInstance(Type.GetTypeFromCLSID(new Guid(strMainMpegGuid))));
            graphBuilder.AddFilter(pMPEGSplitter, strMPGSplitter);  //2。add splitter
            iPinInMPG = DsFindPin.ByDirection(pMPEGSplitter, PinDirection.Input, 0);
            graphBuilder.Connect(iPinOutSource, iPinInMPG);

            IEnumPins ppEnum;
            pMPEGSplitter.EnumPins(out ppEnum);
            IPin[] ppPin = new IPin[1]; string strid;
            IntPtr IntFetch = new IntPtr();
            IPin pinTrack2 = null;
            while (ppEnum.Next(1, ppPin, IntFetch) == S_OK)
            {
                ppPin[0].QueryId(out strid);
                if (strid.Contains("192") || strid.Contains("128"))  //mp2 //ac3
                {
                    iPinOutAudio = ppPin[0];                    
                }
                else if (strid.Contains("193") || strid.Contains("129"))  //伴唱                
                    pinTrack2 = ppPin[0];
                else if (strid.Contains("Video"))
                    iPinOutVideo = ppPin[0];
                //  else if (strid.Contains("Audio"))
                //    iPinOutAudio = ppPin[0];
            }                       
            if (pinTrack2 != null)
            {
                m_bDoubleTrack = true;
                m_Balance = -1;
                pSwitchFilter = (IBaseFilter)(Activator.CreateInstance(Type.GetTypeFromCLSID(new Guid(strMMSwGuid))));
                graphBuilder.AddFilter(pSwitchFilter, strMMSwFilter);  // 3.1.1   //add audio switcher
                IPin pinInput1 = DsFindPin.ByDirection(pSwitchFilter, PinDirection.Input, 0);
                if (m_bInvert)
                    graphBuilder.Connect(iPinOutAudio, pinInput1);
                else
                    graphBuilder.Connect(pinTrack2, pinInput1);   //先连接伴奏
                IPin pinInput2 = DsFindPin.ByDirection(pSwitchFilter, PinDirection.Input, 1);
                if (m_bInvert)
                    graphBuilder.Connect(pinTrack2, pinInput2);
                else
                    graphBuilder.Connect(iPinOutAudio, pinInput2);
                iPinOutAudio = DsFindPin.ByDirection(pSwitchFilter, PinDirection.Output, 0);
            }

            if (iMode != 0 || (!m_bDoubleTrack))
            {
                sampleGrabber = new SampleGrabber() as ISampleGrabber;  //3.1.2 add grabber for audio
                pAudioGrabFilter = sampleGrabber as IBaseFilter;
                AudioGrabber = new AVGrabber(sampleGrabber, MediaType.Audio);
                graphBuilder.AddFilter(pAudioGrabFilter, strSampleGrabber);
                iPinInAudio = DsFindPin.ByDirection(pAudioGrabFilter, PinDirection.Input, 0);
                graphBuilder.Connect(iPinOutAudio, iPinInAudio);
                iPinOutAudio = DsFindPin.ByDirection(pAudioGrabFilter, PinDirection.Output, 0);
                AudioGrabber.SaveSizeInfo(sampleGrabber, null);

                AudioGrabber.bRealdata = iMode == 0;
            }
#if TV
            //  if (iMode!=0)
            {
                gOSD = new DirectOSD(ref TVOsd, ref lic);  // 
                gOSD.Mode = iMode;
            }
            /*
            pSwitchFilter = (IBaseFilter)(Activator.CreateInstance(Type.GetTypeFromCLSID(new Guid(strSigmaMpegGuid))));
            graphBuilder.AddFilter(pSwitchFilter, strMPGSplitter);     //2. add splitter
            iPinInMPG = DsFindPin.ByDirection(pSwitchFilter, PinDirection.Input, 0);
            graphBuilder.Connect(iPinOutSource, iPinInMPG);
            pSwitchFilter.FindPin("Audio", out iPinOutAudio);
            pSwitchFilter.FindPin("Video", out iPinOutVideo);  
            */
            IBaseFilter Tee = (IBaseFilter)new InfTee();  //3.2 add tee for video
            graphBuilder.AddFilter(Tee, strTeeFilter);
            iPinInVideo = DsFindPin.ByDirection(Tee, PinDirection.Input, 0);
            graphBuilder.Connect(iPinOutVideo, iPinInVideo);
            iPinOutVideo = DsFindPin.ByDirection(Tee, PinDirection.Output, 0);
            // if (iMode!=0)            
            gOSD.SaveSizeInfo(iPinInVideo);//, ywtF.SampleRate);

            IBaseFilter PCMSwapper = (IBaseFilter)(Activator.CreateInstance(Type.GetTypeFromCLSID(new Guid(strPCMSwapGuid))));
            graphBuilder.AddFilter(PCMSwapper, strSPCMFilter);   //3.3 add PCM swapper
            iPinInAudio = DsFindPin.ByDirection(PCMSwapper, PinDirection.Input, 0);
            graphBuilder.Connect(iPinOutAudio, iPinInAudio);
            iPinOutAudio = DsFindPin.ByDirection(PCMSwapper, PinDirection.Output, 0);

            pXcardFilter = (IBaseFilter)(Activator.CreateInstance(Type.GetTypeFromCLSID(new Guid(strSigmaDecGuid))));
            graphBuilder.AddFilter(pXcardFilter, strXCARDFilter);         //4. add AV decode
            pXcardFilter.FindPin("Audio In", out iPinInAudio);
            pXcardFilter.FindPin("Video In", out iPinInVideo);
            graphBuilder.Connect(iPinOutAudio, iPinInAudio);
            graphBuilder.Connect(iPinOutVideo, iPinInVideo);

            IPin iPinOutVideo2 = DsFindPin.ByDirection(Tee, PinDirection.Output, 1);
            graphBuilder.Render(iPinOutVideo2);
#else

          //  if (iMode != 0)
            {
                pAVIDecFilter = (IBaseFilter)new AVIDec();   //3.2.1  //add Video decode
                graphBuilder.AddFilter(pAVIDecFilter, strAVIDecFilter);
                iPinInVideo = DsFindPin.ByDirection(pAVIDecFilter, PinDirection.Input, 0);
                int iret = graphBuilder.Connect(iPinOutVideo, iPinInVideo);
                DsError.ThrowExceptionForHR(iret);
                iPinOutVideo = DsFindPin.ByDirection(pAVIDecFilter, PinDirection.Output, 0);
            
                sampleGrabber = new SampleGrabber() as ISampleGrabber;   //3.2.2  //add video grabber
                pVideoGrabFilter = sampleGrabber as IBaseFilter;
                gOSD = new DirectOSD(sampleGrabber,ref lic);  //    
                gOSD.Mode = iMode;                            
                graphBuilder.AddFilter(pVideoGrabFilter, strSampleGrabber);
                iPinInVideo = DsFindPin.ByDirection(pVideoGrabFilter, PinDirection.Input, 0);
                iret = graphBuilder.Connect(iPinOutVideo, iPinInVideo);
                DsError.ThrowExceptionForHR(iret);
                iPinOutVideo = DsFindPin.ByDirection(pVideoGrabFilter, PinDirection.Output, 0);
                gOSD.SaveSizeInfo(iPinInVideo);//,ywtF.SampleRate);             
            }           
#endif
            graphBuilder.Render(iPinOutVideo);   // 5. render 
            graphBuilder.Render(iPinOutAudio);

            if (!m_bDoubleTrack)
            {
                Balance = -1;
            }
           // Volume = intVolumn;
            mediaPosition.get_Duration(out pLength);
            UpdateADInfo();
        }
        private void UpdateADInfo()
        {   
            OleDbConnection conn = new OleDbConnection(License.strConnSQL + strPassword);
            conn.Open();
            OleDbCommand command = new OleDbCommand(string.Format(strSQlUpdate, m_strCode), conn);
            command.ExecuteNonQuery();
            command.CommandText = string.Format(strSQLAD, DateTime.Now.ToString(), strHostName);
            OleDbDataReader reader = command.ExecuteReader();
            colAD = new Collection<string>();
            while (reader.Read())
            {                                                
                //gOSD.strAD += '◇' + reader["Content"].ToString() + '◇';
                colAD.Add(strSpace + reader["Content"].ToString());               
            }
            iColADindex = 0;
            if(colAD.Count > 0)
                gOSD.strAD = colAD[iColADindex];
            reader.Close();
            conn.Close();          
        }
        public void PlaySound(float score)
        {
            int i;
            if (score >= 90)
                i = 0;
            else if (score >= 80)
                i = 1;
            else if (score < 60)
                i = 2;
            else return;
            AudioGrabber.PlaySound(colWaveData[i]);
        }
        private void UpdateSingInfo()
        {
            m_iFinaly = 1;
            float score = gAm.AveScore;
            PlaySound(score);
            gOSD.Update(3, 0, score); //last                
            if (m_strCode != strTestSong) //for BJL
            {
                OleDbConnection conn = new OleDbConnection(License.strConnSQL + strPassword);
                conn.Open();
                OleDbCommand command = new OleDbCommand(string.Format(strSQLInsertSing, m_strCode, strHostName, score, DateTime.Now.ToString()), conn);
                command.ExecuteNonQuery();
                conn.Close();
            }
        }
        private void Timer_Tick(object source, System.Timers.ElapsedEventArgs e)
        {
            lock (oLock)
            {
                double pllTime = CurrentPosition;
                if (iMode == 0)
                {
                    if (colAD.Count > 0)
                    {
                        if (gOSD.ADIndex < gOSD.strAD.Length)
                        {
                            gOSD.Update(-1, 0, 0); //show AD                                                                   
                        }
                        else if (gOSD.ADIndex == gOSD.strAD.Length)
                        {
                            gOSD.Update(0, 0, 0);  //false
                            gOSD.ADIndex++;
                        }
                        else if (((int)pllTime) % 60 == 0)
                        {
                            gOSD.ADIndex = 0;
                            if (++iColADindex >= colAD.Count)
                                iColADindex = 0;
                            gOSD.strAD = colAD[iColADindex];
                        }
                    }
                }
                else
                {
                    if (m_bCutted)
                    {
                        if (pllTime >= m_fCutPosition)
                            Stop();
                    }
                    else if (m_iFinaly == 0)
                    {
                        if (ColPointer >= colSingle.Count || pllTime > pLength - fDelayTime)
                        {                           
                            UpdateSingInfo();
                        }
                        else if ((pllTime >= colSingle[ColPointer]) && (pllTime < colSingle[ColPointer + 1]))
                        {
                            if (m_bUpdateOriFreq)
                            {
                                UpdateOriFreq();
                            }
                            gOSD.Update(1, gAm.CurScore, gAm.CurTone); //true             
                        }
                        else if (pllTime >= colSingle[ColPointer + 1])
                        {
                            ColPointer += 2;
                            if (ColPointer < colSingle.Count)
                            {
                                m_bUpdateOriFreq = true;
                                if (colSingle[ColPointer] - pllTime > 5)
                                {
                                    m_bOverHalf = true;
                                    PlaySound(gAm.AveScore);
                                    gOSD.Update(0, 0, 0);  //false
                                    if ((colAD.Count > 0) && (gOSD.ADIndex >= gOSD.strAD.Length - 10))
                                    {
                                        gOSD.ADIndex = 0;
                                        if (++iColADindex >= colAD.Count)
                                            iColADindex = 0;
                                        gOSD.strAD = colAD[iColADindex];
                                    }
                                }
                                else
                                    gOSD.Update(2, 0, 0);  //next 
                            }
                        }
                        else
                        {
                            if ((colAD.Count > 0) && gOSD.nShowOSD <= 0)
                            {
                                if (gOSD.ADIndex < gOSD.strAD.Length)
                                {
                                    gOSD.Update(-1, 0, 0); //show AD                                                                   
                                }
                                else if (gOSD.ADIndex == gOSD.strAD.Length)
                                {
                                    gOSD.Update(0, 0, 0);  //false
                                    gOSD.ADIndex++;
                                }
                            }
                        }
                    }
                }
            }
        }

        private void SetYwtFile(string strywtfile)
        {
            fsYWT = new FileStream(strywtfile, FileMode.Open, FileAccess.Read);
            mReader = new BinaryReader(fsYWT);

            ywtF = AudioMatch.PreReadYwtFile(mReader);
            colSingle = new Collection<float>();
            for (int i = 0; i < ywtF.SentenceCount; i++)
            {
                colSingle.Add(mReader.ReadSingle());
                colSingle.Add(mReader.ReadSingle());
            }
            ColPointer = 0;
            iYwfStartPos = mReader.BaseStream.Position;
        }
        private void UpdateOriFreq()
        {
            int intMinFreq = MaxFreq, intMaxFreq = MinFreq;
            Single fFrom = colSingle[ColPointer];
            Single fTo = colSingle[ColPointer + 1];

            long intfrompos = (long)((fFrom - ywtF.WaveStartTime) * ywtF.SampleRate / AudioMatch.iSamples);
            long inttopos = (long)((fTo - ywtF.WaveStartTime) * ywtF.SampleRate / AudioMatch.iSamples);

            long length = (inttopos - intfrompos);
            int[] Intfreq = new int[length];
            mReader.BaseStream.Position = iYwfStartPos + intfrompos * 4;
            byte[] pbyte;
            for (int i = 0; i < length; i++)
            {
                pbyte = mReader.ReadBytes(4);
                if (pbyte.Length < 4)
                    break;
                Intfreq[i] = AudioMatch.Index_to_frequency(ywtF.SampleRate, AudioMatch.iSamples, pbyte[2] > 0 ? pbyte[2] : pbyte[3]); //test;;
                if (Intfreq[i] > 0)
                {
                    intMinFreq = Math.Max(Math.Min(intMinFreq, Intfreq[i]), MinFreq);
                    intMaxFreq = Math.Min(Math.Max(intMaxFreq, Intfreq[i]), MaxFreq);
                }
                else
                {
                    if (i == 0)
                        Intfreq[i] = MinFreq;
                    else
                        Intfreq[i] = Intfreq[i - 1];
                }
            }
            gOSD.UpdateFreq(ref Intfreq, intMinFreq, intMaxFreq);
            m_bUpdateOriFreq = false;

        }
        public void Cut()
        {
            //  System.Diagnostics.Trace.WriteLine(DateTime.Now.ToString("HH:mm:ss.fff") + ":Cut");            
            lock (oLock)
            {
                if (IsInitialized && !m_bCutted)
                {
                    m_bCutted = true;
                    if (iMode == 0)
                    {
                        Stop();
                    }
                    else
                    {
                        if (m_iFinaly == 0)
                        {
                            double pllTime = CurrentPosition;
                            if (m_bOverHalf && pllTime * 3 > pLength)
                            {
                                m_fCutPosition = pllTime + fDelayTime;                            
                                UpdateSingInfo();
                            }
                            else
                                Stop();
                        }
                        else
                        {
                            m_fCutPosition = colSingle[colSingle.Count - 1] + fDelayTime;
                        }
                    }                  
                }
            }
        }

        public void SetNotifyWindow(int hwnd, int IMsg)
        {
            if (IsInitialized)
            {               
                mediaEventEx.SetNotifyWindow(new IntPtr(hwnd), IMsg, IntPtr.Zero);
            }
        }
        public void SetOwner(int hPanel, int width, int height)
        {
            if (IsInitialized)
            {
                videoWin = graphBuilder as IVideoWindow;
                // videoWin.AutoShow = Visible ? -1 : 0;  
                try
                {
                    if (hPanel == 0)
                        videoWin.put_AutoShow(OABool.False);
                    else
                    {                       
                        videoWin.put_Owner(new IntPtr(hPanel));                        
                        videoWin.put_WindowStyle(WindowStyle.Child | WindowStyle.ClipChildren | WindowStyle.ClipSiblings);
                        videoWin.put_MessageDrain(new IntPtr(hPanel));
                        //   Rectangle rc = hWin.ClientRectangle;
                        videoWin.SetWindowPosition(0, 0, width, height);
                        videoWin.put_Visible(OABool.True); 
                    }
                }
                catch (Exception)
                { }
            }
        }
        public bool Complete()
        {
            if (mediaEventEx == null)
                return true;
            if (CurrentPosition >= pLength)
            {
                Stop();
                return true;
            }
            else
                return false;
        }
        public bool IsComplete()
        {                     
            EventCode evCode;
            IntPtr evParam1, evParam2;
            // Process all queued events
            while (true)
            {

                if (mediaEventEx.GetEvent(out evCode, out evParam1, out evParam2, 0) == S_OK)
                {
                    mediaEventEx.FreeEventParams(evCode, evParam1, evParam2);
                    if (evCode == EventCode.Complete || evCode == EventCode.UserAbort)
                    {
                        return true;
                    }
                }
                return false;
            }
        }
        public double CurrentPosition
        {
            get
            {
                double pllTime = 0;
                if (mediaPosition != null)
                    mediaPosition.get_CurrentPosition(out pllTime);
                return pllTime;
            }
            set
            {
                OABool pCanseek;
                mediaPosition.CanSeekForward(out pCanseek);
                if (pCanseek == OABool.True)
                    mediaPosition.put_CurrentPosition(value);
            }
        }
        public int Volume
        {
            set
            {
           //     System.Diagnostics.Trace.WriteLine(DateTime.Now.ToString("HH:mm:ss.fff") + ":Volumn:" + value);
                if (IsInitialized)
                {
                    intVolumn = value;
                    if (value == 0)
                    {                       
                        value = -10000;
                    }
                    else
                    {                        
                        value = (int)((Math.Log10(intVolumn) - 2) * 1000);
                    }
                    basicAudio.put_Volume(value);
                }
            }
        }
        public int Balance
        {
            /*Invert = false  含义 VCD L balance = -1  伴唱    0  原唱     
             *                     DVD 音轨0  伴唱              1  原唱                          */
            set
            {
                if (!IsInitialized) return;
                if (iMode != 0 && m_Balance != 0) return;//for test  
                m_Balance = value;
                if (m_bDoubleTrack)
                {
                    //  IAMStreamSelect iam = pMPEGSplitter as IAMStreamSelect; //test
                    IAMStreamSelect iam = pSwitchFilter as IAMStreamSelect;
                    int nTrack;
                    iam.Count(out nTrack);
                    //   AMMediaType ppmt; AMStreamSelectInfoFlags pdw; int plcid, pdwgr; string str; object ppobj, ppunk;
                    //   iam.Info(2, out ppmt, out pdw, out plcid, out pdwgr, out str, out ppobj, out ppunk);
                    if (nTrack >= 2)  //2  
                    {
                        iam.Enable((value == -1 ? 0 : 1), AMStreamSelectEnableFlags.Enable);//0  伴奏 (0:1)
                    }
                }              
                else
                {                 
                    AudioGrabber.Balance = (m_Balance == -1 ? (m_bInvert ? 1 : -1) : 0);  //   basicAudio.put_Balance(value * 10000);
                }
            }
        }
        public double Duration
        {
            get { return pLength; }
        }
        public void Start()
        {
         //   System.Diagnostics.Trace.WriteLine(DateTime.Now.ToString("HH:mm:ss.fff") + ":Start");
            if (IsInitialized)
            {
                mediaControl.Run();
                timer.Start();
                if (iMode != 0)
                {
                    gAm.Start();
                }               
            }            
        }
        public void Pause()
        {
            if (IsInitialized)
            {
                mediaControl.Pause();
                timer.Stop();
                if (iMode != 0)
                {
                    gAm.Pause();
                }

            }
        }
        public void Stop()
        {                       
            if (Interlocked.Exchange(ref m_iFinaly, 2) == 2) return;
            if (!IsInitialized) return;
            IsInitialized = false;        
            if (timer != null)
            {
                timer.Stop();
                timer.Dispose();
                timer = null;
            }
            if (mediaControl != null)
            {
                mediaControl.Stop();
                pSourceFilter = null;
                videoWin = null;
                basicAudio = null;
                mediaControl = null;
                mediaPosition = null;
            }
            if (gOSD != null)
            {
                gOSD.Dispose();
                gOSD = null;
            }
            if (iMode != 0)
            {
                if (gAm != null)
                {
                    gAm.Stop();
                    gAm = null;
                }
                if (fsYWT != null)
                {
                    fsYWT.Close();
                    fsYWT = null;
                }
            }
            if (AudioGrabber != null)
            {
                AudioGrabber.Dispose();
                AudioGrabber = null;
            }
            if (pAudioGrabFilter != null)
            {
                Marshal.ReleaseComObject(pAudioGrabFilter);
                pAudioGrabFilter = null;
            }
#if TV
            if (pXcardFilter != null)
            {                
                Marshal.ReleaseComObject(pXcardFilter);
                pXcardFilter = null;
            }
          //  if (TVOsd != null)
            //    TVOsd.CloseOSD();
#else
                if (pAVIDecFilter != null)
                {
                    Marshal.ReleaseComObject(pAVIDecFilter);
                    pAVIDecFilter = null;
                }
                if (pVideoGrabFilter != null)
                {
                    Marshal.ReleaseComObject(pVideoGrabFilter);
                    pVideoGrabFilter = null;
                }
#endif
            if (mediaEventEx != null)
            {
                mediaEventEx.SetNotifyWindow(IntPtr.Zero, 0, IntPtr.Zero);
                mediaEventEx = null;
            }

            if (graphBuilder != null)
            {
                Marshal.ReleaseComObject(graphBuilder);
                graphBuilder = null;
            }
            GC.Collect();            
        }
        public void Dispose()
        {
          //  System.Diagnostics.Trace.WriteLine(DateTime.Now.ToString("HH:mm:ss.fff") + ":Dispose");
            if (License.connMdb != null)
                License.connMdb.Close();            
#if TV
            if (TVOsd != null)
                TVOsd.Dispose();
#endif
        }
    }
}
