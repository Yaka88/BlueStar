/*++

Copyright (c) 1994  Microsoft Corporation

Module Name:

    mpeg.h

Abstract:

    These are the structures and defines that are used in the
    MPEG port driver.

Author:

    Paul Shih (paulsh) 27-Mar-1994

Revision History:

--*/
#ifndef _DDMPEG_H
#define _DDMPEG_H

#include "mpegcmn.h"
//
// Define the various device type values.  Note that values used by Microsoft
// Corporation are in the range 0-32767, and 32768-65535 are reserved for use
// by customers.
//
#define FILE_DEVICE_MPEG_OVERLAY       0x00008200U
#define FILE_DEVICE_MPEG_VIDEO         0x00008300U
#define FILE_DEVICE_MPEG_AUDIO         0x00008600U
#define FILE_DEVICE_MPEG_SPU           0x00008700U
#define FILE_DEVICE_PCM_AUDIO          0x00008900U
#define FILE_DEVICE_MPEG_MISC		   0x00009000U

//
// Macro definition for defining IOCTL and FSCTL function control codes.  Note
// that function codes 0-2047 are reserved for Microsoft Corporation, and
// 2048-4095 are reserved for customers.
//
#define MPEG_OVERLAY_IOCTL_BASE			0x820U
#define MPEG_VIDEO_IOCTL_BASE			0x830U
#define MPEG_AUDIO_IOCTL_BASE			0x860U
#define MPEG_SPU_IOCTL_BASE				0x870U
#define MPEG_MISC_IOCTL_BASE			0x900U
#define	MPEG_PCM_IOCTL_BASE				0x920U

//
// Defines used in simplifying actual declarations of device IOCTL values below
//
#define CTL_CODE_MPEG_AUDIO(offset)   CTL_CODE(FILE_DEVICE_MPEG_AUDIO,           \
                                               MPEG_AUDIO_IOCTL_BASE   + offset, \
                                               METHOD_BUFFERED,                  \
                                               FILE_ANY_ACCESS)

#define CTL_CODE_MPEG_VIDEO(offset)   CTL_CODE(FILE_DEVICE_MPEG_VIDEO,           \
                                               MPEG_VIDEO_IOCTL_BASE   + offset, \
                                               METHOD_BUFFERED,                  \
                                               FILE_ANY_ACCESS)

#define CTL_CODE_MPEG_OVERLAY(offset) CTL_CODE(FILE_DEVICE_MPEG_OVERLAY,         \
                                               MPEG_OVERLAY_IOCTL_BASE + offset, \
                                               METHOD_BUFFERED,                  \
                                               FILE_ANY_ACCESS)

#define CTL_CODE_MPEG_SPU(offset)     CTL_CODE(FILE_DEVICE_MPEG_SPU,             \
                                               MPEG_SPU_IOCTL_BASE + offset,     \
                                               METHOD_BUFFERED,                  \
                                               FILE_ANY_ACCESS)

#define CTL_CODE_MPEG_MISC(offset)    CTL_CODE(FILE_DEVICE_MPEG_OVERLAY,			 \
                                               MPEG_MISC_IOCTL_BASE + offset,	 \
                                               METHOD_BUFFERED,                  \
                                               FILE_ANY_ACCESS)

#define CTL_CODE_MPEG_PCM(offset)    CTL_CODE(FILE_DEVICE_PCM_AUDIO,			 \
                                               MPEG_PCM_IOCTL_BASE + offset,	 \
                                               METHOD_BUFFERED,                  \
                                               FILE_ANY_ACCESS)

//****************************************************************************
// MPEG_AUDIO device IOCTLs
//****************************************************************************

// Input:  None
// Output: None
#define IOCTL_MPEG_AUDIO_RESET               CTL_CODE_MPEG_AUDIO(0)

// Input:  None
// Output: MPEG_TIME_STAMP
#define IOCTL_MPEG_AUDIO_GET_STC             CTL_CODE_MPEG_AUDIO(1)

// Input:  MPEG_TIME_STAMP
// Output: None
#define IOCTL_MPEG_AUDIO_SET_STC             CTL_CODE_MPEG_AUDIO(2)

// Input:  None
// Output: None
#define IOCTL_MPEG_AUDIO_PLAY                CTL_CODE_MPEG_AUDIO(3)

// Input:  None
// Output: None
#define IOCTL_MPEG_AUDIO_PAUSE				CTL_CODE_MPEG_AUDIO(4)

// Input:  None
// Output: None
#define IOCTL_MPEG_AUDIO_STOP				CTL_CODE_MPEG_AUDIO(5)

// Input:  None
// Output: MPEG_AUDIO_DEVICE_INFO
#define IOCTL_MPEG_AUDIO_QUERY_DEVICE		CTL_CODE_MPEG_AUDIO(6)

// Input:  None
// Output: None
#define IOCTL_MPEG_AUDIO_END_OF_STREAM		CTL_CODE_MPEG_AUDIO(7)

// Input:  MPEG_ATTRIBUTE
// Output: none
#define IOCTL_MPEG_AUDIO_SET_ATTRIBUTE		CTL_CODE_MPEG_AUDIO(8)

// Input:  none
// Output: MPEG_ATTRIBUTE
#define IOCTL_MPEG_AUDIO_GET_ATTRIBUTE		CTL_CODE_MPEG_AUDIO(9)

// Input:  MPEG_PACKET_LIST[]
// Output: none
#define IOCTL_MPEG_AUDIO_WRITE_PACKETS		CTL_CODE_MPEG_AUDIO(10)

// Input:  PMPEG_EVENT
// Output: None
#define IOCTL_MPEG_AUDIO_SET_EVENT			CTL_CODE_MPEG_AUDIO(11)

// Input:  None
// Output: None
#define IOCTL_MPEG_AUDIO_FREEZE             CTL_CODE_MPEG_AUDIO(12)

// Input:  None
// Output: PHW_AUDIO_DEVICE_EXTENSION
#define IOCTL_MPEG_AUDIO_GET_EXTENSION		CTL_CODE_MPEG_AUDIO(13)

// Input:  None
// Output: PCIRCULAR_BUFFER_INFO
#define IOCTL_MPEG_AUDIO_LOCK_CIRCULAR_BUFFER	CTL_CODE_MPEG_AUDIO(14)

// Input:  PCIRCULAR_BUFFER_INFO
// Output: None
#define IOCTL_MPEG_AUDIO_UNLOCK_CIRCULAR_BUFFER	CTL_CODE_MPEG_AUDIO(15)

// Input:  PCIRCULAR_BUFFER_INFO
// Output: None
#define IOCTL_MPEG_AUDIO_SET_CIRCULAR_BUFFER	CTL_CODE_MPEG_AUDIO(16)

// Input:  PCIRCULAR_BUFFER_INFO
// Output: PCIRCULAR_BUFFER_INFO
#define IOCTL_MPEG_AUDIO_ALLOC_BUFFER			CTL_CODE_MPEG_AUDIO(17)

// Input:  PCIRCULAR_BUFFER_INFO
// Output: none
#define IOCTL_MPEG_AUDIO_FREE_BUFFER			CTL_CODE_MPEG_AUDIO(18)
//****************************************************************************
// MPEG_VIDEO device IOCTLs
//****************************************************************************

// Input:  None
// Output: None
#define IOCTL_MPEG_VIDEO_RESET				CTL_CODE_MPEG_VIDEO(0)

// Input:  None
// Output: MPEG_TIME_STAMP
#define IOCTL_MPEG_VIDEO_GET_STC			CTL_CODE_MPEG_VIDEO(1)

// Input:  MPEG_TIME_STAMP
// Output: None
#define IOCTL_MPEG_VIDEO_SET_STC			CTL_CODE_MPEG_VIDEO(2)

// Input:  MPEG_TIME_STAMP (optional)
// Output: MPEG_TIME_STAMP (optional)
#define IOCTL_MPEG_VIDEO_SYNC				CTL_CODE_MPEG_VIDEO(3)

// Input:  None
// Output: None
#define IOCTL_MPEG_VIDEO_PLAY				CTL_CODE_MPEG_VIDEO(4)

// Input:  None
// Output: None
#define IOCTL_MPEG_VIDEO_PAUSE				CTL_CODE_MPEG_VIDEO(5)

// Input:  None
// Output: None
#define IOCTL_MPEG_VIDEO_STOP				CTL_CODE_MPEG_VIDEO(6)

// Input:  None
// Output: MPEG_VIDEO_DEVICE_INFO
#define IOCTL_MPEG_VIDEO_QUERY_DEVICE		CTL_CODE_MPEG_VIDEO(7)

// Input:  None
// Output: None
#define IOCTL_MPEG_VIDEO_END_OF_STREAM		CTL_CODE_MPEG_VIDEO(8)

// Input:  None
// Output: None
#define IOCTL_MPEG_VIDEO_CLEAR_BUFFER		CTL_CODE_MPEG_VIDEO(9)

// Input:  MPEG_ATTRIBUTE
// Output: none
#define IOCTL_MPEG_VIDEO_SET_ATTRIBUTE		CTL_CODE_MPEG_VIDEO(10)

// Input:  none
// Output: MPEG_ATTRIBUTE
#define IOCTL_MPEG_VIDEO_GET_ATTRIBUTE		CTL_CODE_MPEG_VIDEO(11)

// Input:  MPEG_PACKET_LIST[]
// Output: none
#define IOCTL_MPEG_VIDEO_WRITE_PACKETS		CTL_CODE_MPEG_VIDEO(12)

// Input:  MPEG_PACKET_LIST[]
// Output: buffer to receive data, length of buffer
#define IOCTL_MPEG_VIDEO_CAPTO_BUFFER		CTL_CODE_MPEG_VIDEO(13)

// Input:  PMPEG_EVENT (for frame)
// Output: None
#define IOCTL_MPEG_VIDEO_SET_EVENT			CTL_CODE_MPEG_VIDEO(14)

// Input:  PMPEG_SYSTEM_TIME
// Output: None
#define IOCTL_MPEG_VIDEO_FREEZE				CTL_CODE_MPEG_VIDEO(15)

// Input:  PMPEG_EVENT (for bytes)
// Output: None
#define IOCTL_MPEG_VIDEO_SET_EVENT2			CTL_CODE_MPEG_VIDEO(16)

// Input:  None
// Output: None
#define IOCTL_MPEG_VIDEO_RESYNC_NOW			CTL_CODE_MPEG_VIDEO(17)

// Input:  MPEG_PACKET_LIST[]
// Output: None
#define IOCTL_MPEG_VIDEO_OUTPUT_WRITE_PACKETS	CTL_CODE_MPEG_VIDEO(18)

// Input:  PCIRCULAR_BUFFER_INFO
// Output: None
#define IOCTL_MPEG_VIDEO_SET_BUFFER				CTL_CODE_MPEG_VIDEO(19)

// Input:  PULONG
// Output: None
#define IOCTL_MPEG_CLOSE_VXD					CTL_CODE_MPEG_VIDEO(20)

// Input:  PINT
// Output: None
#define IOCTL_MPEG_VIDEO_SET_DISPLAY_EVENT		CTL_CODE_MPEG_VIDEO(21)

#define IOCTL_MPEG_KAPOK_ENABLE_ZV				CTL_CODE_MPEG_VIDEO(22)
#define IOCTL_MPEG_KAPOK_ENABLE_CODEZV			CTL_CODE_MPEG_VIDEO(23)
#define IOCTL_MPEG_KAPOK_DISABLE_ZV				CTL_CODE_MPEG_VIDEO(24)

// Input:  PI2C_INFO
// Output: PI2C_INFO
#define IOCTL_MPEG_READ_I2C						CTL_CODE_MPEG_VIDEO(25)

// Input:  PI2C_INFO
// Output: None
#define IOCTL_MPEG_WRITE_I2C					CTL_CODE_MPEG_VIDEO(26)

// Input:  PULONG
// Output: None
#define IOCTL_MPEG_TV_MODE						CTL_CODE_MPEG_VIDEO(27)

// Input:  none
// Output: None
// added for multiple instance vxd RM8400
#define IOCTL_MPEG_OPEN_INSTANCE				CTL_CODE_MPEG_VIDEO(29)

// Input:  none
// Output: None
#define IOCTL_MPEG_CLOSE_INSTANCE				CTL_CODE_MPEG_VIDEO(30)

// Input:  none
// Output: None
#define IOCTL_MPEG_PROPERTY						CTL_CODE_MPEG_VIDEO(31)

//****************************************************************************
// MPEG_OVERLAY device IOCTLs
//****************************************************************************

// Input:  MPEG_OVERLAY_MODE
// Output: None
#define IOCTL_MPEG_OVERLAY_MODE				CTL_CODE_MPEG_OVERLAY(0)

// Input:  MPEG_OVERLAY_PLACEMENT
// Output: None
#define IOCTL_MPEG_OVERLAY_SET_DESTINATION	CTL_CODE_MPEG_OVERLAY(1)

// Input:  MPEG_OVERLAY_PLACEMENT
// Output: None
#define IOCTL_MPEG_OVERLAY_SET_SOURCE		CTL_CODE_MPEG_OVERLAY(2)

// Input:  MPEG_OVERLAY_KEY
// Output: None
#define IOCTL_MPEG_OVERLAY_SET_VGAKEY		CTL_CODE_MPEG_OVERLAY(3)

// Input:  MPEG_ATTRIBUTE
// Output: none
#define IOCTL_MPEG_OVERLAY_SET_ATTRIBUTE	CTL_CODE_MPEG_OVERLAY(4)

// Input:  none
// Output: MPEG_ATTRIBUTE
#define IOCTL_MPEG_OVERLAY_GET_ATTRIBUTE	CTL_CODE_MPEG_OVERLAY(5)

// Input:  MPEG_OVERLAY_BIT_MASK
// Output: none
#define IOCTL_MPEG_OVERLAY_SET_BIT_MASK		CTL_CODE_MPEG_OVERLAY(6)

// Input:  None
// Output: MPEG_OVERLAY_DEVICE_INFO
#define IOCTL_MPEG_OVERLAY_QUERY_DEVICE		CTL_CODE_MPEG_OVERLAY(7)

// Input:  None
// Output: MPEG_OVERLAY_KEY
#define IOCTL_MPEG_OVERLAY_GET_VGAKEY		CTL_CODE_MPEG_OVERLAY(8)

// Input:  POVERLAY_COLOUR_REGISTERS
// Output: POVERLAY_COLOUR_REGISTERS
#define IOCTL_MPEG_OVERLAY_CALIBRATE		CTL_CODE_MPEG_OVERLAY(9)

// Input:  PMPEG_OVERLAY_KEY2
// Output: None
#define IOCTL_MPEG_OVERLAY_SET_VGAKEY2		CTL_CODE_MPEG_OVERLAY(10)

// Input:  PCALIBRATION_PARAMETERS
// Output: None
#define IOCTL_MPEG_OVERLAY_SET_CALIBRATION	CTL_CODE_MPEG_OVERLAY(11)

//****************************************************************************
// MPEG_SPU device IOCTL (for hardware subpicture decoding)
//****************************************************************************

// Input:  IOCTL_MPEG_SPU_RESET
// Output: None
#define IOCTL_MPEG_SPU_RESET				CTL_CODE_MPEG_SPU(0)

// Input:  None
// Output: None
#define IOCTL_MPEG_SPU_PLAY					CTL_CODE_MPEG_SPU(1)

// Input:  IOCTL_MPEG_SPU_WRITE_PACKETS
// Output: None
#define IOCTL_MPEG_SPU_WRITE_PACKETS		CTL_CODE_MPEG_SPU(2)

// Input:  IOCTL_MPEG_SPU_WRITE_PACKETS
// Output: None
#define IOCTL_MPEG_PCI_WRITE_PACKETS		CTL_CODE_MPEG_SPU(3)

// Input:  IOCTL_MPEG_SPU_PAUSE
// Output: None
#define IOCTL_MPEG_SPU_PAUSE				CTL_CODE_MPEG_SPU(4)

// Input:  IOCTL_MPEG_SPU_STOP
// Output: None
#define IOCTL_MPEG_SPU_STOP					CTL_CODE_MPEG_SPU(5)

// Input:  IOCTL_MPEG_SPU_FREEZE
// Output: None
#define IOCTL_MPEG_SPU_FREEZE				CTL_CODE_MPEG_SPU(6)

// Input:  IOCTL_MPEG_SPU_GET_ATTRIBUTE
// Output: None
#define IOCTL_MPEG_SPU_GET_ATTRIBUTE		CTL_CODE_MPEG_SPU(7)

// Input:  IOCTL_MPEG_SPU_SET_ATTRIBUTE
// Output: None
#define IOCTL_MPEG_SPU_SET_ATTRIBUTE		CTL_CODE_MPEG_SPU(8)

// Input:  IOCTL_MPEG_SPU_HIGHLIGHT_COMMAND
// Output: None
#define IOCTL_MPEG_SPU_HIGHLIGHT_COMMAND	CTL_CODE_MPEG_SPU(9)

// Input:  IOCTL_MPEG_OSD_WRITE_PACKETS
// Output: None
#define IOCTL_MPEG_OSD_WRITE_PACKETS		CTL_CODE_MPEG_SPU(10)

// Input:  IOCTL_MPEG_SET_ATTRIBUTE
// Output: None
#define IOCTL_MPEG_OSD_SET_ATTRIBUTE		CTL_CODE_MPEG_SPU(11)

// Input:  IOCTL_MPEG_OSD_GET_ATTRIBUTE
// Output: None
#define IOCTL_MPEG_OSD_GET_ATTRIBUTE		CTL_CODE_MPEG_SPU(12)

// Input:  IOCTL_MPEG_OSD_RESET
// Output: None
#define IOCTL_MPEG_OSD_RESET				CTL_CODE_MPEG_SPU(13)

//****************************************************************************
// MPEG_MISC device IOCTLs
//****************************************************************************

// Input:  None
// Output: VXD_ADDRESS
#define IOCTL_MPEG_VXD_ADDRESS               CTL_CODE_MPEG_MISC(0)

// Input:  ??
// Output: ??
#define IOCTL_CHECK_SOFTICE                  CTL_CODE_MPEG_MISC(1)

// Input:  ??
// Output: ??
#define IOCTL_GET_MONITOR_VALUE              CTL_CODE_MPEG_MISC(2)

// Input:  ??
// Output: ??
#define IOCTL_GET_DESP_FUNC_TABLE            CTL_CODE_MPEG_MISC(3)

// Input:  ??
// Output: ??
#define IOCTL_SAVE_ORIGINAL_DATA             CTL_CODE_MPEG_MISC(4)

// Input:  ??
// Output: ??
#define IOCTL_END_TAMPER					 CTL_CODE_MPEG_MISC(5)

// Input:  ??
// Output: ??
#define IOCTL_ALLOCATE_CALL_GATE             CTL_CODE_MPEG_MISC(6)

// Input:  ??
// Output: ??
#define IOCTL_FREE_CALL_GATE                 CTL_CODE_MPEG_MISC(7)

// Input:  ??
// Output: ??
#define IOCTL_REGISTER_PROC                  CTL_CODE_MPEG_MISC(8)

// Input:  ??
// Output: ??
#define IOCTL_MPEG_GET_PERF_DATA			 CTL_CODE_MPEG_MISC(9)

// Input:  ??
// Output: ??
#define IOCTL_MPEG_BOARD_CONTROL			 CTL_CODE_MPEG_MISC(10)

// Input:  ULONG MemoryBase
// Output: none
#define IOCTL_MPEG_START_DEVICE				 CTL_CODE_MPEG_MISC(11)

// Input:  none
// Output: none
#define IOCTL_MPEG_STOP_DEVICE				 CTL_CODE_MPEG_MISC(12)

// Input:  none
// Output: PCM_RESOURCE_LIST
#define IOCTL_MPEG_GET_RESOURCES			 CTL_CODE_MPEG_MISC(13)

// Input:  none
// Output: PCM_RESOURCE_LIST
#define IOCTL_MPEG_START_INTERNAL			CTL_CODE_MPEG_MISC(14)

// Input:  advanced power management
// Output: none
#define IOCTL_APM_STATE						CTL_CODE_MPEG_MISC(15)

//****************************************************************************
// MPEG_PCM device IOCTLs
//****************************************************************************

// Input:  MPEG_ATTRIBUTE
// Output: None
#define IOCTL_MPEG_PCM_SET_ATTRIBUTE         CTL_CODE_MPEG_PCM(0)

// Input:  None
// Output: MPEG_ATTRIBUTE
#define IOCTL_MPEG_PCM_GET_ATTRIBUTE         CTL_CODE_MPEG_PCM(1)

// Input:  None
// Output: None
#define IOCTL_MPEG_PCM_PAUSE		         CTL_CODE_MPEG_PCM(2)

// Input:  None
// Output: None
#define IOCTL_MPEG_PCM_PLAY			         CTL_CODE_MPEG_PCM(3)

// Input:  None
// Output: None
#define IOCTL_MPEG_PCM_RESET		         CTL_CODE_MPEG_PCM(4)

// Input:  MPEG_PACKET_LIST[]
// Output: None
#define IOCTL_MPEG_PCM_WRITE			     CTL_CODE_MPEG_PCM(5)

// Input:  None
// Output: None
#define IOCTL_MPEG_PCM_END_OF_STREAM	     CTL_CODE_MPEG_PCM(6)


#endif  // #if _MPEG_H
