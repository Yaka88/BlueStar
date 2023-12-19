/*++
Copyright (c) 1994 Microsoft Corporation
Copyright (c) 1996 Sigma Designs Inc.

Module Name:

    mpegapi.h

Abstract:

    This module defines the MPEG driver API.

--*/

#ifndef _MPEGAPI_H
#define _MPEGAPI_H

#ifdef  __cplusplus
extern "C" {
#endif

/***********************************************
     type and structure definitions
***********************************************/

#include "mpegcmn.h"

typedef DWORDLONG           ULONGLONG; 
typedef HANDLE              HMPEG_DEVICE, *PHMPEG_DEVICE;

typedef long                MPEG_STATUS, *PMPEG_STATUS;
/*
typedef struct _MPEG_ASYNC_CONTEXT {
    HANDLE      hEvent;
    ULONG       Reserved[10];
} MPEG_ASYNC_CONTEXT, *PMPEG_ASYNC_CONTEXT;
*/
// the caller of MpegEnumDevices must allocate
// at least MPEG_MAX_DEVICEID_SIZE bytes

#define MPEG_MAX_DEVICEID_SIZE 25

#ifdef IN_MPEGAPI_DLL
#define MPEGAPI __declspec(dllexport) __cdecl
#else
#define MPEGAPI __declspec(dllimport) __cdecl
#endif

// not part of API, but since the API doesn't support 
// window alignment, we need this for now
// also can be used for the testing purpose

HANDLE MPEGAPI
MpegHandle(
    IN HMPEG_DEVICE hDevice,
    IN MPEG_DEVICE_TYPE eDeviceType
    );

/***********************************************
   functions prototypes
***********************************************/

MPEG_STATUS MPEGAPI 
MpegEnumDevices(
    IN int iAdapterIndex,
    OUT LPTSTR pstrDeviceDescription OPTIONAL,
    IN  UINT uiDescriptionSize,
    OUT LPDWORD pdwDeviceId OPTIONAL,
    OUT PHMPEG_DEVICE phDevice OPTIONAL
    );

MPEG_STATUS MPEGAPI 
MpegOpenDevice(
    IN DWORD dwDeviceId,
    OUT PHMPEG_DEVICE phDevice
    );

MPEG_STATUS MPEGAPI 
MpegCloseDevice(
    IN HMPEG_DEVICE hDevice
    );

MPEG_STATUS MPEGAPI 
MpegQueryDeviceCapabilities(
    IN HMPEG_DEVICE hDevice,
    IN MPEG_CAPABILITY eCapability
    );

MPEG_STATUS MPEGAPI 
MpegWriteData(
    IN HMPEG_DEVICE hDevice,
    IN MPEG_STREAM_TYPE eStreamType,
    IN PMPEG_PACKET_LIST_ENTRY pPacketList,
    IN UINT uiPacketCount,
    IN PMPEG_ASYNC_CONTEXT pAsyncContext OPTIONAL
    );

MPEG_STATUS MPEGAPI
MpegCaptureFrame(
	IN HMPEG_DEVICE hDevice,
	IN MPEG_STREAM_TYPE eStreamType,
	IN OUT PUCHAR pBmp,
	IN ULONG ulSize
	);

MPEG_STATUS MPEGAPI 
MpegQueryAsyncResult(
    IN HMPEG_DEVICE hDevice,
    IN MPEG_STREAM_TYPE eStreamType,
    IN PMPEG_ASYNC_CONTEXT pAsyncContext,
    IN BOOL bWait
    );

MPEG_STATUS MPEGAPI 
MpegResetDevice(
    IN HMPEG_DEVICE hDevice,
    IN MPEG_DEVICE_TYPE eDeviceType
    );

MPEG_STATUS MPEGAPI
MpegSetAutoSync(
    IN HMPEG_DEVICE hDevice,
    IN BOOL bEnable
    );

MPEG_STATUS MPEGAPI 
MpegSyncVideoToAudio(
    IN HMPEG_DEVICE hDevice,
    IN MPEG_SYSTEM_TIME systemTimeDelta
    );

MPEG_STATUS MPEGAPI 
MpegQuerySTC(
    IN HMPEG_DEVICE hDevice,
    IN MPEG_DEVICE_TYPE eDeviceType,
    OUT PMPEG_SYSTEM_TIME pSystemTime
    );

MPEG_STATUS MPEGAPI 
MpegSetSTC(
    IN HMPEG_DEVICE hDevice,
    IN MPEG_DEVICE_TYPE eDeviceType,
    IN MPEG_SYSTEM_TIME systemTime
    );
    
MPEG_STATUS MPEGAPI 
MpegPlay(
    IN HMPEG_DEVICE hDevice,
    IN MPEG_DEVICE_TYPE eDeviceType
    );

MPEG_STATUS MPEGAPI 
MpegPlayTo(
    IN HMPEG_DEVICE hDevice,
    IN MPEG_DEVICE_TYPE eDeviceType,
    IN MPEG_SYSTEM_TIME systemTime,
    IN PMPEG_ASYNC_CONTEXT pAsyncContext OPTIONAL
    );

MPEG_STATUS MPEGAPI 
MpegFreeze(
    IN HMPEG_DEVICE hDevice,
    IN MPEG_DEVICE_TYPE eDeviceType
    );

MPEG_STATUS MPEGAPI 
MpegSetEvent(
    IN HMPEG_DEVICE hDevice,
    IN MPEG_DEVICE_TYPE eDeviceType,
	IN PMPEG_EVENT pEvent,
	IN PMPEG_ASYNC_CONTEXT pAsyncContext
    );

MPEG_STATUS MPEGAPI 
MpegPause(
    IN HMPEG_DEVICE hDevice,
    IN MPEG_DEVICE_TYPE eDeviceType
    );

MPEG_STATUS MPEGAPI 
MpegStop(
    IN HMPEG_DEVICE hDevice,
    IN MPEG_DEVICE_TYPE eDeviceType
    );
    
MPEG_STATUS MPEGAPI 
MpegQueryDeviceState(
    IN HMPEG_DEVICE hDevice,
    IN MPEG_DEVICE_TYPE eDeviceType,
    OUT PMPEG_DEVICE_STATE pCurrentDeviceState
    );

MPEG_STATUS MPEGAPI 
MpegQueryInfo(
    IN HMPEG_DEVICE hDevice,
    IN MPEG_DEVICE_TYPE eDeviceType,
    IN MPEG_INFO_ITEM eInfoItem,
    OUT PULONG pulValue
    );


MPEG_STATUS MPEGAPI 
MpegClearVideoBuffer(
    IN HMPEG_DEVICE hDevice
    );

MPEG_STATUS MPEGAPI 
MpegSetOverlayMode(
    IN HMPEG_DEVICE hDevice,
    IN MPEG_OVERLAY_MODE eNewMode
    );

MPEG_STATUS MPEGAPI 
MpegSetOverlayMask(
    IN HMPEG_DEVICE hDevice,
    IN ULONG ulHeight,
    IN ULONG ulWidth,
    IN ULONG ulOffset,
    IN ULONG ulLineLength,
    IN PUCHAR pMaskBits 
    );

MPEG_STATUS MPEGAPI 
MpegQueryOverlayKey(
    IN HMPEG_DEVICE hDevice,
    OUT COLORREF *prgbColor,
    OUT COLORREF *prgbMask
    );

MPEG_STATUS MPEGAPI 
MpegSetOverlayKey(
    IN HMPEG_DEVICE hDevice,
    IN COLORREF rgbColor,
    IN COLORREF rgbMask
    );

MPEG_STATUS MPEGAPI 
MpegSetOverlayKey2(
    IN HMPEG_DEVICE hDevice,
    IN COLORREF rgbColor,
    IN POVERLAY_COLOUR_REGISTERS pOverride
    );

MPEG_STATUS MPEGAPI 
MpegSetOverlaySource(
    IN HMPEG_DEVICE hDevice,
    IN LONG lX,
    IN LONG lY,
    IN LONG lWidth,
    IN LONG lHeight
    );

MPEG_STATUS MPEGAPI 
MpegSetOverlayDestination(
    IN HMPEG_DEVICE hDevice,
    IN LONG lX,
    IN LONG lY,
    IN LONG lWidth,
    IN LONG lHeight
    );

MPEG_STATUS MPEGAPI 
MpegQueryAttributeRange(
    IN HMPEG_DEVICE hDevice,
    IN MPEG_ATTRIBUTE eAttribute,
    OUT PLONG plMinimum,
    OUT PLONG plMaximum,
    OUT PLONG plStep
    );

MPEG_STATUS MPEGAPI 
MpegQueryAttribute(
    IN HMPEG_DEVICE hDevice,
    IN MPEG_ATTRIBUTE eAttribute,
    OUT PLONG plValue
    );

MPEG_STATUS MPEGAPI
MpegQueryAttributeEx(
    HMPEG_DEVICE    hDevice,
    MPEG_ATTRIBUTE  eAttribute,
    PVOID           plValue,
    ULONG           ValueSize
	);

MPEG_STATUS MPEGAPI 
MpegSetAttribute(
    IN HMPEG_DEVICE hDevice,
    IN MPEG_ATTRIBUTE eAttribute,
    IN LONG lValue
    );

MPEG_STATUS MPEGAPI 
MpegSetAttributeEx(
	IN HMPEG_DEVICE hDevice,
	IN MPEG_ATTRIBUTE eAttribute, 
	IN PVOID pValue, 
	IN ULONG ulValueSize
	);

MPEG_STATUS MPEGAPI
MpegSetAttributeEx(
    IN HMPEG_DEVICE		hDevice,
    IN MPEG_ATTRIBUTE	eAttribute,
    IN PVOID			pValue,
	IN ULONG			ValueSize
	);

MPEG_STATUS MPEGAPI 
MpegOverlayDraw(
    IN HMPEG_DEVICE hDevice,
    IN MPEG_DEVICE_TYPE eDeviceType,
    IN MPEG_DISPLAY_CONTEXT context,
    IN DWORD dwContextSpecific,
    IN RECT rect,
    IN HBRUSH hBrush
    );

MPEG_STATUS MPEGAPI
MpegOverlayRealize(
    IN HMPEG_DEVICE hDevice,
    IN MPEG_DEVICE_TYPE eDeviceType,
    IN MPEG_DISPLAY_CONTEXT context,
    IN BOOL bForceBackground
    );

MPEG_STATUS MPEGAPI
MpegHighlight(
    IN HMPEG_DEVICE hDevice,
    IN MPEG_DEVICE_TYPE eDeviceType,
    IN MPEG_HLI_CMD command,
    IN DWORD dwParameter
    );

MPEG_STATUS MPEGAPI
MpegCalibrate(
    IN HMPEG_DEVICE hDevice,
    IN OUT POVERLAY_COLOUR_REGISTERS pRegs
	);

MPEG_STATUS MPEGAPI
MpegSetCalibrationParameters(
    IN HMPEG_DEVICE hDevice,
    IN PCALIBRATION_PARAMETERS pParams
	);

MPEG_STATUS MPEGAPI
MpegUnprepareData(
    IN HMPEG_DEVICE hDevice,
    IN MPEG_STREAM_TYPE eStreamType,
    IN PMPEG_PACKET_LIST_ENTRY pPacketList,
    IN UINT uiPacketCount,
    IN PMPEG_ASYNC_CONTEXT pAsyncContext
	);

MPEG_STATUS MPEGAPI
MpegEnableDisplay(
	IN BOOL bEnable			// Used by MPEG2 DirectShow filter
);							// to avoid using twice VPE

MPEG_STATUS MPEGAPI
MpegSetWaviface(
	IN LPSTR szWavifaceLib);// Used by MPEG2 DirectShow filter
							// to use a non scrambled waviface
MPEG_STATUS
MpegActivatePort(			// Used to activate MPEGPORT using WDM resources
	IN HMPEG_DEVICE hDevice,
	IN PWDM_ADDRESS pAddr);

MPEG_STATUS					// Used to deactivate MPEGPORT
MpegDeActivatePort(
	IN HMPEG_DEVICE hDevice);

BOOLEAN MPEGAPI
MpegShowOverlay(
	ULONG		ProcessId, 
	BOOLEAN		bShow);

MPEG_STATUS MPEGAPI 
ExternEnumMpegDevice(ULONG index,HMPEG_DEVICE* hDevice);

MPEG_STATUS MPEGAPI 
ExternCloseMpegDevice(HMPEG_DEVICE hDevice);

MPEG_STATUS MPEGAPI 
ExternMpegPropertySync(
		HMPEG_DEVICE	hDevice,
		DWORD			Flags,
		DWORD			PropSet,
		DWORD			PropId,
		DWORD			PropFlags,
		PVOID			pPropData,
		DWORD			dwPropSizeIn,
		DWORD*			pdwPropSizeOut);

typedef struct _DEVICE_LINK_INFO{
	GUID	CLSID;
	ULONG	ven;
	ULONG	dev;
	ULONG	index;
	ULONG	linked;
	PTCHAR	link;
}DEVICE_LINK_INFO,*PDEVICE_LINK_INFO;

MPEG_STATUS MPEGAPI
MpegProperty(
		HMPEG_DEVICE	hDevice,
		DWORD			Flags,
		DWORD			PropSet,
		DWORD			PropId,
		DWORD			PropFlags,
		PVOID			pPropData,
		DWORD			dwPropSizeIn,
		DWORD*			pdwPropSizeOut);

#define LINKS_PATH "System\\CurrentControlSet\\Services\\rmstream\\Links"
#define LINKS_PATH_95 "Software\\Sigma Designs\\RealMagic\\PciEnum"
BOOLEAN rmp_PropertySync(
			HANDLE		h,
			REFGUID		Set,
			ULONG		Id,
			ULONG		Flags,
			LPVOID		PropertyData,
			ULONG		PropertyLength,
			ULONG		*BytesReturned);

// Allocates memory using CoTaskMemAlloc();
// this memory must be deallocated by caller using CoTaskMemFree();
// VG 07/27/01
//
MPEG_STATUS MPEGAPI
MpegGetInstanceIdString(LPOLESTR *ppszName);

#ifdef  __cplusplus
}
#endif

#endif
