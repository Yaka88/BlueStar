// (VG) 1/7/2002 12:14:33 PM

//	miniport propsets, used by clients of IRm ... interface set
//
typedef enum {
	RMVIDEO_CaptureToBuffer,
	RMVIDEO_GetSTC,
	RMVIDEO_SetSTC,
	RMVIDEO_PositionEvent,
	RMVIDEO_DeviceInfo,
	RMVIDEO_ClearBuffer,
}RMVIDEO;

typedef enum {
	RMOVERLAY_Mode,
	RMOVERLAY_VGAKey,
	RMOVERLAY_VGAKey2,
	RMOVERLAY_Source,
	RMOVERLAY_Destination,
	RMOVERLAY_Calibration,
	RMOVERLAY_CalibParam,
	RMOVERLAY_FullScreen,
	RMOVERLAY_VideoPosition
}RMOVERLAY;

typedef enum {
	RMSPU_HliCommand
}RMSPU;

typedef enum {
	RMMEM_DeviceBase,
	RMMEM_DMA_buffer
}RMMEMORY;

typedef enum{
	PROPSET_ATTRIBUTES	= 0x80000000,
	PROPSET_RMVIDEO,
	PROPSET_RMOVERLAY,
	PROPSET_RMSPU,
	PROPSET_RMMEMORY
}RMIMPL_PROPSETS;

/////////////////////////////////////////////////////////////////////////////////////////
// SHARED
//

typedef enum {
    RMSTATE_STOP,
    RMSTATE_ACQUIRE,
    RMSTATE_PAUSE,
    RMSTATE_RUN
}RMSTATE,*PRMSTATE;

typedef struct {
    RMint64		Time;
    RMuint32	Numerator;
    RMuint32	Denominator;
} RMTIME, *PRMTIME;

typedef struct {
	RMuint32	Size;
	RMuint32	TypeSpecificFlags;
    RMTIME      PresentationTime;
    RMuint64	Duration;
    RMuint32	FrameExtent;
    RMuint32	DataUsed;
    void		*pData;
    RMuint32	OptionsFlags;
} RMSTREAM_HEADER, *PRMSTREAM_HEADER;

typedef union {
    struct {
        RMuint32	FormatSize;
        RMuint32	Flags;
        RMuint32	SampleSize;
        RMuint32	Reserved;
        RMID		MajorFormat;
        RMID		SubFormat;
        RMID		Specifier;
    }u;
    RMuint64    Alignment;
} RMDATAFORMAT, *PRMDATAFORMAT, RMDATARANGE, *PRMDATARANGE;

typedef struct _RMOVERLAPIO {
    RMuint32	do_not_use[4];
    RMHANDLE	hEvent;
} RMOVERLAPIO, *PRMOVERLAPIO;

/////////////////////////////////////////////////////////////////////////////////////////
// CAPABILITIES
//

// Capability types
//
typedef enum {
	RMCAPF_2RM32,
	RMCAPF_RM64,
	RMCAPF_MULTI
}RMCAP_TYPE;

typedef struct {
    RMuint32    Size;
    RMuint32    Count;
} RMMULTIPLE_ITEM, *PRMMULTIPLE_ITEM;

typedef struct{
	RMCAP_TYPE	type;
	RMuint32	reserved;
	union{
		RMuint32		dwCaps[2];
		RMuint64		ullCaps;
		RMMULTIPLE_ITEM	multi_header;
	}u;
}RMCAPABILITIES,*PRMCAPABILITIES;
