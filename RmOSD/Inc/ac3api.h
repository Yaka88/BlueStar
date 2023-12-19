// ac3api.h
//
// mac 6-24-1998



#ifndef AC3API_H_INCLUDED
#define AC3API_H_INCLUDED

#pragma once


#ifdef __cplusplus
extern "C" {
#endif


#define AC3_IMPORT __declspec(dllimport)

#define AC3_XFERMODE_NORMAL           0x00000001
#define AC3_XFERMODE_DONTNEEDPREAMBLE 0x00000002
	
typedef enum
{
	AC3_NOERR = 0,
	AC3_BADDEVICE,
	AC3_BADHANDLE,
	AC3_BADVALUE,
	AC3_BUSY,
	AC3_NOTSUPPORTED,
	AC3_NOTALLOWED,
	AC3_NOCANDO
}
AC3_ERR;

//typedef int AC3_HANDLE;
typedef unsigned long AC3_HANDLE;

// this is completely bogus, fix later!
//typedef int AC3_DEVICEINFO;

#ifndef __AC3_DEVICEINFO
#define __AC3_DEVICEINFO
typedef struct
{
    unsigned long dwDeviceNode;
    unsigned char szCardDesc[80];
}AC3_DEVICEINFO;
#endif

typedef unsigned long ULONG;
typedef void * PVOID;

// Function typedefs
typedef ULONG	(*FPAC3DEVICECOUNT)		(void);
typedef AC3_ERR (*FPAC3DEVICEINFO)		(ULONG, AC3_DEVICEINFO *, ULONG);
typedef AC3_ERR (*FPAC3OPEN)			(ULONG, AC3_HANDLE *, ULONG, ULONG);
typedef AC3_ERR (*FPAC3CLOSE)			(AC3_HANDLE);
typedef ULONG	(*FPAC3DATAFRAMES)		(AC3_HANDLE, PVOID, ULONG);
typedef ULONG	(*FPAC3SAMPLECOUNT)		(AC3_HANDLE);
typedef ULONG	(*FPAC3FRAMECOUNT)		(AC3_HANDLE);
typedef ULONG	(*FPAC3SAMPLERATE)		(AC3_HANDLE);
typedef AC3_ERR (*FPAC3RESET)			(AC3_HANDLE);
typedef AC3_ERR (*FPAC3START)			(AC3_HANDLE);
typedef AC3_ERR (*FPAC3STOP)			(AC3_HANDLE);
typedef AC3_ERR (*FPAC3FLUSH)			(AC3_HANDLE);
typedef AC3_ERR (*FPAC3NOTIFYEVENT)		(AC3_HANDLE, PVOID, ULONG, ULONG);
typedef ULONG	(*FPAC3BYTESACCEPTED)	(AC3_HANDLE);
typedef ULONG	(*FPAC3BYTECOUNT)		(AC3_HANDLE);
typedef AC3_ERR (*FPAC3SETXFERMODE)		(AC3_HANDLE, ULONG);


// Function table declaration
typedef struct 
{
	FPAC3DEVICECOUNT	AC3_DeviceCount;
	FPAC3DEVICEINFO		AC3_DeviceInfo;
	FPAC3OPEN			AC3_Open;
	FPAC3CLOSE			AC3_Close;
	FPAC3DATAFRAMES		AC3_DataFrames;
	FPAC3SAMPLECOUNT	AC3_SampleCount;
	FPAC3FRAMECOUNT		AC3_FrameCount;
	FPAC3SAMPLERATE		AC3_SampleRate;
	FPAC3RESET			AC3_Reset;
	FPAC3START			AC3_Start;
	FPAC3STOP			AC3_Stop;
	FPAC3FLUSH			AC3_Flush;
	FPAC3NOTIFYEVENT	AC3_NotifyEvent;
	FPAC3BYTESACCEPTED	AC3_BytesAccepted;
	FPAC3BYTECOUNT		AC3_ByteCount;
	FPAC3SETXFERMODE	AC3_SetXferMode;
} AC3FNTABLE, * PAC3FNTABLE;


AC3_IMPORT 
unsigned long AC3_DeviceCount(void);

AC3_IMPORT 
AC3_ERR AC3_DeviceInfo(unsigned long index, AC3_DEVICEINFO* pInfo, unsigned long infoBytes);

AC3_IMPORT 
AC3_ERR AC3_Open(unsigned long index, AC3_HANDLE* pHandle, unsigned long rate,
#ifdef __cplusplus
			 unsigned long reservedZero = 0);
#else
			 unsigned long reservedZero);
#endif

AC3_IMPORT 
AC3_ERR AC3_Close(AC3_HANDLE handle);

AC3_IMPORT 
unsigned long AC3_DataFrames(AC3_HANDLE handle, void* pData, unsigned long dataBytes);

AC3_IMPORT
unsigned long AC3_SampleCount(AC3_HANDLE handle);

AC3_IMPORT
unsigned long AC3_FrameCount(AC3_HANDLE handle);

AC3_IMPORT 
unsigned long AC3_SampleRate(AC3_HANDLE handle);

AC3_IMPORT 
AC3_ERR AC3_Reset(AC3_HANDLE handle);

AC3_IMPORT 
AC3_ERR AC3_Start(AC3_HANDLE handle);

AC3_IMPORT 
AC3_ERR AC3_Stop(AC3_HANDLE handle);

AC3_IMPORT 
AC3_ERR AC3_Flush(AC3_HANDLE handle);

AC3_IMPORT
AC3_ERR AC3_NotifyEvent(AC3_HANDLE handle, void* hEvent, unsigned long cFrames, unsigned long cLowBytes);

AC3_IMPORT
unsigned long AC3_BytesAccepted(AC3_HANDLE handle);

AC3_IMPORT
unsigned long AC3_ByteCount(AC3_HANDLE handle);

AC3_IMPORT
AC3_ERR AC3_SetXferMode(AC3_HANDLE handle, ULONG ulMode);

AC3_IMPORT
AC3_ERR GetAC3FunctionTable(ULONG ulVersion, PAC3FNTABLE *ppAC3FnTable);

#ifdef __cplusplus
}
#endif

#endif
