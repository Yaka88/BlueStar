#ifndef _WAVIFACE_H
#define _WAVIFACE_H

#include "mpegapi.h"
#include "ac3dec.h"
#include <dsound.h>
#include "ieaxspkr.h"

#ifdef _FILTER_96
#define nsp_UsesFir
#include "nsp\nsp.h"
#endif

#ifdef _MP3_SUPPORT
/// mp3 suport ///
#include "xing\mhead.h"
#include "xing\port.h"
typedef struct tagAUDIODEC
{
    int (*decode_init) (MPEG_HEAD * h, int framebytes_arg,
			int reduction_code, int transform_code,
			int convert_code, int freq_limit);
    void (*decode_info) (DEC_INFO * info);
    IN_OUT(*decode) (unsigned char *bs, short *pcm);
} AUDIODEC;
#endif


#if defined (IN_WAVIFACE_DLL_BUT_DO_NOT_EXPORT)
#define WAVAPI __cdecl
#undef IN_WAVIFACE_DLL
#elif defined (IN_WAVIFACE_DLL)
#define WAVAPI __declspec(dllexport) __cdecl
#else
#define WAVAPI __declspec(dllimport) __cdecl
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#define SAVE_BUF_SIZE	(16384)

typedef enum _CONTROL_DEVICE
{
    AudioDevice,		// mpeg
    VideoDevice,
    OverlayDevice,
	Ac3AudioDevice,		// ac3
	PcmAudioDevice,		// lpcm
	DtsAudioDevice,		// dts
    MaximumControlDevice
} CONTROL_DEVICE;

typedef enum _AUDIO_DEVICE_TYPE
{
    WaveDevice,			// standard wave driver
    DacDevice,			// on board dac (plays pcm only)
	DirectSoundDevice,	// direct sound driver
	Ac3ApiDevice,		// ac3api.dll (creative labs propriety api)
	MaximumAudioDeviceType
} AUDIO_DEVICE_TYPE;

typedef struct tagSYNCIO
{
	HANDLE					hDevice;
	PBYTE					pPacketData;
	PWAVEHDR				pwh;
	LPOVERLAPPED			pOverlapped;
	PMPEG_PACKET_LIST_ENTRY	pMpegPacket;
	struct tagSYNCIO		*pNext;
} SYNCIO, *PSYNCIO;

// linked list stuff
typedef struct tagNODE
{
	PMPEG_PACKET_LIST_ENTRY	pPacketList;
	UINT					uiPacketCount;
	PMPEG_ASYNC_CONTEXT		pAsyncContext;
	struct tagNODE			*Next;
} NODE, *PNODE;

#define WAVE_FORMAT_EXTENSIBLE	0xFFFE
#define WAVE_FORMAT_SPDIF		0x92

#define WAVEFORMATEXTENSIBLE	MY_WAVEFORMATEXTENSIBLE
#define PWAVEFORMATEXTENSIBLE	MY_PWAVEFORMATEXTENSIBLE

typedef struct tagWAVEFORMATEXTENSIBLE {
    WAVEFORMATEX    Format;
    union {
        WORD wValidBitsPerSample;       /* bits of precision  */
        WORD wSamplesPerBlock;          /* valid if wBitsPerSample==0 */
        WORD wReserved;                 /* If neither applies, set to */
                                        /* zero. */
    } Samples;
    DWORD           dwChannelMask;      /* which channels are */
                                        /* present in stream  */
    GUID            SubFormat;
} WAVEFORMATEXTENSIBLE, *PWAVEFORMATEXTENSIBLE;

typedef void (CALLBACK *WAVE_CALLBACK)(HWAVEOUT, UINT, DWORD, DWORD, DWORD);

#ifdef __cplusplus
class LINKED_LIST
{	
private:
	CRITICAL_SECTION		m_cs;
	ULONG					m_cs_init;
	PNODE					m_pHead;
	PNODE					m_pTail;

public:
	LINKED_LIST ();
	~LINKED_LIST ();
	void Add (PNODE pNode);
	PNODE Remove (void);
	void Free (void);
};

typedef struct tagSYNCPOINT
{	
	LONG				Position;		// in bytes
	MPEG_SYSTEM_TIME	Pts;			// in 90 kHz ticks

} SYNCPOINT, *PSYNCPOINT;

class AUDIO_OUT_DEVICE
{
private:
public:
	AUDIO_DEVICE_TYPE	m_DeviceType;
	int					m_SilencePacket;

	AUDIO_OUT_DEVICE ();
	~AUDIO_OUT_DEVICE ();

	MMRESULT SetOutputDevice (AUDIO_DEVICE_TYPE DeviceType);
	MMRESULT Open (LPHWAVEOUT phwo, UINT uDeviceID, LPCWAVEFORMATEX pwfx, 
		DWORD dwCallback, DWORD dwInstance, DWORD fdwOpen, PVOID pwsi);
	MMRESULT Close (HWAVEOUT hwo, PVOID pwsi);
	MMRESULT PrepareHeader (HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh, PVOID pwsi);
	MMRESULT UnprepareHeader (HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh, PVOID pwsi);
	MMRESULT Write (HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh, PVOID pwsi, PSYNCIO *ppSyncIo);
	MMRESULT Pause (HWAVEOUT hwo, PVOID pwsi);
	MMRESULT Restart (HWAVEOUT hwo, PVOID pwsi);
	MMRESULT Reset (HWAVEOUT hwo, PVOID pwsi);
	MMRESULT GetPosition (HWAVEOUT hwo, LPMMTIME pmmt, UINT cbmmt, PVOID pwsi);
	MMRESULT GetVolume (HWAVEOUT hwo, LPDWORD pdwVolume, PVOID pwsi);
	MMRESULT SetVolume (HWAVEOUT hwo, DWORD dwVolume, PVOID pwsi);
};

#define MAX_CHANNELS	6

typedef struct tagDIRECT_SOUND_BUFFER
{
	ULONG	RefCount;
	WAVEHDR	*WaveHdr;
	struct tagDIRECT_SOUND_BUFFER *pNext;
} DIRECT_SOUND_BUFFER, *PDIRECT_SOUND_BUFFER;

class DIRECT_SOUND_DEVICE
{	
public:
	DIRECT_SOUND_DEVICE ();
	~DIRECT_SOUND_DEVICE ();

	CRITICAL_SECTION		m_cs;			// to synchronize access to linked list
	LPDIRECTSOUND			m_lpDirectSound;// dsound surface
	LPDIRECTSOUNDBUFFER     m_lpdsPrimaryBuffer;	// dsound primary buffer
	LPDIRECTSOUND3DLISTENER	m_lpds3DListener;
	LPDIRECTSOUNDBUFFER		m_lpdsBuffer[MAX_CHANNELS];		// assigned buffer object
	LPKSPROPERTYSET			m_lpPropSet[MAX_CHANNELS];		// IKSPropertySet interface
	LPDIRECTSOUND3DBUFFER	m_lpds3DBuffer[MAX_CHANNELS];	// 3D buffer interface
	DWORD					m_dwDescFlags[MAX_CHANNELS];	// buffer description flags
	DWORD					m_dwDescBufferBSize[MAX_CHANNELS];	// buffer size
	DWORD					m_dwSelection[MAX_CHANNELS];	// speaker mappings
	ULONG					m_BytesWritten[MAX_CHANNELS];	// #of bytes written to te dsound device
	ULONG					m_Wr[MAX_CHANNELS];				// current write pointer in the dsound buffer
	ULONG					m_PrevRd[MAX_CHANNELS];
	ULONG					m_BytesRead;
	WAVEFORMATEXTENSIBLE	m_wfx;			// buffer format
	UINT					m_uTimerID;	// timer id
	WAVE_CALLBACK			m_WaveCallback;	// wave callback proc
	PDIRECT_SOUND_BUFFER	m_pHead;		// head of linked list
	PDIRECT_SOUND_BUFFER	m_pCurrBuf[MAX_CHANNELS];	// current stream buffer
	ULONG					m_pCurrBufPos[MAX_CHANNELS];// current stream position within current buffer
	ULONG					m_dwInstance;	// instance data to pass to callback
	MPEG_DEVICE_STATE		m_State;		// current state
	ULONG					m_TimerRes;	
	LONG					m_Volume;

	HINSTANCE				m_hDSoundLib;
	HRESULT (WINAPI *m_pDirectSoundCreate)(LPGUID, LPDIRECTSOUND *, LPUNKNOWN);

	MMRESULT DSoundOpen (HWAVEOUT *phwo, LPWAVEFORMATEX pwfx, DWORD dwCallback, DWORD dwInstance, PVOID pwsi);
	MMRESULT DSoundClose (PVOID pwsi);
	MMRESULT DSoundPrepareHeader (LPWAVEHDR pwh, UINT cbwh, PVOID pwsi);
	MMRESULT DSoundUnPrepareHeader (LPWAVEHDR pwh, UINT cbwh, PVOID pwsi);
	MMRESULT DSoundWrite (LPWAVEHDR pwh, UINT cbwh, PVOID pwsi, PSYNCIO *ppSyncIo);
	MMRESULT DSoundPause ();
	MMRESULT DSoundRestart ();
	MMRESULT DSoundReset ();
	MMRESULT DSoundGetPosition (LPMMTIME pmmt, UINT cbmmt, PVOID pwsi);
	MMRESULT DSoundGetVolume (DWORD *pdwVolume, PVOID pwsi);
	MMRESULT DSoundSetVolume (DWORD dwVolume, PVOID pwsi);

	ULONG DSoundMemcpy (ULONG StreamNo, PBYTE pPcm, ULONG cbPcm);
	ULONG DSoundUpdate ();
	static void CALLBACK DSoundTimer(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
};

#include "ac3api.h"

class AC3API_DEVICE
{
public:
	AC3API_DEVICE ();
	~AC3API_DEVICE ();
	
	PWAVEHDR			m_pHead;	// head of the linked list of buffers to be queued
	UINT				m_uTimerID;	// timer to dequeue a buffer and write it to the ac3_api device
	ULONG				m_TimerRes;
	CRITICAL_SECTION	m_cs;		// to synchronize queue access
	ULONG				m_cs_inititialized;
	AC3_HANDLE			m_hAc3;
	HINSTANCE			m_hAc3Api;
	WAVE_CALLBACK		m_WaveCallback;
	ULONG				m_dwInstance;
	LONG				m_BufferCount;
	ULONG				m_Mode;
	LONG				m_PrefillThreshold;
	MPEG_DEVICE_STATE	m_State;

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

	MMRESULT Ac3Open (HWAVEOUT *phwo, LPWAVEFORMATEX pwfx, DWORD dwCallback, DWORD dwInstance, PVOID pwsi);
	MMRESULT Ac3Close (PVOID pwsi);
	MMRESULT Ac3PrepareHeader (LPWAVEHDR pwh, UINT cbwh, PVOID pwsi);
	MMRESULT Ac3UnPrepareHeader (LPWAVEHDR pwh, UINT cbwh, PVOID pwsi);
	MMRESULT Ac3Write (LPWAVEHDR pwh, UINT cbwh, PVOID pwsi, PSYNCIO *ppSyncIo);
	MMRESULT Ac3Pause ();
	MMRESULT Ac3Restart ();
	MMRESULT Ac3Reset ();
	MMRESULT Ac3GetPosition (LPMMTIME pmmt, UINT cbmmt, PVOID pwsi);
	MMRESULT Ac3GetVolume (DWORD *pdwVolume, PVOID pwsi);
	MMRESULT Ac3SetVolume (DWORD dwVolume, PVOID pwsi);

	ULONG Ac3Update ();

	static void CALLBACK Ac3Timer(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
};

typedef struct tagWAVESTREAMINFO
{
	HWAVEOUT			hWaveOut;		// handle of wave device
	HWAVEOUT			hVxD;			// handle of vxd / kernel driver
	ULONG				DevNum;			// device number
	BOOLEAN				is_mpeg;		// true if stream is mpeg, false if stream is ac3
	MPEG_SYSTEM_TIME	TrackSTC;		// relative start time of mpeg audio
	MPEG_SYSTEM_TIME	RelativeStart;	// relative start time of wave device
	MPEG_DEVICE_STATE	DeviceState;	// current state of device
	BOOLEAN				NeedsStc;		// true if sts needs to be set
	ULONG				AudioFormat;	// current audio format
	ULONG				DecodeOnly;		// true if decoding only

	// source information
    WORD        nChannels;				// number of channels (i.e. mono, stereo...) 
    DWORD       nSamplesPerSec;			// sample rate 
    DWORD       nAvgBytesPerSec;		// for buffer estimation 
    WORD        nBlockAlign;			// block size of data 
    WORD        wBitsPerSample;			// number of bits per sample of mono data 
    WORD        cbSize;					// the count in bytes of the size of 	
	BYTE		SubStreamId;			// the current stream number
	ULONG		InitialVolumeLeft;		// initial volume before playing
	ULONG		InitialVolumeRight;		// since we do not actuall open the device
										// until we start playing

	// mpeg
	WORD		Layer;					// mpeg layer
	ULONG		Bitrate;				// mpeg bitrate
	WORD		Mode;					// mpeg mode

	// ac3
	WORD		nAuxBitsCode;			// ac3 aux bits
	WORD		karaoke_mode;
	ULONG		ExtraBytes;				// padding and header bytes for ac3 spdif encoding

	// general
	ULONG		ValidData;				// valid data in temporary buffer
	UCHAR		pBuf[SAVE_BUF_SIZE];	// temporary buffer used to store partial frames
	ULONG		MpegDecoder;			// mpeg audio decoder
	ULONG		Ac3Decoder;				// ac3 audio decoder
	AC3DEC_IN	ac3dec_in;				// for ibm ac3 decoder (stores parameters)
	SYNCPOINT	SyncPoint;
	HANDLE		hDecodeThread;			// decode thread
	HANDLE		DecodeWakeUp;			// event to wake up the decode thread
	DWORD		DecodeId;				// decode thread id
	DWORD		decode_audio;			// true if we want the thread to decode audio
	LINKED_LIST	List;
	ULONG		LowCpu;					// flag to indicate if we should try to decode using less cpu, but worse audio qualty
	AUDIO_OUT_DEVICE PcmOut;			// Audio Out object - wave, dac, or spdif
	ULONG		SendCompressedData;		// if 1 then we send compressed data to hw
	ULONG		EnableSpdif;			// if 1 then send compressed ac3 to the spdif encoder
	ULONG		EnableSync;				// if 1 then we enable video sync (we set the stc)
	MPEG_SYSTEM_TIME BufferPts;			// the pts associated with a decompressed pcm buffer
	ULONG		SyncCounter;			// counts number of SyncVideoToAudio sent

	ULONG		IsNT;					// 1 if running under NT

	CONTROL_DEVICE ControlDevice;		// current device (audio format) we are decoding

	// function pointers for decoder specific routines
	ULONG (*decode_frame) (PUCHAR, ULONG, PUCHAR, ULONG, PWAVEFORMATEX, struct tagWAVESTREAMINFO *);
	ULONG (*get_audio_frame_length) (struct tagWAVESTREAMINFO *, ULONG, PUCHAR);
	ULONG (*resync_to_next_audio_frame) (PUCHAR, ULONG);

	// functions pointers for outputing only left/right
	VOID  (*set_source) (PUCHAR, ULONG);

	// pcm
	WAVEFORMATEX	wfxDst;				// destination pcm format
	ULONG			FilterPcm;			// true if we should enable our 48 - xx filter
	ULONG			FilterCount;
	ULONG			OriginalRate;		// original sampling rate - before conversion
	ULONG			SampleCounter;
	BOOLEAN			bResyncPcm;
	BOOLEAN			QueueReturnedBuffers;	// true if you want to re-send the buffers that have been sent back from the wave device
	ULONG			nBuffersQueued;
	LPWAVEHDR		QueuedBuffers[256];		// maximum 100 buffers queued
	ULONG			nBytesQueued;			// number of bytes saved in the buffer q - for CloseOnPause only
	int				ForteSoundCard;			// !0 if using forte sound card
	LONG			ScaleSoundCardVolume;

	// for sblive wave support
	ULONG			SendSpdifStream;
	WAVEFORMATEXTENSIBLE wfxDstEx;

#ifdef _FILTER_96	 
	// used for 96->48 filtering
	NSPFirState		fir_state;				// fir state for channel 0
	NSPFirState		fir_state2;				// fir state for channel 1
	BYTE			pInBuf[4096];			// temp buf used in filtering
	BYTE			pOutBuf[4096];			// temp buf used in filtering
	ULONG			Do96Filter;				// enable 96 -> 48 filltering
#endif

	// for wave under NT
	CRITICAL_SECTION wave_cs;
	LPWAVEHDR		WaveHeaders[256];
	ULONG			WaveHeaderCount;

	// for direct sound support
	DIRECT_SOUND_DEVICE DSoundDevice;
	// for ac3api support
	AC3API_DEVICE		Ac3Api;
#ifdef _MP3_SUPPORT
	AUDIODEC		AuxMpegDecoder;
	BYTE			needs_init;
	ULONG			mp3_sample_rate;
#endif
	ULONG			ignore_ac3_crc;
} WAVESTREAMINFO, *PWAVESTREAMINFO;

#else
typedef struct tagWAVESTREAMINFO
{
	HWAVEOUT			hWaveOut;		// handle of wave device
	HWAVEOUT			hVxD;			// handle of vxd / kernel driver
	ULONG				DevNum;			// device number
	// the c program should not care how big the structure is
} WAVESTREAMINFO, *PWAVESTREAMINFO;
#endif

MPEG_STATUS WAVAPI 
WaveOpenDevice(
	IN PWAVESTREAMINFO *ppwsi
	);

MPEG_STATUS WAVAPI 
WaveCloseDevice(
	IN PWAVESTREAMINFO pwsi
	);

MPEG_STATUS WAVAPI 
WaveWriteData(
	IN PWAVESTREAMINFO pwsi,
    IN PMPEG_PACKET_LIST_ENTRY pPacketList,
    IN UINT uiPacketCount,
    IN PMPEG_ASYNC_CONTEXT pAsyncContext OPTIONAL
    );

MPEG_STATUS WAVAPI 
WaveDecode(
	IN PWAVESTREAMINFO pwsi,
    IN PBYTE pSrc,
    IN ULONG SrcLen,
	IN OUT PBYTE pDst,
	IN OUT ULONG *pDstLen
    );

MPEG_STATUS WAVAPI 
WaveQueryAsyncResult(
	IN PWAVESTREAMINFO pwsi,
    IN PMPEG_ASYNC_CONTEXT pAsyncContext,
    IN BOOL bWait
    );

MPEG_STATUS WAVAPI 
WaveResetDevice(
    IN PWAVESTREAMINFO pwsi
    );

MPEG_STATUS WAVAPI 
WaveSyncVideoToAudio(
	IN PWAVESTREAMINFO pwsi,
	IN HMPEG_DEVICE hDevice,
    IN MPEG_SYSTEM_TIME systemTimeDelta
    );

MPEG_STATUS WAVAPI 
WaveQuerySTC(
	IN PWAVESTREAMINFO pwsi,
    OUT PMPEG_SYSTEM_TIME pSystemTime
    );

MPEG_STATUS WAVAPI 
WaveSetSTC(
	IN PWAVESTREAMINFO pwsi,
    IN MPEG_SYSTEM_TIME systemTime
    );
    
MPEG_STATUS WAVAPI 
WavePlay(
    IN PWAVESTREAMINFO pwsi
    );

MPEG_STATUS WAVAPI
WavePause(
    IN PWAVESTREAMINFO pwsi
    );

MPEG_STATUS WAVAPI 
WaveStop(
    IN PWAVESTREAMINFO pwsi
    );
    
MPEG_STATUS WAVAPI 
WaveQueryDeviceState(
	IN PWAVESTREAMINFO pwsi,
    OUT PMPEG_DEVICE_STATE pCurrentDeviceState
    );

MPEG_STATUS WAVAPI 
WaveQueryInfo(
	IN PWAVESTREAMINFO pwsi,
    IN MPEG_INFO_ITEM eInfoItem,
    OUT PULONG pulValue
    );

MPEG_STATUS WAVAPI 
WaveQueryAttribute(
	IN PWAVESTREAMINFO pwsi,
    IN MPEG_ATTRIBUTE eAttribute,
    OUT PLONG plValue
    );

MPEG_STATUS WAVAPI 
WaveSetAttribute(
	IN PWAVESTREAMINFO pwsi,
    IN MPEG_ATTRIBUTE eAttribute,
    IN LONG lValue
    );

MPEG_STATUS WAVAPI 
WaveEos(
	IN PWAVESTREAMINFO pwsi,
	IN PMPEG_ASYNC_CONTEXT pAsyncContext
    );

MPEG_STATUS WAVAPI 
WaveUnprepareData(
	IN PWAVESTREAMINFO pwsi,
	IN PMPEG_ASYNC_CONTEXT pAsyncContext
    );

////// taken from mpegmini.h //////
#define MPEG_PACKET_TYPE_MPEG1      1
#define MPEG_PACKET_TYPE_MPEG2      2

// MPEG packet header information
typedef struct _MPEG_PACKET
{
    MPEG_SYSTEM_TIME PtsValue;      // presentation time stamp
    MPEG_SYSTEM_TIME DtsValue;      // decode time stamp
    ULONG PacketType;               // Packet Type
    ULONG StreamNumber;             // packet stream id
    ULONG PacketTotalSize;          // total size of the packet including header
    ULONG PacketHeaderSize;         // size of compressed header (in bytes)
    ULONG PacketPayloadSize;        // size of the actuly data (full packet-header)
    PUCHAR PacketData;              // pointer to the MPEG packet
    MPEG_SYSTEM_TIME ScrValue;      // system SCR time for this packet
} MPEG_PACKET, *PMPEG_PACKET;

////// Various constants defined by the ISO MPEG 1 specification /////

// Mask to derive stream type from stream_id field
#define STREAM_TYPE_MASK    0xE0

// Type for all audio streams (mpeg)
#define STREAM_TYPE_AUDIO   0xC0

// Type for private, reserved, and padding streams
#define STREAM_TYPE_OTHER		0xA0

// type for pcm stream
#define SUB_STREAM_TYPE_PCM		0xA0

// type for sc3 stream
#define SUB_STREAM_TYPE_AC3		0x80

// type for sc3 stream
#define SUB_STREAM_TYPE_DTS		0x88

// Mask to derive stream number from stream_id field
#define STREAM_NUMBER_MASK  (~STREAM_TYPE_MASK)

// Mask to extract the packet_start_header from the first ULONG
#define PACKET_START_MASK   0x00FFFFFF

// Bit layout of the stream_type_header adjust for intel processors
#define PACKET_START_CODE_PREFIX  0x00010000

// Mask to derive stream type from stream_id field
#define STREAM_TYPE_MASK    0xE0

// Type for all audio streams
#define STREAM_TYPE_AUDIO   0xC0

// Type for all video streams
#define STREAM_TYPE_VIDEO   0xE0

// Mask to derive stream number from stream_id field
#define STREAM_NUMBER_MASK  (~STREAM_TYPE_MASK)

// Mask to extract the packet_start_header from the first ULONG
#define PACKET_START_MASK   0x00FFFFFF

// Bit layout of the stream_type_header adjust for intel processors
#define PACKET_START_CODE_PREFIX  0x00010000

// intel byte swap
#define BSWAP(n)      ((USHORT)((((USHORT)(n)) << 8) | (((USHORT)(n)) >> 8)))

#ifdef __cplusplus
}
#endif

#endif


