/////////////////////////////////////////////////////////////////////////////
// spuinc.h : external definitions of spudec DLL
// REALmagic mcifmp 32 bits.
// Created by Jacques MAHE
// Copyright Sigma Designs Inc
// Sigma Designs Proprietary and confidential
// Created on 04/01/97

#ifndef _SPUINC_H
#define _SPUINC_H

#include "mpegapi.h"

#ifdef IN_SPUDEC_DLL
#define SPUAPI __declspec(dllexport) __cdecl
#else
#define SPUAPI
#endif

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct tagSPUSTREAMINFO
{
	LPVOID lpSpuControl;		// Our spu control object
} SPUSTREAMINFO, *PSPUSTREAMINFO;

MPEG_STATUS SPUAPI 
SpuOpenDevice(
	IN MPEG_DISPLAY_CONTEXT spuDevType,
	OUT PSPUSTREAMINFO *pspui
	);

MPEG_STATUS SPUAPI 
SpuCloseDevice(
	IN PSPUSTREAMINFO pspui
	);

MPEG_STATUS SPUAPI 
SpuResetDevice(
	IN PSPUSTREAMINFO pspui
	);

MPEG_STATUS SPUAPI 
SpuWriteData(
	IN PSPUSTREAMINFO pspui,
	IN PMPEG_PACKET_LIST_ENTRY pPacketList,
	IN UINT uiPacketCount,
	IN PMPEG_ASYNC_CONTEXT pAsyncContext OPTIONAL
	);

MPEG_STATUS SPUAPI 
SpuWritePciData(
	IN PSPUSTREAMINFO pspui,
	IN PMPEG_PACKET_LIST_ENTRY pPacketList,
	IN UINT uiPacketCount,
	IN PMPEG_ASYNC_CONTEXT pAsyncContext OPTIONAL
	);

MPEG_STATUS SPUAPI 
SpuSetReferenceTime(
	IN PSPUSTREAMINFO pspui,
	IN MPEG_SYSTEM_TIME systemTimeDelta
	);

MPEG_STATUS SPUAPI
SpuSetCalibrationParameters(
    IN PSPUSTREAMINFO pspui,
	IN COLORREF rgbLowerValue,
	IN COLORREF rgbUpperValue
	);

MPEG_STATUS SPUAPI
SpuSetKeyColor(
	IN PSPUSTREAMINFO pspui,
	IN COLORREF crKeyColor
	);

MPEG_STATUS SPUAPI 
SpuPlay(
	IN PSPUSTREAMINFO pspui,
	IN HMPEG_DEVICE hVideoDevice
	);

MPEG_STATUS SPUAPI
SpuPause(
	IN PSPUSTREAMINFO pspui
	);

MPEG_STATUS SPUAPI 
SpuStop(
	IN PSPUSTREAMINFO pspui
	);

MPEG_STATUS SPUAPI 
SpuFreeze(
	IN PSPUSTREAMINFO pspui
	);

MPEG_STATUS SPUAPI 
SpuDraw(
	IN PSPUSTREAMINFO pspui,
	IN DWORD dwContextSpecific,
	IN RECT rect, 
	IN HBRUSH hBrush
	);

MPEG_STATUS SPUAPI 
SpuRealize(
	IN PSPUSTREAMINFO pspui,
	IN BOOL bForceBackground
	);

MPEG_STATUS SPUAPI 
SpuHighlightCommand(
	IN PSPUSTREAMINFO pspui,
	IN MPEG_HLI_CMD command,
	IN DWORD dwParameter
	);

MPEG_STATUS SPUAPI 
SpuQueryAttribute(
	IN PSPUSTREAMINFO pwsi,
	IN MPEG_ATTRIBUTE eAttribute,
	OUT PLONG plValue
	);

MPEG_STATUS SPUAPI 
SpuSetAttribute(
	IN PSPUSTREAMINFO pwsi,
	IN MPEG_ATTRIBUTE eAttribute,
	IN LONG lValue
	);

#ifdef __cplusplus
}
#endif

#endif
