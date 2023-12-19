#ifndef __guid_8400_h
#define __guid_8400_h

typedef enum {
	_A_byte_cnt				,
	_A_input_queue_cnt		,
	_A_wait_queue_cnt		,
	_A_device_state			, 
	_A_requested_state		,
	_A_DATA_Q_Size			,
	_A_DATA_Q_RdPtr			,
	_A_DATA_Q_WrPtr			,
	_A_DATA_Q_Emptiness		,
	_A_DATA_Q_Fullness		,
	_A_PTS_Q_Emptiness		, 
	_A_PACKETS_Q_Size		,
	_A_PACKETS_Q_RdPtr		,
	_A_PACKETS_Q_WrPtr		,
	_A_PACKETS_Q_PrevRdPtr	,
	_A_PACKETS_Q_Emptiness	,
	_A_PACKETS_Q_Fullness	,
	_A_Queued_PTS_lo			,
	_A_Queued_PTS_hi			,
	_A_Completed_PTS_lo		,
	_A_Completed_PTS_hi		,
	_V_byte_cnt				,
	_V_input_queue_cnt		, 
	_V_wait_queue_cnt		,
	_V_device_state			, 
	_V_requested_state		,
	_V_DATA_Q_Size			,
	_V_DATA_Q_RdPtr			,
	_V_DATA_Q_WrPtr			,
	_V_DATA_Q_Emptiness		,
	_V_DATA_Q_Fullness		,
	_V_PTS_Q_Emptiness		,
	_V_PACKETS_Q_Size		,
	_V_PACKETS_Q_RdPtr		,
	_V_PACKETS_Q_WrPtr		, 
	_V_PACKETS_Q_PrevRdPtr	,
	_V_PACKETS_Q_Emptiness	,
	_V_PACKETS_Q_Fullness	,
	_V_Queued_PTS_lo			,
	_V_Queued_PTS_hi			,
	_V_Completed_PTS_lo		,
	_V_Completed_PTS_hi		,
	_SP_byte_cnt			,
	_SP_input_queue_cnt		, 
	_SP_wait_queue_cnt		,
	_SP_device_state		,
	_SP_requested_state		,
	_SP_DATA_Q_Size			,
	_SP_DATA_Q_RdPtr		,
	_SP_DATA_Q_WrPtr		, 
	_SP_DATA_Q_Emptiness	,
	_SP_DATA_Q_Fullness		,
	_SP_PTS_Q_Emptiness		,
	_SP_PACKETS_Q_Size		,
	_SP_PACKETS_Q_RdPtr		,
	_SP_PACKETS_Q_WrPtr		,
	_SP_PACKETS_Q_PrevRdPtr	, 
	_SP_PACKETS_Q_Emptiness	,
	_SP_PACKETS_Q_Fullness	,
	_SP_Queued_PTS_lo			,
	_SP_Queued_PTS_hi			,
	_SP_Completed_PTS_lo		,
	_SP_Completed_PTS_hi		,
	_frame_event_type		, 
	_frame_event_data		,
	_frame_event_flags		,
	_interrupt_cnt			,
	_last_int_state			,
	_EVENT_SRB_pending		,
	_EVENT_data				,
	_EVENT_flags			,
	_EVENT_type				,
	_AV_PTS_msec_diff_lo	,
	_AV_PTS_msec_diff_hi	,
	_AV_PTS_FIFO_diff_lo	,
	_AV_PTS_FIFO_diff_hi	,
	_class_IrpRefCount		,
	_OSD_byte_cnt			,
	_OSD_input_queue_cnt	, 
	_OSD_wait_queue_cnt		,
	_OSD_device_state		,
	_OSD_requested_state	,
	_OSD_DATA_Q_Size		,
	_OSD_DATA_Q_RdPtr		,
	_OSD_DATA_Q_WrPtr		, 
	_OSD_DATA_Q_Emptiness	,
	_OSD_DATA_Q_Fullness	,
	_OSD_PTS_Q_Emptiness	,
	_OSD_PACKETS_Q_Size		,
	_OSD_PACKETS_Q_RdPtr	,
	_OSD_PACKETS_Q_WrPtr	,
	_OSD_PACKETS_Q_PrevRdPtr, 
	_OSD_PACKETS_Q_Emptiness,
	_OSD_PACKETS_Q_Fullness	,
	_OSD_Queued_PTS_lo		,
	_OSD_Queued_PTS_hi		,
	_OSD_Completed_PTS_lo		,
	_OSD_Completed_PTS_hi		,
	_DebugRegister_0		,
	_DebugRegister_1		,
	_DebugRegister_2		,
	_DebugRegister_3		,
	_DebugRegister_4		,
	_DebugRegister_5		,
	_DebugRegister_6		,
	_DebugRegister_7		,
	_max_board_property		
}type;

#define PROP_BASE				0x1	//

#define A_byte_cnt				PROP_BASE + _A_byte_cnt
#define A_input_queue_cnt		PROP_BASE + _A_input_queue_cnt
#define A_wait_queue_cnt		PROP_BASE + _A_wait_queue_cnt
#define A_device_state			PROP_BASE + _A_device_state
#define A_requested_state		PROP_BASE + _A_requested_state
#define A_DATA_Q_Size			PROP_BASE + _A_DATA_Q_Size
#define A_DATA_Q_RdPtr			PROP_BASE + _A_DATA_Q_RdPtr
#define A_DATA_Q_WrPtr			PROP_BASE + _A_DATA_Q_WrPtr
#define A_DATA_Q_Emptiness		PROP_BASE + _A_DATA_Q_Emptiness
#define A_DATA_Q_Fullness		PROP_BASE + _A_DATA_Q_Fullness
#define A_PTS_Q_Emptiness		PROP_BASE + _A_PTS_Q_Emptiness
#define A_PACKETS_Q_Size		PROP_BASE + _A_PACKETS_Q_Size
#define A_PACKETS_Q_RdPtr		PROP_BASE + _A_PACKETS_Q_RdPtr
#define A_PACKETS_Q_WrPtr		PROP_BASE + _A_PACKETS_Q_WrPtr
#define A_PACKETS_Q_PrevRdPtr	PROP_BASE + _A_PACKETS_Q_PrevRdPtr
#define A_PACKETS_Q_Emptiness	PROP_BASE + _A_PACKETS_Q_Emptiness
#define A_PACKETS_Q_Fullness	PROP_BASE + _A_PACKETS_Q_Fullness
#define A_Queued_PTS_lo			PROP_BASE + _A_Queued_PTS_lo
#define A_Queued_PTS_hi			PROP_BASE + _A_Queued_PTS_hi
#define A_Completed_PTS_lo		PROP_BASE + _A_Completed_PTS_lo
#define A_Completed_PTS_hi		PROP_BASE + _A_Completed_PTS_hi
#define V_byte_cnt				PROP_BASE + _V_byte_cnt
#define V_input_queue_cnt		PROP_BASE + _V_input_queue_cnt
#define V_wait_queue_cnt		PROP_BASE + _V_wait_queue_cnt
#define V_device_state			PROP_BASE + _V_device_state
#define V_requested_state		PROP_BASE + _V_requested_state
#define V_DATA_Q_Size			PROP_BASE + _V_DATA_Q_Size
#define V_DATA_Q_RdPtr			PROP_BASE + _V_DATA_Q_RdPtr
#define V_DATA_Q_WrPtr			PROP_BASE + _V_DATA_Q_WrPtr
#define V_DATA_Q_Emptiness		PROP_BASE + _V_DATA_Q_Emptiness
#define V_DATA_Q_Fullness		PROP_BASE + _V_DATA_Q_Fullness
#define V_PTS_Q_Emptiness		PROP_BASE + _V_PTS_Q_Emptiness
#define V_PACKETS_Q_Size		PROP_BASE + _V_PACKETS_Q_Size
#define V_PACKETS_Q_RdPtr		PROP_BASE + _V_PACKETS_Q_RdPtr
#define V_PACKETS_Q_WrPtr		PROP_BASE + _V_PACKETS_Q_WrPtr
#define V_PACKETS_Q_PrevRdPtr	PROP_BASE + _V_PACKETS_Q_PrevRdPtr
#define V_PACKETS_Q_Emptiness	PROP_BASE + _V_PACKETS_Q_Emptiness
#define V_PACKETS_Q_Fullness	PROP_BASE + _V_PACKETS_Q_Fullness
#define V_Queued_PTS_lo			PROP_BASE + _V_Queued_PTS_lo
#define V_Queued_PTS_hi			PROP_BASE + _V_Queued_PTS_hi
#define V_Completed_PTS_lo		PROP_BASE + _V_Completed_PTS_lo
#define V_Completed_PTS_hi		PROP_BASE + _V_Completed_PTS_hi
#define SP_byte_cnt				PROP_BASE + _SP_byte_cnt
#define SP_input_queue_cnt		PROP_BASE + _SP_input_queue_cnt
#define SP_wait_queue_cnt		PROP_BASE + _SP_wait_queue_cnt
#define SP_device_state			PROP_BASE + _SP_device_state
#define SP_requested_state		PROP_BASE + _SP_requested_state
#define SP_DATA_Q_Size			PROP_BASE + _SP_DATA_Q_Size
#define SP_DATA_Q_RdPtr			PROP_BASE + _SP_DATA_Q_RdPtr
#define SP_DATA_Q_WrPtr			PROP_BASE + _SP_DATA_Q_WrPtr
#define SP_DATA_Q_Emptiness		PROP_BASE + _SP_DATA_Q_Emptiness
#define SP_DATA_Q_Fullness		PROP_BASE + _SP_DATA_Q_Fullness
#define SP_PTS_Q_Emptiness		PROP_BASE + _SP_PTS_Q_Emptiness
#define SP_PACKETS_Q_Size		PROP_BASE + _SP_PACKETS_Q_Size
#define SP_PACKETS_Q_RdPtr		PROP_BASE + _SP_PACKETS_Q_RdPtr
#define SP_PACKETS_Q_WrPtr		PROP_BASE + _SP_PACKETS_Q_WrPtr
#define SP_PACKETS_Q_PrevRdPtr	PROP_BASE + _SP_PACKETS_Q_PrevRdPtr
#define SP_PACKETS_Q_Emptiness	PROP_BASE + _SP_PACKETS_Q_Emptiness
#define SP_PACKETS_Q_Fullness	PROP_BASE + _SP_PACKETS_Q_Fullness
#define SP_Queued_PTS_lo		PROP_BASE + _SP_Queued_PTS_lo
#define SP_Queued_PTS_hi		PROP_BASE + _SP_Queued_PTS_hi
#define SP_Completed_PTS_lo		PROP_BASE + _SP_Completed_PTS_lo
#define SP_Completed_PTS_hi		PROP_BASE + _SP_Completed_PTS_hi
#define frame_event_type		PROP_BASE + _frame_event_type
#define frame_event_data		PROP_BASE + _frame_event_data
#define frame_event_flags		PROP_BASE + _frame_event_flags
#define interrupt_cnt			PROP_BASE + _interrupt_cnt
#define last_int_state			PROP_BASE + _last_int_state
#define EVENT_SRB_pending		PROP_BASE + _EVENT_SRB_pending
#define EVENT_data				PROP_BASE + _EVENT_data
#define EVENT_flags				PROP_BASE + _EVENT_flags
#define EVENT_type				PROP_BASE + _EVENT_type
#define AV_PTS_msec_diff_lo		PROP_BASE + _AV_PTS_msec_diff_lo
#define AV_PTS_msec_diff_hi		PROP_BASE + _AV_PTS_msec_diff_hi
#define AV_PTS_FIFO_diff_lo		PROP_BASE + _AV_PTS_FIFO_diff_lo
#define AV_PTS_FIFO_diff_hi		PROP_BASE + _AV_PTS_FIFO_diff_hi
#define	class_IrpRefCount		PROP_BASE + _class_IrpRefCount
#define OSD_byte_cnt			PROP_BASE + _OSD_byte_cnt
#define OSD_input_queue_cnt		PROP_BASE + _OSD_input_queue_cnt
#define OSD_wait_queue_cnt		PROP_BASE + _OSD_wait_queue_cnt
#define OSD_device_state		PROP_BASE + _OSD_device_state
#define OSD_requested_state		PROP_BASE + _OSD_requested_state
#define OSD_DATA_Q_Size			PROP_BASE + _OSD_DATA_Q_Size
#define OSD_DATA_Q_RdPtr		PROP_BASE + _OSD_DATA_Q_RdPtr
#define OSD_DATA_Q_WrPtr		PROP_BASE + _OSD_DATA_Q_WrPtr
#define OSD_DATA_Q_Emptiness	PROP_BASE + _OSD_DATA_Q_Emptiness
#define OSD_DATA_Q_Fullness		PROP_BASE + _OSD_DATA_Q_Fullness
#define OSD_PTS_Q_Emptiness		PROP_BASE + _OSD_PTS_Q_Emptiness
#define OSD_PACKETS_Q_Size		PROP_BASE + _OSD_PACKETS_Q_Size
#define OSD_PACKETS_Q_RdPtr		PROP_BASE + _OSD_PACKETS_Q_RdPtr
#define OSD_PACKETS_Q_WrPtr		PROP_BASE + _OSD_PACKETS_Q_WrPtr
#define OSD_PACKETS_Q_PrevRdPtr	PROP_BASE + _OSD_PACKETS_Q_PrevRdPtr
#define OSD_PACKETS_Q_Emptiness	PROP_BASE + _OSD_PACKETS_Q_Emptiness
#define OSD_PACKETS_Q_Fullness	PROP_BASE + _OSD_PACKETS_Q_Fullness
#define OSD_Queued_PTS_lo		PROP_BASE + _OSD_Queued_PTS_lo
#define OSD_Queued_PTS_hi		PROP_BASE + _OSD_Queued_PTS_hi
#define OSD_Completed_PTS_lo	PROP_BASE + _OSD_Completed_PTS_lo
#define OSD_Completed_PTS_hi	PROP_BASE + _OSD_Completed_PTS_hi
#define DebugRegister_0			PROP_BASE + _DebugRegister_0
#define DebugRegister_1			PROP_BASE + _DebugRegister_1
#define DebugRegister_2			PROP_BASE + _DebugRegister_2
#define DebugRegister_3			PROP_BASE + _DebugRegister_3
#define DebugRegister_4			PROP_BASE + _DebugRegister_4
#define DebugRegister_5			PROP_BASE + _DebugRegister_5
#define DebugRegister_6			PROP_BASE + _DebugRegister_6
#define DebugRegister_7			PROP_BASE + _DebugRegister_7

///////////////////////////////////////////////////////////////////////////////
typedef enum {
	prop_IOCTL_AUDIO_MPEG_DEVICE_INFO,	// 0x0
	prop_IOCTL_AUDIO_RESET,
	prop_IOCTL_MPEG_AUDIO_PLAY,
	prop_IOCTL_MPEG_AUDIO_PAUSE,
	prop_IOCTL_MPEG_AUDIO_STOP,
	prop_IOCTL_AUDIO_FREEZE,
	prop_IOCTL_AUDIO_SET_EVENT,
	prop_IOCTL_MPEG_AUDIO_QUERY_DEVICE,	

	prop_IOCTL_MPEG_AV_GET_STC,			// 0x8
	prop_IOCTL_MPEG_AV_SET_STC,
	prop_IOCTL_AVOS_GET_ATTRIBUTE,
	prop_IOCTL_AVOS_SET_ATTRIBUTE,	

	prop_IOCTL_VIDEO_RESET,				// 0xC
	prop_IOCTL_VIDEO_SYNC,
	prop_IOCTL_MPEG_VIDEO_PLAY,
	prop_IOCTL_VIDEO_FREEZE,
	prop_IOCTL_VIDEO_SET_EVENT,		
	prop_IOCTL_MPEG_VIDEO_PAUSE,
	prop_IOCTL_MPEG_VIDEO_STOP,
	prop_IOCTL_MPEG_VIDEO_QUERY_DEVICE,
	prop_IOCTL_MPEG_VIDEO_CLEAR_BUFFER,	

	prop_IOCTL_SPU_RESET,				// 0x15
	prop_IOCTL_MPEG_SPU_PLAY,
	prop_IOCTL_SPU_FREEZE,
	prop_IOCTL_MPEG_SPU_PAUSE,
	prop_IOCTL_MPEG_SPU_STOP,
	prop_IOCTL_MPEG_SPU_HIGHLIGHT_COMMAND,

	prop_IOCTL_MPEG_OVERLAY_QUERY_DEVICE,	// 0x1B
	prop_IOCTL_OVERLAY_MODE,
	prop_IOCTL_MPEG_OVERLAY_SET_BIT_MASK,
	prop_IOCTL_MPEG_OVERLAY_GET_VGAKEY,
	prop_IOCTL_MPEG_OVERLAY_SET_VGAKEY,
	prop_IOCTL_MPEG_OVERLAY_SET_VGAKEY2,
	prop_IOCTL_OVERLAY_VGAKEY2,
	prop_IOCTL_MPEG_OVERLAY_SET_SOURCE,
	prop_IOCTL_MPEG_OVERLAY_SET_DESTINATION,
	prop_IOCTL_MPEG_OVERLAY_CALIBRATE,
	prop_IOCTL_MPEG_OVERLAY_SET_CALIBRATION, 
	prop_IOCTL_MPEG_VIDEO_CAPTO_BUFFER,

	prop_TEST_PROPERTY_ULONG,				// 0x27
	prop_IOCTL_MPEG_BOARD_CONTROL,
	prop_IOCTL_MPEG_START_DEVICE,
	prop_IOCTL_MPEG_STOP_DEVICE

}PROPERTIES;
///////////////////////////////////////////////////////////////////////////////

typedef enum {
	QUASAR_DEVICE_Monitoring,
	QUASAR_DEVICE_HwLibProperty,
	QUASAR_DEVICE_HwLibAttribute,
	QUASAR_DEVICE_MapMem,
	QUASAR_DEVICE_DMA_buffer,
	QUASAR_DEVICE_Capabilities,
	QUASAR_DEVICE_Info,
	QUASAR_DEVICE_Test,
	QUASAR_DEVICE_MAX
}QUASAR_DEVICE;

typedef enum {
    QUASAR_CONNECTION_Reset,
    QUASAR_CONNECTION_STATE,
    QUASAR_CONNECTION_DATAFORMAT,
    QUASAR_CONNECTION_PROPOSEDATAFORMAT
}QUASAR_CONNECTION;

typedef enum {
	QUASAR_AUDIO_Attributes,
	QUASAR_AUDIO_DeviceInfo,
	QUASAR_AUDIO_Reset,
	QUASAR_AUDIO_GetSTC,
	QUASAR_AUDIO_SetSTC,
	QUASAR_AUDIO_Play,
	QUASAR_AUDIO_Pause,
	QUASAR_AUDIO_Freeze,
	QUASAR_AUDIO_Stop,
	QUASAR_AUDIO_PositionEvent,
	QUASAR_AUDIO_MAX
}QUASAR_AUDIO;

typedef enum {
	QUASAR_VIDEO_Attributes,
	QUASAR_VIDEO_CaptureToBuffer,
	QUASAR_VIDEO_Reset,
	QUASAR_VIDEO_SyncToAudio,
	QUASAR_VIDEO_GetSTC,
	QUASAR_VIDEO_SetSTC,
	QUASAR_VIDEO_Play,
	QUASAR_VIDEO_Pause,
	QUASAR_VIDEO_Freeze,
	QUASAR_VIDEO_Stop,
	QUASAR_VIDEO_PositionEvent,
	QUASAR_VIDEO_DeviceInfo,
	QUASAR_VIDEO_ClearBuffer,
	QUASAR_VIDEO_MAX
}QUASAR_VIDEO;

typedef enum {
	QUASAR_OVERLAY_DeviceInfo,
	QUASAR_OVERLAY_Mode,
	QUASAR_OVERLAY_BitMask,
	QUASAR_OVERLAY_VGAKey,
	QUASAR_OVERLAY_Source,
	QUASAR_OVERLAY_Destination,
	QUASAR_OVERLAY_Calibration,
	QUASAR_OVERLAY_CalibParam,
	QUASAR_OVERLAY_VGAKey2,
	QUASAR_OVERLAY_Attributes,
	QUASAR_OVERLAY_MAX
}QUASAR_OVERLAY;

typedef enum {
	QUASAR_SPU_Reset,
	QUASAR_SPU_Play,
	QUASAR_SPU_Pause,
	QUASAR_SPU_Freeze,
	QUASAR_SPU_Stop,
	QUASAR_SPU_HliCommand,
	QUASAR_SPU_Attributes,
	QUASAR_SPU_MAX
}QUASAR_SPU;

typedef enum {
	QUASAR_OSD_Reset,
	QUASAR_OSD_Play,
	QUASAR_OSD_Pause,
	QUASAR_OSD_Stop,
	QUASAR_OSD_Attributes,
	QUASAR_OSD_MAX
}QUASAR_OSD;

typedef enum {
	QUASAR_COMMON_Attributes,
	QUASAR_COMMON_Properties
}QUASAR_COMMON;

typedef struct{
	DWORD	Flags;
	DWORD	PropSet;
	DWORD	PropId;
	DWORD	PropFlags;
	PVOID	pPropData;
	DWORD	dwPropSizeIn;
	DWORD*	pdwPropSizeOut;
}QUASAR_COMMON_PropData,*PQUASAR_COMMON_PropData;

typedef QUASAR_COMMON_PropData RMPROPERTY_DESCRIPTOR, *PRMPROPERTY_DESCRIPTOR;

// RM8400_PROP_SET_General used only for WDM - Hollywood Plus bridge to START/STOP driver
DEFINE_GUID(RM8400_PROP_SET_General		, 0xa57c04f2, 0xbbea, 0x4376, 0xae, 0x6b, 0x52, 0xbf, 0x54, 0x3d, 0x92, 0x7b);

DEFINE_GUID(QUASAR_PROP_SET_Device		, 0x18dc3d17, 0xb060, 0x46fd, 0x8b, 0x5c, 0xe4, 0xb6, 0x29, 0x19, 0xdf, 0xe0);
DEFINE_GUID(QUASAR_PROP_SET_Audio		, 0xf886f30d, 0xba9b, 0x497c, 0x8d, 0x97, 0xc5, 0x3c, 0x26, 0x7d, 0x63, 0xfa);
DEFINE_GUID(QUASAR_PROP_SET_Video		, 0x33d133e2, 0xe577, 0x44e3, 0xa5, 0x4e, 0x78, 0xbb, 0x96, 0x0a, 0x53, 0x83);
DEFINE_GUID(QUASAR_PROP_SET_Subpicture	, 0xc7015395, 0x9390, 0x4d4d, 0xb7, 0xce, 0x8f, 0xe8, 0xd9, 0xd9, 0x5a, 0x48);
DEFINE_GUID(QUASAR_PROP_SET_Overlay		, 0x78d30ff0, 0xaf83, 0x4459, 0x98, 0xf1, 0xcd, 0x96, 0x96, 0x02, 0x53, 0xe6);
DEFINE_GUID(QUASAR_PROP_SET_OSD			, 0xb3b19a10, 0x3a62, 0x47df, 0xae, 0xa8, 0x9b, 0x66, 0x7e, 0x25, 0x7a, 0x4e);
DEFINE_GUID(QUASAR_PROP_SET_Connection	, 0x7ccf0089, 0x4ffe, 0x476b, 0x8a, 0x13, 0x83, 0x07, 0xfa, 0x6e, 0xf4, 0x7e);
/*
// {0DD3212C-55FF-472c-AD29-C626FD9CA9D7}
DEFINE_GUID(RMDATAFORMAT_TYPE_MPEG4_VIDEO,
0x0dd3212c, 0x55ff, 0x472c, 0xad, 0x29, 0xc6, 0x26, 0xfd, 0x9c, 0xa9, 0xd7);

// {AD79B0EE-DE64-45b1-BD92-75F7502CFC0B}
DEFINE_GUID(RMDATAFORMAT_SUBTYPE_MPEG4_PAYLOAD, 
0xad79b0ee, 0xde64, 0x45b1, 0xbd, 0x92, 0x75, 0xf7, 0x50, 0x2c, 0xfc, 0xb);

  // {FE24CD13-45CF-4b20-A23C-0B2B2EA08531}
DEFINE_GUID(RMDATAFORMAT_TYPE_MPEG4_AUDIO, 
0xfe24cd13, 0x45cf, 0x4b20, 0xa2, 0x3c, 0xb, 0x2b, 0x2e, 0xa0, 0x85, 0x31);

*/

// GUID Created to support MPEG4 format

// VIDEO
//
// {8AB4D3D1-C812-11d5-BE17-00A0C90AA8A1}
DEFINE_GUID(RMDATAFORMAT_SUBTYPE_SDMPEG4_Video,		//MEDIASUBTYPE_SDMPEG4_Video, 
0x8ab4d3d1, 0xc812, 0x11d5, 0xbe, 0x17, 0x0, 0xa0, 0xc9, 0xa, 0xa8, 0xa1);

// {99F38D11-49A4-4956-989E-B659D74AD86D}
DEFINE_GUID(RMDATAFORMAT_SPECIFIER_RM_MPEG4_VIDEO_FORMAT_STRUCT, 
0x99f38d11, 0x49a4, 0x4956, 0x98, 0x9e, 0xb6, 0x59, 0xd7, 0x4a, 0xd8, 0x6d);

// AUDIO
//
// {8AB4D3D2-C812-11d5-BE17-00A0C90AA8A1}
DEFINE_GUID(RMDATAFORMAT_SUBTYPE_SDMPEG4_PCMAudio,	// MEDIASUBTYPE_SDMPEG4_PCMAudio, 
0x8ab4d3d2, 0xc812, 0x11d5, 0xbe, 0x17, 0x0, 0xa0, 0xc9, 0xa, 0xa8, 0xa1);

// {4581637C-9D62-446f-A1CC-82F09E476855}
DEFINE_GUID(RMDATAFORMAT_SPECIFIER_RM_MPEG4_PCM_FORMAT_STRUCT, 
0x4581637c, 0x9d62, 0x446f, 0xa1, 0xcc, 0x82, 0xf0, 0x9e, 0x47, 0x68, 0x55);


typedef enum {
	LP_rmstream_WriteStream		= 0x01000000,
	LP_rmstream_WriteStream2	= 0x02000000,
	LP_rm8400_ReceiveDataPacket = 0x10000000,
	LP_rm8400_ReferCurrentBuffer= 0x11000000,
	LP_rm8400_ReleaseUsedBuffer	= 0x12000000,
	LP_mask						= 0x7F000000
}LOOPED_POINT;

#endif	// __guid_8400_h
