#ifndef _DXIFACE_H
#define _DXIFACE_H

#include "mpegapi.h"

#ifdef IN_DXIFACE_DLL
#define DXAPI __declspec(dllexport) __cdecl
#else
#define DXAPI __declspec(dllimport) __cdecl
#endif

#define CLASS_NAME	"DekafDXWindowClass"
#define WINDOW_NAME	"DKAFDX"

#ifdef __cplusplus
extern "C"
{
#endif

// init
MPEG_STATUS DXAPI InitializeDXIface (HMPEG_DEVICE hDevice);
// exit
MPEG_STATUS DXAPI ReleaseDXIface (HMPEG_DEVICE hDevice);
// overlay
MPEG_STATUS DXAPI DXSetOverlayDestination (LONG lX, LONG lY, LONG lWidth, LONG lHeight);
// video through pci
MPEG_STATUS DXAPI DXDecodeToGraphicMemory (HMPEG_DEVICE hDevice);
// audio through pci - video as well?
MPEG_STATUS DXAPI DXDecodeToSystemMemory (HMPEG_DEVICE hDevice);
// timing services
MPEG_STATUS DXAPI DXStartTimerServices (HMPEG_DEVICE hDevice);
MPEG_STATUS DXAPI DXEndTimerServices (HMPEG_DEVICE hDevice);
// start audio playback
MPEG_STATUS DXAPI DXSoundPlay (HMPEG_DEVICE hDevice);

#ifdef __cplusplus
}
#endif


MPEG_STATUS	OpenDDraw (void);
MPEG_STATUS CloseDDraw (HMPEG_DEVICE hDevice);
MPEG_STATUS DDrawSetOverlayDestination (LONG lX, LONG lY, LONG lWidth, LONG lHeight);
MPEG_STATUS DDrawDecodeToGraphicMemory (HMPEG_DEVICE hDevice);
MPEG_STATUS DDrawDecodeToSystemMemory (HMPEG_DEVICE hDevice);

MPEG_STATUS	OpenDSound (void);
MPEG_STATUS CloseDSound (HMPEG_DEVICE hDevice);
MPEG_STATUS DSoundDecodeToSystemMemory (HMPEG_DEVICE hDevice);
MPEG_STATUS DSoundPlay (void);

#define SAMPLE_RATE			(44100)
#define NCHANNELS			(2)
#define	BITS_PER_SAMPLE		(16)
#define BLOCK_ALIGN			(4)
#define BYTE_RATE			(176400)
#define BUFFER_SIZE_IN_SEC	(3)
#define DSOUND_BUFFER_SIZE	(BYTE_RATE*BUFFER_SIZE_IN_SEC)
#define TIMER_RESOLUTION	(8)
#define TIMER_PERIOD		(8)


#endif


