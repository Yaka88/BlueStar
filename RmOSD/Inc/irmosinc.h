#ifndef _IRMOSINC_H_INCLUDED_
#define _IRMOSINC_H_INCLUDED_

#include "rmbasictypes.h"		// __RMBASICTYPES_H__
#include "rmosbasictypes.h"		// __RMOSBASICTYPES_H__
/*
#ifndef _RM_BASE_TYPE_DEFINED_
#define _RM_BASE_TYPE_DEFINED_
	typedef unsigned char	RMUCHAR;
	typedef			 char	RMCHAR;
	typedef unsigned char	RMBYTE;
	typedef unsigned short	RMUSHORT;
	typedef          short	RMSHORT;
	typedef unsigned long	RMULONG;
	typedef          long	RMLONG;
	typedef unsigned int	RMUINT;
	typedef			 int	RMINT;
	typedef union {
		struct {
			DWORD LowPart;
			LONG HighPart;
		}u;
#ifdef _I64_DEFINED_
		LONGLONG QuadPart;
#else
		double QuadPart;
#endif
	}RM64;

#endif// _RM_BASE_TYPE_DEFINED_
*/


#ifndef _INTERFACE_TYPES_DEFINED_
#define _INTERFACE_TYPES_DEFINED_

//#ifdef _WINDOWS_
	#define	IRMCALLTYPE STDMETHODCALLTYPE
	#define DEFINE_RMID DEFINE_GUID
	#define REFRMID		const GUID &
	typedef HANDLE		RMHANDLE;
	typedef HRESULT		RMRESULT;
	typedef GUID		RMID;
	#define IRMBase		IUnknown
	DEFINE_RMID(IID_IRMBase				, 0x00000000,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);
/*#else
	#define	IRMCALLTYPE
	typedef void * RMHANDLE;
	typedef RMuint32 RMRESULT;

	typedef struct _RMID {          // size is 16
		RMuint32	Data1;
		RMuint16	Data2;
		RMuint16	Data3;
		RMuint8		Data4[8];
	} RMID;

	#define REFRMID	const RMID &
	DEFINE_RMID(IID_IRMBase				, 0x00000000,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);
	struct IRMBase
	{
	public:
		virtual RMRESULT IRMCALLTYPE QueryInterface(REFRMID riid,void **ppvObject) = 0;
		virtual RMULONG IRMCALLTYPE AddRef ( void) = 0;
		virtual RMULONG IRMCALLTYPE Release( void) = 0;
	};

#endif// _WINDOWS_*/
#endif// _INTERFACE_TYPES_DEFINED_
#endif // _IRMOSINC_H_INCLUDED_
