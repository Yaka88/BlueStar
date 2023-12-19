//#define VERSION1  // 歌首去0   
//#define VERSION2    // 延迟100ms 
#define VERSION3    //  mute 10  
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Text;
using System.IO;
using System.Runtime.InteropServices;
using DirectShowLib;

namespace BlueStar
{
    public class Mpg2Wav
    {
#if VERSION1
        private const short YwtVersion = 1;
#elif VERSION2
        private const short YwtVersion = 2;
#elif VERSION3
        private const short YwtVersion = 3;
#endif
        public int iDataSize = 0;
        public bool IsInitialized = false;
        private const long S_OK = 0;
        private const long S_FALSE = 1;
        private IGraphBuilder graphBuilder = null;
        private IMediaControl mediaControl = null;
        private IMediaEventEx mediaEventEx = null;
        private AVGrabber AudioGrabber = null;
        private AVGrabber AudioGrabber2 = null;

        private bool bInvert = false;
        private bool bToYwt = true;
        private bool bAC3 = false;

        private ISampleGrabber sampleGrabber = null;
        private IMediaPosition mediaPosition = null;

        private Stream fswavefile = null;
        private Stream fswavefile2 = null;        

        private IBaseFilter pSourceFilter = null;
        private IBaseFilter pMPEGSplitter = null;
        private IBaseFilter pAudioDec = null;
        private IBaseFilter pGrabFilter = null;
        private IBaseFilter pNullRenderer = null;
        private Guid m_mediatype;
        private string strFileName;
        private string strFileKsc;

        private const string strSourceFilter = "Source Filter";
        private const string strMPGSplitter = "MPEG Stream Splitter";
        private const string strAudioDec = "MPEG Audio Decoder";
        private const string strSampleGrabber = "Sample Grabber";
       // private const string strAC3Filter = "AC3 Filter";
        private const string strNullRenderer = "Null Renderer";      
        private const string strMainMpegGuid = "B4951392-7D41-4E7A-AA60-CEAD5615E672";         
        private const string strAC3Guid = "A753A1EC-973E-4718-AF8E-A3F554D45C44";          
      //  DsROTEntry m_rot;

     /*   private Guid CheckMediaType(IPin IPinSource)
        {
            AMMediaType[] ppmedia = new AMMediaType[1];
            IEnumMediaTypes ppeum;
            int iret = IPinSource.EnumMediaTypes(out ppeum);
            iret = ppeum.Next(1, ppmedia, new IntPtr());
            Guid mediatype = ppmedia[0].subType;            
            DsUtils.FreeAMMediaType(ppmedia[0]);
            return mediatype;
        }*/             
        private AVGrabber CreateGraber(IPin iPinAudio,Stream fsFile)
        {
            IPin iPinOutAudio = null, iPinInAudio = null;

            if (bAC3)
                pAudioDec = (IBaseFilter)(Activator.CreateInstance(Type.GetTypeFromCLSID(new Guid(strAC3Guid))));
            else
                pAudioDec = (IBaseFilter)new CMpegAudioCodec(); 

            graphBuilder.AddFilter(pAudioDec, strAudioDec);
            iPinInAudio = DsFindPin.ByDirection(pAudioDec, PinDirection.Input, 0);
            graphBuilder.Connect(iPinAudio, iPinInAudio);
            iPinOutAudio = DsFindPin.ByDirection(pAudioDec, PinDirection.Output, 0);

            sampleGrabber = new SampleGrabber() as ISampleGrabber;
            pGrabFilter = sampleGrabber as IBaseFilter;
            AVGrabber AudioGrabber = new AVGrabber(sampleGrabber, m_mediatype);//
            
            graphBuilder.AddFilter(pGrabFilter, strSampleGrabber);
            iPinInAudio = DsFindPin.ByDirection(pGrabFilter, PinDirection.Input, 0);
            graphBuilder.Connect(iPinOutAudio, iPinInAudio);
            iPinOutAudio = DsFindPin.ByDirection(pGrabFilter, PinDirection.Output, 0);

            pNullRenderer = (IBaseFilter)new NullRenderer();
            graphBuilder.AddFilter(pNullRenderer, strNullRenderer);
            iPinInAudio = DsFindPin.ByDirection(pNullRenderer, PinDirection.Input, 0);
            graphBuilder.Connect(iPinOutAudio, iPinInAudio);

            AudioGrabber.SaveSizeInfo(sampleGrabber, fsFile);
            return AudioGrabber;

        }

        public Mpg2Wav(string strMpg, string strFile, string strKsc, bool Invert,ref License lic)
        {
            if (lic == null)
            {
                lic = new License();
            }
            if (lic.isValid && File.Exists(strMpg))
                IsInitialized = true;
            else
                return;
           
            IPin iPinOutSource = null;
            IPin iPinInAudio = null;
            strFileName = strFile;
            strFileKsc = strKsc;
            bInvert = Invert;
            bToYwt = strFile.EndsWith(License.strYwtExt);

            graphBuilder = (IGraphBuilder)new FilterGraph();
            mediaControl = (IMediaControl)graphBuilder;

            graphBuilder.AddSourceFilter(strMpg, strSourceFilter, out pSourceFilter);
            iPinOutSource = DsFindPin.ByDirection(pSourceFilter, PinDirection.Output, 0);

            pMPEGSplitter = (IBaseFilter)(Activator.CreateInstance(Type.GetTypeFromCLSID(new Guid(strMainMpegGuid))));
            // IBaseFilter pMPEGSplitter = (IBaseFilter)new MPEG2Demultiplexer();                                                         
            graphBuilder.AddFilter(pMPEGSplitter, strMPGSplitter);
            iPinInAudio = DsFindPin.ByDirection(pMPEGSplitter, PinDirection.Input, 0);
            graphBuilder.Connect(iPinOutSource, iPinInAudio);

//            m_rot = new DsROTEntry(graphBuilder);
            if (bToYwt)
                fswavefile = new MemoryStream(); //m_mediatype = MediaType.File;  
            else
                fswavefile = new FileStream(strFileName, FileMode.Create);

            IEnumPins ppEnum;
            pMPEGSplitter.EnumPins(out ppEnum);
            IPin[] ppPin = new IPin[1]; string strid;
            IntPtr IntFetch = new IntPtr();
            IPin pinTrack1=null, pinTrack2 = null;

            while (ppEnum.Next(1, ppPin, IntFetch) == S_OK)
            {                
                ppPin[0].QueryId(out strid);               
                if (strid.Contains("192"))  //0xC0
                {
                    pinTrack1 = ppPin[0];                    
                }
                else if (strid.Contains("128"))  //原唱 0x80
                {
                    pinTrack1 = ppPin[0];
                    bAC3 = true;
                }
                else if (strid.Contains("193") || strid.Contains("129"))  //伴唱                
                    pinTrack2 = ppPin[0];                
            }
            if (pinTrack2 == null)
            {
                m_mediatype = MediaSubType.MPEG1System;
                AudioGrabber = CreateGraber(pinTrack1, fswavefile);
                if (bInvert)
                    AudioGrabber.LeftVocal = true;
            }
            else
            {
                if (bToYwt)
                {
                    m_mediatype = MediaSubType.Mpeg2Program;
                    fswavefile2 = new MemoryStream();
                }
                else
                {
                    m_mediatype = MediaSubType.MPEG1System;
                    fswavefile2 = new FileStream(strFileName.Replace(License.strWaveExt, "_2" + License.strWaveExt), FileMode.Create);
                }
                if (bInvert)
                {
                    AudioGrabber = CreateGraber(pinTrack1, fswavefile);    //fswavefile 伴唱
                    AudioGrabber2 = CreateGraber(pinTrack2, fswavefile2);    //fswavefile2 原唱
                }
                else
                {
                    AudioGrabber = CreateGraber(pinTrack1, fswavefile2);    //fswavefile 伴唱
                    AudioGrabber2 = CreateGraber(pinTrack2, fswavefile);    //fswavefile2 原唱
                }              
            }
            //m_mediatype = CheckMediaType(iPinOutSource);                       
            mediaPosition = (IMediaPosition)graphBuilder;
            mediaPosition.put_Rate(100);  
        }
        public void SetNotifyWindow(IntPtr hwnd, int IMsg)
        {
            if (mediaControl != null)
            {
                mediaEventEx = mediaControl as IMediaEventEx;
                mediaEventEx.SetNotifyWindow(hwnd, IMsg, IntPtr.Zero);
            }
        }
        public bool Complete()
        {
            EventCode evCode;
            IntPtr evParam1, evParam2;
            if (mediaEventEx == null)
                return true;
            // Process all queued events
            while (true)
            {
                if (mediaEventEx.GetEvent(out evCode, out evParam1, out evParam2, 0) == S_OK)
                {
                    mediaEventEx.FreeEventParams(evCode, evParam1, evParam2);
                    if (evCode == EventCode.Complete || evCode == EventCode.UserAbort)
                    {
                        Stop();
                        return true;
                    }
                }
                else
                    return false;
            }
        }
        public static WaveFormatEx PreReadWaveFile(BinaryReader mReader,int nVersion)
        {
            //   char[] ChunkRiff = { 'R', 'I', 'F', 'F' };                     
            // RIFF 块            
            WaveFormatEx wave = new WaveFormatEx();
            mReader.BaseStream.Position = 22;
            wave.nChannels = mReader.ReadInt16();
            wave.nSamplesPerSec = mReader.ReadInt32();
            wave.nAvgBytesPerSec = mReader.ReadInt32();
            wave.nBlockAlign = mReader.ReadInt16();
            wave.wBitsPerSample = mReader.ReadInt16();
            int iBytesPerSample = wave.nBlockAlign / wave.nChannels;
            mReader.BaseStream.Position += 4;
            int iSampleSize = mReader.ReadInt32();
            
            if (nVersion == 1)
            {
                if (iBytesPerSample == 2)
                {
                    short bsample = mReader.ReadInt16();
                    while (bsample >= -600 && bsample <= 600)  // 256 * 256 /200
                    {
                        if (wave.nChannels == 2)
                            mReader.BaseStream.Position += 2;
                        bsample = mReader.ReadInt16();
                    }
                    mReader.BaseStream.Position -= 2;
                }
                else
                {
                    byte bsample = mReader.ReadByte();
                    while (bsample >= 0x7E && bsample <= 0x82)  //while (bsample >= 0x7F && bsample <= 0x81) 
                    {
                        if (wave.nChannels == 2)
                            mReader.BaseStream.Position++;
                        bsample = mReader.ReadByte();
                    }
                    mReader.BaseStream.Position--;
                }
            }
            return wave;
            //    iSampleSize = (int)(mReader.BaseStream.Length - mReader.BaseStream.Position);

        }
        public static void Wave2Ywf(Stream fswavefile,Stream fswavefile2,string strYwt,string strKsc, out int isampleSize)
        {
            WaveFormatEx wave;
            YwtFormat ywtF = new YwtFormat();
            BinaryReader WaveReader = new BinaryReader(fswavefile);   //伴奏
            BinaryReader WaveReader2 = null;                  //原唱
            bool bMpeg2 = fswavefile2 != null;
            if (bMpeg2)
                WaveReader2 = new BinaryReader(fswavefile2);    

            ywtF.Version = YwtVersion;
            wave = PreReadWaveFile(WaveReader,YwtVersion);
            ywtF.SampleRate = wave.nSamplesPerSec;
            ywtF.BytesPerSample = (short)(wave.nBlockAlign / wave.nChannels);

            bool bMoreData = ywtF.SampleRate == 8000;
          
            float interval = (float)AudioMatch.iSamples / wave.nSamplesPerSec;
            Collection<Single> colSingle;
            ConvertYWFbyKsc(interval, strKsc, out colSingle);

            ywtF.SentenceCount = colSingle.Count / 2;

            byte[] mbyte, mbyte2;
            int iBeatRate = AudioMatch.iSamples * wave.nBlockAlign;
            byte[] mFreqPair = new byte[4];       
            double[] mAmpPair = new double[2];            
            isampleSize = 0;

#if VERSION1  //查找特征频率 
            ywtF.FirstFreq = 0;
            int index = -1;
            do
            {                
                mbyte = WaveReader.ReadBytes(iBeatRate);
                if (mbyte.Length < iBeatRate)
                    return;
                index = AudioMatch.GetFirstFreq(ref mbyte, ref ywtF, wave.nChannels);
            }
            while (index == -1);

            WaveReader.BaseStream.Position -= iBeatRate - index * wave.nBlockAlign;            
            long iWavestartPos = WaveReader.BaseStream.Position;
            
            ywtF.ShowTime = colSingle[0] - 1;
            ywtF.WaveStartTime = ((float)iWavestartPos - 44) / (wave.nSamplesPerSec * wave.nBlockAlign);            
            if (ywtF.WaveStartTime > ywtF.ShowTime)                            
                return;
#else
            long iWavestartPos = WaveReader.BaseStream.Position;
#endif

            FileStream fsywt = new FileStream(strYwt, FileMode.Create);
            BinaryWriter mWriter = new BinaryWriter(fsywt);
            AudioMatch.CreateYwtFile(mWriter, ywtF);         

            for (int i = 0; i < colSingle.Count; i++)
            {
                mWriter.Write(colSingle[i]);
            }
            long iYwfStartPos = mWriter.BaseStream.Position;
                       
            
            float fFrom, fTo;
            for (int i = 0; i < colSingle.Count; )
            {
                fFrom = colSingle[i++];
                fTo = colSingle[i++];    
#if VERSION1
                long intfrom = (long)(fFrom * wave.nSamplesPerSec * wave.nBlockAlign + 44);
                long intto = (long)(fTo * wave.nSamplesPerSec * wave.nBlockAlign + 44);
                long intfrompos = (intfrom - iWavestartPos) / iBeatRate;
                long inttopos = (intto - iWavestartPos) / iBeatRate;
#else
                long intfrompos = (long)(fFrom * wave.nSamplesPerSec / AudioMatch.iSamples);
                long inttopos = (long)(fTo * wave.nSamplesPerSec / AudioMatch.iSamples);
#endif
                WaveReader.BaseStream.Position = iWavestartPos + intfrompos * iBeatRate;
                if(bMpeg2)
                    WaveReader2.BaseStream.Position = WaveReader.BaseStream.Position;
                mWriter.BaseStream.Position = iYwfStartPos + intfrompos * 4;
                for (long j = intfrompos; j < inttopos; j++)
                {
                    mbyte = WaveReader.ReadBytes(iBeatRate);
                    if (mbyte.Length < iBeatRate)
                        break;
                    if (bMpeg2)
                    {
                        mbyte2 = WaveReader2.ReadBytes(iBeatRate);
                        AudioMatch.GetMainFreq(ref mbyte, ref mbyte2, ref mFreqPair, ywtF.BytesPerSample, bMoreData);
                    }                    
                    else
                        AudioMatch.GetMainFreq(ref mbyte, ref mFreqPair, ywtF.BytesPerSample, bMoreData);
                    if (mFreqPair[2] > 0) { isampleSize++; }
                    mWriter.Write(mFreqPair);
                }
            }           
            mWriter.Seek(16, SeekOrigin.Begin);
            mWriter.Write(isampleSize);

            WaveReader.Close();
            if (bMpeg2)
                WaveReader2.Close();
            mWriter.Close();
            fsywt.Close();
        }
        public static void ConvertYWFbyKsc(float interval, string strKSC, out Collection<float> colSingle)
        {
            colSingle = new Collection<float>();           
            FileStream fsksc = new FileStream(strKSC, FileMode.Open, FileAccess.Read);
            StreamReader mReaderKsc = new StreamReader(fsksc, Encoding.GetEncoding("GB2312"));
            string strline;
            int findadd = -1;
            float fFrom, fTo;
            bool isOdd = true;
            bool bFirstTime = true;
            float fShowTime = 0;
            float foffset = 0;
            strline = mReaderKsc.ReadLine();
            interval = interval * 40;
            findadd = strline.IndexOf("karaoke.ShowTime");
            if (findadd != -1)
            {
                fShowTime = float.Parse(strline.Substring(20, 7));
            }

            while ((strline = mReaderKsc.ReadLine()) != null)
            {
                findadd = strline.IndexOf("karaoke.add('");
                if (findadd != -1)
                {
                    string strBegin, strEnd, strWords, strTimes;
                    int intBegin, intEnd = 0;
                    char ch = '\'';
                    intBegin = strline.IndexOf(ch, intEnd + 1) + 1;
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
                        int iMun = strBegin.IndexOf(':');
                        fFrom = int.Parse(strBegin.Substring(0, iMun)) * 60 + float.Parse(strBegin.Substring(iMun + 1)) + foffset;

                        if (bFirstTime)
                        {
                            if (fShowTime != 0)
                            {                                
                                foffset = fShowTime - fFrom;
                                if (foffset < 0.5 && foffset > - 0.25)
                                    foffset = 0;
                                fFrom += foffset;
                            }
                            bFirstTime = false;
                        }                                             

                        fTo = int.Parse(strEnd.Substring(0, iMun)) * 60 + float.Parse(strEnd.Substring(iMun+1)) + foffset;                               
  //                      if (!isOdd && (fFrom - colSingle[colSingle.Count - 1] < 2) && (colSingle[colSingle.Count - 1] - colSingle[colSingle.Count - 2] < interval))
                       
                        if (!isOdd && (fFrom - colSingle[colSingle.Count - 1] < 3) && (fTo - colSingle[colSingle.Count - 2] < interval))                        
                        {
                            colSingle[colSingle.Count - 1] = fTo;
                            isOdd = true;
                        }
                        else
                        {
                            colSingle.Add(fFrom);
                            colSingle.Add(fTo);
                            isOdd = false;
                        }
                    }
                }
            }
            mReaderKsc.Close();
            fsksc.Close();
        }
        public void Stop()
        {
            if (IsInitialized)
            {
                mediaControl.Stop();
                AudioGrabber.Finaly();
                if (AudioGrabber2 != null)
                {
                    AudioGrabber2.Finaly();
                    AudioGrabber2 = null;
                }

                if (bToYwt)
                {
                    Wave2Ywf(fswavefile, fswavefile2, strFileName, strFileKsc, out iDataSize);
                }
                if (fswavefile2 != null)
                {
                    fswavefile2.Close();
                    fswavefile2 = null;
                }

                //iDataSize = AudioGrabber.nsampleSize;

                fswavefile.Close();
                AudioGrabber = null;

                pSourceFilter = null;
                //   pMPEGSplitter = null;
                //   pAudioDec = null;
                //    pWavDest = null;
                //    pFileWriter = null;           
                mediaControl = null;

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
            }
            GC.Collect();
        }
        public void Start()
        {
            if (IsInitialized)
            mediaControl.Run();
        }

    }
}
