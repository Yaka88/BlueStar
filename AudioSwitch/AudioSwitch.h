// AudioSwitch.h

#pragma once
namespace BlueStar
{
	public class CAudioSwitchInputPin : public CTransInPlaceInputPin
	{
	public:
		CAudioSwitchInputPin( TCHAR *pObjectName
                            , CTransInPlaceFilter *pTransInPlaceFilter
                            , HRESULT * phr
                            , LPCWSTR pName)
                            : CTransInPlaceInputPin( pObjectName
                                                     , pTransInPlaceFilter
                                                     , phr
                                                     , pName)                                               
		{}
		STDMETHODIMP Receive(IMediaSample * pSample);
	};

	public class CAudioSwitch : public CTransInPlaceFilter
	{
		friend class CAudioSwitchInputPin;     
	public:
		HRESULT CheckInputType(const CMediaType *pmt);
		static CUnknown * WINAPI CreateInstance(LPUNKNOWN punk, HRESULT *phr);		
		  // CTransInPlaceFilter Overrides 
		virtual int GetPinCount();
        virtual CBasePin *GetPin( int n );
		CAudioSwitchInputPin * m_pTrackPin0;
		CAudioSwitchInputPin * m_pTrackPin1;
		//IMediaSample * pSample1;
		int Balance;  //-1 ,1

	//	STDMETHODIMP Count(DWORD* pcStreams);
	//	STDMETHODIMP Enable(long lIndex, DWORD dwFlags); 
	//	STDMETHODIMP Info(long lIndex, AM_MEDIA_TYPE** ppmt, DWORD* pdwFlags, LCID* plcid, DWORD* pdwGroup, WCHAR** ppszName, IUnknown** ppObject, IUnknown** ppUnk);

		STDMETHODIMP FindPin(LPCWSTR Id, IPin **ppPin) 
			{
				if (lstrcmpW(Id,L"1") == 0)					
					Balance = 1;
				else 
					Balance = -1;
				return CBaseFilter::FindPin(Id, ppPin);
			};
		
	private:
		CAudioSwitch(TCHAR *tszName, LPUNKNOWN punk, HRESULT *phr);
		~CAudioSwitch();		  
        HRESULT Transform(IMediaSample *pSample);
	};
}
