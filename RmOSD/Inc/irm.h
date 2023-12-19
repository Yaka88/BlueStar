#ifndef _IRM_H_INCLUDED
#define _IRM_H_INCLUDED
/*
//#include "irmbase.h"
//#include "irmext.h"

///////////////////////////////////////////////////////////////////////////////////

typedef ULONG RMCOLORREF;
typedef ULONG RMMPEG_ATTRIBUTE;
typedef ULONG	RMMPEG_EVENT_TYPE;
typedef ULONG RMMPEG_DEVICE_STATE;
typedef ULONG	RMREQUESTED_STATE_TYPE;

// Color limits for one specified color
//
typedef struct tagCOLOR_LIMITS{
	RMCOLORREF crKeyColor;
	RMCOLORREF crUpperLimit;
	RMCOLORREF crLowerLimit;
} RMCOLOR_LIMITS, *PRMCOLOR_LIMITS;

typedef struct _RMMPEG_EVENT{
	RMMPEG_EVENT_TYPE	MpegEvent;			// type of event requested
	ULONG				ulData;				// event specific info (eg #of frames)
	ULONG				ulFlags;			// event flags - pause or continue?
} RMMPEG_EVENT, *PRMMPEG_EVENT;

typedef struct _RMMPEG_DEVICE_INFO{
    RMMPEG_DEVICE_STATE		DeviceState;		// Current MPEG device decode state
	RMREQUESTED_STATE_TYPE	RequestedState;		// Current requested state of MPEG device
}RMMPEG_DEVICE_INFO;

typedef struct  _RMMPEG_ASYNC_CONTEXT{
	RMHANDLE	hEvent;
	ULONG		Reserved[ 10 ];
} RMMPEG_ASYNC_CONTEXT, *PRMMPEG_ASYNC_CONTEXT;

typedef enum _RMMPEG_OVERLAY_MODE{
    MpegModeNone = 1,
    MpegModeRectangle,
    MpegModeOverlay,
	MpegModeCalibrate
} RMMPEG_OVERLAY_MODE, *PRMMPEG_OVERLAY_MODE;

typedef struct _RMOVERLAY_COLOUR_REGISTERS
{
	RMUSHORT	RedUpper;
	RMUSHORT	RedLower;
	RMUSHORT	GreenUpper;
	RMUSHORT	GreenLower;
	RMUSHORT	BlueUpper;
	RMUSHORT	BlueLower;
	RMUSHORT	Mask;
	RMUSHORT	Status;
} RMOVERLAY_COLOUR_REGISTERS, *PRMOVERLAY_COLOUR_REGISTERS;

typedef struct _RMMPEG_OVERLAY_RECT
{
    ULONG X;                         // window x position,width
    ULONG Y;                         // window y position,height
    ULONG cX;                        // window x position,width
    ULONG cY;                        // window y position,height
} RMMPEG_OVERLAY_RECT, *PRMMPEG_OVERLAY_RECT;

typedef struct _MPEG_POINT{
	ULONG	x;
	ULONG	y;
}MPEG_POINT,*PMPEG_POINT;

typedef struct _RMCALIBRATION_PARAMETERS
{
	COLORREF	UpperFF;	
	COLORREF	LowerFF;
	COLORREF	Upper80;	
	COLORREF	Lower80;
	COLORREF	Upper00;	
	COLORREF	Lower00;
} RMCALIBRATION_PARAMETERS, *PRMCALIBRATION_PARAMETERS;

typedef enum _MPEG_HLI_CMD
{
	MpegSelectAdjacentButton = 0,
	MpegActivate,
	MpegSelectAndActivate,
	MpegMouseMove,
	MpegMouseButton,
	MpegSelectButton
} MPEG_HLI_CMD, *PMPEG_HLI_CMD;

typedef struct _RMHIGHLIGHT_COMMANDEX
{
	MPEG_HLI_CMD	command;
	union{
		BYTE		bButtonNumber;
		DWORD		dwParam;
		MPEG_POINT	point;
	}u;
} RMHIGHLIGHT_COMMANDEX, *PRMHIGHLIGHT_COMMANDEX;

typedef struct  _MPEG_ASYNC_CONTEXT{
	RMHANDLE	hEvent;
	ULONG		Reserved[ 10 ];
} MPEG_ASYNC_CONTEXT, *PMPEG_ASYNC_CONTEXT;

// Color limits for one specified color
//
typedef struct tagCOLOR_LIMITS{
	COLORREF crKeyColor;
	COLORREF crUpperLimit;
	COLORREF crLowerLimit;
} COLOR_LIMITS, *PCOLOR_LIMITS;
*/
/////////////////////////////////////////////////////////////////////////////////////////
//
//	INTERFACES
//
/////////////////////////////////////////////////////////////////////////////////////////

DEFINE_RMID(IID_IRmDeviceMoniker	, 0x77167D8A,0x8090,0x11d5,0xB8,0x5E,0x00,0x90,0x27,0x65,0xE1,0x6C);
struct IRmDeviceMoniker : public IUnknown 
{
public:
	// Create object and/or get pointer to specified interface
	virtual HRESULT	IRMCALLTYPE BindToObject(REFIID riid,void **ppObj) = 0;
	// Get name to display( like "MPEG Decoder" or "Video") 
	virtual HRESULT IRMCALLTYPE GetDisplayName(LPOLESTR *ppszName) = 0;
	// Get string which uniquely identifies instance
	virtual HRESULT IRMCALLTYPE GetInstanceID(LPOLESTR *ppszID) = 0;
	// Is stream opened or was driver opened and so on.
	virtual HRESULT	IRMCALLTYPE IsRunning() = 0;

	// Way to obtain type - specific information
	// RETURN: actual data size
	//
	virtual DWORD   IRMCALLTYPE GetInfo(DWORD type,PVOID buffer,DWORD buff_size,HRESULT *phr) = 0;
};

/////////////////////////////////////////////////////////////////////////////////////////

DEFINE_RMID(IID_IRmDeviceEnumerator , 0xCD83BC0A,0x8090,0x11d5,0xB8,0x5E,0x00,0x90,0x27,0x65,0xE1,0x6C);
struct IRmDeviceEnumerator : public IUnknown 
{
public:
	virtual void STDMETHODCALLTYPE Reset() = 0;
	virtual RMRESULT IRMCALLTYPE Next(IRmDeviceMoniker **ppIRmDeviceMoniker) = 0;
};

DEFINE_RMID(IID_IRmDevice			, 0x5D896824,0x4239,0x4ddb,0xAF,0x13,0xC8,0x09,0x36,0xC2,0x46,0xBD);
struct IRmDevice : public IRMBase 
{
public:
	// Can give caps from outside of HwLibrary
	//
	virtual HRESULT IRMCALLTYPE GetDeviceCapabilities(RMCAPABILITIES* pCaps) = 0;

	// To access any property outside of HwLibrary
	//
	virtual HRESULT IRMCALLTYPE Property(
					PKSPROPERTY	pprop,
					DWORD		pprop_size,
					PVOID		pPropertyData,
					DWORD		PropertySize,
					DWORD		*cbReturn,
					OVERLAPPED	*ovr) = 0;
	
	// To get/set attributes with no stream opening
	//
	virtual HRESULT IRMCALLTYPE SetAttributes(
					MPEG_ATTRIBUTE	eAttribute, 
					LONG			lValue) = 0;
	virtual HRESULT IRMCALLTYPE GetAttributes(
					MPEG_ATTRIBUTE	eAttribute,
					LONG			*lValue) = 0;
	
	// better way to work with sized attributes/properties
	//
	virtual HRESULT IRMCALLTYPE GetHwLibProperty(
					DWORD	PropertySetID,
					DWORD	PropertyItemID,
					DWORD	PropertyItemFlags,
					DWORD	PropertySize,
					PVOID	pPropertyData,
					DWORD	*cbReturn) = 0;

	virtual HRESULT IRMCALLTYPE SetHwLibProperty(
					DWORD	PropertySetID,
					DWORD	PropertyItemID,
					DWORD	PropertyItemFlags,
					DWORD	PropertySize,
					PVOID	pPropertyData) = 0;

};

typedef struct {
    ULONG    Size;
    ULONG    Count;
} MULTIPLE_ITEM, *PMULTIPLE_ITEM;

DEFINE_RMID(IID_IRmBaseStreaming	, 0x4757FEB1,0x883D,0x41d4,0x99,0x0B,0x2E,0x7E,0x90,0x18,0xB7,0x3A);
struct IRmBaseStreaming : public IRMBase 
{
public:
	virtual HRESULT IRMCALLTYPE Play	() = 0;
	virtual HRESULT IRMCALLTYPE Pause	() = 0;
	virtual HRESULT IRMCALLTYPE Stop	() = 0;

	virtual HRESULT IRMCALLTYPE Reset() = 0;

	// Say to objects the path down to release data;
	virtual HRESULT IRMCALLTYPE BeginFlush	(void) = 0;

	// All data (including helded by us) are released
	virtual HRESULT IRMCALLTYPE EndFlush	(void) = 0;

	// Explicit working with formats then stream is not running
	//
	virtual HRESULT IRMCALLTYPE CheckFormat	(PRMDATAFORMAT		format) = 0;	
	virtual HRESULT IRMCALLTYPE GetFormat	(PRMMULTIPLE_ITEM	format_list) = 0;
	virtual HRESULT IRMCALLTYPE SetFormat	(PRMDATAFORMAT		format) = 0;

	// Send buffers described by pHeaders to the driver
	// One event is used to release list of bufers
	// described by headers
	virtual HRESULT IRMCALLTYPE Write(
				MULTIPLE_ITEM	* pHeaders,
				OVERLAPPED		* ovr) = 0;

	// Send buffers described by pHeaders to the driver
	// When buffers are not needed anymore, function from
	// ICompletionCallBack will be called with user-defined
	// completion context as argument
	virtual HRESULT IRMCALLTYPE WriteEx(
				MULTIPLE_ITEM		* pHeaders,
				ICompletionCallBack	* pICCallback,
				void				* CompletionContext) = 0;

	// Read functionality is not used 
	// and not implemented
	//
	virtual HRESULT IRMCALLTYPE Read(
				MULTIPLE_ITEM		* pHeaders,
				OVERLAPPED			* ovr) = 0;

	virtual HRESULT IRMCALLTYPE ReadEx(
				MULTIPLE_ITEM		* pHeaders,
				ICompletionCallBack	* pICCallback,
				void				* CompletionContext) = 0;

/*	// Analog of HwLibProperty in IRmDevice, just routed through the stream handle
	// 
	virtual HRESULT IRMCALLTYPE Property(
				[in]	PRMPROPERTY		RMID,
				[in]	ULONG			RMID_size,
				[in]	PVOID			prop,
				[in]	ULONG			prop_size,
				[out]	ULONG			*bret) = 0;

	// Analog of HwLibAttributes in IRmDevice, just routed through the stream handle
	//
	virtual HRESULT IRMCALLTYPE SetAttributes(
				[in]	MPEG_ATTRIBUTE	eAttribute, 
				[in]	LONG			lValue) = 0;
	virtual HRESULT IRMCALLTYPE GetAttributes(
				[in]	MPEG_ATTRIBUTE	eAttribute,
				[out]	LONG			*lValue) = 0;
*/
};

DEFINE_RMID(IID_IRmVideo             , 0x4F8A6623,0xF303,0x4d23,0x92,0x3F,0x5A,0xD3,0x70,0x7E,0x5B,0xF0);
struct IRmVideo : public IRmBaseStreaming
{
public:
    virtual HRESULT STDMETHODCALLTYPE ClearBuffer( void) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE CaptureToBuffer( 
        BYTE *pBmp,
        ULONG ulSize) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE SetPositionEvent( 
        PMPEG_EVENT pEvent,
        PMPEG_ASYNC_CONTEXT pAsyncContext) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE GetDeviceInfo( 
        PMPEG_DEVICE_INFO  deviceInfo) = 0;
    
};


DEFINE_RMID(IID_IRmAudio             , 0x48394E01,0x8A68,0x48fa,0xA9,0x0F,0x77,0xCD,0x65,0x52,0xFB,0x1E);
struct IRmAudio : public IRmBaseStreaming
{
public:
    virtual HRESULT STDMETHODCALLTYPE SetPositionEvent( 
        PMPEG_EVENT pEvent,
        PMPEG_ASYNC_CONTEXT pAsyncContext) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE GetDeviceInfo( 
        MPEG_DEVICE_INFO  *deviceInfo) = 0;
    
};


DEFINE_RMID(IID_IRmOverlay           , 0xFC017BFF,0x301E,0x475a,0xA0,0x6E,0x42,0xF2,0xCA,0x00,0x73,0x96);
struct IRmOverlay : public IRMBase
{
public:
    virtual HRESULT STDMETHODCALLTYPE Get_Mode( 
        MPEG_OVERLAY_MODE  *OverlayMode) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE Put_Mode( 
        MPEG_OVERLAY_MODE OverlayMode) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE Get_VGAKey( 
        COLORREF  *prgbColor,
        COLORREF  *prgbMask) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE Put_VGAKey( 
        COLORREF  *prgbColor,
        COLORREF  *prgbMask) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE Put_VGAKey2( 
        COLORREF rgbColor,
        POVERLAY_COLOUR_REGISTERS pOverride) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE Put_Source( 
        MPEG_OVERLAY_RECT  *rect) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE Get_Source( 
        MPEG_OVERLAY_RECT  *rect) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE Put_Destination( 
        MPEG_OVERLAY_RECT  *rect) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE Get_Destination( 
        MPEG_OVERLAY_RECT  *rect) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE Do_Calibration( 
        POVERLAY_COLOUR_REGISTERS pRegs) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE Put_CalibParam( 
        PCALIBRATION_PARAMETERS pParams) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE SetAttributes( 
        MPEG_ATTRIBUTE eAttribute,
        ULONG lValue) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE GetAttributes( 
        MPEG_ATTRIBUTE eAttribute,
        ULONG  *lValue) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE GetDeviceInfo( 
        MPEG_DEVICE_INFO  *deviceInfo) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE SetAttributeEx( 
        MPEG_ATTRIBUTE eAttribute,
        void  *lValue,
        ULONG size) = 0;
    
};


DEFINE_RMID(IID_IRmSubpicture        , 0xF934C7A2,0x4192,0x4b19,0xB3,0x11,0x09,0x72,0xC3,0xC7,0x47,0x57);
struct IRmSubpicture : public IRmBaseStreaming
{
public:
    virtual HRESULT STDMETHODCALLTYPE HliCommand( 
        PHIGHLIGHT_COMMANDEX cmd) = 0;
    
};


DEFINE_RMID(IID_IRmOSD               , 0x41189722,0x20DF,0x43a8,0x87,0x19,0xF9,0x56,0xDD,0x8B,0xB9,0x70);
struct IRmOSD : public IRmBaseStreaming
{
public:
    virtual PVOID STDMETHODCALLTYPE AllocateSharedBuffer( 
        ULONG size) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE FreeSharedBuffer( 
        PVOID Addr) = 0;
    
};


DEFINE_RMID(IID_IOverlayConfig       , 0xA22206B3,0x93C2,0x45a9,0xB1,0x97,0xFE,0x40,0x7D,0xD0,0x28,0x25);
struct IOverlayConfig : public IRMBase
{
public:
    virtual HRESULT STDMETHODCALLTYPE put_OverlayMode( 
        MPEG_OVERLAY_MODE OverlayMode) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE get_OverlayMode( 
        MPEG_OVERLAY_MODE  *pOverlayMode) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE put_OverlayPosition( 
        MPEG_OVERLAY_RECT  *rcDestination) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE get_OverlayPosition( 
        MPEG_OVERLAY_RECT  *prcDestination) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE put_TopBorder( 
        ULONG ulYOffset) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE get_TopBorder( 
        ULONG  *pulYOffset) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE put_LeftBorder( 
        ULONG ulXOffset) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE get_LeftBorder( 
        ULONG  *pulXOffset) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE put_VgaCorrection( 
        ULONG ulVgaCorrection) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE get_VgaCorrection( 
        ULONG  *pulVgaCorrection) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE put_JitterAdjustment( 
        ULONG ulJitterAdjustment) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE get_JitterAdjustment( 
        ULONG  *pulJitterAdjustment) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE put_VgaFineAdjustment( 
        ULONG ulVgaFineAdjustment) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE get_VgaFineAdjustment( 
        ULONG  *pulVgaFineAdjustment) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE UpdateResolution( void) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE AutoCalibrate( void) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE StartAutoCalibration( void) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE StopAutoCalibration( void) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE CalibrateTopBorder( void) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE CalibrateLeftBorder( void) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE CalibrateCorrection( void) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE CalibrateColorLimits( 
        PCOLOR_LIMITS pColorLimits) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE put_CalibrationParameters( 
        PCALIBRATION_PARAMETERS  pCalParams) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE get_CalibrationParameters( 
        PCALIBRATION_PARAMETERS  pCalParams) = 0;
    
};

#endif // _IRM_H_INCLUDED

