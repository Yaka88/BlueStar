/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Jan 17 18:24:24 2002
 */
/* Compiler settings for E:\users\Vladimir\rm8400\impegapi.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __impegapi_h__
#define __impegapi_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IPivateRegProfile_FWD_DEFINED__
#define __IPivateRegProfile_FWD_DEFINED__
typedef interface IPivateRegProfile IPivateRegProfile;
#endif 	/* __IPivateRegProfile_FWD_DEFINED__ */


#ifndef __IRmDeviceMoniker_FWD_DEFINED__
#define __IRmDeviceMoniker_FWD_DEFINED__
typedef interface IRmDeviceMoniker IRmDeviceMoniker;
#endif 	/* __IRmDeviceMoniker_FWD_DEFINED__ */


#ifndef __IRmDeviceEnumerator_FWD_DEFINED__
#define __IRmDeviceEnumerator_FWD_DEFINED__
typedef interface IRmDeviceEnumerator IRmDeviceEnumerator;
#endif 	/* __IRmDeviceEnumerator_FWD_DEFINED__ */


#ifndef __IRmDevice_FWD_DEFINED__
#define __IRmDevice_FWD_DEFINED__
typedef interface IRmDevice IRmDevice;
#endif 	/* __IRmDevice_FWD_DEFINED__ */


#ifndef __IRmBaseStreaming_FWD_DEFINED__
#define __IRmBaseStreaming_FWD_DEFINED__
typedef interface IRmBaseStreaming IRmBaseStreaming;
#endif 	/* __IRmBaseStreaming_FWD_DEFINED__ */


#ifndef __IRmVideo_FWD_DEFINED__
#define __IRmVideo_FWD_DEFINED__
typedef interface IRmVideo IRmVideo;
#endif 	/* __IRmVideo_FWD_DEFINED__ */


#ifndef __IRmAudio_FWD_DEFINED__
#define __IRmAudio_FWD_DEFINED__
typedef interface IRmAudio IRmAudio;
#endif 	/* __IRmAudio_FWD_DEFINED__ */


#ifndef __IRmOverlay_FWD_DEFINED__
#define __IRmOverlay_FWD_DEFINED__
typedef interface IRmOverlay IRmOverlay;
#endif 	/* __IRmOverlay_FWD_DEFINED__ */


#ifndef __IRmSubpicture_FWD_DEFINED__
#define __IRmSubpicture_FWD_DEFINED__
typedef interface IRmSubpicture IRmSubpicture;
#endif 	/* __IRmSubpicture_FWD_DEFINED__ */


#ifndef __IRmOSD_FWD_DEFINED__
#define __IRmOSD_FWD_DEFINED__
typedef interface IRmOSD IRmOSD;
#endif 	/* __IRmOSD_FWD_DEFINED__ */


#ifndef __IOverlayConfig_FWD_DEFINED__
#define __IOverlayConfig_FWD_DEFINED__
typedef interface IOverlayConfig IOverlayConfig;
#endif 	/* __IOverlayConfig_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_impegapi_0000 */
/* [local] */ 

typedef ULONG MPEG_STATUS;

typedef ULONG RM_STATE;

typedef ULONG DEVINSTINFO;

typedef ULONG REGISTERS;

typedef ULONG REGINFO;

#if 0
typedef /* [public] */ 
enum __MIDL___MIDL_itf_impegapi_0000_0001
    {	DIGITAL_AUDIO	= 0,
	PCM_AUDIO	= DIGITAL_AUDIO + 1,
	AC3_AUDIO	= PCM_AUDIO + 1
    }	AUDIO_OUTPUT;

typedef enum __MIDL___MIDL_itf_impegapi_0000_0001 __RPC_FAR *PAUDIO_OUTPUT;

typedef struct  _MPEG_ASYNC_CONTEXT
    {
    HANDLE hEvent;
    ULONG Reserved[ 10 ];
    }	MPEG_ASYNC_CONTEXT;

typedef struct _MPEG_ASYNC_CONTEXT __RPC_FAR *PMPEG_ASYNC_CONTEXT;

#endif
#ifdef TYPEDEF_HERE
typedef void CMediaType;

typedef void IMediaSample;

typedef ULONGLONG MPEG_SYSTEM_TIME;

typedef ULONG MPEG_ATTRIBUTE;

typedef ULONG MPEG_OVERLAY_MODE;

typedef void CALIBRATION_PARAMETERS;

typedef void __RPC_FAR *PFN_CALLBACK;

typedef void __RPC_FAR *PMPEG_EVENT;

typedef void MPEG_DEVICE_INFO;

typedef void __RPC_FAR *POVERLAY_COLOUR_REGISTERS;

typedef void __RPC_FAR *PCALIBRATION_PARAMETERS;

typedef ULONG MPEG_HLI_CMD;

typedef ULONG MPEG_OVERLAY_RECT;

#endif
#ifndef _RMDEV_CAPABILITIES_DEFINED_
#define _RMDEV_CAPABILITIES_DEFINED_
typedef /* [public][public][public][public] */ 
enum __MIDL___MIDL_itf_impegapi_0000_0002
    {	RMCAPF_dw2	= 0,
	RMCAPF_ull	= RMCAPF_dw2 + 1,
	RMCAPF_multi	= RMCAPF_ull + 1
    }	RMCAP_TYPE;

typedef /* [public][public][public][public] */ struct  __MIDL___MIDL_itf_impegapi_0000_0003
    {
    ULONG Size;
    ULONG Count;
    }	RMMULTIPLE_ITEM;

typedef struct __MIDL___MIDL_itf_impegapi_0000_0003 __RPC_FAR *PRMMULTIPLE_ITEM;

typedef /* [public][public] */ struct  __MIDL___MIDL_itf_impegapi_0000_0004
    {
    RMCAP_TYPE type;
    ULONG reserved;
    union 
        {
        ULONG dwCaps[ 2 ];
        ULONGLONG ullCaps;
        RMMULTIPLE_ITEM multi_header;
        }	u;
    }	RMDEV_CAPABILITIES;

typedef struct __MIDL___MIDL_itf_impegapi_0000_0004 __RPC_FAR *PRMDEV_CAPABILITIES;

#endif
#ifdef DEFINE_KS
typedef /* [public][public][public][public][public] */ struct  __MIDL___MIDL_itf_impegapi_0000_0006
    {
    LONGLONG Time;
    ULONG Numerator;
    ULONG Denominator;
    }	KSTIME;

typedef struct __MIDL___MIDL_itf_impegapi_0000_0006 __RPC_FAR *PKSTIME;

typedef /* [public][public][public] */ struct  __MIDL___MIDL_itf_impegapi_0000_0007
    {
    ULONG Size;
    ULONG TypeSpecificFlags;
    KSTIME PresentationTime;
    LONGLONG Duration;
    ULONG FrameExtent;
    ULONG DataUsed;
    PVOID Data;
    ULONG OptionsFlags;
    }	KSSTREAM_HEADER;

typedef struct __MIDL___MIDL_itf_impegapi_0000_0007 __RPC_FAR *PKSSTREAM_HEADER;

typedef /* [public][public][public][public][public][public][public][public] */ struct  __MIDL___MIDL_itf_impegapi_0000_0008
    {
    union 
        {
        struct  
            {
            GUID Set;
            ULONG Id;
            ULONG Flags;
            }	;
        LONGLONG Alignment;
        }	;
    }	KSIDENTIFIER;

typedef struct __MIDL___MIDL_itf_impegapi_0000_0008 __RPC_FAR *PKSIDENTIFIER;

typedef KSIDENTIFIER KSPROPERTY;

typedef KSIDENTIFIER __RPC_FAR *PKSPROPERTY;

typedef KSIDENTIFIER KSMETHOD;

typedef KSIDENTIFIER __RPC_FAR *PKSMETHOD;

typedef KSIDENTIFIER KSEVENT;

typedef KSIDENTIFIER __RPC_FAR *PKSEVENT;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_impegapi_0000_0011
    {	KSSTATE_STOP	= 0,
	KSSTATE_ACQUIRE	= KSSTATE_STOP + 1,
	KSSTATE_PAUSE	= KSSTATE_ACQUIRE + 1,
	KSSTATE_RUN	= KSSTATE_PAUSE + 1
    }	KSSTATE;

typedef enum __MIDL___MIDL_itf_impegapi_0000_0011 __RPC_FAR *PKSSTATE;

#endif
#ifdef DEFINE_OVERLAPPED
typedef struct  _OVERLAPPED
    {
    DWORD Internal;
    DWORD InternalHigh;
    DWORD Offset;
    DWORD OffsetHigh;
    HANDLE hEvent;
    }	OVERLAPPED;

typedef struct _OVERLAPPED __RPC_FAR *LPOVERLAPPED;

#endif
#if 0
typedef struct  tagCOLOR_LIMITS
    {
    COLORREF crKeyColor;
    COLORREF crUpperLimit;
    COLORREF crLowerLimit;
    }	COLOR_LIMITS;

typedef struct tagCOLOR_LIMITS __RPC_FAR *PCOLOR_LIMITS;

#endif
typedef /* [public] */ 
enum __MIDL___MIDL_itf_impegapi_0000_0012
    {	RMDEVMONIKER_INFOTYPE_NOT_DEFINED	= 0,
	RMDEVMONIKER_INFOTYPE_SUBSYSTEM_ID	= RMDEVMONIKER_INFOTYPE_NOT_DEFINED + 1,
	RMDEVMONIKER_INFOTYPE_BUS_NUMBER	= RMDEVMONIKER_INFOTYPE_SUBSYSTEM_ID + 1,
	RMDEVMONIKER_INFOTYPE_NUMBER	= RMDEVMONIKER_INFOTYPE_BUS_NUMBER + 1,
	RMDEVMONIKER_INFOTYPE_FUNC_NUMBER	= RMDEVMONIKER_INFOTYPE_NUMBER + 1
    }	RMDEVMONIKER_INFOTYPE;

DEFINE_GUID(CLSID_rm8400             , 0x2f921938,0x54ab,0x4fc3,0x8a,0xdf,0x71,0x9b,0x8c,0xc8,0xf4,0xbb);
DEFINE_GUID(IID_IPivateRegProfile    , 0xEE543A70,0x2D27,0x43fb,0x96,0x6F,0xCC,0xF8,0xE5,0x39,0x6E,0x62);
DEFINE_GUID(IID_IRmDevice            , 0x5D896824,0x4239,0x4ddb,0xAF,0x13,0xC8,0x09,0x36,0xC2,0x46,0xBD);
DEFINE_GUID(IID_IRmBaseStreaming     , 0x4757FEB1,0x883D,0x41d4,0x99,0x0B,0x2E,0x7E,0x90,0x18,0xB7,0x3A);
DEFINE_GUID(IID_IRmVideo             , 0x4F8A6623,0xF303,0x4d23,0x92,0x3F,0x5A,0xD3,0x70,0x7E,0x5B,0xF0);
DEFINE_GUID(IID_IRmAudio             , 0x48394E01,0x8A68,0x48fa,0xA9,0x0F,0x77,0xCD,0x65,0x52,0xFB,0x1E);
DEFINE_GUID(IID_IRmOverlay           , 0xFC017BFF,0x301E,0x475a,0xA0,0x6E,0x42,0xF2,0xCA,0x00,0x73,0x96);
DEFINE_GUID(IID_IRmSubpicture        , 0xF934C7A2,0x4192,0x4b19,0xB3,0x11,0x09,0x72,0xC3,0xC7,0x47,0x57);
DEFINE_GUID(IID_IRmOSD               , 0x41189722,0x20DF,0x43a8,0x87,0x19,0xF9,0x56,0xDD,0x8B,0xB9,0x70);
DEFINE_GUID(IID_IOverlayConfig       , 0xA22206B3,0x93C2,0x45a9,0xB1,0x97,0xFE,0x40,0x7D,0xD0,0x28,0x25);
DEFINE_GUID(IID_IRmDeviceMoniker     , 0x77167D8A,0x8090,0x11d5,0xB8,0x5E,0x00,0x90,0x27,0x65,0xE1,0x6C);
DEFINE_GUID(IID_IRmDeviceEnumerator  , 0xCD83BC0A,0x8090,0x11d5,0xB8,0x5E,0x00,0x90,0x27,0x65,0xE1,0x6C);


extern RPC_IF_HANDLE __MIDL_itf_impegapi_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_impegapi_0000_v0_0_s_ifspec;

#ifndef __IPivateRegProfile_INTERFACE_DEFINED__
#define __IPivateRegProfile_INTERFACE_DEFINED__

/* interface IPivateRegProfile */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IPivateRegProfile;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EE543A70-2D27-43fb-966F-CCF8E5396E62")
    IPivateRegProfile : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetInt( 
            TCHAR __RPC_FAR *SectionName,
            TCHAR __RPC_FAR *ValueName,
            int Default,
            int __RPC_FAR *pValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WriteInt( 
            TCHAR __RPC_FAR *SectionName,
            TCHAR __RPC_FAR *ValueName,
            int Value) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WriteDisplayInt( 
            TCHAR __RPC_FAR *ValueName,
            int Value) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDisplayInt( 
            TCHAR __RPC_FAR *ValueName,
            int Default,
            int __RPC_FAR *Value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPivateRegProfileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPivateRegProfile __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPivateRegProfile __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPivateRegProfile __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInt )( 
            IPivateRegProfile __RPC_FAR * This,
            TCHAR __RPC_FAR *SectionName,
            TCHAR __RPC_FAR *ValueName,
            int Default,
            int __RPC_FAR *pValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WriteInt )( 
            IPivateRegProfile __RPC_FAR * This,
            TCHAR __RPC_FAR *SectionName,
            TCHAR __RPC_FAR *ValueName,
            int Value);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WriteDisplayInt )( 
            IPivateRegProfile __RPC_FAR * This,
            TCHAR __RPC_FAR *ValueName,
            int Value);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDisplayInt )( 
            IPivateRegProfile __RPC_FAR * This,
            TCHAR __RPC_FAR *ValueName,
            int Default,
            int __RPC_FAR *Value);
        
        END_INTERFACE
    } IPivateRegProfileVtbl;

    interface IPivateRegProfile
    {
        CONST_VTBL struct IPivateRegProfileVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPivateRegProfile_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPivateRegProfile_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPivateRegProfile_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPivateRegProfile_GetInt(This,SectionName,ValueName,Default,pValue)	\
    (This)->lpVtbl -> GetInt(This,SectionName,ValueName,Default,pValue)

#define IPivateRegProfile_WriteInt(This,SectionName,ValueName,Value)	\
    (This)->lpVtbl -> WriteInt(This,SectionName,ValueName,Value)

#define IPivateRegProfile_WriteDisplayInt(This,ValueName,Value)	\
    (This)->lpVtbl -> WriteDisplayInt(This,ValueName,Value)

#define IPivateRegProfile_GetDisplayInt(This,ValueName,Default,Value)	\
    (This)->lpVtbl -> GetDisplayInt(This,ValueName,Default,Value)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPivateRegProfile_GetInt_Proxy( 
    IPivateRegProfile __RPC_FAR * This,
    TCHAR __RPC_FAR *SectionName,
    TCHAR __RPC_FAR *ValueName,
    int Default,
    int __RPC_FAR *pValue);


void __RPC_STUB IPivateRegProfile_GetInt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPivateRegProfile_WriteInt_Proxy( 
    IPivateRegProfile __RPC_FAR * This,
    TCHAR __RPC_FAR *SectionName,
    TCHAR __RPC_FAR *ValueName,
    int Value);


void __RPC_STUB IPivateRegProfile_WriteInt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPivateRegProfile_WriteDisplayInt_Proxy( 
    IPivateRegProfile __RPC_FAR * This,
    TCHAR __RPC_FAR *ValueName,
    int Value);


void __RPC_STUB IPivateRegProfile_WriteDisplayInt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPivateRegProfile_GetDisplayInt_Proxy( 
    IPivateRegProfile __RPC_FAR * This,
    TCHAR __RPC_FAR *ValueName,
    int Default,
    int __RPC_FAR *Value);


void __RPC_STUB IPivateRegProfile_GetDisplayInt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPivateRegProfile_INTERFACE_DEFINED__ */


#ifndef __IRmDeviceMoniker_INTERFACE_DEFINED__
#define __IRmDeviceMoniker_INTERFACE_DEFINED__

/* interface IRmDeviceMoniker */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IRmDeviceMoniker;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("77167D8A-8090-11d5-B85E-00902765E16C")
    IRmDeviceMoniker : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE BindToObject( 
            REFIID riid,
            void __RPC_FAR *__RPC_FAR *ppObj) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDisplayName( 
            LPOLESTR __RPC_FAR *ppszName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetInstanceID( 
            LPOLESTR __RPC_FAR *ppszID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsRunning( void) = 0;
        
        virtual DWORD STDMETHODCALLTYPE GetInfo( 
            DWORD type,
            PVOID buffer,
            DWORD size,
            HRESULT __RPC_FAR *phr) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRmDeviceMonikerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRmDeviceMoniker __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRmDeviceMoniker __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRmDeviceMoniker __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BindToObject )( 
            IRmDeviceMoniker __RPC_FAR * This,
            REFIID riid,
            void __RPC_FAR *__RPC_FAR *ppObj);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDisplayName )( 
            IRmDeviceMoniker __RPC_FAR * This,
            LPOLESTR __RPC_FAR *ppszName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInstanceID )( 
            IRmDeviceMoniker __RPC_FAR * This,
            LPOLESTR __RPC_FAR *ppszID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsRunning )( 
            IRmDeviceMoniker __RPC_FAR * This);
        
        DWORD ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IRmDeviceMoniker __RPC_FAR * This,
            DWORD type,
            PVOID buffer,
            DWORD size,
            HRESULT __RPC_FAR *phr);
        
        END_INTERFACE
    } IRmDeviceMonikerVtbl;

    interface IRmDeviceMoniker
    {
        CONST_VTBL struct IRmDeviceMonikerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRmDeviceMoniker_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRmDeviceMoniker_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRmDeviceMoniker_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRmDeviceMoniker_BindToObject(This,riid,ppObj)	\
    (This)->lpVtbl -> BindToObject(This,riid,ppObj)

#define IRmDeviceMoniker_GetDisplayName(This,ppszName)	\
    (This)->lpVtbl -> GetDisplayName(This,ppszName)

#define IRmDeviceMoniker_GetInstanceID(This,ppszID)	\
    (This)->lpVtbl -> GetInstanceID(This,ppszID)

#define IRmDeviceMoniker_IsRunning(This)	\
    (This)->lpVtbl -> IsRunning(This)

#define IRmDeviceMoniker_GetInfo(This,type,buffer,size,phr)	\
    (This)->lpVtbl -> GetInfo(This,type,buffer,size,phr)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRmDeviceMoniker_BindToObject_Proxy( 
    IRmDeviceMoniker __RPC_FAR * This,
    REFIID riid,
    void __RPC_FAR *__RPC_FAR *ppObj);


void __RPC_STUB IRmDeviceMoniker_BindToObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmDeviceMoniker_GetDisplayName_Proxy( 
    IRmDeviceMoniker __RPC_FAR * This,
    LPOLESTR __RPC_FAR *ppszName);


void __RPC_STUB IRmDeviceMoniker_GetDisplayName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmDeviceMoniker_GetInstanceID_Proxy( 
    IRmDeviceMoniker __RPC_FAR * This,
    LPOLESTR __RPC_FAR *ppszID);


void __RPC_STUB IRmDeviceMoniker_GetInstanceID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmDeviceMoniker_IsRunning_Proxy( 
    IRmDeviceMoniker __RPC_FAR * This);


void __RPC_STUB IRmDeviceMoniker_IsRunning_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


DWORD STDMETHODCALLTYPE IRmDeviceMoniker_GetInfo_Proxy( 
    IRmDeviceMoniker __RPC_FAR * This,
    DWORD type,
    PVOID buffer,
    DWORD size,
    HRESULT __RPC_FAR *phr);


void __RPC_STUB IRmDeviceMoniker_GetInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRmDeviceMoniker_INTERFACE_DEFINED__ */


#ifndef __IRmDeviceEnumerator_INTERFACE_DEFINED__
#define __IRmDeviceEnumerator_INTERFACE_DEFINED__

/* interface IRmDeviceEnumerator */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IRmDeviceEnumerator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CD83BC0A-8090-11d5-B85E-00902765E16C")
    IRmDeviceEnumerator : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            IRmDeviceMoniker __RPC_FAR *__RPC_FAR *ppIRmDeviceMoniker) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRmDeviceEnumeratorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRmDeviceEnumerator __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRmDeviceEnumerator __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRmDeviceEnumerator __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IRmDeviceEnumerator __RPC_FAR * This,
            IRmDeviceMoniker __RPC_FAR *__RPC_FAR *ppIRmDeviceMoniker);
        
        END_INTERFACE
    } IRmDeviceEnumeratorVtbl;

    interface IRmDeviceEnumerator
    {
        CONST_VTBL struct IRmDeviceEnumeratorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRmDeviceEnumerator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRmDeviceEnumerator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRmDeviceEnumerator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRmDeviceEnumerator_Next(This,ppIRmDeviceMoniker)	\
    (This)->lpVtbl -> Next(This,ppIRmDeviceMoniker)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRmDeviceEnumerator_Next_Proxy( 
    IRmDeviceEnumerator __RPC_FAR * This,
    IRmDeviceMoniker __RPC_FAR *__RPC_FAR *ppIRmDeviceMoniker);


void __RPC_STUB IRmDeviceEnumerator_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRmDeviceEnumerator_INTERFACE_DEFINED__ */


#ifndef __IRmDevice_INTERFACE_DEFINED__
#define __IRmDevice_INTERFACE_DEFINED__

/* interface IRmDevice */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IRmDevice;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5D896824-4239-4ddb-AF13-C80936C246BD")
    IRmDevice : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetDevInstanceInfo( 
            DEVINSTINFO __RPC_FAR *pDevInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRegistersInfo( 
            REGINFO __RPC_FAR *pRegInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDeviceRegisters( 
            REGISTERS __RPC_FAR *pRegs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDeviceRegisters( 
            REGISTERS __RPC_FAR *pRegs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDeviceCapabilities( 
            RMDEV_CAPABILITIES __RPC_FAR *pCaps) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAttributes( 
            MPEG_ATTRIBUTE eAttribute,
            LONG lValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAttributes( 
            MPEG_ATTRIBUTE eAttribute,
            LONG __RPC_FAR *lValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetHwLibProperty( 
            DWORD PropertySetID,
            DWORD PropertyItemID,
            DWORD PropertyItemFlags,
            DWORD PropertySize,
            PVOID pPropertyData,
            DWORD __RPC_FAR *cbReturn) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetHwLibProperty( 
            DWORD PropertySetID,
            DWORD PropertyItemID,
            DWORD PropertyItemFlags,
            DWORD PropertySize,
            PVOID pPropertyData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRmDeviceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRmDevice __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRmDevice __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRmDevice __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDevInstanceInfo )( 
            IRmDevice __RPC_FAR * This,
            DEVINSTINFO __RPC_FAR *pDevInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRegistersInfo )( 
            IRmDevice __RPC_FAR * This,
            REGINFO __RPC_FAR *pRegInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDeviceRegisters )( 
            IRmDevice __RPC_FAR * This,
            REGISTERS __RPC_FAR *pRegs);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDeviceRegisters )( 
            IRmDevice __RPC_FAR * This,
            REGISTERS __RPC_FAR *pRegs);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDeviceCapabilities )( 
            IRmDevice __RPC_FAR * This,
            RMDEV_CAPABILITIES __RPC_FAR *pCaps);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAttributes )( 
            IRmDevice __RPC_FAR * This,
            MPEG_ATTRIBUTE eAttribute,
            LONG lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAttributes )( 
            IRmDevice __RPC_FAR * This,
            MPEG_ATTRIBUTE eAttribute,
            LONG __RPC_FAR *lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHwLibProperty )( 
            IRmDevice __RPC_FAR * This,
            DWORD PropertySetID,
            DWORD PropertyItemID,
            DWORD PropertyItemFlags,
            DWORD PropertySize,
            PVOID pPropertyData,
            DWORD __RPC_FAR *cbReturn);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetHwLibProperty )( 
            IRmDevice __RPC_FAR * This,
            DWORD PropertySetID,
            DWORD PropertyItemID,
            DWORD PropertyItemFlags,
            DWORD PropertySize,
            PVOID pPropertyData);
        
        END_INTERFACE
    } IRmDeviceVtbl;

    interface IRmDevice
    {
        CONST_VTBL struct IRmDeviceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRmDevice_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRmDevice_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRmDevice_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRmDevice_GetDevInstanceInfo(This,pDevInfo)	\
    (This)->lpVtbl -> GetDevInstanceInfo(This,pDevInfo)

#define IRmDevice_GetRegistersInfo(This,pRegInfo)	\
    (This)->lpVtbl -> GetRegistersInfo(This,pRegInfo)

#define IRmDevice_GetDeviceRegisters(This,pRegs)	\
    (This)->lpVtbl -> GetDeviceRegisters(This,pRegs)

#define IRmDevice_SetDeviceRegisters(This,pRegs)	\
    (This)->lpVtbl -> SetDeviceRegisters(This,pRegs)

#define IRmDevice_GetDeviceCapabilities(This,pCaps)	\
    (This)->lpVtbl -> GetDeviceCapabilities(This,pCaps)

#define IRmDevice_SetAttributes(This,eAttribute,lValue)	\
    (This)->lpVtbl -> SetAttributes(This,eAttribute,lValue)

#define IRmDevice_GetAttributes(This,eAttribute,lValue)	\
    (This)->lpVtbl -> GetAttributes(This,eAttribute,lValue)

#define IRmDevice_GetHwLibProperty(This,PropertySetID,PropertyItemID,PropertyItemFlags,PropertySize,pPropertyData,cbReturn)	\
    (This)->lpVtbl -> GetHwLibProperty(This,PropertySetID,PropertyItemID,PropertyItemFlags,PropertySize,pPropertyData,cbReturn)

#define IRmDevice_SetHwLibProperty(This,PropertySetID,PropertyItemID,PropertyItemFlags,PropertySize,pPropertyData)	\
    (This)->lpVtbl -> SetHwLibProperty(This,PropertySetID,PropertyItemID,PropertyItemFlags,PropertySize,pPropertyData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRmDevice_GetDevInstanceInfo_Proxy( 
    IRmDevice __RPC_FAR * This,
    DEVINSTINFO __RPC_FAR *pDevInfo);


void __RPC_STUB IRmDevice_GetDevInstanceInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmDevice_GetRegistersInfo_Proxy( 
    IRmDevice __RPC_FAR * This,
    REGINFO __RPC_FAR *pRegInfo);


void __RPC_STUB IRmDevice_GetRegistersInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmDevice_GetDeviceRegisters_Proxy( 
    IRmDevice __RPC_FAR * This,
    REGISTERS __RPC_FAR *pRegs);


void __RPC_STUB IRmDevice_GetDeviceRegisters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmDevice_SetDeviceRegisters_Proxy( 
    IRmDevice __RPC_FAR * This,
    REGISTERS __RPC_FAR *pRegs);


void __RPC_STUB IRmDevice_SetDeviceRegisters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmDevice_GetDeviceCapabilities_Proxy( 
    IRmDevice __RPC_FAR * This,
    RMDEV_CAPABILITIES __RPC_FAR *pCaps);


void __RPC_STUB IRmDevice_GetDeviceCapabilities_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmDevice_SetAttributes_Proxy( 
    IRmDevice __RPC_FAR * This,
    MPEG_ATTRIBUTE eAttribute,
    LONG lValue);


void __RPC_STUB IRmDevice_SetAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmDevice_GetAttributes_Proxy( 
    IRmDevice __RPC_FAR * This,
    MPEG_ATTRIBUTE eAttribute,
    LONG __RPC_FAR *lValue);


void __RPC_STUB IRmDevice_GetAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmDevice_GetHwLibProperty_Proxy( 
    IRmDevice __RPC_FAR * This,
    DWORD PropertySetID,
    DWORD PropertyItemID,
    DWORD PropertyItemFlags,
    DWORD PropertySize,
    PVOID pPropertyData,
    DWORD __RPC_FAR *cbReturn);


void __RPC_STUB IRmDevice_GetHwLibProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmDevice_SetHwLibProperty_Proxy( 
    IRmDevice __RPC_FAR * This,
    DWORD PropertySetID,
    DWORD PropertyItemID,
    DWORD PropertyItemFlags,
    DWORD PropertySize,
    PVOID pPropertyData);


void __RPC_STUB IRmDevice_SetHwLibProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRmDevice_INTERFACE_DEFINED__ */


#ifndef __IRmBaseStreaming_INTERFACE_DEFINED__
#define __IRmBaseStreaming_INTERFACE_DEFINED__

/* interface IRmBaseStreaming */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IRmBaseStreaming;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4757FEB1-883D-41d4-990B-2E7E9018B73A")
    IRmBaseStreaming : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Property( 
            /* [in] */ PKSPROPERTY KSID,
            /* [in] */ ULONG KSID_size,
            /* [in] */ PVOID prop,
            /* [in] */ ULONG prop_size,
            /* [out] */ ULONG __RPC_FAR *bret) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Play( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Pause( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Write( 
            KSSTREAM_HEADER __RPC_FAR *pHeaders,
            ULONG HeadersCount,
            OVERLAPPED __RPC_FAR *ovr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Read( 
            KSSTREAM_HEADER __RPC_FAR *pHeaders,
            ULONG HeadersCount,
            OVERLAPPED __RPC_FAR *ovr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BeginFlush( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EndFlush( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAttributes( 
            /* [in] */ MPEG_ATTRIBUTE eAttribute,
            /* [in] */ LONG lValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAttributes( 
            /* [in] */ MPEG_ATTRIBUTE eAttribute,
            /* [out] */ LONG __RPC_FAR *lValue) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRmBaseStreamingVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRmBaseStreaming __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRmBaseStreaming __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRmBaseStreaming __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Property )( 
            IRmBaseStreaming __RPC_FAR * This,
            /* [in] */ PKSPROPERTY KSID,
            /* [in] */ ULONG KSID_size,
            /* [in] */ PVOID prop,
            /* [in] */ ULONG prop_size,
            /* [out] */ ULONG __RPC_FAR *bret);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Play )( 
            IRmBaseStreaming __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Pause )( 
            IRmBaseStreaming __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IRmBaseStreaming __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Write )( 
            IRmBaseStreaming __RPC_FAR * This,
            KSSTREAM_HEADER __RPC_FAR *pHeaders,
            ULONG HeadersCount,
            OVERLAPPED __RPC_FAR *ovr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Read )( 
            IRmBaseStreaming __RPC_FAR * This,
            KSSTREAM_HEADER __RPC_FAR *pHeaders,
            ULONG HeadersCount,
            OVERLAPPED __RPC_FAR *ovr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BeginFlush )( 
            IRmBaseStreaming __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EndFlush )( 
            IRmBaseStreaming __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAttributes )( 
            IRmBaseStreaming __RPC_FAR * This,
            /* [in] */ MPEG_ATTRIBUTE eAttribute,
            /* [in] */ LONG lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAttributes )( 
            IRmBaseStreaming __RPC_FAR * This,
            /* [in] */ MPEG_ATTRIBUTE eAttribute,
            /* [out] */ LONG __RPC_FAR *lValue);
        
        END_INTERFACE
    } IRmBaseStreamingVtbl;

    interface IRmBaseStreaming
    {
        CONST_VTBL struct IRmBaseStreamingVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRmBaseStreaming_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRmBaseStreaming_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRmBaseStreaming_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRmBaseStreaming_Property(This,KSID,KSID_size,prop,prop_size,bret)	\
    (This)->lpVtbl -> Property(This,KSID,KSID_size,prop,prop_size,bret)

#define IRmBaseStreaming_Play(This)	\
    (This)->lpVtbl -> Play(This)

#define IRmBaseStreaming_Pause(This)	\
    (This)->lpVtbl -> Pause(This)

#define IRmBaseStreaming_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IRmBaseStreaming_Write(This,pHeaders,HeadersCount,ovr)	\
    (This)->lpVtbl -> Write(This,pHeaders,HeadersCount,ovr)

#define IRmBaseStreaming_Read(This,pHeaders,HeadersCount,ovr)	\
    (This)->lpVtbl -> Read(This,pHeaders,HeadersCount,ovr)

#define IRmBaseStreaming_BeginFlush(This)	\
    (This)->lpVtbl -> BeginFlush(This)

#define IRmBaseStreaming_EndFlush(This)	\
    (This)->lpVtbl -> EndFlush(This)

#define IRmBaseStreaming_SetAttributes(This,eAttribute,lValue)	\
    (This)->lpVtbl -> SetAttributes(This,eAttribute,lValue)

#define IRmBaseStreaming_GetAttributes(This,eAttribute,lValue)	\
    (This)->lpVtbl -> GetAttributes(This,eAttribute,lValue)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRmBaseStreaming_Property_Proxy( 
    IRmBaseStreaming __RPC_FAR * This,
    /* [in] */ PKSPROPERTY KSID,
    /* [in] */ ULONG KSID_size,
    /* [in] */ PVOID prop,
    /* [in] */ ULONG prop_size,
    /* [out] */ ULONG __RPC_FAR *bret);


void __RPC_STUB IRmBaseStreaming_Property_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmBaseStreaming_Play_Proxy( 
    IRmBaseStreaming __RPC_FAR * This);


void __RPC_STUB IRmBaseStreaming_Play_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmBaseStreaming_Pause_Proxy( 
    IRmBaseStreaming __RPC_FAR * This);


void __RPC_STUB IRmBaseStreaming_Pause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmBaseStreaming_Stop_Proxy( 
    IRmBaseStreaming __RPC_FAR * This);


void __RPC_STUB IRmBaseStreaming_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmBaseStreaming_Write_Proxy( 
    IRmBaseStreaming __RPC_FAR * This,
    KSSTREAM_HEADER __RPC_FAR *pHeaders,
    ULONG HeadersCount,
    OVERLAPPED __RPC_FAR *ovr);


void __RPC_STUB IRmBaseStreaming_Write_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmBaseStreaming_Read_Proxy( 
    IRmBaseStreaming __RPC_FAR * This,
    KSSTREAM_HEADER __RPC_FAR *pHeaders,
    ULONG HeadersCount,
    OVERLAPPED __RPC_FAR *ovr);


void __RPC_STUB IRmBaseStreaming_Read_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmBaseStreaming_BeginFlush_Proxy( 
    IRmBaseStreaming __RPC_FAR * This);


void __RPC_STUB IRmBaseStreaming_BeginFlush_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmBaseStreaming_EndFlush_Proxy( 
    IRmBaseStreaming __RPC_FAR * This);


void __RPC_STUB IRmBaseStreaming_EndFlush_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmBaseStreaming_SetAttributes_Proxy( 
    IRmBaseStreaming __RPC_FAR * This,
    /* [in] */ MPEG_ATTRIBUTE eAttribute,
    /* [in] */ LONG lValue);


void __RPC_STUB IRmBaseStreaming_SetAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmBaseStreaming_GetAttributes_Proxy( 
    IRmBaseStreaming __RPC_FAR * This,
    /* [in] */ MPEG_ATTRIBUTE eAttribute,
    /* [out] */ LONG __RPC_FAR *lValue);


void __RPC_STUB IRmBaseStreaming_GetAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRmBaseStreaming_INTERFACE_DEFINED__ */


#ifndef __IRmVideo_INTERFACE_DEFINED__
#define __IRmVideo_INTERFACE_DEFINED__

/* interface IRmVideo */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IRmVideo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F8A6623-F303-4d23-923F-5AD3707E5BF0")
    IRmVideo : public IRmBaseStreaming
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ClearBuffer( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSTC( 
            MPEG_SYSTEM_TIME __RPC_FAR *pTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSTC( 
            MPEG_SYSTEM_TIME __RPC_FAR *pTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SyncToAudio( 
            MPEG_SYSTEM_TIME systemTimeDelta) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CaptureToBuffer( 
            UCHAR __RPC_FAR *pBmp,
            ULONG ulSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPositionEvent( 
            PMPEG_EVENT pEvent,
            PMPEG_ASYNC_CONTEXT pAsyncContext) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDeviceInfo( 
            MPEG_DEVICE_INFO __RPC_FAR *deviceInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRmVideoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRmVideo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRmVideo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRmVideo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Property )( 
            IRmVideo __RPC_FAR * This,
            /* [in] */ PKSPROPERTY KSID,
            /* [in] */ ULONG KSID_size,
            /* [in] */ PVOID prop,
            /* [in] */ ULONG prop_size,
            /* [out] */ ULONG __RPC_FAR *bret);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Play )( 
            IRmVideo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Pause )( 
            IRmVideo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IRmVideo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Write )( 
            IRmVideo __RPC_FAR * This,
            KSSTREAM_HEADER __RPC_FAR *pHeaders,
            ULONG HeadersCount,
            OVERLAPPED __RPC_FAR *ovr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Read )( 
            IRmVideo __RPC_FAR * This,
            KSSTREAM_HEADER __RPC_FAR *pHeaders,
            ULONG HeadersCount,
            OVERLAPPED __RPC_FAR *ovr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BeginFlush )( 
            IRmVideo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EndFlush )( 
            IRmVideo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAttributes )( 
            IRmVideo __RPC_FAR * This,
            /* [in] */ MPEG_ATTRIBUTE eAttribute,
            /* [in] */ LONG lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAttributes )( 
            IRmVideo __RPC_FAR * This,
            /* [in] */ MPEG_ATTRIBUTE eAttribute,
            /* [out] */ LONG __RPC_FAR *lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IRmVideo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClearBuffer )( 
            IRmVideo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSTC )( 
            IRmVideo __RPC_FAR * This,
            MPEG_SYSTEM_TIME __RPC_FAR *pTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSTC )( 
            IRmVideo __RPC_FAR * This,
            MPEG_SYSTEM_TIME __RPC_FAR *pTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SyncToAudio )( 
            IRmVideo __RPC_FAR * This,
            MPEG_SYSTEM_TIME systemTimeDelta);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CaptureToBuffer )( 
            IRmVideo __RPC_FAR * This,
            UCHAR __RPC_FAR *pBmp,
            ULONG ulSize);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPositionEvent )( 
            IRmVideo __RPC_FAR * This,
            PMPEG_EVENT pEvent,
            PMPEG_ASYNC_CONTEXT pAsyncContext);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDeviceInfo )( 
            IRmVideo __RPC_FAR * This,
            MPEG_DEVICE_INFO __RPC_FAR *deviceInfo);
        
        END_INTERFACE
    } IRmVideoVtbl;

    interface IRmVideo
    {
        CONST_VTBL struct IRmVideoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRmVideo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRmVideo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRmVideo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRmVideo_Property(This,KSID,KSID_size,prop,prop_size,bret)	\
    (This)->lpVtbl -> Property(This,KSID,KSID_size,prop,prop_size,bret)

#define IRmVideo_Play(This)	\
    (This)->lpVtbl -> Play(This)

#define IRmVideo_Pause(This)	\
    (This)->lpVtbl -> Pause(This)

#define IRmVideo_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IRmVideo_Write(This,pHeaders,HeadersCount,ovr)	\
    (This)->lpVtbl -> Write(This,pHeaders,HeadersCount,ovr)

#define IRmVideo_Read(This,pHeaders,HeadersCount,ovr)	\
    (This)->lpVtbl -> Read(This,pHeaders,HeadersCount,ovr)

#define IRmVideo_BeginFlush(This)	\
    (This)->lpVtbl -> BeginFlush(This)

#define IRmVideo_EndFlush(This)	\
    (This)->lpVtbl -> EndFlush(This)

#define IRmVideo_SetAttributes(This,eAttribute,lValue)	\
    (This)->lpVtbl -> SetAttributes(This,eAttribute,lValue)

#define IRmVideo_GetAttributes(This,eAttribute,lValue)	\
    (This)->lpVtbl -> GetAttributes(This,eAttribute,lValue)


#define IRmVideo_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IRmVideo_ClearBuffer(This)	\
    (This)->lpVtbl -> ClearBuffer(This)

#define IRmVideo_GetSTC(This,pTime)	\
    (This)->lpVtbl -> GetSTC(This,pTime)

#define IRmVideo_SetSTC(This,pTime)	\
    (This)->lpVtbl -> SetSTC(This,pTime)

#define IRmVideo_SyncToAudio(This,systemTimeDelta)	\
    (This)->lpVtbl -> SyncToAudio(This,systemTimeDelta)

#define IRmVideo_CaptureToBuffer(This,pBmp,ulSize)	\
    (This)->lpVtbl -> CaptureToBuffer(This,pBmp,ulSize)

#define IRmVideo_SetPositionEvent(This,pEvent,pAsyncContext)	\
    (This)->lpVtbl -> SetPositionEvent(This,pEvent,pAsyncContext)

#define IRmVideo_GetDeviceInfo(This,deviceInfo)	\
    (This)->lpVtbl -> GetDeviceInfo(This,deviceInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRmVideo_Reset_Proxy( 
    IRmVideo __RPC_FAR * This);


void __RPC_STUB IRmVideo_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmVideo_ClearBuffer_Proxy( 
    IRmVideo __RPC_FAR * This);


void __RPC_STUB IRmVideo_ClearBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmVideo_GetSTC_Proxy( 
    IRmVideo __RPC_FAR * This,
    MPEG_SYSTEM_TIME __RPC_FAR *pTime);


void __RPC_STUB IRmVideo_GetSTC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmVideo_SetSTC_Proxy( 
    IRmVideo __RPC_FAR * This,
    MPEG_SYSTEM_TIME __RPC_FAR *pTime);


void __RPC_STUB IRmVideo_SetSTC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmVideo_SyncToAudio_Proxy( 
    IRmVideo __RPC_FAR * This,
    MPEG_SYSTEM_TIME systemTimeDelta);


void __RPC_STUB IRmVideo_SyncToAudio_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmVideo_CaptureToBuffer_Proxy( 
    IRmVideo __RPC_FAR * This,
    UCHAR __RPC_FAR *pBmp,
    ULONG ulSize);


void __RPC_STUB IRmVideo_CaptureToBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmVideo_SetPositionEvent_Proxy( 
    IRmVideo __RPC_FAR * This,
    PMPEG_EVENT pEvent,
    PMPEG_ASYNC_CONTEXT pAsyncContext);


void __RPC_STUB IRmVideo_SetPositionEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmVideo_GetDeviceInfo_Proxy( 
    IRmVideo __RPC_FAR * This,
    MPEG_DEVICE_INFO __RPC_FAR *deviceInfo);


void __RPC_STUB IRmVideo_GetDeviceInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRmVideo_INTERFACE_DEFINED__ */


#ifndef __IRmAudio_INTERFACE_DEFINED__
#define __IRmAudio_INTERFACE_DEFINED__

/* interface IRmAudio */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IRmAudio;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("48394E01-8A68-48fa-A90F-77CD6552FB1E")
    IRmAudio : public IRmBaseStreaming
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSTC( 
            MPEG_SYSTEM_TIME __RPC_FAR *pTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSTC( 
            MPEG_SYSTEM_TIME __RPC_FAR *pTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPositionEvent( 
            PMPEG_EVENT pEvent,
            PMPEG_ASYNC_CONTEXT pAsyncContext) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDeviceInfo( 
            MPEG_DEVICE_INFO __RPC_FAR *deviceInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRmAudioVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRmAudio __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRmAudio __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRmAudio __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Property )( 
            IRmAudio __RPC_FAR * This,
            /* [in] */ PKSPROPERTY KSID,
            /* [in] */ ULONG KSID_size,
            /* [in] */ PVOID prop,
            /* [in] */ ULONG prop_size,
            /* [out] */ ULONG __RPC_FAR *bret);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Play )( 
            IRmAudio __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Pause )( 
            IRmAudio __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IRmAudio __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Write )( 
            IRmAudio __RPC_FAR * This,
            KSSTREAM_HEADER __RPC_FAR *pHeaders,
            ULONG HeadersCount,
            OVERLAPPED __RPC_FAR *ovr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Read )( 
            IRmAudio __RPC_FAR * This,
            KSSTREAM_HEADER __RPC_FAR *pHeaders,
            ULONG HeadersCount,
            OVERLAPPED __RPC_FAR *ovr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BeginFlush )( 
            IRmAudio __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EndFlush )( 
            IRmAudio __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAttributes )( 
            IRmAudio __RPC_FAR * This,
            /* [in] */ MPEG_ATTRIBUTE eAttribute,
            /* [in] */ LONG lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAttributes )( 
            IRmAudio __RPC_FAR * This,
            /* [in] */ MPEG_ATTRIBUTE eAttribute,
            /* [out] */ LONG __RPC_FAR *lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IRmAudio __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSTC )( 
            IRmAudio __RPC_FAR * This,
            MPEG_SYSTEM_TIME __RPC_FAR *pTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSTC )( 
            IRmAudio __RPC_FAR * This,
            MPEG_SYSTEM_TIME __RPC_FAR *pTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPositionEvent )( 
            IRmAudio __RPC_FAR * This,
            PMPEG_EVENT pEvent,
            PMPEG_ASYNC_CONTEXT pAsyncContext);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDeviceInfo )( 
            IRmAudio __RPC_FAR * This,
            MPEG_DEVICE_INFO __RPC_FAR *deviceInfo);
        
        END_INTERFACE
    } IRmAudioVtbl;

    interface IRmAudio
    {
        CONST_VTBL struct IRmAudioVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRmAudio_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRmAudio_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRmAudio_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRmAudio_Property(This,KSID,KSID_size,prop,prop_size,bret)	\
    (This)->lpVtbl -> Property(This,KSID,KSID_size,prop,prop_size,bret)

#define IRmAudio_Play(This)	\
    (This)->lpVtbl -> Play(This)

#define IRmAudio_Pause(This)	\
    (This)->lpVtbl -> Pause(This)

#define IRmAudio_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IRmAudio_Write(This,pHeaders,HeadersCount,ovr)	\
    (This)->lpVtbl -> Write(This,pHeaders,HeadersCount,ovr)

#define IRmAudio_Read(This,pHeaders,HeadersCount,ovr)	\
    (This)->lpVtbl -> Read(This,pHeaders,HeadersCount,ovr)

#define IRmAudio_BeginFlush(This)	\
    (This)->lpVtbl -> BeginFlush(This)

#define IRmAudio_EndFlush(This)	\
    (This)->lpVtbl -> EndFlush(This)

#define IRmAudio_SetAttributes(This,eAttribute,lValue)	\
    (This)->lpVtbl -> SetAttributes(This,eAttribute,lValue)

#define IRmAudio_GetAttributes(This,eAttribute,lValue)	\
    (This)->lpVtbl -> GetAttributes(This,eAttribute,lValue)


#define IRmAudio_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IRmAudio_GetSTC(This,pTime)	\
    (This)->lpVtbl -> GetSTC(This,pTime)

#define IRmAudio_SetSTC(This,pTime)	\
    (This)->lpVtbl -> SetSTC(This,pTime)

#define IRmAudio_SetPositionEvent(This,pEvent,pAsyncContext)	\
    (This)->lpVtbl -> SetPositionEvent(This,pEvent,pAsyncContext)

#define IRmAudio_GetDeviceInfo(This,deviceInfo)	\
    (This)->lpVtbl -> GetDeviceInfo(This,deviceInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRmAudio_Reset_Proxy( 
    IRmAudio __RPC_FAR * This);


void __RPC_STUB IRmAudio_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmAudio_GetSTC_Proxy( 
    IRmAudio __RPC_FAR * This,
    MPEG_SYSTEM_TIME __RPC_FAR *pTime);


void __RPC_STUB IRmAudio_GetSTC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmAudio_SetSTC_Proxy( 
    IRmAudio __RPC_FAR * This,
    MPEG_SYSTEM_TIME __RPC_FAR *pTime);


void __RPC_STUB IRmAudio_SetSTC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmAudio_SetPositionEvent_Proxy( 
    IRmAudio __RPC_FAR * This,
    PMPEG_EVENT pEvent,
    PMPEG_ASYNC_CONTEXT pAsyncContext);


void __RPC_STUB IRmAudio_SetPositionEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmAudio_GetDeviceInfo_Proxy( 
    IRmAudio __RPC_FAR * This,
    MPEG_DEVICE_INFO __RPC_FAR *deviceInfo);


void __RPC_STUB IRmAudio_GetDeviceInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRmAudio_INTERFACE_DEFINED__ */


#ifndef __IRmOverlay_INTERFACE_DEFINED__
#define __IRmOverlay_INTERFACE_DEFINED__

/* interface IRmOverlay */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IRmOverlay;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FC017BFF-301E-475a-A06E-42F2CA007396")
    IRmOverlay : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Get_Mode( 
            MPEG_OVERLAY_MODE __RPC_FAR *OverlayMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Put_Mode( 
            MPEG_OVERLAY_MODE OverlayMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Get_VGAKey( 
            COLORREF __RPC_FAR *prgbColor,
            COLORREF __RPC_FAR *prgbMask) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Put_VGAKey( 
            COLORREF __RPC_FAR *prgbColor,
            COLORREF __RPC_FAR *prgbMask) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Put_VGAKey2( 
            COLORREF rgbColor,
            POVERLAY_COLOUR_REGISTERS pOverride) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Put_Source( 
            MPEG_OVERLAY_RECT __RPC_FAR *rect) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Get_Source( 
            MPEG_OVERLAY_RECT __RPC_FAR *rect) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Put_Destination( 
            MPEG_OVERLAY_RECT __RPC_FAR *rect) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Get_Destination( 
            MPEG_OVERLAY_RECT __RPC_FAR *rect) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Do_Calibration( 
            POVERLAY_COLOUR_REGISTERS pRegs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Put_CalibParam( 
            PCALIBRATION_PARAMETERS pParams) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAttributes( 
            MPEG_ATTRIBUTE eAttribute,
            LONG lValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAttributes( 
            MPEG_ATTRIBUTE eAttribute,
            LONG __RPC_FAR *lValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDeviceInfo( 
            MPEG_DEVICE_INFO __RPC_FAR *deviceInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAttributeEx( 
            MPEG_ATTRIBUTE eAttribute,
            void __RPC_FAR *lValue,
            ULONG size) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRmOverlayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRmOverlay __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRmOverlay __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRmOverlay __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get_Mode )( 
            IRmOverlay __RPC_FAR * This,
            MPEG_OVERLAY_MODE __RPC_FAR *OverlayMode);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put_Mode )( 
            IRmOverlay __RPC_FAR * This,
            MPEG_OVERLAY_MODE OverlayMode);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get_VGAKey )( 
            IRmOverlay __RPC_FAR * This,
            COLORREF __RPC_FAR *prgbColor,
            COLORREF __RPC_FAR *prgbMask);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put_VGAKey )( 
            IRmOverlay __RPC_FAR * This,
            COLORREF __RPC_FAR *prgbColor,
            COLORREF __RPC_FAR *prgbMask);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put_VGAKey2 )( 
            IRmOverlay __RPC_FAR * This,
            COLORREF rgbColor,
            POVERLAY_COLOUR_REGISTERS pOverride);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put_Source )( 
            IRmOverlay __RPC_FAR * This,
            MPEG_OVERLAY_RECT __RPC_FAR *rect);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get_Source )( 
            IRmOverlay __RPC_FAR * This,
            MPEG_OVERLAY_RECT __RPC_FAR *rect);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put_Destination )( 
            IRmOverlay __RPC_FAR * This,
            MPEG_OVERLAY_RECT __RPC_FAR *rect);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get_Destination )( 
            IRmOverlay __RPC_FAR * This,
            MPEG_OVERLAY_RECT __RPC_FAR *rect);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Do_Calibration )( 
            IRmOverlay __RPC_FAR * This,
            POVERLAY_COLOUR_REGISTERS pRegs);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put_CalibParam )( 
            IRmOverlay __RPC_FAR * This,
            PCALIBRATION_PARAMETERS pParams);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAttributes )( 
            IRmOverlay __RPC_FAR * This,
            MPEG_ATTRIBUTE eAttribute,
            LONG lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAttributes )( 
            IRmOverlay __RPC_FAR * This,
            MPEG_ATTRIBUTE eAttribute,
            LONG __RPC_FAR *lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDeviceInfo )( 
            IRmOverlay __RPC_FAR * This,
            MPEG_DEVICE_INFO __RPC_FAR *deviceInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAttributeEx )( 
            IRmOverlay __RPC_FAR * This,
            MPEG_ATTRIBUTE eAttribute,
            void __RPC_FAR *lValue,
            ULONG size);
        
        END_INTERFACE
    } IRmOverlayVtbl;

    interface IRmOverlay
    {
        CONST_VTBL struct IRmOverlayVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRmOverlay_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRmOverlay_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRmOverlay_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRmOverlay_Get_Mode(This,OverlayMode)	\
    (This)->lpVtbl -> Get_Mode(This,OverlayMode)

#define IRmOverlay_Put_Mode(This,OverlayMode)	\
    (This)->lpVtbl -> Put_Mode(This,OverlayMode)

#define IRmOverlay_Get_VGAKey(This,prgbColor,prgbMask)	\
    (This)->lpVtbl -> Get_VGAKey(This,prgbColor,prgbMask)

#define IRmOverlay_Put_VGAKey(This,prgbColor,prgbMask)	\
    (This)->lpVtbl -> Put_VGAKey(This,prgbColor,prgbMask)

#define IRmOverlay_Put_VGAKey2(This,rgbColor,pOverride)	\
    (This)->lpVtbl -> Put_VGAKey2(This,rgbColor,pOverride)

#define IRmOverlay_Put_Source(This,rect)	\
    (This)->lpVtbl -> Put_Source(This,rect)

#define IRmOverlay_Get_Source(This,rect)	\
    (This)->lpVtbl -> Get_Source(This,rect)

#define IRmOverlay_Put_Destination(This,rect)	\
    (This)->lpVtbl -> Put_Destination(This,rect)

#define IRmOverlay_Get_Destination(This,rect)	\
    (This)->lpVtbl -> Get_Destination(This,rect)

#define IRmOverlay_Do_Calibration(This,pRegs)	\
    (This)->lpVtbl -> Do_Calibration(This,pRegs)

#define IRmOverlay_Put_CalibParam(This,pParams)	\
    (This)->lpVtbl -> Put_CalibParam(This,pParams)

#define IRmOverlay_SetAttributes(This,eAttribute,lValue)	\
    (This)->lpVtbl -> SetAttributes(This,eAttribute,lValue)

#define IRmOverlay_GetAttributes(This,eAttribute,lValue)	\
    (This)->lpVtbl -> GetAttributes(This,eAttribute,lValue)

#define IRmOverlay_GetDeviceInfo(This,deviceInfo)	\
    (This)->lpVtbl -> GetDeviceInfo(This,deviceInfo)

#define IRmOverlay_SetAttributeEx(This,eAttribute,lValue,size)	\
    (This)->lpVtbl -> SetAttributeEx(This,eAttribute,lValue,size)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRmOverlay_Get_Mode_Proxy( 
    IRmOverlay __RPC_FAR * This,
    MPEG_OVERLAY_MODE __RPC_FAR *OverlayMode);


void __RPC_STUB IRmOverlay_Get_Mode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmOverlay_Put_Mode_Proxy( 
    IRmOverlay __RPC_FAR * This,
    MPEG_OVERLAY_MODE OverlayMode);


void __RPC_STUB IRmOverlay_Put_Mode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmOverlay_Get_VGAKey_Proxy( 
    IRmOverlay __RPC_FAR * This,
    COLORREF __RPC_FAR *prgbColor,
    COLORREF __RPC_FAR *prgbMask);


void __RPC_STUB IRmOverlay_Get_VGAKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmOverlay_Put_VGAKey_Proxy( 
    IRmOverlay __RPC_FAR * This,
    COLORREF __RPC_FAR *prgbColor,
    COLORREF __RPC_FAR *prgbMask);


void __RPC_STUB IRmOverlay_Put_VGAKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmOverlay_Put_VGAKey2_Proxy( 
    IRmOverlay __RPC_FAR * This,
    COLORREF rgbColor,
    POVERLAY_COLOUR_REGISTERS pOverride);


void __RPC_STUB IRmOverlay_Put_VGAKey2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmOverlay_Put_Source_Proxy( 
    IRmOverlay __RPC_FAR * This,
    MPEG_OVERLAY_RECT __RPC_FAR *rect);


void __RPC_STUB IRmOverlay_Put_Source_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmOverlay_Get_Source_Proxy( 
    IRmOverlay __RPC_FAR * This,
    MPEG_OVERLAY_RECT __RPC_FAR *rect);


void __RPC_STUB IRmOverlay_Get_Source_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmOverlay_Put_Destination_Proxy( 
    IRmOverlay __RPC_FAR * This,
    MPEG_OVERLAY_RECT __RPC_FAR *rect);


void __RPC_STUB IRmOverlay_Put_Destination_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmOverlay_Get_Destination_Proxy( 
    IRmOverlay __RPC_FAR * This,
    MPEG_OVERLAY_RECT __RPC_FAR *rect);


void __RPC_STUB IRmOverlay_Get_Destination_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmOverlay_Do_Calibration_Proxy( 
    IRmOverlay __RPC_FAR * This,
    POVERLAY_COLOUR_REGISTERS pRegs);


void __RPC_STUB IRmOverlay_Do_Calibration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmOverlay_Put_CalibParam_Proxy( 
    IRmOverlay __RPC_FAR * This,
    PCALIBRATION_PARAMETERS pParams);


void __RPC_STUB IRmOverlay_Put_CalibParam_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmOverlay_SetAttributes_Proxy( 
    IRmOverlay __RPC_FAR * This,
    MPEG_ATTRIBUTE eAttribute,
    LONG lValue);


void __RPC_STUB IRmOverlay_SetAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmOverlay_GetAttributes_Proxy( 
    IRmOverlay __RPC_FAR * This,
    MPEG_ATTRIBUTE eAttribute,
    LONG __RPC_FAR *lValue);


void __RPC_STUB IRmOverlay_GetAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmOverlay_GetDeviceInfo_Proxy( 
    IRmOverlay __RPC_FAR * This,
    MPEG_DEVICE_INFO __RPC_FAR *deviceInfo);


void __RPC_STUB IRmOverlay_GetDeviceInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmOverlay_SetAttributeEx_Proxy( 
    IRmOverlay __RPC_FAR * This,
    MPEG_ATTRIBUTE eAttribute,
    void __RPC_FAR *lValue,
    ULONG size);


void __RPC_STUB IRmOverlay_SetAttributeEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRmOverlay_INTERFACE_DEFINED__ */


#ifndef __IRmSubpicture_INTERFACE_DEFINED__
#define __IRmSubpicture_INTERFACE_DEFINED__

/* interface IRmSubpicture */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IRmSubpicture;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F934C7A2-4192-4b19-B311-0972C3C74757")
    IRmSubpicture : public IRmBaseStreaming
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HliCommand( 
            MPEG_HLI_CMD command,
            DWORD dwParameter) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRmSubpictureVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRmSubpicture __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRmSubpicture __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRmSubpicture __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Property )( 
            IRmSubpicture __RPC_FAR * This,
            /* [in] */ PKSPROPERTY KSID,
            /* [in] */ ULONG KSID_size,
            /* [in] */ PVOID prop,
            /* [in] */ ULONG prop_size,
            /* [out] */ ULONG __RPC_FAR *bret);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Play )( 
            IRmSubpicture __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Pause )( 
            IRmSubpicture __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IRmSubpicture __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Write )( 
            IRmSubpicture __RPC_FAR * This,
            KSSTREAM_HEADER __RPC_FAR *pHeaders,
            ULONG HeadersCount,
            OVERLAPPED __RPC_FAR *ovr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Read )( 
            IRmSubpicture __RPC_FAR * This,
            KSSTREAM_HEADER __RPC_FAR *pHeaders,
            ULONG HeadersCount,
            OVERLAPPED __RPC_FAR *ovr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BeginFlush )( 
            IRmSubpicture __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EndFlush )( 
            IRmSubpicture __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAttributes )( 
            IRmSubpicture __RPC_FAR * This,
            /* [in] */ MPEG_ATTRIBUTE eAttribute,
            /* [in] */ LONG lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAttributes )( 
            IRmSubpicture __RPC_FAR * This,
            /* [in] */ MPEG_ATTRIBUTE eAttribute,
            /* [out] */ LONG __RPC_FAR *lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IRmSubpicture __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HliCommand )( 
            IRmSubpicture __RPC_FAR * This,
            MPEG_HLI_CMD command,
            DWORD dwParameter);
        
        END_INTERFACE
    } IRmSubpictureVtbl;

    interface IRmSubpicture
    {
        CONST_VTBL struct IRmSubpictureVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRmSubpicture_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRmSubpicture_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRmSubpicture_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRmSubpicture_Property(This,KSID,KSID_size,prop,prop_size,bret)	\
    (This)->lpVtbl -> Property(This,KSID,KSID_size,prop,prop_size,bret)

#define IRmSubpicture_Play(This)	\
    (This)->lpVtbl -> Play(This)

#define IRmSubpicture_Pause(This)	\
    (This)->lpVtbl -> Pause(This)

#define IRmSubpicture_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IRmSubpicture_Write(This,pHeaders,HeadersCount,ovr)	\
    (This)->lpVtbl -> Write(This,pHeaders,HeadersCount,ovr)

#define IRmSubpicture_Read(This,pHeaders,HeadersCount,ovr)	\
    (This)->lpVtbl -> Read(This,pHeaders,HeadersCount,ovr)

#define IRmSubpicture_BeginFlush(This)	\
    (This)->lpVtbl -> BeginFlush(This)

#define IRmSubpicture_EndFlush(This)	\
    (This)->lpVtbl -> EndFlush(This)

#define IRmSubpicture_SetAttributes(This,eAttribute,lValue)	\
    (This)->lpVtbl -> SetAttributes(This,eAttribute,lValue)

#define IRmSubpicture_GetAttributes(This,eAttribute,lValue)	\
    (This)->lpVtbl -> GetAttributes(This,eAttribute,lValue)


#define IRmSubpicture_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IRmSubpicture_HliCommand(This,command,dwParameter)	\
    (This)->lpVtbl -> HliCommand(This,command,dwParameter)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRmSubpicture_Reset_Proxy( 
    IRmSubpicture __RPC_FAR * This);


void __RPC_STUB IRmSubpicture_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRmSubpicture_HliCommand_Proxy( 
    IRmSubpicture __RPC_FAR * This,
    MPEG_HLI_CMD command,
    DWORD dwParameter);


void __RPC_STUB IRmSubpicture_HliCommand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRmSubpicture_INTERFACE_DEFINED__ */


#ifndef __IRmOSD_INTERFACE_DEFINED__
#define __IRmOSD_INTERFACE_DEFINED__

/* interface IRmOSD */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IRmOSD;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("41189722-20DF-43a8-8719-F956DD8BB970")
    IRmOSD : public IRmBaseStreaming
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRmOSDVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRmOSD __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRmOSD __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRmOSD __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Property )( 
            IRmOSD __RPC_FAR * This,
            /* [in] */ PKSPROPERTY KSID,
            /* [in] */ ULONG KSID_size,
            /* [in] */ PVOID prop,
            /* [in] */ ULONG prop_size,
            /* [out] */ ULONG __RPC_FAR *bret);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Play )( 
            IRmOSD __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Pause )( 
            IRmOSD __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IRmOSD __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Write )( 
            IRmOSD __RPC_FAR * This,
            KSSTREAM_HEADER __RPC_FAR *pHeaders,
            ULONG HeadersCount,
            OVERLAPPED __RPC_FAR *ovr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Read )( 
            IRmOSD __RPC_FAR * This,
            KSSTREAM_HEADER __RPC_FAR *pHeaders,
            ULONG HeadersCount,
            OVERLAPPED __RPC_FAR *ovr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BeginFlush )( 
            IRmOSD __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EndFlush )( 
            IRmOSD __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAttributes )( 
            IRmOSD __RPC_FAR * This,
            /* [in] */ MPEG_ATTRIBUTE eAttribute,
            /* [in] */ LONG lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAttributes )( 
            IRmOSD __RPC_FAR * This,
            /* [in] */ MPEG_ATTRIBUTE eAttribute,
            /* [out] */ LONG __RPC_FAR *lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IRmOSD __RPC_FAR * This);
        
        END_INTERFACE
    } IRmOSDVtbl;

    interface IRmOSD
    {
        CONST_VTBL struct IRmOSDVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRmOSD_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRmOSD_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRmOSD_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRmOSD_Property(This,KSID,KSID_size,prop,prop_size,bret)	\
    (This)->lpVtbl -> Property(This,KSID,KSID_size,prop,prop_size,bret)

#define IRmOSD_Play(This)	\
    (This)->lpVtbl -> Play(This)

#define IRmOSD_Pause(This)	\
    (This)->lpVtbl -> Pause(This)

#define IRmOSD_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IRmOSD_Write(This,pHeaders,HeadersCount,ovr)	\
    (This)->lpVtbl -> Write(This,pHeaders,HeadersCount,ovr)

#define IRmOSD_Read(This,pHeaders,HeadersCount,ovr)	\
    (This)->lpVtbl -> Read(This,pHeaders,HeadersCount,ovr)

#define IRmOSD_BeginFlush(This)	\
    (This)->lpVtbl -> BeginFlush(This)

#define IRmOSD_EndFlush(This)	\
    (This)->lpVtbl -> EndFlush(This)

#define IRmOSD_SetAttributes(This,eAttribute,lValue)	\
    (This)->lpVtbl -> SetAttributes(This,eAttribute,lValue)

#define IRmOSD_GetAttributes(This,eAttribute,lValue)	\
    (This)->lpVtbl -> GetAttributes(This,eAttribute,lValue)


#define IRmOSD_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRmOSD_Reset_Proxy( 
    IRmOSD __RPC_FAR * This);


void __RPC_STUB IRmOSD_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRmOSD_INTERFACE_DEFINED__ */


#ifndef __IOverlayConfig_INTERFACE_DEFINED__
#define __IOverlayConfig_INTERFACE_DEFINED__

/* interface IOverlayConfig */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IOverlayConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A22206B3-93C2-45a9-B197-FE407DD02825")
    IOverlayConfig : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE put_OverlayMode( 
            MPEG_OVERLAY_MODE OverlayMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_OverlayMode( 
            MPEG_OVERLAY_MODE __RPC_FAR *pOverlayMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_OverlayPosition( 
            RECT __RPC_FAR *rcDestination) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_OverlayPosition( 
            RECT __RPC_FAR *prcDestination) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_TopBorder( 
            ULONG ulYOffset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_TopBorder( 
            ULONG __RPC_FAR *pulYOffset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_LeftBorder( 
            ULONG ulXOffset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_LeftBorder( 
            ULONG __RPC_FAR *pulXOffset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_VgaCorrection( 
            ULONG ulVgaCorrection) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_VgaCorrection( 
            ULONG __RPC_FAR *pulVgaCorrection) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_JitterAdjustment( 
            ULONG ulJitterAdjustment) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_JitterAdjustment( 
            ULONG __RPC_FAR *pulJitterAdjustment) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_VgaFineAdjustment( 
            ULONG ulVgaFineAdjustment) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_VgaFineAdjustment( 
            ULONG __RPC_FAR *pulVgaFineAdjustment) = 0;
        
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
            CALIBRATION_PARAMETERS __RPC_FAR *pCalParams) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_CalibrationParameters( 
            CALIBRATION_PARAMETERS __RPC_FAR *pCalParams) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IOverlayConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IOverlayConfig __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IOverlayConfig __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IOverlayConfig __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OverlayMode )( 
            IOverlayConfig __RPC_FAR * This,
            MPEG_OVERLAY_MODE OverlayMode);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OverlayMode )( 
            IOverlayConfig __RPC_FAR * This,
            MPEG_OVERLAY_MODE __RPC_FAR *pOverlayMode);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OverlayPosition )( 
            IOverlayConfig __RPC_FAR * This,
            RECT __RPC_FAR *rcDestination);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OverlayPosition )( 
            IOverlayConfig __RPC_FAR * This,
            RECT __RPC_FAR *prcDestination);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TopBorder )( 
            IOverlayConfig __RPC_FAR * This,
            ULONG ulYOffset);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TopBorder )( 
            IOverlayConfig __RPC_FAR * This,
            ULONG __RPC_FAR *pulYOffset);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LeftBorder )( 
            IOverlayConfig __RPC_FAR * This,
            ULONG ulXOffset);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LeftBorder )( 
            IOverlayConfig __RPC_FAR * This,
            ULONG __RPC_FAR *pulXOffset);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_VgaCorrection )( 
            IOverlayConfig __RPC_FAR * This,
            ULONG ulVgaCorrection);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VgaCorrection )( 
            IOverlayConfig __RPC_FAR * This,
            ULONG __RPC_FAR *pulVgaCorrection);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_JitterAdjustment )( 
            IOverlayConfig __RPC_FAR * This,
            ULONG ulJitterAdjustment);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_JitterAdjustment )( 
            IOverlayConfig __RPC_FAR * This,
            ULONG __RPC_FAR *pulJitterAdjustment);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_VgaFineAdjustment )( 
            IOverlayConfig __RPC_FAR * This,
            ULONG ulVgaFineAdjustment);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VgaFineAdjustment )( 
            IOverlayConfig __RPC_FAR * This,
            ULONG __RPC_FAR *pulVgaFineAdjustment);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UpdateResolution )( 
            IOverlayConfig __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AutoCalibrate )( 
            IOverlayConfig __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartAutoCalibration )( 
            IOverlayConfig __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopAutoCalibration )( 
            IOverlayConfig __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CalibrateTopBorder )( 
            IOverlayConfig __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CalibrateLeftBorder )( 
            IOverlayConfig __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CalibrateCorrection )( 
            IOverlayConfig __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CalibrateColorLimits )( 
            IOverlayConfig __RPC_FAR * This,
            PCOLOR_LIMITS pColorLimits);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CalibrationParameters )( 
            IOverlayConfig __RPC_FAR * This,
            CALIBRATION_PARAMETERS __RPC_FAR *pCalParams);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CalibrationParameters )( 
            IOverlayConfig __RPC_FAR * This,
            CALIBRATION_PARAMETERS __RPC_FAR *pCalParams);
        
        END_INTERFACE
    } IOverlayConfigVtbl;

    interface IOverlayConfig
    {
        CONST_VTBL struct IOverlayConfigVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IOverlayConfig_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IOverlayConfig_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IOverlayConfig_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IOverlayConfig_put_OverlayMode(This,OverlayMode)	\
    (This)->lpVtbl -> put_OverlayMode(This,OverlayMode)

#define IOverlayConfig_get_OverlayMode(This,pOverlayMode)	\
    (This)->lpVtbl -> get_OverlayMode(This,pOverlayMode)

#define IOverlayConfig_put_OverlayPosition(This,rcDestination)	\
    (This)->lpVtbl -> put_OverlayPosition(This,rcDestination)

#define IOverlayConfig_get_OverlayPosition(This,prcDestination)	\
    (This)->lpVtbl -> get_OverlayPosition(This,prcDestination)

#define IOverlayConfig_put_TopBorder(This,ulYOffset)	\
    (This)->lpVtbl -> put_TopBorder(This,ulYOffset)

#define IOverlayConfig_get_TopBorder(This,pulYOffset)	\
    (This)->lpVtbl -> get_TopBorder(This,pulYOffset)

#define IOverlayConfig_put_LeftBorder(This,ulXOffset)	\
    (This)->lpVtbl -> put_LeftBorder(This,ulXOffset)

#define IOverlayConfig_get_LeftBorder(This,pulXOffset)	\
    (This)->lpVtbl -> get_LeftBorder(This,pulXOffset)

#define IOverlayConfig_put_VgaCorrection(This,ulVgaCorrection)	\
    (This)->lpVtbl -> put_VgaCorrection(This,ulVgaCorrection)

#define IOverlayConfig_get_VgaCorrection(This,pulVgaCorrection)	\
    (This)->lpVtbl -> get_VgaCorrection(This,pulVgaCorrection)

#define IOverlayConfig_put_JitterAdjustment(This,ulJitterAdjustment)	\
    (This)->lpVtbl -> put_JitterAdjustment(This,ulJitterAdjustment)

#define IOverlayConfig_get_JitterAdjustment(This,pulJitterAdjustment)	\
    (This)->lpVtbl -> get_JitterAdjustment(This,pulJitterAdjustment)

#define IOverlayConfig_put_VgaFineAdjustment(This,ulVgaFineAdjustment)	\
    (This)->lpVtbl -> put_VgaFineAdjustment(This,ulVgaFineAdjustment)

#define IOverlayConfig_get_VgaFineAdjustment(This,pulVgaFineAdjustment)	\
    (This)->lpVtbl -> get_VgaFineAdjustment(This,pulVgaFineAdjustment)

#define IOverlayConfig_UpdateResolution(This)	\
    (This)->lpVtbl -> UpdateResolution(This)

#define IOverlayConfig_AutoCalibrate(This)	\
    (This)->lpVtbl -> AutoCalibrate(This)

#define IOverlayConfig_StartAutoCalibration(This)	\
    (This)->lpVtbl -> StartAutoCalibration(This)

#define IOverlayConfig_StopAutoCalibration(This)	\
    (This)->lpVtbl -> StopAutoCalibration(This)

#define IOverlayConfig_CalibrateTopBorder(This)	\
    (This)->lpVtbl -> CalibrateTopBorder(This)

#define IOverlayConfig_CalibrateLeftBorder(This)	\
    (This)->lpVtbl -> CalibrateLeftBorder(This)

#define IOverlayConfig_CalibrateCorrection(This)	\
    (This)->lpVtbl -> CalibrateCorrection(This)

#define IOverlayConfig_CalibrateColorLimits(This,pColorLimits)	\
    (This)->lpVtbl -> CalibrateColorLimits(This,pColorLimits)

#define IOverlayConfig_put_CalibrationParameters(This,pCalParams)	\
    (This)->lpVtbl -> put_CalibrationParameters(This,pCalParams)

#define IOverlayConfig_get_CalibrationParameters(This,pCalParams)	\
    (This)->lpVtbl -> get_CalibrationParameters(This,pCalParams)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IOverlayConfig_put_OverlayMode_Proxy( 
    IOverlayConfig __RPC_FAR * This,
    MPEG_OVERLAY_MODE OverlayMode);


void __RPC_STUB IOverlayConfig_put_OverlayMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlayConfig_get_OverlayMode_Proxy( 
    IOverlayConfig __RPC_FAR * This,
    MPEG_OVERLAY_MODE __RPC_FAR *pOverlayMode);


void __RPC_STUB IOverlayConfig_get_OverlayMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlayConfig_put_OverlayPosition_Proxy( 
    IOverlayConfig __RPC_FAR * This,
    RECT __RPC_FAR *rcDestination);


void __RPC_STUB IOverlayConfig_put_OverlayPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlayConfig_get_OverlayPosition_Proxy( 
    IOverlayConfig __RPC_FAR * This,
    RECT __RPC_FAR *prcDestination);


void __RPC_STUB IOverlayConfig_get_OverlayPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlayConfig_put_TopBorder_Proxy( 
    IOverlayConfig __RPC_FAR * This,
    ULONG ulYOffset);


void __RPC_STUB IOverlayConfig_put_TopBorder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlayConfig_get_TopBorder_Proxy( 
    IOverlayConfig __RPC_FAR * This,
    ULONG __RPC_FAR *pulYOffset);


void __RPC_STUB IOverlayConfig_get_TopBorder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlayConfig_put_LeftBorder_Proxy( 
    IOverlayConfig __RPC_FAR * This,
    ULONG ulXOffset);


void __RPC_STUB IOverlayConfig_put_LeftBorder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlayConfig_get_LeftBorder_Proxy( 
    IOverlayConfig __RPC_FAR * This,
    ULONG __RPC_FAR *pulXOffset);


void __RPC_STUB IOverlayConfig_get_LeftBorder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlayConfig_put_VgaCorrection_Proxy( 
    IOverlayConfig __RPC_FAR * This,
    ULONG ulVgaCorrection);


void __RPC_STUB IOverlayConfig_put_VgaCorrection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlayConfig_get_VgaCorrection_Proxy( 
    IOverlayConfig __RPC_FAR * This,
    ULONG __RPC_FAR *pulVgaCorrection);


void __RPC_STUB IOverlayConfig_get_VgaCorrection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlayConfig_put_JitterAdjustment_Proxy( 
    IOverlayConfig __RPC_FAR * This,
    ULONG ulJitterAdjustment);


void __RPC_STUB IOverlayConfig_put_JitterAdjustment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlayConfig_get_JitterAdjustment_Proxy( 
    IOverlayConfig __RPC_FAR * This,
    ULONG __RPC_FAR *pulJitterAdjustment);


void __RPC_STUB IOverlayConfig_get_JitterAdjustment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlayConfig_put_VgaFineAdjustment_Proxy( 
    IOverlayConfig __RPC_FAR * This,
    ULONG ulVgaFineAdjustment);


void __RPC_STUB IOverlayConfig_put_VgaFineAdjustment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlayConfig_get_VgaFineAdjustment_Proxy( 
    IOverlayConfig __RPC_FAR * This,
    ULONG __RPC_FAR *pulVgaFineAdjustment);


void __RPC_STUB IOverlayConfig_get_VgaFineAdjustment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlayConfig_UpdateResolution_Proxy( 
    IOverlayConfig __RPC_FAR * This);


void __RPC_STUB IOverlayConfig_UpdateResolution_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlayConfig_AutoCalibrate_Proxy( 
    IOverlayConfig __RPC_FAR * This);


void __RPC_STUB IOverlayConfig_AutoCalibrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlayConfig_StartAutoCalibration_Proxy( 
    IOverlayConfig __RPC_FAR * This);


void __RPC_STUB IOverlayConfig_StartAutoCalibration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlayConfig_StopAutoCalibration_Proxy( 
    IOverlayConfig __RPC_FAR * This);


void __RPC_STUB IOverlayConfig_StopAutoCalibration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlayConfig_CalibrateTopBorder_Proxy( 
    IOverlayConfig __RPC_FAR * This);


void __RPC_STUB IOverlayConfig_CalibrateTopBorder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlayConfig_CalibrateLeftBorder_Proxy( 
    IOverlayConfig __RPC_FAR * This);


void __RPC_STUB IOverlayConfig_CalibrateLeftBorder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlayConfig_CalibrateCorrection_Proxy( 
    IOverlayConfig __RPC_FAR * This);


void __RPC_STUB IOverlayConfig_CalibrateCorrection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlayConfig_CalibrateColorLimits_Proxy( 
    IOverlayConfig __RPC_FAR * This,
    PCOLOR_LIMITS pColorLimits);


void __RPC_STUB IOverlayConfig_CalibrateColorLimits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlayConfig_put_CalibrationParameters_Proxy( 
    IOverlayConfig __RPC_FAR * This,
    CALIBRATION_PARAMETERS __RPC_FAR *pCalParams);


void __RPC_STUB IOverlayConfig_put_CalibrationParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlayConfig_get_CalibrationParameters_Proxy( 
    IOverlayConfig __RPC_FAR * This,
    CALIBRATION_PARAMETERS __RPC_FAR *pCalParams);


void __RPC_STUB IOverlayConfig_get_CalibrationParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IOverlayConfig_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
