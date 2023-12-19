// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the RMOSD_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// RMOSD_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#include ".\\Inc\\mpegcmn.h"
#include ".\\Inc\\irminc.h"

typedef struct 
{
	RMMULTIPLE_ITEM		multi;
	RMSTREAM_HEADER		header;
}HEADER,*PHEADER;

namespace BlueStar
{
	// This class is exported from the RmOSD.dll
	//public class RMOSD_API CRmOSD {
	public ref class CRmOSD {
	public:
		CRmOSD(License ^%lic);
		~CRmOSD();
		//bool IsValid();
		//bool SetOsdFile(); 
		bool LoadHBitmap(int nBitsPixel,LPVOID lpBits);
		bool SetOSDSize(int nX,int nY,int nWidth,int nHeight);
		bool SetOSDRect(int nX,int nY,int nWidth,int nHeight);
		bool CloseOSD();		
		
		// TODO: add your methods here.
		private:
			HRESULT	hr;
			//FILE	*fOsdFile;

			IRmStream		* pOSD;
			IRmControlNode	* pDevice;
			IRmMapMem		* pMemAlloc;	
			
			PUCHAR	pshared;
			BYTE* pBmp;
			UINT size,bmpSize;
			PHEADER p_hdr;

			bool m_bShowOSD;				
			bool UnInitOSD();	
			bool IsInitialized;
	};

}