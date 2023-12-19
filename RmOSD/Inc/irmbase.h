/*///////////////////////////////////////////////////////////////////////////////////////
FILE		irmbase.h

CREATED		12/06/01 by Vladimir Gaputin(VG), Sigma Design, Inc.

DESCRIPTION	Definitions of base - level interfaces. Actually this is generic
			enumerator binded with primitive communication interface,
			In order to be complete interface must be used with shared header 
			from underlined implementation.

COMMENTS	Logical model description:
			All this interfaces are implemented by one object and serves as set of 
			communication rools used to access this logical object.

			Sample steps:

			1. Find if there is resources in the system required to create this object:
				IRmObjectEnumerator->Next(IRmObjectMoniker * p);

			2. Optionally get information needed to make decision:
				IRmObjectMoniker->GetInfo(RMDEVMONIKER_INFOTYPE_ );

			3. Optionally check if the resource instance is not in use:
				IRmObjectMoniker->IsRunning();

			This way all instances can be enumerated.

			4. Find if the object has parts accessible from outside:
				IRmObjectMoniker->GetSubEnumerator(IRmObjectEnumerator*);
				IRmObjectEnumerator->Next(IRmObjectMoniker * p);

			Depth of this down enumeration is determined by implementation.

			Finally we found moniker representing something we want. Lets create object:

				IRmObjectMoniker->BindToObject(IID_ISomeInterface,ppObject);

			NOTE: There can be only ONE PER OBJECT IRmDeviceNode created 
			by moniker from the root of enumeration.

			5. When the object is created we can ask for some interface like:
				- IID_IRMBase			every object must have it.
				- IID_IRmControlNode	object containing property sets
				- IID_IRmStream			object can stream data
				- IID_IRmBridge			just format negotiation and 
										stream state notification only, no streaming.
				
			Meaning of created object and interfaces is opaque and completely
			up to inderlying implementation which shares additional information
			with application. All this interfaces are only connection specification.

			For instance,
			
				- IRmControlNode can be representation of HwLibrary instance
				- IRmStream		* pVideo is Video Stream
				- IRmStream		* pAudio is Audio Stream
				- IRmBridge		* pOverlay is non - streaming connection
				point wich has formats.

			or 

				- IRmControlNode	* pTvEncoder represents TV Encoder wich has stream 
				internally connected to MPEG Decoder and not accessible from outside but
				properties can be accessed.
				- IRmControlNode	* pInternalGraphManager can be something to change
				internal connection in runtime.

			or even 

				- IRmControlNode	* pSplitter
				- IRmStream			* pSplitterInputStream

			6. This object will be destroyed then all interfaces released;


///////////////////////////////////////////////////////////////////////////////////////*/

/*	ITEMS TO DISCUSS:

	1.	CATEGORIES: use GUID or strings or enumerated?
	2.	CATEGORIES: global list or SetID/ItemID ?
	3.	char:		should be char, not uchar to avoid unnecessary casting.
	4.	ATTRIBUTES:	drop it and use instead 
					Get/SetProperty(PROPSET_ATTRIBUTES,MpegAttr...,flags,size,data);
	5.	STREAM:		use Stop/Pause/Run or Get/SetStreamState(RMSTATE state) ?
*/

#ifndef _IRMBASE_H_INCLUDED
#define _IRMBASE_H_INCLUDED

/////////////////////////////////////////////////////////////////////////////////////////
//
//	DEFINES
//
/////////////////////////////////////////////////////////////////////////////////////////

//#define ANY_INSTANCE				0xFFFFFFFF
#define FIRST_AVALIABLE_INSTANCE	0xFFFFFFFE

// Every object can be represented by different type of information, like
// Name, Category , IRmObjectMoniker/IRmDeviceNode interface and so on.
// App can select most suitable type of representation.

// CATEGORIES
//
// TODO: use GUID instead of strings (???)
//
// Every Category can be represented by IRmObjectMoniker which 
// can be obtained from IRmObjectEnumerator. 
// IRmObjectMoniker->BindToObject(IID_IRmDeviceNode,pIRmDeviceNode) brings
// ability to query capabilities of selected category.
// This capabilities are to be defined.
//
#define CATEGORY_MODULE_QUAD_BOARD	"CATEGORY_MODULE_QuadBoard"
#define CATEGORY_MODULE_SINGLE_HOST	"CATEGORY_MODULE_SingleHost"
#define CATEGORY_NODE_HW_LIB		"CATEGORY_NODE_HwLibrary"
#define CATEGORY_PIN_VIDEO			"CATEGORY_PIN_Video"
#define CATEGORY_PIN_AUDIO			"CATEGORY_PIN_Audio"
#define CATEGORY_PIN_OVERLAY		"CATEGORY_PIN_Overlay"
#define CATEGORY_PIN_SUBPICTURE		"CATEGORY_PIN_Subpicture"
#define CATEGORY_PIN_OSD			"CATEGORY_PIN_OSD"

// Categories can be extended like this:
//
#define CATEGORY_NODE_MPEG_DECODER	"CATEGORY_NODE_MPEG Decoder"
#define CATEGORY_NODE_AUDIO_DECODER	"CATEGORY_NODE_Audio Decoder"
#define CATEGORY_NODE_TV_ENCODER	"CATEGORY_NODE_TvEncoder"

// Obsolete Categories can be dropped.

//	IRmObjectEnumerator enumerates:
//
//	CoCreateInstance()		BOARD instance
//	GetSubEnumerator()			Logical Devices with direct access(nodes)
//	GetSubEnumerator()					Connection points(pins,streams)

typedef RMuint32	RMMPEG_ATTRIBUTE;
//typedef char		char;		// char should not be uchar

// Object Enumeration levels
//
typedef enum{
	EOTYPE_MODULE,
	EOTYPE_NODE,
	EOTYPE_PIN
}ENUM_OBJECT_TYPE;

// Information about all resources, allocated or not
//
typedef enum {
	IT_STANDARD_CATEGORY,
	IT_STANDARD_DISPLAY_NAME,
	IT_STANDARD_INSTANCE_ID,
	IT_STANDARD_LOCATION
}IT_STANDARD;

typedef enum {
	IT_PIN_DIRECTION,
	IT_PIN_TYPE_INDEX,
	IT_PIN_NAME
}IT_PIN;

// new implementation - specific infosets can be added in future
//
typedef enum {
	IS_MONIKER_INTERNAL,
	IS_MONIKER_STANDARD,
	IS_MONIKER_PIN
}IS_MONIKER;

/////////////////////////////////////////////////////////////////////////////////////////
//
//	CLASS FACTORY IDENTIFIERS
//
/////////////////////////////////////////////////////////////////////////////////////////

// Class Factory ID. If client use this CLSID resulting object represent HwLibrary.
// Any other object types must use different CLSID.

// old interfaces, used for backward compatibility
// USED BY:
//		OSD
//		quadro_test
//
//DEFINE_RMID(CLSID_rm8400	,0x2f921938,0x54ab,0x4fc3,0x8a,0xdf,0x71,0x9b,0x8c,0xc8,0xf4,0xbb);

// interfaces represents HwLibrary for EM8xxx chipset
//
DEFINE_GUID(CLSID_RMBASE	,0x5e91af27,0x24d3,0x47ac,0x9c,0x55,0x13,0x2f,0x04,0xc9,0x82,0x81);

/////////////////////////////////////////////////////////////////////////////////////////
//
//	INTERFACES
//
/////////////////////////////////////////////////////////////////////////////////////////

struct IRmObjectEnumerator;	// Forward declaration

DEFINE_RMID(IID_IRmObjectMoniker     , 0x77167D8A,0x8090,0x11d5,0xB8,0x5E,0x00,0x90,0x27,0x65,0xE1,0x6C);
struct IRmObjectMoniker : public IRMBase
{
public:
    virtual RMRESULT IRMCALLTYPE BindToObject	 (REFIID riid,void **ppObj) = 0;
    virtual RMRESULT IRMCALLTYPE IsRunning		 ( void) = 0;
	virtual RMRESULT IRMCALLTYPE GetEnumerator	 (IRmObjectEnumerator ** p) = 0;
	virtual RMRESULT IRMCALLTYPE GetSubEnumerator(IRmObjectEnumerator ** p) = 0;
    virtual RMRESULT IRMCALLTYPE GetInfo(
				RMuint32	info_set,
				RMuint32	info_type,
				void		*pBuffer,
				RMuint32	buff_size,
				RMuint32	*cbRet) = 0;
};


DEFINE_RMID(IID_IRmObjectEnumerator  , 0xCD83BC0A,0x8090,0x11d5,0xB8,0x5E,0x00,0x90,0x27,0x65,0xE1,0x6C);
struct IRmObjectEnumerator : public IRMBase
{
public:
    virtual void IRMCALLTYPE Reset( void) = 0;
    virtual RMRESULT IRMCALLTYPE Next(IRmObjectMoniker **ppIRmObjectMoniker) = 0;
};

DEFINE_RMID(IID_ICompletionCallBack	 , 0xEDB5A0D2,0xE32B,0x4290,0x9E,0xDC,0x0F,0x9F,0xE4,0x13,0x27,0xF2);
struct ICompletionCallBack : public IRMBase
{
public:
    virtual void IRMCALLTYPE Complete(void *Context) = 0;
};

DEFINE_RMID(IID_IRmControlNode	, 0x5D896824,0x4239,0x4ddb,0xAF,0x13,0xC8,0x09,0x36,0xC2,0x46,0xBD);
struct IRmControlNode : public IRMBase
{
public:
    virtual RMRESULT IRMCALLTYPE GetCapabilities(RMCAPABILITIES *pCaps) = 0;

    virtual RMRESULT IRMCALLTYPE GetProperty( 
        RMuint32	PropertySetID,
        RMuint32	PropertyItemID,
        RMuint32	PropertyItemFlags,
        RMuint32	PropertySize,
        void		*pPropertyData,
        RMuint32	*cbReturn) = 0;
    
    virtual RMRESULT IRMCALLTYPE SetProperty( 
        RMuint32	PropertySetID,
        RMuint32	PropertyItemID,
        RMuint32	PropertyItemFlags,
        RMuint32	PropertySize,
        void		*pPropertyData) = 0;

	// TODO: drop it and use instead SetProperty(PROPSET_ATTRIBUTES,MpegAttr...,flags,size,data);
	//
   virtual RMRESULT IRMCALLTYPE SetAttributes(
        RMMPEG_ATTRIBUTE	eAttribute,
        RMint32				lValue) = 0;
    
    virtual RMRESULT IRMCALLTYPE GetAttributes( 
        RMMPEG_ATTRIBUTE	eAttribute,
        RMint32				*lValue) = 0;

};


// No streaming, but can be connected using Format Negotiation algoritm.
// This is Control Point, like Overlay - it can be connected using different
// formats, but there is not streaming data.
//
DEFINE_GUID(IID_IRmBridge		, 0x18ca821d,0x7e35,0x464c,0x9e,0x17,0xc5,0xf4,0x38,0xf1,0xc5,0x51);
struct IRmBridge : public IRMBase
{
public:
    virtual RMRESULT IRMCALLTYPE Play	( void) = 0;
    virtual RMRESULT IRMCALLTYPE Pause	( void) = 0;
    virtual RMRESULT IRMCALLTYPE Stop	( void) = 0;

	// or

	//RMRESULT IRMCALLTYPE GetStreamState( PRMSTATE state) = 0; ???
	//RMRESULT IRMCALLTYPE SetStreamState( RMSTATE state) = 0; ???

    virtual RMRESULT IRMCALLTYPE Reset	( void) = 0;

    virtual RMRESULT IRMCALLTYPE CheckFormat( 
        PRMDATAFORMAT format) = 0;
    
    virtual RMRESULT IRMCALLTYPE GetFormat( 
        PRMMULTIPLE_ITEM format_list) = 0;
    
    virtual RMRESULT IRMCALLTYPE SetFormat( 
        PRMDATAFORMAT format) = 0;
    
};

DEFINE_RMID(IID_IRmStream     , 0x4757FEB1,0x883D,0x41d4,0x99,0x0B,0x2E,0x7E,0x90,0x18,0xB7,0x3A);
struct IRmStream : public IRmBridge
{
public:
    virtual RMRESULT IRMCALLTYPE BeginFlush	( void) = 0;
    virtual RMRESULT IRMCALLTYPE EndFlush	( void) = 0;

    virtual RMRESULT IRMCALLTYPE Write( 
        PRMMULTIPLE_ITEM pHeaders,
        RMOVERLAPIO *ovr) = 0;
    
    virtual RMRESULT IRMCALLTYPE WriteEx( 
        PRMMULTIPLE_ITEM pHeaders,
        ICompletionCallBack *pICCallback,
        void *CompletionContext) = 0;
    
    virtual RMRESULT IRMCALLTYPE Read( 
        PRMMULTIPLE_ITEM pHeaders,
        RMOVERLAPIO *ovr) = 0;
    
    virtual RMRESULT IRMCALLTYPE ReadEx( 
        PRMMULTIPLE_ITEM pHeaders,
        ICompletionCallBack *pICCallback,
        void  *CompletionContext) = 0;
};

// object instance - specific place to save some information
//
DEFINE_RMID(IID_IPivateRegProfile	, 0xEE543A70,0x2D27,0x43fb,0x96,0x6F,0xCC,0xF8,0xE5,0x39,0x6E,0x62);
struct IPivateRegProfile : public IRMBase
{
public:
    virtual RMRESULT IRMCALLTYPE GetInt( 
        char	*SectionName,
        char	*ValueName,
        RMint32	Default,
        RMint32	*pValue) = 0;
    
    virtual RMRESULT IRMCALLTYPE WriteInt( 
        char	*SectionName,
        char	*ValueName,
        RMint32	Value) = 0;
    
    virtual RMRESULT IRMCALLTYPE WriteDisplayInt( 
        char	*ValueName,
        RMint32	Value) = 0;
    
    virtual RMRESULT IRMCALLTYPE GetDisplayInt( 
        char	*ValueName,
        RMint32	Default,
        RMint32	*Value) = 0;
    
};

// Helper interface, use istead of IRmObjectEnumerator in simple cases
//
DEFINE_GUID(IID_IRmObjectFinder		,0x27128970,0x797a,0x460e,0x92,0xee,0xb6,0x3f,0x98,0xd7,0x55,0xbf);
struct IRmObjectFinder : public IRMBase
{
public:
    virtual RMRESULT IRMCALLTYPE FindMoniker(
		IRmObjectMoniker	* root,
		RMuint32			InstanceNumber,
		char				* Category,
		IRmObjectMoniker	**ppIRmObjectMoniker) = 0;

    virtual RMRESULT IRMCALLTYPE FindObject(
		IRMBase				* root,
		RMuint32			InstanceNumber,
		char				* Category,
		REFIID				riid,
		void				**ppObj) = 0;

};

DEFINE_GUID(IID_IRmMapMem,0x9CB7F9A8,0x0AE5,0x4a2c,0x99,0xDB,0x9B,0x4D,0x58,0x96,0x7B,0x45);
struct IRmMapMem : public IRMBase
{
public:
    virtual RMRESULT IRMCALLTYPE GetDeviceBase(PVOID *pAddr) = 0;
    virtual RMRESULT IRMCALLTYPE FreeDeviceBase() = 0;

	virtual	RMRESULT IRMCALLTYPE GetDMABuffer(
		RMuint32	size, 
		void		** pLinearAddr, 
		void		** pPhysicalAddr) = 0;	
	virtual	RMRESULT IRMCALLTYPE FreeDMABuffer(void * LinearAddr) = 0;

	virtual	RMRESULT IRMCALLTYPE GetBuffer(
		RMuint32	size, 
		void		** pAddr) = 0;	
	virtual	RMRESULT IRMCALLTYPE FreeBuffer(void * Addr) = 0;
};
#endif // _IRMBASE_H_INCLUDED

