using System;
using System.Threading;
using System.IO;
using System.Collections.Generic;
using System.Text;
using System.Data.OleDb;
using Microsoft.DirectX.DirectSound;
using System.Net.Sockets;
using System.Security.Cryptography;

namespace BlueStar
{
    public class License
    {
        private static string strBaseDirectory = System.Reflection.Assembly.GetExecutingAssembly().Location;
        public static string BaseDirectory = strBaseDirectory.Substring(0, strBaseDirectory.LastIndexOf('\\') + 1);
     //   private const string strConnFormat = "Provider=Microsoft.JET.OLEDB.4.0;Jet OLEDB:Database Password={0};Data Source=|DataDirectory|\\BlueStar.ydb";
        public static string strConn = "Provider=Microsoft.JET.OLEDB.4.0;Data Source=" + BaseDirectory + "BlueStar.ydb;Jet OLEDB:Database Password=";
        public static string strConnSQL = "Provider=SQLOLEDB;Data Source={0},1433;Initial Catalog=BlueStar;User ID=BlueStar;Password=";
        public static string strConnAD;
        public const string strWaveExt = ".wav";
        public const string strMpgExt = ".mpg";
        public const string strYwtExt = ".ywt";
        public const string strYwtPath = "Ywt\\";
        public const string strWavPath = "Wav\\";

        private const string strSQL = "SELECT * FROM ServerInfo WHERE Used = Yes"; 
        private const string strDateFormat = "yyyyMMdd";
        private const string strLocalHost = "127.0.0.1";
        private const string strPassword = "bl2160635";
        private bool bIsValid = false;
        public static OleDbConnection connMdb = null;
        public static bool CheckLic()
        {
            string strServerCode;
            string strIP;
            int port;
            connMdb = new OleDbConnection(strConn + strPassword);
            connMdb.Open();
            OleDbCommand command = new OleDbCommand(strSQL, connMdb);
            OleDbDataReader reader = command.ExecuteReader();
            if (reader.Read())
            {
                strServerCode = reader["ServerCode"].ToString();
                strIP = reader["ServerIP"].ToString();
                port = (int)reader["ServerPort"];
                strConnAD = reader["ADServerString"].ToString();
                                                 
                if (reader["EndLine"] != DBNull.Value && (DateTime)reader["EndLine"] < DateTime.Now)
                {
                    connMdb.Close();
                    return false;
                }
                if (strIP == strLocalHost)
                    strConnSQL = strConn;
                else
                    strConnSQL = string.Format(strConnSQL, strIP);
                reader.Close();               
            }
            else
            {
                connMdb.Close();
                return false;
            }

            string strDate = DateTime.Now.ToString(strDateFormat);

            StringBuilder strMessage = new StringBuilder(strServerCode);
            strMessage.Append(strDate);
            MD5 md5 = MD5.Create();
            byte[] bytePass = md5.ComputeHash(Encoding.ASCII.GetBytes(strMessage.ToString()));
            byte[] data = Encoding.ASCII.GetBytes(strDate);
            try
            {
                TcpClient client = new TcpClient(strIP, port);
                // Translate the passed message into ASCII and store it as a Byte array.                
                NetworkStream stream = client.GetStream();
                // Send the message to the connected TcpServer. 
                stream.Write(data, 0, data.Length);
                data = new Byte[bytePass.Length];
                // Read the first batch of the TcpServer response bytes.
                Int32 bytes = stream.Read(data, 0, data.Length);

                // Close everything.
                stream.Close();
                client.Close();
            }
            catch (SocketException)
            {
                return false;
            }
            for (int i = 0; i < bytePass.Length; i++)
            {
                if (bytePass[i] != data[i])
                    return false;
            }
            return true;
        }
        public License()
        {
            bIsValid = CheckLic();
        }
        public bool isValid
        {
            get { return bIsValid; }
        }
    }
    public struct YwtFormat
    {
       // public YwtFormat();        
        public short Version;
        public short BytesPerSample;
        public int SampleRate;
        public int SentenceCount;
        public int DataSize;        
        public Single ShowTime;
        public Single WaveStartTime;
        public int FirstFreq;
    }
    public class AudioMatch
    {               
        public static short Grade = 85;
        private bool IsInitialized = false;
        public const short iSamples = 2048;
        public const short SkipCount = 10;
        private const float MinScore = 50;

        private byte mCurTone = 0;        
        private short iBeatCount = 0;
        private int mTotalScore = 0;
        private Single mCurScore = 0;
        private bool bSaveWaveFile=false;
        private bool bRealdata = false;
        private bool bFindData = false;

        private static char[] ChunkRiff = { 'R', 'I', 'F', 'F' };
        private static char[] ChunkType = { 'W', 'A', 'V', 'E' };
        private static char[] ChunkFmt = { 'f', 'm', 't', ' ' };
        private static char[] ChunkData = { 'd', 'a', 't', 'a' };
        private static char[] ChunkYwt = { 'Y', 'W', 'T', 'F' };       
                   
        private FileStream fsYWT = null;//保存的文件流
        private BinaryReader mReader;
       
        
        private const string strDateFormat = "_yyMMdd_HHmmss";         
        private FileStream fsWav = null;//保存的文件流
        private BinaryWriter mWriter;
        private WaveFormat mWavFormat;//PCM格式
        private YwtFormat mYwtFormat;
        private int iSampleSize = 0;//所采集到的wav数据大小        

        private int iNotifyNum = 8;//通知的个数
        private int iNotifySize = 0;//设置通知大小

       // private int iSampleRate = 11025;
        // private int iDataSize = 0;//YWT的数据大小        
      //  private short iBytesPerSample = 2;
       // private double startTime = 0;
      //  private const uint NumBits = 11;
        
        private const byte byteMax = byte.MaxValue;                
        private Notify myNotify = null;//缓冲区提示事件
        private int iBufferOffset = 0;//本次数据起始点， 上一次数据的终点。               
        private int iBufferSize = 0;//缓冲区大小
               
        private Capture capture = null;//捕捉设备对象
        private CaptureBuffer capturebuffer = null;//捕捉缓冲区
        private AutoResetEvent notifyevent = null;
        private Thread notifythread = null;

        public byte CurTone
        {
            get { return mCurTone; }
        }
        public Single CurScore
        {
            get { return mCurScore; }
        }
        public Single AveScore
        {
            get { return iBeatCount == 0 ? MinScore : MinScore + mTotalScore * MinScore / iBeatCount; } //min 50
        }
    
        public int Interval
        {
            get { return iSamples * 1000 / mYwtFormat.SampleRate; }
        }
        private static WaveFormat SetWaveFormat(short nChannels,short iBytesPerSample,int iSampleRate)
        {
            WaveFormat format = new WaveFormat() ;
            format.FormatTag = WaveFormatTag.Pcm;//设置音频类型
            format.SamplesPerSecond = iSampleRate;//采样率（单位：赫兹）典型值：11025、22050、44100Hz
            format.BitsPerSample = (short)(iBytesPerSample * 8);//采样位数
            format.Channels = nChannels;//声道
            format.BlockAlign = (short)(format.Channels * iBytesPerSample);//单位采样点的字节数
            format.AverageBytesPerSecond = format.BlockAlign * format.SamplesPerSecond;
            return format;            
        }
        public static void CreateYwtFile(BinaryWriter ywtWriter, YwtFormat YwtF)
        {
            ywtWriter.Write(ChunkYwt);    //YWFF
            ywtWriter.Write(YwtF.SampleRate);
            ywtWriter.Write(YwtF.BytesPerSample);  
            ywtWriter.Write(YwtF.Version);  //version 1,2
            ywtWriter.Write(YwtF.SentenceCount); // // 句子数 
            ywtWriter.Write(YwtF.DataSize); // 匹配点数
            if (YwtF.Version == 1)
            {
                ywtWriter.Write(YwtF.ShowTime);  //
                ywtWriter.Write(YwtF.WaveStartTime);
                ywtWriter.Write(YwtF.FirstFreq);
            }
           // ywtWriter.Write((int)0);    // 句子首+尾  //匹配数据对
                                            
        }
        public static YwtFormat PreReadYwtFile(BinaryReader mReader)
        {
           // fsYWT = new FileStream(strFileName, FileMode.Open,FileAccess.Read);
          //  mReader = new BinaryReader(fsYWT);

            YwtFormat YwtF = new YwtFormat();
            mReader.BaseStream.Position = 4;

            YwtF.SampleRate = mReader.ReadInt32();
            YwtF.BytesPerSample = mReader.ReadInt16();
            YwtF.Version = mReader.ReadInt16();
            YwtF.SentenceCount  = mReader.ReadInt32();
            YwtF.DataSize = mReader.ReadInt32();
            if (YwtF.Version == 1)
            {
                YwtF.ShowTime = mReader.ReadSingle();
                YwtF.WaveStartTime = mReader.ReadSingle();
                YwtF.FirstFreq = mReader.ReadInt32();
            }
            else
            {               
                YwtF.WaveStartTime = 0;
                YwtF.FirstFreq = (YwtF.SampleRate % 8000) == 0 ? 205 : 137; //205  204.8 

            }
            return YwtF;
            //startTime = mReader.ReadDouble();
        }
        /**************************************************************************
              Here is where the file will be created. A
              wave file is a RIFF file, which has chunks
              of data that describe what the file contains.
              A wave RIFF file is put together like this:
              The 12 byte RIFF chunk is constructed like this:
              Bytes 0 - 3 :  'R' 'I' 'F' 'F'
              Bytes 4 - 7 :  Length of file, minus the first 8 bytes of the RIFF description.
                                (4 bytes for "WAVE" + 24 bytes for format chunk length +
                                8 bytes for data chunk description + actual sample data size.)
               Bytes 8 - 11: 'W' 'A' 'V' 'E'
               The 24 byte FORMAT chunk is constructed like this:
               Bytes 0 - 3 : 'f' 'm' 't' ' '
               Bytes 4 - 7 : The format chunk length. This is always 16.
               Bytes 8 - 9 : File padding. Always 1.
               Bytes 10- 11: Number of channels. Either 1 for mono,  or 2 for stereo.
               Bytes 12- 15: Sample rate.
               Bytes 16- 19: Number of bytes per second.
               Bytes 20- 21: Bytes per sample. 1 for 8 bit mono, 2 for 8 bit stereo or
                               16 bit mono, 4 for 16 bit stereo.
               Bytes 22- 23: Number of bits per sample.
               The DATA chunk is constructed like this:
               Bytes 0 - 3 : 'd' 'a' 't' 'a'
               Bytes 4 - 7 : Length of data, in bytes.
               Bytes 8 -: Actual sample data.
             ***************************************************************************/
        public static void GetAmp_Freq(ref double[] pRealIn, out int pFreqIndex, out double pAmpPair)
        {
            int iSamples = pRealIn.Length;
            double[] pRealOut, pImagOut, pImagIn = null;
            YWTransform((uint)iSamples, false, ref pRealIn, ref pImagIn, out pRealOut, out pImagOut);

            double Amplitude = 0;
            pAmpPair = 0;
            pFreqIndex = 1;
            for (int i = 1; i < iSamples / 2; i++)
            {
                Amplitude = Math.Sqrt(pRealOut[i] * pRealOut[i] + pImagOut[i] * pImagOut[i]) * 2 / iSamples;
                if (Amplitude > pAmpPair)
                {
                    pAmpPair = Amplitude;
                    pFreqIndex = i;                    
                }
            }                                                                
        }
        public static void GetAmp_Freq(ref double[] pRealIn, ref byte[] pFreqPair, ref double[] pAmpPair)
        {          
            double[] pRealOut, pImagOut, pImagIn = null;          
            YWTransform((uint)iSamples, false, ref pRealIn, ref pImagIn, out pRealOut, out pImagOut);

            double FirstAmp = 0, SecondAmp = 0,Amplitude = 0;            
            pRealIn[0] = 0;           
            int FirstIndex = 1, SecondIndex = 0;
            for (int i = 1; i < iSamples / 2; i++)
            {                
                Amplitude = Math.Sqrt(pRealOut[i] * pRealOut[i] + pImagOut[i] * pImagOut[i]) * 2 / iSamples;               
                    pRealIn[i] = Amplitude;
                if (Amplitude > pRealIn[i-1])
                {
                    if (Amplitude > SecondAmp)
                    {
                        if (Amplitude > FirstAmp)
                        {
                            if ((i - FirstIndex) > 1) //not near
                            {
                                SecondAmp = FirstAmp;
                                SecondIndex = FirstIndex;
                            }
                            FirstAmp = Amplitude;
                            FirstIndex = i;
                        //    if (FirstIndex >= byteMax)
                          //      break;
                        }
                        else
                        {                            
                             SecondAmp = Amplitude;
                             SecondIndex = i;                            
                        }
                    }
                }
            }
            //???                                              
            pFreqPair[0] = (byte)(FirstIndex > byteMax ? byteMax : FirstIndex);//nFirstFreqIndex = (byte)FirstIndex;
            pAmpPair[0] = FirstAmp;//(byte)(FirstAmp > byteMax ? byteMax : FirstAmp);//nFirstAmp = (byte)(FirstAmp > byteMax ? byteMax : FirstAmp);
            pFreqPair[1] = (byte)(SecondIndex > byteMax ? byteMax : SecondIndex);// nSecondFreqIndex = (byte)SecondIndex;
            pAmpPair[1] = SecondAmp;//(byte)(SecondAmp > byteMax ? byteMax : SecondAmp); // nSecondAmp = (byte)(SecondAmp > byteMax ? byteMax : SecondAmp);                                                    
        }
        public static void GetMainFreq(ref byte[] pBytes, ref byte[] pBytes2, ref byte[] pFreqPair, short iBytes, bool MoreData)
        {
            double[] pRealIn = new double[iSamples];
            byte[] LeftPair = new byte[2], RightPair = new byte[2];
            double[] LeftAmp = new double[2], RightAmp = new double[2];

            //Vocal channel
            if (iBytes == 1)
            {
                for (int i = 0; i < iSamples; i++)
                    pRealIn[i] = pBytes2[i];
            }
            else
            {
                for (int i = 0; i < iSamples; i++)
                    pRealIn[i] = (short)(pBytes2[i << 1] | (pBytes2[(i << 1) + 1] << 8));
            }
            GetAmp_Freq(ref pRealIn, ref RightPair, ref RightAmp);                
            //GetMainFreq(ref pBytes2, ref RightPair,ref RightAmp,iBytes);
            //music channel
            if (iBytes == 1)
            {
                for (int i = 0; i < iSamples; i++)
                    pRealIn[i] = pBytes[i];
            }
            else
            {
                for (int i = 0; i < iSamples; i++)
                    pRealIn[i] = (short)(pBytes[i << 1] | (pBytes[(i << 1) + 1] << 8));
            }
            GetAmp_Freq(ref pRealIn, ref LeftPair, ref LeftAmp);      

            pFreqPair[0] = LeftPair[0];
            pFreqPair[1] = LeftPair[1];

            if (RightPair[0] == byteMax || RightPair[0] < 20)
                RightPair[0] = 0;
            if (RightPair[1] == byteMax || RightPair[1] < 20)
                RightPair[1] = 0;
            double Multiple = MoreData ? 2 : 3;
            if (RightPair[0] == 0  || RightAmp[0] <= LeftAmp[1] || Math.Abs(LeftPair[0] - RightPair[0]) <= 1 || Math.Abs(LeftPair[1] - RightPair[0]) <= 1 ||
                    pRealIn[RightPair[0]] * Multiple >= RightAmp[0] || pRealIn[RightPair[0] - 1] * Multiple >= RightAmp[0] || pRealIn[RightPair[0] + 1] * Multiple >= RightAmp[0])  //右声道基波匹配伴奏                
            {
                if (!MoreData || RightPair[1] == 0 || RightAmp[1] <= LeftAmp[1] || Math.Abs(LeftPair[0] - RightPair[1]) <= 1 || Math.Abs(LeftPair[1] - RightPair[1]) <= 1 ||
                   pRealIn[RightPair[1]] * 3 > RightAmp[1] || pRealIn[RightPair[1] - 1] * 3 > RightAmp[1] || pRealIn[RightPair[1] + 1] * 3 > RightAmp[1])//右声道谐波匹配伴奏               
                {
                    pFreqPair[2] = 0;
                    pFreqPair[3] = RightPair[0];
                }
                else
                {
                    pFreqPair[2] = RightPair[1];
                    pFreqPair[3] = 0;
                }                
            }
            else
            {
                pFreqPair[2] = RightPair[0];
                if (RightPair[1] == 0 || Math.Abs(LeftPair[0] - RightPair[1]) <= 1 || Math.Abs(LeftPair[1] - RightPair[1]) <= 1 ||
                    pRealIn[RightPair[1]] * 3 > RightAmp[1] || pRealIn[RightPair[1] - 1] * 3 > RightAmp[1] || pRealIn[RightPair[1] + 1] * 3 > RightAmp[1])//右声道谐波匹配伴奏               
                {
                    pFreqPair[3] = 0;
                }
                else
                {
                    pFreqPair[3] = RightPair[1];
                }
            }

        }
        public static void GetMainFreq(ref byte[] pBytes, ref byte[] pFreqPair, short iBytes, bool MoreData)
        {
            double[] pRealIn = new double[iSamples];

            byte[] LeftPair = new byte[2], RightPair = new byte[2];
            double[] LeftAmp = new double[2], RightAmp = new double[2];

            //  int j = LeftVocal ? iBytes : 0;                      
            //Vocal channel
            if (iBytes == 1)
            {
                for (int i = 0; i < iSamples; i++)
                    pRealIn[i] = pBytes[(i << 1) + 1];// pRealIn[i] = pBytes[(i<<1) + 1 - j];                   
            }
            else
            {
                for (int i = 0; i < iSamples; i++)
                    pRealIn[i] = (short)(pBytes[(i << 2) + 2] | (pBytes[(i << 2) + 3] << 8));
                //  pRealIn[i] = (short)(pBytes[(i << 2) + 2 - j] | (pBytes[(i << 2) + 3 - j] << 8));
            }

            GetAmp_Freq(ref pRealIn, ref RightPair, ref RightAmp);

            //music channel
            if (iBytes == 1)
            {
                for (int i = 0; i < iSamples; i++)
                    pRealIn[i] = pBytes[i << 1];
            }
            else
            {
                for (int i = 0; i < iSamples; i++)
                    pRealIn[i] = (short)(pBytes[i << 2] | (pBytes[(i << 2) + 1] << 8));
            }

            GetAmp_Freq(ref pRealIn, ref LeftPair, ref LeftAmp);

            pFreqPair[0] = LeftPair[0];
            pFreqPair[1] = LeftPair[1];

            if (RightPair[0] == byteMax || RightPair[0] < 20)
                RightPair[0] = 0;
            if (RightPair[1] == byteMax || RightPair[1] < 20)
                RightPair[1] = 0;

            double Multiple = MoreData ? 2 : 3;
            if (RightPair[0] == 0 || RightAmp[0] <= LeftAmp[1] || Math.Abs(LeftPair[0] - RightPair[0]) <= 1 || Math.Abs(LeftPair[1] - RightPair[0]) <= 1 ||
                    pRealIn[RightPair[0]] * Multiple >= RightAmp[0] || pRealIn[RightPair[0] - 1] * Multiple >= RightAmp[0] || pRealIn[RightPair[0] + 1] * Multiple >= RightAmp[0])  //右声道基波匹配伴奏                
            {
                if (!MoreData || RightPair[1] == 0 || RightAmp[1] <= LeftAmp[1] || Math.Abs(LeftPair[0] - RightPair[1]) <= 1 || Math.Abs(LeftPair[1] - RightPair[1]) <= 1 ||
                   pRealIn[RightPair[1]] * 3 > RightAmp[1] || pRealIn[RightPair[1] - 1] * 3 > RightAmp[1] || pRealIn[RightPair[1] + 1] * 3 > RightAmp[1])//右声道谐波匹配伴奏               
                {
                    pFreqPair[2] = 0;
                    pFreqPair[3] = RightPair[0];
                }
                else
                {
                    pFreqPair[2] = RightPair[1];
                    pFreqPair[3] = 0;
                }
            }
            else
            {
                pFreqPair[2] = RightPair[0];
                if (RightPair[1] == 0 || Math.Abs(LeftPair[0] - RightPair[1]) <= 1 || Math.Abs(LeftPair[1] - RightPair[1]) <= 1 ||
                    pRealIn[RightPair[1]] * 3 > RightAmp[1] || pRealIn[RightPair[1] - 1] * 3 > RightAmp[1] || pRealIn[RightPair[1] + 1] * 3 > RightAmp[1])//右声道谐波匹配伴奏               
                {
                    pFreqPair[3] = 0;
                }
                else
                {
                    pFreqPair[3] = RightPair[1];
                }
            }
        }
        public static void GetMainFreq(ref byte[] pBytes, ref byte[] pFreqPair,ref double[] pAmpPair, short iBytes)
        {      
            double[] pRealIn = new double[iSamples];   
             if (iBytes == 1)
             {
                 for (int i = 0; i < iSamples; i++)
                     pRealIn[i] = pBytes[i];
             }
             else
             {
                 for (int i = 0; i < iSamples; i++)
                     pRealIn[i] = (short)(pBytes[i << 1] | (pBytes[(i << 1) + 1] << 8));
             }                                  
            GetAmp_Freq(ref pRealIn, ref pFreqPair,ref pAmpPair);           
        }
        public static int GetFirstFreq(ref byte[] pBytes, ref YwtFormat ywtF, short iChannels)
        {
            double[] pRealIn = new double[iSamples];
            if (iChannels == 1)
            {
                if (ywtF.BytesPerSample == 1)
                {
                    for (int i = 0; i < iSamples; i++)
                        pRealIn[i] = pBytes[i];
                }
                else
                {
                    for (int i = 0; i < iSamples; i++)
                        pRealIn[i] = (short)(pBytes[i << 1] | (pBytes[(i << 1) + 1] << 8));
                }
            }
            else
            {
                //music channel
                if (ywtF.BytesPerSample == 1)
                {
                    for (int i = 0; i < iSamples; i++)
                        pRealIn[i] = pBytes[i << 1];
                }
                else
                {
                    for (int i = 0; i < iSamples; i++)
                        pRealIn[i] = (short)(pBytes[i << 2] | (pBytes[(i << 2) + 1] << 8));
                }
            }

            int LeftFreq;
            double LeftAmp;
            GetAmp_Freq(ref pRealIn, out LeftFreq, out LeftAmp);
            int index = -1;            
            if (LeftAmp >= (ywtF.BytesPerSample == 1 ? 2 : 600) && (LeftFreq >= 100))
            {
                int FirstFreq = LeftFreq;  //Index_to_frequency(ywtF.SampleRate, iSamples, LeftPair[0]);
                if (ywtF.FirstFreq != 0)  //核对
                {
                    if (Math.Abs(ywtF.FirstFreq - FirstFreq) > 2)
                        return index;
                    else if (ywtF.Version == 3)
                        return 0;
                }
                else  //查找                               
                {
                    ywtF.FirstFreq = LeftFreq; 
                }
                index = 0;
                int length = iSamples >>1;
                while (length >= 64)
                {
                    double[] pbyte = new double[length];
                    for(int i=0;i<length;i++)
                        pbyte[i] = pRealIn[index + i];
                    GetAmp_Freq(ref pbyte, out LeftFreq, out LeftAmp);
                    FirstFreq >>= 1;
                    if (Math.Abs(LeftFreq - FirstFreq) > 1)
                    {
                        index += length;
                    }
                    length >>= 1;
                }
            }            
            return index;
        }               
        private static uint ReverseBits(uint nIndex, uint nBits)
        {
            uint i, rev;
            for (i = rev = 0; i < nBits; i++)
            {
                rev = (rev << 1) | (nIndex & 1);
                nIndex >>= 1;
            }
            return rev;
        }

        //////////////////////////////////////////////////////////////////////////////////////
        // return a frequency from the basefreq and num of samples
        //////////////////////////////////////////////////////////////////////////////////////

        public static int Index_to_frequency(int nSampleFreq, int nSamples, int nIndex)
        {
            if (nIndex >= nSamples)
            {
                return 0;
            }
            else if (nIndex <= nSamples / 2)
            {
                return (nIndex * nSampleFreq / nSamples);
            }
            else
            {
                return ((nSamples - nIndex) * nSampleFreq / nSamples);
            }
        }
        private static void YWTransform(uint nSamples, bool bInverse, ref double[] p_lpRealIn, ref double[] p_lpImagIn, out double[] p_lpRealOut, out double[] p_lpImagOut)
        {           
            p_lpRealOut = new double[nSamples];
            p_lpImagOut = new double[nSamples];
            uint i, j, k, n;
            uint BlockSize, BlockEnd;
            double angle_numerator = 2 * Math.PI;
            double tr, ti;
            //	if( !IsPowerOfTwo(nSamples) ) return
             if (bInverse) angle_numerator = -angle_numerator;
            uint nNumBits = NumberOfBitsNeeded ( nSamples );
             for (i = 0; i < nSamples; i++)
            {
                j = ReverseBits(i, nNumBits);
                p_lpRealOut[j] = p_lpRealIn[i];
                p_lpImagOut[j] = (p_lpImagIn == null) ? 0.0 : p_lpImagIn[i];                
            }
            double[] ar = new double[3], ai = new double[3];
            BlockEnd = 1;
            for (BlockSize = 2; BlockSize <= nSamples; BlockSize <<= 1)
            {
                double delta_angle = angle_numerator / (double)BlockSize;
                double sm2 = Math.Sin(-2 * delta_angle);
                double sm1 = Math.Sin(-delta_angle);
                double cm2 = Math.Cos(-2 * delta_angle);
                double cm1 = Math.Cos(-delta_angle);
                double w = 2 * cm1;                
                for (i = 0; i < nSamples; i += BlockSize)
                {
                    ar[2] = cm2;
                    ar[1] = cm1;
                    ai[2] = sm2;
                    ai[1] = sm1;
                    for (j = i, n = 0; n < BlockEnd; j++, n++)
                    {
                        ar[0] = w * ar[1] - ar[2];
                        ar[2] = ar[1];
                        ar[1] = ar[0];
                        ai[0] = w * ai[1] - ai[2];
                        ai[2] = ai[1];
                        ai[1] = ai[0];
                        k = j + BlockEnd;
                        tr = ar[0] * p_lpRealOut[k] - ai[0] * p_lpImagOut[k];
                        ti = ar[0] * p_lpImagOut[k] + ai[0] * p_lpRealOut[k];

                        p_lpRealOut[k] = p_lpRealOut[j] - tr;
                        p_lpImagOut[k] = p_lpImagOut[j] - ti;
                        p_lpRealOut[j] += tr;
                        p_lpImagOut[j] += ti;
                    }
                }
                BlockEnd = BlockSize;
            }
            if (bInverse)
            {
                double denom = (double)nSamples;
                for (i = 0; i < nSamples; i++)
                {
                    p_lpRealOut[i] /= denom;
                    p_lpImagOut[i] /= denom;
                }
            }                
        }       
//////////////////////////////////////////////////////////////////////////////////////
// check is a number is a power of 2
//////////////////////////////////////////////////////////////////////////////////////
/*bool IsPowerOfTwo( unsigned int p_nX )
{

	if( p_nX < 2 ) return false;

	if( p_nX & (p_nX-1) ) return false;

    return true;

}
        */
//////////////////////////////////////////////////////////////////////////////////////
// return needed bits for fft
//////////////////////////////////////////////////////////////////////////////////////
        private static uint NumberOfBitsNeeded(uint p_nSamples)
        {            
            if (p_nSamples < 2)
            {
                return 0;
            }          
            for (int i = 0; ; i++)
            {                
                if((p_nSamples & (1<<i)) != 0)
                return (uint)i;
            }
        }        
        private static void CreateWaveFile(BinaryWriter mWriter, WaveFormat mWavFormat)
        {                                  
            short shPad = 1;                // File padding
            int nFormatChunkLength = 0x10;  // Format chunk length.
            int nLength = 0;                // File length, minus first 8 bytes of RIFF description. This will be filled in later.         
            // 一个样本点的字节数目
                       
            // RIFF 块
            mWriter.Write(ChunkRiff);
            mWriter.Write(nLength);
            mWriter.Write(ChunkType);
            // WAVE块
            mWriter.Write(ChunkFmt);
            mWriter.Write(nFormatChunkLength);
            mWriter.Write(shPad);
            mWriter.Write(mWavFormat.Channels);
            mWriter.Write(mWavFormat.SamplesPerSecond);
            mWriter.Write(mWavFormat.AverageBytesPerSecond);
            mWriter.Write(mWavFormat.BlockAlign);
            mWriter.Write(mWavFormat.BitsPerSample);
            // 数据块
            mWriter.Write(ChunkData);
            mWriter.Write((int)0);   // The sample length will be written in later.
        }
        public static void CreateWaveFile(BinaryWriter mWriter,short nChannel, short nBytes, int nSamplePerSecond)
        {
            CreateWaveFile(mWriter, SetWaveFormat(nChannel, nBytes, nSamplePerSecond));
        }
        private bool CreateCaputerDevice()
        {
            //首先要玫举可用的捕捉设备
            CaptureDevicesCollection capturedev = new CaptureDevicesCollection();
            Guid devguid;
            if (capturedev.Count > 0)
            {
                devguid = capturedev[0].DriverGuid;
            }
            else
            {
                return false;
            }
            //利用设备GUID来建立一个捕捉设备对象
            capture = new Capture(devguid);
            return true;
        }
        private void CreateCaptureBuffer()

        {//想要创建一个捕捉缓冲区必须要两个参数：缓冲区信息（描述这个缓冲区中的格式等），缓冲设备。

                CaptureBufferDescription bufferdescription = new CaptureBufferDescription();
                bufferdescription.Format = mWavFormat;//设置缓冲区要捕捉的数据格式           
                iNotifySize = iSamples * mYwtFormat.BytesPerSample;
                iBufferSize = iNotifyNum * iNotifySize;
                bufferdescription.BufferBytes = iBufferSize;
                capturebuffer = new CaptureBuffer(bufferdescription, capture);//建立设备缓冲区对象              
        }
        private void CreateNotification()
        {
            BufferPositionNotify[] bpn = new BufferPositionNotify[iNotifyNum];//设置缓冲区通知个数
            //设置通知事件
            notifyevent = new AutoResetEvent(false);
            notifythread = new Thread(RecoData);
            notifythread.Start();
            for (int i = 0; i < iNotifyNum; i++)
            {
                bpn[i].Offset = iNotifySize + i * iNotifySize - 1;//设置具体每个的位置
                bpn[i].EventNotifyHandle = notifyevent.SafeWaitHandle.DangerousGetHandle();
            }
            myNotify = new Notify(capturebuffer);
            myNotify.SetNotificationPositions(bpn);

        }
        private void RecoData()
        {
            while (true)
            {
                // 等待缓冲区的通知消息
                notifyevent.WaitOne(Timeout.Infinite, true);
                // 录制数据
                RecordCapturedData();
            }
        }
      /*  public static short GetHz(byte[] mbytes)
        {
            short iHz = 0;
            bool bTop = true;  //波峰
            byte bMax = 0;
            for (int i = 0; i < mbytes.Length ; i++)
            {
                if (mbytes[i] > bMax)
                    bMax = mbytes[i];
            }
            bMax = (byte)((bMax - 0x80) / 10);
            for (int i = 0; i < mbytes.Length; i++)
            {
                if (bTop)
                {
                    if (mbytes[i] < 0x7F-bMax)   //  波谷 7B
                        bTop = false;
                }
                else
                {
                    if (mbytes[i] > 0x81+bMax)   //  波峰  85
                    {
                        bTop = true;
                        iHz++;
                    }
                }
            }
            return iHz;
        }
        */
      /*  public static Single GetScore2(ref byte[] OriFreqPair, ref byte[] NewFreqPair,short nGrade)
        {
            byte nFirstHZ, nSecondHZ, nFirstAmp, nSecondAmp, newFirstHZ, newSecondHZ;
            nFirstHZ = OriFreqPair[0]; nFirstAmp = OriFreqPair[1]; nSecondHZ = OriFreqPair[2]; nSecondAmp = OriFreqPair[3];
            newFirstHZ = NewFreqPair[0]; newSecondHZ = NewFreqPair[2];
            Single mScore = 0;
            if (Math.Abs(nFirstHZ - newFirstHZ) > Math.Abs(nFirstHZ - newSecondHZ))
            {
                newFirstHZ ^= newSecondHZ; //swap
                newSecondHZ ^= newFirstHZ;
                newFirstHZ ^= newSecondHZ;
            }
            int FirstScore = 100 - Math.Abs(newFirstHZ - nFirstHZ) * 100 / nFirstHZ;
            if (FirstScore < nGrade) FirstScore = 0;
            if (nSecondHZ == 0)
            {
                mScore = FirstScore;
            }
            else
            {
                int SecondScore = 100 - Math.Abs(newSecondHZ - nSecondHZ) * 100 / nSecondHZ;                
                if (SecondScore <= nGrade) SecondScore = 0;
                mScore = (FirstScore * nFirstAmp + SecondScore * nSecondAmp) / (nFirstAmp + nSecondAmp);
            }
            if (mScore > nGrade) mScore = 100;
            return mScore;
        }  */
    /*    public static Single GetScore(ref byte[] OriFreqPair, ref byte[] NewFreqPair)
        {
            byte nLeftHz, nLeftHz2, nRightHz, nRightHz2, newRecHz, newRecHz2;
            nLeftHz = OriFreqPair[0]; nLeftHz2 = OriFreqPair[1]; nRightHz = OriFreqPair[2]; nRightHz2 = OriFreqPair[3];
            newRecHz = NewFreqPair[0]; newRecHz2 = NewFreqPair[1];
            Single mScore = 0, mScore1 = 0, mScore2 = 0;

            bool matchRecHz = Math.Abs(nLeftHz - newRecHz) <= 1 || Math.Abs(nLeftHz2 - newRecHz) <= 1;  //录音基波匹配伴奏
            bool matchRecHz2 = Math.Abs(nLeftHz - newRecHz2) <= 1 || Math.Abs(nLeftHz2 - newRecHz2) <= 1;  //录音谐波匹配伴奏

            if (matchRecHz)
            {
                if (matchRecHz2)
                {
                    return 0;
                }
                else
                {
                    mScore = 100 - Math.Abs(newRecHz2 - nRightHz) * 100 / nRightHz;
                    if (nRightHz2 != 0)
                        mScore = Math.Max(mScore, 100 - Math.Abs(newRecHz2 - nRightHz2) * 100 / nRightHz2);
                }
            }
            else
            {
                if (matchRecHz2)
                {
                    mScore = 100 - Math.Abs(newRecHz - nRightHz) * 100 / nRightHz;
                    if (nRightHz2 != 0)
                        mScore = Math.Max(mScore, 100 - Math.Abs(newRecHz - nRightHz2) * 100 / nRightHz2);
                }
                else
                {
                    mScore1 = 100 - Math.Abs(newRecHz - nRightHz) * 100 / nRightHz;
                    mScore2 = 100 - Math.Abs(newRecHz2 - nRightHz) * 100 / nRightHz;
                    mScore = Math.Max(mScore1, mScore2);
                    if (nRightHz2 != 0)
                    {                      
                        mScore1 = 100 - Math.Abs(newRecHz - nRightHz2) * 100 / nRightHz2;                              
                        mScore2 = 100 - Math.Abs(newRecHz2 - nRightHz2) * 100 / nRightHz2;
                        mScore1 = Math.Max(mScore1, mScore2);
                        mScore = Math.Max(mScore1, mScore);
                    }                    
                }
            }
            return mScore < 0 ? 0 : mScore;
        }*/
        public static Single GetScore2(ref byte[] OriFreqPair, ref byte[] NewFreqPair)
        {
            float nLeftHz, nLeftHz2, newRecHz, newRecHz2;
            float nRightHz, nRightHz2;
            nLeftHz = OriFreqPair[0]; nLeftHz2 = OriFreqPair[1]; nRightHz = OriFreqPair[2]; nRightHz2 = OriFreqPair[3];
            newRecHz = NewFreqPair[0]; newRecHz2 = NewFreqPair[1];
            double mScore = 0, mScore1 = 0, mScore2 = 0;

            bool matchRecHz = Math.Abs(nLeftHz - newRecHz) <= 1 || Math.Abs(nLeftHz2 - newRecHz) <= 1;  //录音基波匹配伴奏
            bool matchRecHz2 = Math.Abs(nLeftHz - newRecHz2) <= 1 || Math.Abs(nLeftHz2 - newRecHz2) <= 1;  //录音谐波匹配伴奏

            if (matchRecHz)
            {
                if (matchRecHz2)
                {
                    return 0;
                }
                else
                {
                    mScore = 100 - Math.Abs(Math.Log(newRecHz2/nRightHz,2)) * 120;   //  Math.Log(880.0/440,2) * 12 = 12;
                    if (nRightHz2 != 0)
                        mScore = Math.Max(mScore, 100 - Math.Abs(Math.Log(newRecHz2 / nRightHz2, 2)) * 120);
                }
            }
            else
            {
                if (matchRecHz2)
                {
                    mScore = 100 - Math.Abs(Math.Log(newRecHz / nRightHz, 2)) * 120;
                    if (nRightHz2 != 0)
                        mScore = Math.Max(mScore, 100 - Math.Abs(Math.Log(newRecHz / nRightHz2, 2)) * 120);
                }
                else
                {
                    mScore1 = 100 - Math.Abs(Math.Log(newRecHz / nRightHz, 2)) * 120;
                    mScore2 = 100 - Math.Abs(Math.Log(newRecHz2 / nRightHz, 2)) * 120;
                    mScore = Math.Max(mScore1, mScore2);
                    if (nRightHz2 != 0)
                    {
                        mScore1 = 100 - Math.Abs(Math.Log(newRecHz / nRightHz2, 2)) * 120;
                        mScore2 = 100 - Math.Abs(Math.Log(newRecHz2 / nRightHz2, 2)) * 120;
                        mScore1 = Math.Max(mScore1, mScore2);
                        mScore = Math.Max(mScore1, mScore);
                    }
                }
            }
            return mScore < 0 ? 0 : (float)mScore;
        }
        private void RecordCapturedData()
        {            
            byte[] capturedata = (byte[])capturebuffer.Read(iBufferOffset, typeof(byte), LockFlag.FromWriteCursor, iNotifySize);    
            if (!bRealdata)
            {
               int i = 0;
               if (mYwtFormat.Version == 2)
               {
                   i = mYwtFormat.SampleRate / 10 * mYwtFormat.BytesPerSample;  //delay 100ms
                   bRealdata = true;
               }
               else
               {
                   if (!bFindData)
                   {
                       #region
                       if (mYwtFormat.BytesPerSample == 1)
                       {
                           for (i = 0; i < iNotifySize; i++)
                           {
                               if (capturedata[i] < 0x7E || capturedata[i] > 0x82)  //while (bsample >= 0x7F && bsample <= 0x81) 
                               {
                                   bFindData = true; //找到非0
                                   break;
                               }
                           }
                       }
                       else
                       {
                           for (i = 0; i < iNotifySize; i += 2)
                           {
                               short idata = (short)(capturedata[i] | (capturedata[i + 1] << 8));
                               if (idata < -600 || idata > 600)
                               {
                                   bFindData = true;
                                   break;
                               }
                           }
                       }
                       #endregion
                   }
                   if (bFindData)
                   {       
                       int iret = GetFirstFreq(ref capturedata, ref mYwtFormat, 1);
                       if (iret == -1)
                       {
                           i = iNotifySize;
                           bFindData = false;
                       }
                       else
                       {
                           if (mYwtFormat.Version == 1)
                           {
                               i = iret * mYwtFormat.BytesPerSample;
                           }
                           else
                               mReader.BaseStream.Seek(SkipCount * 4, SeekOrigin.Current);
                           bRealdata = true;
                       }
                   }
               }                                                             
                iBufferOffset = (iBufferOffset + i) % iBufferSize;                
                if (bSaveWaveFile)
                {
                    mWriter.Write(capturedata,0,i); 
                    iSampleSize += i;
                }
                return;
            }             
            if (mReader.BaseStream.Position < mReader.BaseStream.Length)
            {
                byte[] OriFreqPair = null;
                byte[] NewFreqPair = new byte[2];
                double[] NewAmp = new double[2];
                OriFreqPair = mReader.ReadBytes(4);

                GetMainFreq(ref capturedata, ref NewFreqPair, ref NewAmp, mYwtFormat.BytesPerSample);

                if (NewAmp[0] >= (mYwtFormat.BytesPerSample == 2 ? 400 : 2))
                    mCurTone = NewFreqPair[0];
                else
                    mCurTone = 0;
                if (OriFreqPair[2] > 0) //
                {
                    
                    mCurScore = GetScore2(ref OriFreqPair, ref NewFreqPair); 
                    if (mCurScore >= Grade)
                    {
                        mTotalScore ++;                       
                    }                  
                    iBeatCount++;
                }                
                if (bSaveWaveFile)
                {
                    mWriter.Write(capturedata);//写入到文件                 
                    iSampleSize += iNotifySize;
                }
            }            
            iBufferOffset = (iBufferOffset + iNotifySize) % iBufferSize;                                    
        }

        public AudioMatch(string strywtfile, bool SaveWaveFile, ref License lic)
        {
            if (lic == null)
            {
                lic = new License();
            }            
            if (lic.isValid && File.Exists(strywtfile))
                IsInitialized = true;
            else
                return;

            fsYWT = new FileStream(strywtfile, FileMode.Open, FileAccess.Read);
            mReader = new BinaryReader(fsYWT);
            bSaveWaveFile = SaveWaveFile;
            mYwtFormat = PreReadYwtFile(mReader);
            mReader.BaseStream.Seek(mYwtFormat.SentenceCount * 8, SeekOrigin.Current);

            mWavFormat = SetWaveFormat(1, mYwtFormat.BytesPerSample, mYwtFormat.SampleRate);
            if (bSaveWaveFile)
            {
                string strWavefile = strywtfile.Replace(License.strYwtPath, License.strWavPath);
                strWavefile = strWavefile.Replace(License.strYwtExt, DateTime.Now.ToString(strDateFormat) + License.strWaveExt);                                
                fsWav = new FileStream(strWavefile, FileMode.Create);
                mWriter = new BinaryWriter(fsWav);
                CreateWaveFile(mWriter, mWavFormat);
            }

            CreateCaputerDevice();
            CreateCaptureBuffer();
            CreateNotification();
        }
        public void Start()
        {
            if (IsInitialized)                           
                capturebuffer.Start(true);            
        }
        public void Pause()
        {
            if (IsInitialized)
            capturebuffer.Stop();
        }
        public void Stop()
        {
            if (!IsInitialized) return;
            IsInitialized = false;
            try
            {
                capturebuffer.Stop();//调用缓冲区的停止方法。停止采集声音                        
                notifyevent.Set();//关闭通知
                notifyevent.Close();
                notifythread.Abort();//结束线程                
                capturebuffer.Dispose();
                capture.Dispose();

                //写WAV文件尾
                if (bSaveWaveFile)
                {
                    mWriter.Seek(4, SeekOrigin.Begin);
                    mWriter.Write((int)(iSampleSize + 36));   // 写文件长度
                    mWriter.Seek(40, SeekOrigin.Begin);
                    mWriter.Write(iSampleSize);                // 写数据长度
                    mWriter.Close();
                    fsWav.Close();
                }

                mReader.Close();
                fsYWT.Close();
            }
            catch (Exception)
            {             
            }
            GC.Collect();            
        }
       
    }
}
