using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using DirectShowLib;
using System.Drawing;
using System.Drawing.Imaging;
using System.Drawing.Drawing2D;
using System.Runtime.InteropServices;

namespace BlueStar
{
    public class AVGrabber : ISampleGrabberCB
    {                  
        private Guid m_mediaType; 
        private bool bLeftVocal = false;
        private int npointer = 0;
        private byte[] byteFreq;
        private BinaryWriter FileWriter;
        public int nsampleSize = 0;
        private short[] AData;        
        private int nDiv = 1, iStep;
        private short nbytes = 2;
        private byte[] pbyte = null;
        private byte[] pbyteWave = null;

        public bool bRealdata = false; 
        private int iSampleRate = 0;
        private int nBlockAlign;
        private int MuteSamples = 0, LargeSamples = 0;
        private int intIndexofWav = -1;
       
        public int Balance = 0;

        public void PlaySound(byte[] pByte)
        {
            pbyteWave = pByte;
            intIndexofWav = 0;
        }
        public void Dispose()
        {           
            GC.Collect();
        }
        public bool LeftVocal
        {
            set
            {
                bLeftVocal = value;
                if (value && m_mediaType == MediaSubType.MPEG1System)
                {
                    nsampleSize += nbytes;
                    FileWriter.BaseStream.Position += nbytes;
                }
            }
        }
        public AVGrabber(ISampleGrabber sampleGrabber, Guid mediatype)
        {
            int hr;
            m_mediaType = mediatype;
            // Set the media type to Video/RBG24
            AMMediaType media = new AMMediaType();
            media.majorType = MediaType.Audio;        
            media.subType = MediaSubType.PCM ;
            media.formatType = FormatType.WaveEx;
            
            hr = sampleGrabber.SetMediaType(media);
            DsError.ThrowExceptionForHR(hr);
            DsUtils.FreeAMMediaType(media);
            media = null;
            hr = sampleGrabber.SetCallback(this, 1);
            DsError.ThrowExceptionForHR(hr);
        }
     
        public void SaveSizeInfo(ISampleGrabber sampGrabber, Stream fsFile)
        {
            int hr;
            // Get the media type from the SampleGrabber
            AMMediaType media = new AMMediaType();
            hr = sampGrabber.GetConnectedMediaType(media);
            DsError.ThrowExceptionForHR(hr);
            
            WaveFormatEx wavEx = (WaveFormatEx)Marshal.PtrToStructure(media.formatPtr, typeof(WaveFormatEx));                     
            
            int Splitter;
            int AdataLength;
            if ((wavEx.nSamplesPerSec % 8000) == 0)
            {
                Splitter = 8000;
                AdataLength = 10;
            }
            else
            {
                Splitter = 11025;
                AdataLength = 15;
            }                        
            nDiv = wavEx.nSamplesPerSec / Splitter;     
            nbytes = (short)(wavEx.wBitsPerSample / 8);
            if (m_mediaType == MediaType.Audio)  //   播放mute
            {              
                nBlockAlign = wavEx.nBlockAlign;
                MuteSamples = AudioMatch.iSamples * AudioMatch.SkipCount * nDiv * nBlockAlign;
                LargeSamples = MuteSamples + AudioMatch.iSamples * nDiv * nBlockAlign;
                AData = new short[AdataLength * nDiv];
                if (nbytes == 2)
                    for (int i = 0; i < AData.Length; i++)
                        AData[i] = (short)(Math.Sin(2 * Math.PI * i / AData.Length) * short.MaxValue / 2);  //2
                else
                    for (int i = 0; i < AData.Length; i++)
                    {
                        byte data = (byte)((Math.Sin(2 * Math.PI * i / AData.Length) + 1) * byte.MaxValue / 4); //4
                        AData[i] = (short)((data << 8) | data);
                    }              
            }
            else
            {
                iSampleRate = wavEx.nSamplesPerSec / nDiv;
                iStep = (nbytes << 1) * nDiv;
                FileWriter = new BinaryWriter(fsFile);
                if (m_mediaType == MediaSubType.MPEG1System)
                {
                    nBlockAlign = wavEx.nBlockAlign;
                    AudioMatch.CreateWaveFile(FileWriter, 2, nbytes, iSampleRate);
                }
                else if (m_mediaType == MediaSubType.Mpeg2Program)
                {
                    nBlockAlign = nbytes;
                    AudioMatch.CreateWaveFile(FileWriter, 1, nbytes, iSampleRate);
                }
                else if (m_mediaType == MediaType.File)
                {
                    YwtFormat ywtF = new YwtFormat();
                    ywtF.BytesPerSample = nbytes;
                    ywtF.SampleRate = iSampleRate;
                    ywtF.Version = 1;
                    AudioMatch.CreateYwtFile(FileWriter, ywtF);
                    FileWriter.Write((long)0);
                    pbyte = new byte[AudioMatch.iSamples * (nbytes << 1) + nbytes];
                    byteFreq = new byte[4];
                }
            }
            DsUtils.FreeAMMediaType(media);
            media = null;
        }

        public void Finaly()
        {
            if (m_mediaType == MediaType.File)
            {
                FileWriter.Seek(16, SeekOrigin.Begin);
                FileWriter.Write(nsampleSize);
            }
            else
            {
                if (m_mediaType == MediaSubType.Mpeg2Program)
                    nsampleSize >>= 1;
                FileWriter.Seek(4, SeekOrigin.Begin);
                FileWriter.Write((int)(nsampleSize + 36));   // 写文件长度
                FileWriter.Seek(40, SeekOrigin.Begin);
                FileWriter.Write(nsampleSize);                // 写数据长度                
            }
            // FileWriter.Close();
        }
        int ISampleGrabberCB.SampleCB(double SampleTime, IMediaSample pSample)
        {
            return 0;
        }

        /// <summary> buffer callback, COULD BE FROM FOREIGN THREAD. </summary>
        int ISampleGrabberCB.BufferCB(double SampleTime, IntPtr pBuffer, int BufferLen)
        {        
            if (m_mediaType == MediaType.Audio)
            {
                if (bRealdata)
                {                                          
                    if (Balance == 0 && intIndexofWav == -1)
                        return 0;
                    else
                    {
                        int FirstFrom, nextFrom;
                        if (Balance == -1)
                        {
                            FirstFrom = 0;
                            nextFrom = nbytes;
                        }
                        else
                        {
                            FirstFrom = nbytes;
                            nextFrom = -nbytes;
                        }
                        if (nbytes == 2)
                        {                                                                                                              
                            
                            short data;                            
                            for (int k = FirstFrom; k < BufferLen; k += 4)
                            {
                                data = Marshal.ReadInt16(pBuffer, k);
                                if (intIndexofWav != -1)
                                {
                                    data = (short)(data + (short)(pbyteWave[intIndexofWav] | (pbyteWave[intIndexofWav + 1] << 8)));
                                    Marshal.WriteInt16(pBuffer, k, data);
                                    intIndexofWav += 2;
                                    if (intIndexofWav >= pbyteWave.Length)                                    
                                        intIndexofWav = -1;                                    
                                }
                                Marshal.WriteInt16(pBuffer, k + nextFrom, data);                                
                            }
                        }
                        else
                        {
                            byte data;
                            for (int k = FirstFrom; k < BufferLen; k += 2)
                            {
                                data = Marshal.ReadByte(pBuffer, k);
                                if (intIndexofWav != -1)
                                {

                                    data = (byte)(data + (sbyte)(pbyteWave[intIndexofWav + 1]));
                                    Marshal.WriteByte(pBuffer, k, data);
                                    intIndexofWav += 2;
                                    if (intIndexofWav >= pbyteWave.Length)
                                        intIndexofWav = -1;
                                }
                                Marshal.WriteByte(pBuffer, k + nextFrom, data);
                            }
                        }
                    }
                }
                else if (nsampleSize < MuteSamples)
                {
                    int i = MuteSamples - nsampleSize;
                    if (i > BufferLen)
                    {
                        i = BufferLen;
                        nsampleSize += BufferLen;
                    }
                    else
                        nsampleSize = MuteSamples;
                    for (int j = 0; j < i; j++)
                        Marshal.WriteByte(pBuffer, j, 0);
                }
                else if (nsampleSize < LargeSamples)
                {
                    int i = LargeSamples - nsampleSize;
                    if (i > BufferLen)
                    {
                        i = BufferLen;
                        nsampleSize += BufferLen;
                    }
                    else
                    {
                        bRealdata = true;
                        nsampleSize = LargeSamples;
                    }
                    int j = 0;                  
                    if (nbytes == 1)
                        while (j < i)
                        {
                            for (int k = 0; k < AData.Length; k++)
                            {
                                Marshal.WriteInt16(pBuffer, j,AData[k]);
                                j += 2;
                                if (j >= i) break;
                            }
                        }
                    else
                        while (j < i)
                        {
                            for (int k = 0; k < AData.Length; k++)
                            {
                                Marshal.WriteInt16(pBuffer, j, AData[k]);
                                j += 2;
                                Marshal.WriteInt16(pBuffer, j, AData[k]);
                                j += 2;
                                if (j >= i) break;
                            } 
                        }
                }
            }
            else if (m_mediaType == MediaType.File)
            {
                #region
                int nBlockAlign = nbytes << 1;
                int size = BufferLen / iStep;
                int i = 0;
                int ofs = bLeftVocal ? nbytes : 0;
                if (!bRealdata)
                {
                    if (nbytes == 2)
                    {
                        short idata;
                        for (; i < size; i++)
                        {
                            idata = Marshal.ReadInt16(pBuffer, i * iStep + ofs);
                            if (idata < -600 || idata > 600)
                            {
                                bRealdata = true;
                                FileWriter.Write(SampleTime + (double)i / iSampleRate);//
                                npointer += ofs;
                                break;
                            }
                        }
                    }
                    else
                    {
                        byte idata;
                        for (; i < size; i++)
                        {
                            idata = Marshal.ReadByte(pBuffer, i * iStep + ofs);
                            if (idata < 0x7E || idata > 0x82)
                            {
                                bRealdata = true;
                                FileWriter.Write(SampleTime + (double)i / iSampleRate);//
                                npointer += ofs;
                                break;
                            }
                        }
                    }
                }
                if (bRealdata)
                {
                    //
                    for (long j = pBuffer.ToInt64() + i * iStep; j < BufferLen + pBuffer.ToInt64(); j += iStep)
                    {
                        // idata = Marshal.ReadInt32(pBuffer, i * nBlockAlign * nDiv);
                        Marshal.Copy(new IntPtr(j), pbyte, npointer, nBlockAlign);
                        npointer += nBlockAlign;
                        if (npointer >= AudioMatch.iSamples * nBlockAlign)
                        {
                            AudioMatch.GetMainFreq(ref pbyte, ref byteFreq, nbytes, false);
                            if (byteFreq[2] > 0) { nsampleSize++; }
                            FileWriter.Write(byteFreq);
                            for (int k = 0; k < ofs; k++)
                                pbyte[k] = pbyte[AudioMatch.iSamples * nBlockAlign + k];
                            npointer = ofs;
                        }
                    }
                }
                #endregion
            }
            else
            {
                nsampleSize += BufferLen / nDiv;
                byte[] data = new byte[nBlockAlign];
                for (long i = pBuffer.ToInt64(); i < BufferLen + pBuffer.ToInt64(); i += iStep)
                {
                    Marshal.Copy(new IntPtr(i), data, 0, nBlockAlign);
                    FileWriter.Write(data);
                }
            }
            return 0;
        }
    }
    public class DirectOSD : ISampleGrabberCB
    {
    

        private int m_videoWidth;
        private int m_videoHeight;
        private int m_stride;
        public int Mode = 1;  // 1: line ,2,Note  3: Dash//4 roll
//for BackDash
        private Point LastPoint;
        private Pen LinePen;       
        private string strOsdLine = "Images\\BackLine.png";
//for BackNote
        private string strOsdNote = "Images\\BackNote.png";    
        private string strNewTone = "Images\\NewNote.png";
        private string strOriTone = "Images\\OriNote.png";
        private string strADBack = "Images\\ADBack.png";  
        private Bitmap bitmapTone, bitmapNewTone;
//for BackLine        
        private Pen OriPen, NewPen;

   //     private string strScore = "你的巨星指数是";
        public int nShowOSD = 0; //0  false, 1 = true, 2, next  3, last,-1 AD
        public string strAD = string.Empty;
        public int ADIndex = 0;
        private bool bTV = true;      
        private bool m_bOdd = false;
        private int iPixelPointer = -1;
        private Bitmap bitmapOverlay, bmpADback;
        private Bitmap bitmapOrigin;
        private LinearGradientBrush RedBrush;
        private Brush GreenBrush;

        //private Guid m_mediaType;
        private CRmOSD TVOsd = null;
        private Rectangle Bmprect, VGArect;
        private Font ADFont;
        private int m_ADFontSize = 30;
        private Point OSDPoint;
        private int Top, Bottom,Height, iStep;
        private int Left = 40, Left2 = 616;        //private int Left = 70,Left2 = 605;        
        private int iBytesPixel = 24;
        //public byte[] byteFreq;
        private int[] intFreq;
        private int intMinFreq, intMaxFreq;
        private float fCount = 0, yStep;
        private  bool bupdated = false;
        private Single iAveScore, iCurScore;
        private int iCurTone;

        public DirectOSD(ref CRmOSD osd, ref License lic)
        {
            bTV = true;
            TVOsd = osd;
        }
        public DirectOSD(ISampleGrabber sampleGrabber, ref License lic)
        {
            bTV = false;
            /* bTV = mediatype == MediaType.AnalogVideo;
             if (bTV)            
                 TVOsd = new CRmOSD(ref lic);                           
             else*/

            int hr;
            // Set the media type to Video/RBG24
            AMMediaType media = new AMMediaType();
            media.majorType = MediaType.Video;
            media.subType = MediaSubType.ARGB32;
            media.formatType = FormatType.VideoInfo;

            hr = sampleGrabber.SetMediaType(media);
            DsError.ThrowExceptionForHR(hr);
            DsUtils.FreeAMMediaType(media);
            media = null;

            hr = sampleGrabber.SetCallback(this, 1);
            DsError.ThrowExceptionForHR(hr);
        }
        private void ShowTVOSD()
        {
            UpdateBitmap();
            BitmapData bmpData = bitmapOverlay.LockBits(Bmprect, ImageLockMode.ReadOnly, bitmapOverlay.PixelFormat);
            unsafe { TVOsd.LoadHBitmap(iBytesPixel, bmpData.Scan0.ToPointer()); }
            bitmapOverlay.UnlockBits(bmpData);
        }
        public void Update(int bShowOSD, Single CurScore, Single CurTone)
        {            
            if (nShowOSD == 3)
                return;
            nShowOSD = bShowOSD;
            switch (bShowOSD)
            {
                case -1:  // AD                   
                    if (bTV)
                        ShowTVOSD();
                    else
                        bupdated = true;                    
                    break;
                case 0:  //close
                    iPixelPointer = -1;
                    fCount = 0;
                    m_bOdd = false;
                    if (bTV)
                    {
                        TVOsd.CloseOSD();
                        if (Mode != 0)
                            TVOsd.SetOSDRect(OSDPoint.X, 8, bitmapOrigin.Width, bitmapOrigin.Height);                        
                    }
                    else
                    {
                        if (Mode != 0)
                            VGArect.Y = m_videoHeight - VGArect.Height;
                    }
                    break;
                case 1:     //show tone             
                    //LastValue = iCurTone;
                    iCurScore = CurScore;
                    iCurTone = (int)CurTone;
                    iPixelPointer++;
                    if (bTV)
                    {
                        if (iPixelPointer == 0)
                            TVOsd.SetOSDRect(OSDPoint.X, OSDPoint.Y, bitmapOrigin.Width, bitmapOrigin.Height);
                        ShowTVOSD();
                    }
                    else
                    {
                        if (iPixelPointer == 0)
                            VGArect.Y = m_videoHeight / 3;
                        bupdated = true;
                    }
                    break;
                case 2:  //next 
                    iPixelPointer = -1;
                    fCount = 0;
                    break;
                case 3:  //finaly 
                    iAveScore = CurTone;
                    iPixelPointer = -1;                   
                    if (bTV)
                    {
                        TVOsd.CloseOSD();
                        TVOsd.SetOSDRect(OSDPoint.X, OSDPoint.Y, bitmapOrigin.Width, bitmapOrigin.Height);                    
                    }
                    else                    
                        VGArect.Y = m_videoHeight / 3;                                            
                    bupdated = true;
                    while (bTV && bupdated)
                    {
                        ShowTVOSD();                     
                    }
                    break;
            }                                                                     
        }
        public void UpdateFreq(ref int[] pintFreq, int MinFreq, int MaxFreq)
        {
            intFreq = pintFreq;
            intMinFreq = MinFreq;
            intMaxFreq = (MaxFreq / MinFreq < 2 ? MinFreq * 2 : MaxFreq);
        }
        private int IndexToGrade(int Freq)
        {
            int grade;
            if (Freq <= intMinFreq)
                grade = 1;
            else if (Freq >= intMaxFreq)
                grade = 6;
            else
                grade = (int)(Math.Log((float)Freq / intMinFreq, (float)intMaxFreq / intMinFreq) * 6) + 1;
            return bTV ? -grade : grade;
        }
        private int IndexToGradeO(int Freq)
        {           
            int grade;
            if (Freq < 240) grade = 1;
            else if (Freq >= 420) grade = 5;//else if (Freq >= 540) grade = 7;
            else
                grade = (Freq - 120) / 60;
            return bTV ? -grade : grade;
        }
        private void IniBmp()
        {           
            bitmapOrigin = new Bitmap(License.BaseDirectory + (Mode == 3 ? strOsdLine : strOsdNote));
            bmpADback = new Bitmap(License.BaseDirectory + strADBack);
            ADFont = new Font(FontFamily.GenericSerif, m_ADFontSize, GraphicsUnit.Pixel);            
            if (Mode == 2)//note
            {
                bitmapTone = new Bitmap(License.BaseDirectory + strOriTone);
                bitmapNewTone = new Bitmap(License.BaseDirectory + strNewTone);
                if (!bTV)
                {
                    bitmapTone.RotateFlip(RotateFlipType.RotateNoneFlipY);
                    bitmapNewTone.RotateFlip(RotateFlipType.RotateNoneFlipY);
                }
            }
            else
            {
                OriPen = new Pen(Color.White, 3);
                NewPen = new Pen(Color.Red, 3);
                if (Mode == 4)
                    GreenBrush = new SolidBrush(Color.FromArgb(0,255,0));
            }

            Bmprect = new Rectangle(0, 0, bitmapOrigin.Width, bitmapOrigin.Height);
            Top = 5;
            Height = bitmapOrigin.Height - 10;
            float angle;        
            if (bTV)
            {
                Bottom = bitmapOrigin.Height;
                angle = 270;                
            }
            else
            {
                bitmapOrigin.RotateFlip(RotateFlipType.RotateNoneFlipY);
                Bottom = 0;
                angle = 90;                
            }
           
            RedBrush = new LinearGradientBrush(Bmprect, Color.White, Color.Red, angle);                  
            if (Mode == 3) //dash
            {               
                LinePen = new Pen(RedBrush, 2);
                LinePen.DashStyle = DashStyle.Dash;
            }                    
        }
        private void UpdateBitmap()
        {
            Graphics g;
            if (nShowOSD == -1) //show ad
            {
                if (bitmapOverlay != null)
                    bitmapOverlay.Dispose();
                bitmapOverlay = (Bitmap)bmpADback.Clone();
            }
            else if (iPixelPointer <= 0 || Mode == 4 && nShowOSD == 1) //for BJL mode = 4
            {
                if (bitmapOverlay != null)
                    bitmapOverlay.Dispose();
                bitmapOverlay = (Bitmap)bitmapOrigin.Clone();
            }
            g = Graphics.FromImage(bitmapOverlay);
            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            if (nShowOSD == -1)
            {
                
                m_bOdd = !m_bOdd;
                g.DrawString(strAD.Substring(ADIndex), ADFont, RedBrush, 70 + (m_bOdd ? 0 : m_ADFontSize / 2 + 1), 20, StringFormat.GenericTypographic);                                
                if (!bTV)
                    bitmapOverlay.RotateFlip(RotateFlipType.RotateNoneFlipY);
                if (m_bOdd)
                {
                    if (strAD[ADIndex] <= byte.MaxValue)
                        m_bOdd = false;
                    ADIndex++;                   
                }
                bupdated = false;
            }
            else if (nShowOSD == 1)
            {
                int grade;
                Point p1 = new Point();//Left,Bottom + Height /7);
                Point p2 = new Point();//Left2, Bottom + Height / 7);
                int length = intFreq.Length;
                if (iPixelPointer == 0)
                {
                    yStep = Height / (float)length;
                    if (Mode == 4) iStep = 20;
                    else
                    {
                        iStep = (Left2 - Left) / (length - 1);//4/4
                        if (Mode == 3) iStep = iStep / 4 * 4;
                        if (iStep > 40) iStep = 40;
                    }
                    p1.X = Left;
                    for (int i = 0; i < length - 2; i++)
                    {
                        grade = IndexToGrade(intFreq[i]);
                        p1.Y = Bottom + 11 * grade;//p1.Y = Bottom + grade * Height / 7 - 10;                             
                        switch (Mode)
                        {
                            case 1://line
                            case 4:// roll
                                p2.X = p1.X + iStep;
                                p2.Y = p1.Y;
                                g.DrawLine(OriPen, p1, p2);
                                break;
                            case 2://note
                                p1.Y -= 10;
                                g.DrawImageUnscaled(bitmapTone, p1);
                                break;
                            case 3:
                                if (i > 0)
                                    g.DrawLine(OriPen, p1, p2);
                                p2 = p1;
                                break;                            
                        }
                        if (Mode == 4 && i >= 27)
                            break;
                        p1.X += iStep; 
                    }
                }
                else if (iPixelPointer < length - 1)  //iCurTone > 0 &&
                {
                    if (iCurScore >= AudioMatch.Grade)
                        iCurTone = intFreq[iPixelPointer - 1];
                    p1.X = Left + (iPixelPointer - 1) * iStep;
                    grade = IndexToGrade(iCurTone);
                    p1.Y = Bottom + 11 * grade;
                    switch (Mode)
                    {
                        case 1://line
                            p2.X = p1.X + iStep;
                            p2.Y = p1.Y;
                            g.DrawLine(NewPen, p1, p2);
                            break;
                        case 2://note
                            p1.Y -= 10;
                            g.DrawImageUnscaled(bitmapNewTone, p1);
                            break;
                        case 3:
                            if (iPixelPointer > 1)
                            {
                                for (int i = 0; i < iStep; i += 4)
                                {
                                    g.DrawLine(LinePen, LastPoint.X + i + 1, Bottom, LastPoint.X + i + 1, LastPoint.Y + (p1.Y - LastPoint.Y) * i / iStep);
                                }
                                g.DrawLine(NewPen, p1, LastPoint);
                            }
                            LastPoint = p1;
                            break;
                        case 4://roll                           
                            p1.X = Left;
                            for (int i = iPixelPointer - 1; i < length - 2; i++)
                            {
                                grade = IndexToGrade(intFreq[i]);
                                p1.Y = Bottom + 11 * grade;//p1.Y = Bottom + grade * Height / 7 - 10;                             
                                p2.X = p1.X + iStep;
                                p2.Y = p1.Y;
                                g.DrawLine(OriPen, p1, p2);
                                if (i - iPixelPointer >= 26)
                                    break;
                                p1.X += iStep;
                            }
                            // p1.X = Left;
                            grade = IndexToGrade(iCurTone);
                            int OriGrade = IndexToGrade(intFreq[iPixelPointer - 1]);
                            //p1.Y = Bottom + 11 * grade;
                            int angle = 12;
                            int startAngle = 0;
                            if (grade > OriGrade)
                                startAngle = angle * 2;
                            else if (grade == OriGrade)
                                startAngle = angle;
                            else
                                startAngle = 0;

                            g.FillPie(iCurScore >= AudioMatch.Grade ? GreenBrush : NewPen.Brush,
                                Left, Bottom + 11 * grade - 20 - (startAngle - angle ) /3, 40, 40, 180 - startAngle, angle * 2);
                            break;
                    }
                    if (iCurScore >= AudioMatch.Grade || Mode == 4)
                    {
                        if (iCurScore >= AudioMatch.Grade)
                            fCount += yStep;
                        if (bTV)
                            g.FillRectangle(RedBrush, Left2, Bottom - fCount, 20, fCount);
                        else
                            g.FillRectangle(RedBrush, Left2, Bottom, 20, fCount);
                    }
                }
                bupdated = false;
            }
            else if (nShowOSD == 3) 
            {
                if (iPixelPointer <= 0)
                {
                    /*   if (iPixelPointer == -1 && m_mediaType == MediaType.AnalogVideo)
                       {
                           RedBrush.Color = Color.FromArgb(MaxByte, MaxByte, 0, 0);
                           g.DrawString(strScore, ScoreFont, RedBrush, Left, Top, StringFormat.GenericTypographic);
                       }*/
                    RedBrush = new LinearGradientBrush(Bmprect, Color.White, Color.Red, 0f);
                    iPixelPointer += 2;
                }
                else if (iPixelPointer / 4 < iAveScore)
                {
                    g.FillRectangle(RedBrush, Left, Top, iPixelPointer, Height);
                    iPixelPointer += 10;
                }
                else
                {
                    if (!bTV)
                        bitmapOverlay.RotateFlip(RotateFlipType.RotateNoneFlipY);
                    Font ScoreFont = new Font(FontFamily.GenericSerif, 40);
                    g.DrawString(iAveScore.ToString("F02"), ScoreFont, RedBrush, Left + iPixelPointer, Top, StringFormat.GenericTypographic);
                    if (!bTV)
                        bitmapOverlay.RotateFlip(RotateFlipType.RotateNoneFlipY);
                    bupdated = false;
                }
            }
            g.Dispose();                    
        }

        public void Dispose()
        {           
           /* if (TVOsd != null)
            {
                TVOsd.Dispose();
                TVOsd = null;
            }*/            
            GC.Collect();
        }
        public void SaveSizeInfo(IPin pin)//,int SampleRate)
        {
           // iSampleRate = SampleRate;
            IniBmp();
            int hr;
            // Get the media type from the SampleGrabber
            AMMediaType media = new AMMediaType();
            hr = pin.ConnectionMediaType(media);            
            DsError.ThrowExceptionForHR(hr);
            VideoInfoHeader videoInfoHeader = (VideoInfoHeader)Marshal.PtrToStructure(media.formatPtr, typeof(VideoInfoHeader));            
            if (bTV)
            {
                int nY;
                if (videoInfoHeader.SrcRect.bottom % 240 == 0)   //             
                    nY = 240;  //480-240
                else
                    nY = 304;  //576-192-80        
                OSDPoint = new Point((720 - bitmapOrigin.Width) / 2,nY);
                TVOsd.CloseOSD();
                TVOsd.SetOSDRect(OSDPoint.X, 8, bitmapOrigin.Width, bitmapOrigin.Height);
                iBytesPixel = bitmapOrigin.PixelFormat == PixelFormat.Format24bppRgb ? 24 : 32;
            }
            else
            {                              
                m_videoWidth = videoInfoHeader.BmiHeader.Width;
                m_videoHeight = videoInfoHeader.BmiHeader.Height;
                m_stride = m_videoWidth * (videoInfoHeader.BmiHeader.BitCount / 8);
                int newWidth, newHeight;
                if (bitmapOrigin.Width > m_videoWidth)
                    newWidth = m_videoWidth;
                else
                    newWidth = bitmapOrigin.Width;
                if (480 > m_videoHeight)
                    newHeight = bitmapOrigin.Height / 2;
                else
                    newHeight = bitmapOrigin.Height;
                VGArect = new Rectangle((m_videoWidth - newWidth) / 2, m_videoHeight - newHeight, newWidth, newHeight);   
            }            
            
            DsUtils.FreeAMMediaType(media);
            media = null;
        }
        
        int ISampleGrabberCB.SampleCB(double SampleTime, IMediaSample pSample)
        {
            return 0;
        }

        /// <summary> buffer callback, COULD BE FROM FOREIGN THREAD. </summary>
        int ISampleGrabberCB.BufferCB(double SampleTime, IntPtr pBuffer, int BufferLen)
        {

            if (nShowOSD == 0)
                return 0;
            if (bupdated)
                UpdateBitmap();
            // create and copy the video's buffer image to a bitmap
            Bitmap v;
            v = new Bitmap(m_videoWidth, m_videoHeight, m_stride,
                System.Drawing.Imaging.PixelFormat.Format32bppArgb, pBuffer); 
            Graphics g = Graphics.FromImage(v);
            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
         
            g.DrawImage(bitmapOverlay, VGArect);
            // dispose of the various objects
            g.Dispose();
            v.Dispose();
            return 0;
        }
    }
}
