/////////////////////////////////////////////////////////////////////////////////////////
//
//  FILENAME    :   iundoc.h
//  DESCRIPTION :   This header file contains interfaces for internal use.
//
/////////////////////////////////////////////////////////////////////////////////////////
//	CHANGES		:	
//VG 10/30/2001 4:29:46 PM Created

#ifndef IUNDOC_INCLUDED
#define IUNDOC_INCLUDED

DEFINE_GUID(IID_IRmMapMem,0x9CB7F9A8,0x0AE5,0x4a2c,0x99,0xDB,0x9B,0x4D,0x58,0x96,0x7B,0x45);

EXTERN_C const IID IID_IRmMapMem;

MIDL_INTERFACE("9CB7F9A8-0AE5-4a2c-99DB-9B4D58967B45")
IRmMapMem : public IUnknown
{
public:
    virtual HRESULT STDMETHODCALLTYPE GetDeviceBase(PVOID *pAddr) = 0;
    virtual HRESULT STDMETHODCALLTYPE FreeDeviceBase() = 0;
	virtual	HRESULT STDMETHODCALLTYPE GetDMABuffer(
							ULONG size, 
							void ** pLinearAddr, 
							void ** pPhysicalAddr) = 0;	
	virtual	HRESULT STDMETHODCALLTYPE FreeDMABuffer(void * LinearAddr) = 0;
};

#endif