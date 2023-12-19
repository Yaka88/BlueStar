using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using QuartzTypeLib;

namespace BlueStar
{    
    [ClassInterface(ClassInterfaceType.AutoDual)]
    public class Player 
    {
       // private IGraphBuilder graphBuilder = null;
        private IMediaControl mediaControl = null;
        private IMediaEventEx mediaEventEx = null;
        private IBasicAudio basicAudio = null;
      //  private IBasicVideo basicVideo = null;
        private IVideoWindow videoWin = null;
        private IMediaPosition mediaPosition = null;
      
        private IFilterInfo pSourceFilter = null;
      //  private IFilterInfo pAVISplitter = null;
        private IFilterInfo pXCARDFilter = null;
      //  private IFilterInfo pMP3Filter = null;
      //  private IFilterInfo pSPCMFilter = null;
      //  private IFilterInfo pVidRenderer = null;
        IAMCollection pCollection = null;

        private enum WindowStyle
        {
            Popup = -2147483648,
            Overlapped = 0,
            TabStop = 65536,
            MaximizeBox = 65536,
            MinimizeBox = 131072,
            Group = 131072,
            ThickFrame = 262144,
            SysMenu = 524288,
            HScroll = 1048576,
            VScroll = 2097152,
            DlgFrame = 4194304,
            Border = 8388608,
            Caption = 12582912,
            Maximize = 16777216,
            ClipChildren = 33554432,
            ClipSiblings = 67108864,
            Disabled = 134217728,
            Visible = 268435456,
            Minimize = 536870912,
            Child = 1073741824,
        }

        private const string strAVISplitter = "Sigma Designs AVI Splitter";
        private const string strXCARDFilter = "Sigma Designs MPEG-2 hardware decoder";
        private const string strSPCMFilter = "Sigma Designs PCM Swapper";
        private const string strMP3Filter = "MPEG Layer-3 Decoder";
       
        private string strfilename = string.Empty;
 

        private void AppendFilter(string strFilterName, out IFilterInfo pFilter, IMediaControl mc)    
        {

            object oFilter=null,oRegFilter=null;
            IRegFilterInfo pRegFilter = null;
            
            for (int i = 0; i < pCollection.Count ; i++)
            {
                pCollection.Item(i, out oRegFilter);
                pRegFilter = (IRegFilterInfo)oRegFilter;
                if (pRegFilter.Name == strFilterName)
                {
                    pRegFilter.Filter(out oFilter);
                    break;
                }                              
            }
            pFilter = (IFilterInfo)oFilter;
        }
        public Player()
        {
        }
        public bool Initialize(string FileName)
        {
            PlayVod(FileName);
            return true;
        }
        private void PlayVod(string FileName)
        {
            object oSourceFilter = null;
            IPinInfo pOutPin = null;
            object oPin = null;

            strfilename = FileName;
          
           // graphBuilder = (IGraphBuilder)new FilterGraph();
            mediaControl = (IMediaControl)new FilgraphManagerClass();            
            mediaPosition = mediaControl as IMediaPosition;
            basicAudio = mediaControl as IBasicAudio;            

            mediaControl.AddSourceFilter(strfilename, out oSourceFilter);            
            pSourceFilter = (IFilterInfo)oSourceFilter;

            pCollection = (IAMCollection) mediaControl.RegFilterCollection;
          
          //  AppendFilter(strAVISplitter, out pAVISplitter, mediaControl);
          //  AppendFilter(strXCARDFilter, out pXCARDFilter, mediaControl);
          //  AppendFilter(strSPCMFilter, out pSPCMFilter, mediaControl);
           // AppendFilter(strMP3Filter, out pMP3Filter, mediaControl);
         
            pSourceFilter.FindPin("Output", out oPin);
            
            pOutPin = (IPinInfo)oPin;
            pOutPin.Render();
                             
            basicAudio.Volume = 0;
        }        
        public Player(string FileName)
        {
            PlayVod(FileName);
        }

        public void SetNotifyWindow(int hwnd, int IMsg)
        {           
            mediaEventEx = mediaControl as IMediaEventEx;
            mediaEventEx.SetNotifyWindow(hwnd, IMsg, 0);        
        }
        public void SetOwner(int hPanel, int width, int height)
        {
            videoWin = mediaControl as IVideoWindow;        
           // videoWin.AutoShow = Visible ? -1 : 0;  
            try
            {
                if (hPanel == 0)
                    videoWin.AutoShow = 0;
                else
                {
                    videoWin.AutoShow = -1;
                    videoWin.Owner = hPanel;
                    videoWin.WindowStyle = (int)(WindowStyle.Child | WindowStyle.ClipChildren | WindowStyle.ClipSiblings);
                    //   Rectangle rc = hWin.ClientRectangle;
                    videoWin.SetWindowPosition(0, 0, width, height);
                }
            }
            catch (Exception)
            { }
        }
        public bool Complete()
        {         
            int evCode;
            int evParam1, evParam2;
          
            if (mediaEventEx == null)
                return true;            
            // Process all queued events
            while (true)                
            {
                try
                {
                    mediaEventEx.GetEvent(out evCode, out evParam1, out evParam2, 0);
                    mediaEventEx.FreeEventParams(evCode, evParam1, evParam2);
                    if (evCode == 1 || evCode == 2)
                    {
                        return true;
                    }
                }
                catch (Exception)
                {
                    if (CurrentPosition >= mediaPosition.Duration)
                        return true;
                    else
                        return false;
                }                       
            }      
        }
        public double CurrentPosition
        {
            get
            {
                return mediaPosition.CurrentPosition;
            }
            set
            {
                mediaPosition.CurrentPosition = value;
            }
        }
        public int Volume
        {
            set
            {
                int intVol = 1 - (int)Math.Pow(10, ((double)100 - value) / 25);
                basicAudio.Volume = intVol;
            }
        }
        public int Balance
        {           
            set
            {                
                basicAudio.Balance = value * 10000;
            }
        }       
        public void Start()
        {          
            mediaControl.Run();
        }
        public void Pause()
        {
            mediaControl.Pause();
        }
        public void Stop()
        {
            mediaControl.Stop();            
            
            pSourceFilter = null;
         //   pAVISplitter = null;
            pXCARDFilter = null;
         //   pMP3Filter = null;
         //   pSPCMFilter = null;

            pCollection = null;
            videoWin = null;
            basicAudio = null;
            mediaControl = null;
            mediaPosition = null;
            if (mediaEventEx != null)
            {
                mediaEventEx.SetNotifyWindow(0, 0, 0);
                mediaEventEx = null;
            }
            GC.Collect();
        }
        public void Cut()
        {
            Stop();
        }

    }
}
