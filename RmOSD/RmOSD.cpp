// RmOSD.cpp : Defines the exported functions for the DLL application.
#include "stdafx.h"
#include "RmOSD.h"

#include <stdlib.h>
#include <Shlwapi.h>

BYTE PalYUV[1024] = 
{
0, 16, 128, 128,   //black 0, (0 ,0,0)
0xFF, 20, 150, 124, 
0xFF, 25, 172, 120, 
0xFF, 30, 195, 117, 
0xFF, 35, 217, 113, 
0xFF, 40, 239, 109, 
0xFF, 41, 113, 109, 
0xFF, 46, 135, 105, 
0xFF, 51, 157, 101, 
0xFF, 56, 180, 98, 
0xFF, 61, 202, 94, 
0xFF, 66, 225, 91, 
0xFF, 67, 98, 90, 
0xFF, 72, 120, 86, 
0xFF, 77, 143, 83, 
0xFF, 82, 165, 79, 
0xFF, 87, 187, 75, 
0xFF, 92, 210, 72, 
0xFF, 93, 83, 71, 
0xFF, 98, 105, 68, 
0xFF, 103, 128, 64, 
0xFF, 108, 150, 60, 
0xFF, 113, 173, 57, 
0xFF, 118, 195, 53, 
0xFF, 118, 68, 52, 
0xFF, 123, 91, 49, 
0xFF, 128, 113, 45, 
0xFF, 133, 135, 42, 
0xFF, 138, 158, 38, 
0xFF, 143, 180, 34, 
0xFF, 144, 53, 34, 
0xFF, 149, 76, 30,		//31  绿色音符  （0，255，64）
0xFF, 154, 98, 26, 
0xFF, 159, 120, 23, 
0xFF, 164, 143, 19, 
0xFF, 169, 165, 16, 
0xFF, 29, 120, 150, 
0xFF, 34, 142, 146, 
0xFF, 39, 165, 143, 
0xFF, 44, 187, 139, 
0xFF, 49, 210, 135, 
0xFF, 54, 232, 132, 
0xFF, 54, 105, 131, 
0x50, 59, 128, 128,    //43   黑线  80,(51,51,51)
0xFF, 64, 150, 124, 
0xFF, 69, 172, 120, 
0xFF, 74, 195, 117, 
0xFF, 79, 217, 113, 
0xFF, 80, 90, 112, 
0xFF, 85, 113, 109, 
0xFF, 90, 135, 105, 
0xFF, 95, 157, 101, 
0xFF, 100, 180, 98, 
0xFF, 105, 202, 94, 
0xFF, 106, 75, 94, 
0xFF, 111, 98, 90, 
0xFF, 116, 120, 86, 
0xFF, 121, 143, 83, 
0xFF, 126, 165, 79, 
0xFF, 131, 187, 75, 
0xFF, 131, 61, 75, 
0xFF, 136, 83, 71, 
0xFF, 141, 105, 68, 
0xFF, 146, 128, 64, 
0xFF, 151, 150, 60, 
0xFF, 156, 173, 57, 
0xFF, 157, 46, 56, 
0xFF, 162, 68, 52, 
0xFF, 167, 91, 49, 
0xFF, 172, 113, 45, 
0xFF, 177, 135, 42, 
0xFF, 182, 158, 38, 
0xFF, 42, 112, 172, 
0xFF, 47, 135, 169, 
0xFF, 52, 157, 165, 
0xFF, 57, 180, 161, 
0xFF, 62, 202, 158, 
0xFF, 67, 224, 154, 
0xFF, 67, 98, 154, 
0xFF, 72, 120, 150,  
0xFF, 77, 142, 146, 
0xFF, 82, 165, 143, 
0xFF, 87, 187, 139, 
0xFF, 92, 210, 135, 
0xFF, 93, 83, 135, 
0xFF, 98, 105, 131, 
0xFF, 103, 128, 128, 
0xFF, 108, 150, 124, 
0xFF, 113, 172, 120, 
0xFF, 118, 195, 117, 
0xFF, 119, 68, 116, 
0xFF, 124, 90, 112, 
0xFF, 129, 113, 109, 
0xFF, 134, 135, 105, 
0xFF, 139, 157, 101, 
0xFF, 144, 180, 98, 
0xFF, 145, 53, 97, 
0xFF, 150, 75, 94, 
0xFF, 155, 98, 90, 
0xFF, 160, 120, 86, 
0xFF, 165, 143, 83, 
0xFF, 170, 165, 79, 
0xFF, 170, 38, 78, 
0xFF, 175, 61, 75, 
0xFF, 180, 83, 71, 
0xFF, 185, 105, 68, 
0xFF, 190, 128, 64, 
0xFF, 195, 150, 60, 
0xFF, 55, 105, 195, 
0xFF, 60, 127, 191, 
0xFF, 65, 150, 187, 
0xFF, 70, 172, 184, 
0xFF, 75, 194, 180, 
0xFF, 80, 217, 177, 
0xFF, 81, 90, 176, 
0xFF, 86, 112, 172, 
0xFF, 91, 135, 169, 
0xFF, 96, 157, 165, 
0xFF, 101, 180, 161, 
0xFF, 106, 202, 158, 
0xFF, 106, 75, 157, 
0xFF, 111, 98, 154, 
0xFF, 116, 120, 150, 
0xFF, 121, 142, 146, 
0xFF, 126, 165, 143, 
0xFF, 131, 187, 139, 
0xFF, 132, 60, 138, 
0xFF, 137, 83, 135, 
0xFF, 142, 105, 131, 
0xFF, 147, 128, 128, 
0xFF, 152, 150, 124, 
0xFF, 157, 172, 120, 
0xFF, 158, 45, 120, 
0xFF, 163, 68, 116, 
0xFF, 168, 90, 112, 
0xFF, 173, 113, 109, 
0xFF, 178, 135, 105,    //  136  天蓝 //lightblue （153，217,234)
0xFF, 183, 157, 101,  
0xFF, 183, 31, 101, 
0xFF, 188, 53, 97, 
0xFF, 193, 75, 94, 
0xFF, 198, 98, 90, 
0xFF, 203, 120, 86, 
0xFF, 208, 143, 83, 
0xFF, 68, 97, 217, 
0xFF, 73, 120, 213, 
0xFF, 78, 142, 210, 
0xFF, 83, 164, 206, 
0xFF, 88, 187, 203, 
0xFF, 93, 209, 199, 
0xFF, 94, 82, 198, 
0xFF, 99, 105, 195, 
0xFF, 104, 127, 191, 
0xFF, 109, 150, 187, 
0xFF, 114, 172, 184, 
0xFF, 119, 194, 180, 
0xFF, 119, 68, 180, 
0xFF, 124, 90, 176, 
0xFF, 129, 112, 172, 
0xFF, 134, 135, 169, 
0xFF, 139, 157, 165, 
0xFF, 144, 180, 161, 
0xFF, 145, 53, 161, 
0xFF, 150, 75, 157, 
0xFF, 155, 98, 154, 
0xFF, 160, 120, 150, 
0xFF, 165, 142, 146, 
0xFF, 170, 165, 143, 
0xFF, 171, 38, 142, 
0xFF, 176, 60, 138, 
0xFF, 181, 83, 135, 
0xFF, 186, 105, 131, 
0xFF, 191, 128, 128, 
0xFF, 196, 150, 124, 
0xFF, 196, 23, 123, 
0xFF, 201, 45, 120, 
0xFF, 206, 68, 116, 
0xFF, 211, 90, 112, 
0xFF, 216, 113, 109, 
0xFF, 221, 135, 105,    
255, 81, 90, 239,		//180 (255,0,0)红色
0xFF, 86, 112, 236, 
255, 91, 135, 232,      //182  粉红色音符  （255，0，128） 
0xFF, 96, 157, 229, 
0xFF, 101, 179, 225, 
0xFF, 106, 202, 221, 
0xFF, 107, 75, 221,		
255, 112, 97, 217,   //187 (255,51,51)	  
0xFF, 117, 120, 213, 
0xFF, 122, 142, 210, 
0xFF, 127, 164, 206, 
0xFF, 132, 187, 203, 
255, 132, 60, 202,   //192 (255,127,39) //橙色
0xFF, 137, 82, 198, 
255, 142, 105, 195,  //194 (255,102,102)	  
0xFF, 147, 127, 191, 
0xFF, 152, 150, 187, 
0xFF, 157, 172, 184, 
0xFF, 158, 45, 183, 
0xFF, 163, 68, 180, 
0xFF, 168, 90, 176, 
255, 173, 112, 172,   //201 (255,153,153)	  
0xFF, 178, 135, 169, 
0xFF, 183, 157, 165, 
0xFF, 184, 30, 164, 
0xFF, 189, 53, 161, 
0xFF, 194, 75, 157, 
0xFF, 199, 98, 154, 
255, 204, 120, 150,   //218 (255,204,204)
0xFF, 209, 142, 146, 
0xFF, 210, 16, 146, 
0xFF, 215, 38, 142, 
0xFF, 220, 60, 138, 
0xFF, 225, 83, 135, 
0xFF, 230, 105, 131, 
0xFF, 235, 128, 128,   //215   （255，255，255）白色
0xFF, 180, 128, 128, 
0xFF, 125, 128, 128, 
0xFF, 48, 109, 184, 
0xFF, 80, 90, 80, 
0xFF, 28, 184, 118, 
0xFF, 113, 71, 137, 
0xFF, 61, 165, 175, 
0xFF, 93, 146, 71, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128, 
0xFF, 235, 128, 128};

/*
BYTE pPalRgb[1024];
		
			int j = 0;
		 for(int i=0;i<216;i++)
		 {
			 pPalRgb[j++] = i%6 * 0x33; // bitmap.Palette->Entries[i].B;
			 pPalRgb[j++] = (i/6) % 6 * 0x33;// bitmap.Palette->Entries[i].G;
			 pPalRgb[j++] = i/36 * 0x33;// bitmap.Palette->Entries[i].R;
			 pPalRgb[j++] = 255;//bitmap.Palette->Entries[i].A;
		 }
		pPalRgb[864] = 0xc0;
		pPalRgb[865] = 0xc0;
		pPalRgb[866] = 0xc0;
		pPalRgb[867] = 0xff;

		pPalRgb[868] = 0x80;
		pPalRgb[869] = 0x80;
		pPalRgb[870] = 0x80;
		pPalRgb[871] = 0xff;

		pPalRgb[872] = 0x00;
		pPalRgb[873] = 0x00;
		pPalRgb[874] = 0x80;
		pPalRgb[875] = 0xff;

		pPalRgb[876] = 0x00;
		pPalRgb[877] = 0x80;
		pPalRgb[878] = 0x00;
		pPalRgb[879] = 0xff;

		pPalRgb[880] = 0x80;
		pPalRgb[881] = 0x00;
		pPalRgb[882] = 0x00;
		pPalRgb[883] = 0xff;

		pPalRgb[884] = 0x00;
		pPalRgb[885] = 0x80;
		pPalRgb[886] = 0x80;
		pPalRgb[887] = 0xff;

		pPalRgb[888] = 0x80;
		pPalRgb[889] = 0x00;
		pPalRgb[890] = 0x80;
		pPalRgb[891] = 0xff;

		pPalRgb[892] = 0x80;
		pPalRgb[893] = 0x80;
		pPalRgb[894] = 0x00;
		pPalRgb[895] = 0xff;

		 for(int i=896;i<1024;i++)
		 {
			 pPalRgb[i] = 0xff; // bitmap.Palette->Entries[i].B;			
		 }
		 */
// This is the constructor of a class that has been exported.
// see RmOSD.h for the class definition
BlueStar::CRmOSD::CRmOSD(License ^%lic)
{	
	IsInitialized = false;
	if (lic == nullptr)
	{
		lic = gcnew License();
	}
	if (!lic->isValid) return;
	
	CoInitialize(NULL);	

	IRmObjectFinder *pIRmObjectFinder;
	hr = CoCreateInstance(CLSID_RMBASE,NULL,CLSCTX_INPROC_SERVER,IID_IRmObjectFinder,(void**)&pIRmObjectFinder);	
	if (FAILED(hr))	return;	
	// GET OSD		
	pin_ptr<IRmStream *> pin_pOSD = &pOSD;	
	hr = pIRmObjectFinder->FindObject(NULL,FIRST_AVALIABLE_INSTANCE,CATEGORY_PIN_OSD,IID_IRmStream,(void**)pin_pOSD);	
	pIRmObjectFinder->Release();
	if (FAILED(hr))
	{		
		UnInitOSD();
		return;
	}					
	pOSD->Reset();	
	
	pDevice = NULL;	
	pin_ptr<IRmControlNode *> pin_pDevice = &pDevice;
	hr = pOSD->QueryInterface(IID_IRmControlNode,(void**)pin_pDevice);
	if (FAILED(hr)) 
	{
		UnInitOSD();
		return;
	}

	pin_ptr<IRmMapMem *> pin_pMemAlloc = &pMemAlloc;
	hr = pOSD->QueryInterface(IID_IRmMapMem,(void**)pin_pMemAlloc);	
	if (FAILED(hr)) 
	{
		UnInitOSD();
		return;
	}
	
	// switch to TV
	long dwTvOutKeep,dwTvOut;
	RMint32 HwLibVersion;	
	pDevice->GetAttributes(MpegAttrCodeVersion,&HwLibVersion);
	pDevice->GetAttributes(MpegAttrVideoTv,&dwTvOutKeep);
	dwTvOut = dwTvOutKeep & ~OUTPUT_OFF;
	
	if (HwLibVersion < 9)
	{
		dwTvOut |= SET_TV;
	}
	else
	{
		dwTvOut |= SET_TV | 0x80000000;
		dwTvOut &= ~SET_HDTV; 
	}
	pDevice->SetAttributes(MpegAttrVideoTv,dwTvOut);
    IsInitialized=true;		
	return;
}


BlueStar::CRmOSD::~CRmOSD()
{
	UnInitOSD();
}
bool BlueStar::CRmOSD::SetOSDRect(int nX,int nY,int nWidth,int nHeight)
{	
	if (!IsInitialized) return false;	
	MPEG_OVERLAY_RECT rc_dest = {nX,nY,nWidth,nHeight};
	pDevice->SetAttributes(MpegAttrOsdDest,(long)&rc_dest);
	return true;
}
bool BlueStar::CRmOSD::SetOSDSize(int nX,int nY,int nWidth,int nHeight)
{		
	if (SetOSDRect(nX,nY,nWidth,nHeight) == false) return false;
	long PalEntries =  sizeof(RGBQUAD) * 256;
	bmpSize = nWidth * nHeight;
	size = bmpSize + PalEntries + 8;
	PVOID	phys;
	PVOID pin_shared;
	hr = pMemAlloc->GetDMABuffer(size,(void**)&pin_shared,&phys);
	pshared = (PBYTE)pin_shared;
	//pshared =(PUCHAR)malloc(size);
	if (pshared == NULL) return false;
		
	BYTE* pointer = (BYTE*)pshared;
	BYTE b = 0x3e;
	*pointer++ = b;			
	b = (BYTE)(size >> 16);
	*pointer++ = b;	
	b = (BYTE)(size >> 8);
	*pointer++ = b;			
	b = (BYTE)(size >> 0);
	*pointer++ = b;			
	// write width
	b = (BYTE)(nWidth >> 8);
	*pointer++ = b;	
	b = (BYTE)(nWidth >> 0);
	*pointer++ = b;	
	// write height
	b = (BYTE)(nHeight >> 8);
	*pointer++ = b;	
	b = (BYTE)(nHeight >> 0);
	*pointer++ = b;	

	CopyMemory(pointer,PalYUV,PalEntries);
	pBmp = pointer + PalEntries;

	p_hdr = new HEADER;	
	ZeroMemory(p_hdr,sizeof(HEADER));
			
	p_hdr->multi.Count = 1;
	p_hdr->multi.Size  = sizeof(HEADER);
	p_hdr->header.Size = sizeof(RMSTREAM_HEADER);
	p_hdr->header.pData = pshared;
	p_hdr->header.FrameExtent = size;

	return true;

}
bool BlueStar::CRmOSD::LoadHBitmap(int nBitsPixel,LPVOID lpBits)
{
	//关闭以前的文件显示
	//CloseOSDFile();
	if (!IsInitialized) return false;
	
	BYTE* pointer = pBmp;
	BYTE* lpBmpData = (BYTE*)lpBits;
 		
	switch (nBitsPixel)
	{
	case 32:
		for(UINT i = 0;i < bmpSize;i++)
		{
			*pointer++=  lpBmpData[0]/0x33  + lpBmpData[1]/0x33 * 6 + lpBmpData[2]/0x33 * 36; //255,0,0,51  
			lpBmpData += 4;
		}
		break;
	case 24:	
		for(UINT i = 0;i < bmpSize;i++)
		{
			*pointer++=  lpBmpData[0]/0x33  + lpBmpData[1]/0x33 * 6 + lpBmpData[2]/0x33 * 36; //255,0,0,51  
			lpBmpData += 3;
		}
		break;
	case 8:					
		CopyMemory(pBmp,(BYTE *)lpBits,bmpSize);
		//bmp8_reverse (pRgb, bmih.biWidth, bmih.biHeight);	// reverse the data (bmp is stored upside-down)
		break;		
	default:
		break;
	}
	   
	pOSD->Play();			
	
	RMOVERLAPIO ovr = {0,0,0,0,CreateEvent(NULL,TRUE,FALSE,NULL)};
	// Send whole bitmap down
//	pOSD->Write(&hdr.multi,&ovr);
	pOSD->Write(&p_hdr->multi,&ovr);
	
	// Wait for completion
	long ret = WaitForSingleObject(ovr.hEvent,10000);
	
	if (ret == WAIT_TIMEOUT)
	{
		return false;
	}
	
	CloseHandle(ovr.hEvent);

	pDevice->SetAttributes(MpegAttrOsdON,1);
	
	pOSD->Stop();	
    m_bShowOSD=true;	
	return true;
}

bool BlueStar::CRmOSD::CloseOSD()
{
	m_bShowOSD= false;
	if (NULL != pDevice) 
    	pDevice->SetAttributes(MpegAttrOsdOFF,1);	
	return true;
}

bool BlueStar::CRmOSD::UnInitOSD()
{	
	CloseOSD();
	if (pshared != NULL)
	{
		pMemAlloc->FreeDMABuffer(pshared);		
		pshared=NULL;
	}	
	if (p_hdr != NULL)
	{
		delete p_hdr;
		p_hdr = NULL;
	}
	if (pMemAlloc!= NULL )
	{
		pMemAlloc->Release();
		pMemAlloc=NULL;
	}	
	if (pDevice!= NULL )
	{
		pDevice->Release();
		pDevice=NULL;
	}		
	if (pOSD!= NULL )
	{
		pOSD->Release();
		pOSD=NULL;
	}	
	CoUninitialize();	
	return true;
}