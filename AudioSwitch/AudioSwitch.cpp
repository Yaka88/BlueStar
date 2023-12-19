// This is the main DLL file.

#include "stdafx.h"
#include <initguid.h>
#include <streams.h>
#include "AudioSwitch.h"

// {2583025B-F1AD-46A1-91F3-314B8C2AAC28}
DEFINE_GUID(CLSID_AudioSwitch, 
0x2583025b, 0xf1ad, 0x46a1, 0x91, 0xf3, 0x31, 0x4b, 0x8c, 0x2a, 0xac, 0x28);

static WCHAR g_wszName[] = L"BlueLaser AudioSwitcher";
	

HRESULT BlueStar::CAudioSwitchInputPin::Receive(IMediaSample * pSample)
{
	CAudioSwitch *pSwitcher = (CAudioSwitch *) m_pTIPFilter;
	HRESULT hr = S_OK;
	if (pSwitcher->m_pInput == this)
	{
		CAutoLock lck(&pSwitcher->m_csReceive);
		ASSERT(pSample);	
		// check all is well with the base class
		hr = CBaseInputPin::Receive(pSample);
		if (S_OK == hr) {
			// send the sample to our filter
			hr = pSwitcher->Receive(pSample);
		}	
	}
	else
	{
		CAutoLock lck(&pSwitcher->m_csReceive);
		ASSERT(pSample);	
		// check all is well with the base class
		hr = CBaseInputPin::Receive(pSample);
	}
	return hr;
}

BlueStar::CAudioSwitch::CAudioSwitch(TCHAR *tszName, LPUNKNOWN punk, HRESULT *phr)
	:CTransInPlaceFilter (tszName, punk, CLSID_AudioSwitch, phr)
{
	Balance = -1;
}
BlueStar::CAudioSwitch::~CAudioSwitch()
{
	 delete m_pTrackPin0;
	 delete m_pTrackPin1;
}
HRESULT BlueStar::CAudioSwitch::CheckInputType(const CMediaType *pmt)
{
	if (pmt->majortype == MEDIATYPE_Audio &&
		pmt->subtype == MEDIASUBTYPE_PCM && 
		pmt->formattype == FORMAT_WaveFormatEx)
        return S_OK;
	else
        return VFW_E_TYPE_NOT_ACCEPTED;
}
HRESULT BlueStar::CAudioSwitch::Transform(IMediaSample *pSample)
{	
	if (Balance == 1)
	{
		IMediaSample *pSample1;
		IMemAllocator *ppAllocator;
		LONGLONG pTimeStart,pTimeEnd;
		pSample->GetTime(&pTimeStart,&pTimeEnd); 
		m_pTrackPin1->GetAllocator(&ppAllocator);
		ppAllocator->GetBuffer(&pSample1,&pTimeStart,&pTimeEnd,0);
		BYTE *ppBuffer,*ppBuffer1;
		pSample->GetPointer(&ppBuffer);
		pSample1->GetPointer(&ppBuffer1);
		memcpy(ppBuffer,ppBuffer1,pSample->GetSize());
		pSample1->Release();
	}
	return S_OK;
}

int BlueStar::CAudioSwitch::GetPinCount()
{	
    return 3;
}

CBasePin *BlueStar::CAudioSwitch::GetPin(int n)
{
    HRESULT hr = S_OK;
    // Create an input pin if not already done
    if (m_pOutput == NULL) {
        m_pTrackPin0 = new CAudioSwitchInputPin(g_wszName
                                            , this        // Owner filter
                                            , &hr         // Result code
                                            , L"Track0"    // Pin name
                                            );
		m_pTrackPin1 = new CAudioSwitchInputPin(g_wszName
                                            , this        // Owner filter
                                            , &hr         // Result code
                                            , L"Track1"    // Pin name
                                            );
		m_pOutput = new CTransInPlaceOutputPin( g_wszName
                                              , this       // Owner filter
                                              , &hr        // Result code
                                              , L"Output"  // Pin name
                                              );
		m_pInput = m_pTrackPin0;
        // Constructor for CTransInPlaceInputPin can't fail
        ASSERT(SUCCEEDED(hr));
    } 
    // Return the appropriate pin
    ASSERT (n>=0 && n<=2);
    if (n == 0) {
        return m_pTrackPin0;
    } else if (n==1) {
        return m_pOutput;
    } else if (n==2) {
		return m_pTrackPin1;
	} else{		
        return NULL;
	}

} // GetPin

CUnknown * WINAPI BlueStar::CAudioSwitch::CreateInstance(LPUNKNOWN punk, HRESULT *phr)
{

	CAudioSwitch *pNewObject = new CAudioSwitch(g_wszName, punk, phr );
    if (pNewObject == NULL) {
        *phr = E_OUTOFMEMORY;
    }
    return pNewObject;

} // CreateInstance
const AMOVIESETUP_MEDIATYPE
sudPinTypes =   { &MEDIATYPE_Audio              // clsMajorType
				, &MEDIASUBTYPE_PCM  }  ;       // clsMinorType

const AMOVIESETUP_PIN
psudPins[] = {{ 0 , FALSE               // bRendered
               , FALSE               // bOutput
               , FALSE               // bZero
               , TRUE		         // bMany
               , 0,0, 1                   // nTypes
               , &sudPinTypes }
			, { 0 , FALSE               // bRendered
               , TRUE                // bOutput
               , FALSE               // bZero
               , FALSE               // bMany
               , 0,0, 1                   // nTypes
               , &sudPinTypes }
			};   // lpTypes

const AMOVIESETUP_FILTER
sudSwitcherIP = { &CLSID_AudioSwitch                 // clsID
            , g_wszName                // strName            
			, MERIT_PREFERRED			  // dwMerit			//for test
            , 2                               // nPins
            , psudPins };                     // lpPin
//
// Needed for the CreateInstance mechanism
//
CFactoryTemplate g_Templates[]=
    {
		{g_wszName,
         &CLSID_AudioSwitch,
         BlueStar::CAudioSwitch::CreateInstance,
         NULL,
         &sudSwitcherIP 
		}
    };
int g_cTemplates = sizeof(g_Templates)/sizeof(g_Templates[0]);

STDAPI DllRegisterServer()
{
    return AMovieDllRegisterServer2( TRUE );
}
STDAPI DllUnregisterServer()
{
    return AMovieDllRegisterServer2( FALSE );
}

/*
extern "C" BOOL WINAPI DllEntryPoint(HINSTANCE, ULONG, LPVOID);

BOOL APIENTRY DllMain(HANDLE hModule, 
                      DWORD  dwReason, 
                      LPVOID lpReserved)
{
	return DllEntryPoint((HINSTANCE)(hModule), dwReason, lpReserved);
}
*/