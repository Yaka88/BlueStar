/*---------------------------------------------------------------------
 * IBM CONFIDENTIAL
 * Copyright 1996 by IBM Corporation
 *
 * File Name    :   ac3dec.h
 *
 * Authors      :   Yossi Erlich
 * Date Begun   :   17.04.96   Yossi Erlich.
 * Modified     :   06.05.96   Benny Reich      Added Karaoke mode parameter
 *                  31.07.96   Yossi Erlich     Avoid multi-inclusion of the
 *                                              header
 *
 * Developed At :   IBM Israel, Haifa Research Lab,
 *                  Multimedia Department - Audio and Video group
 *
 * Description  :   An header file for the Dolby AC3 decoder user.
 *--------------------------------------------------------------------*/

#ifndef _AC3DEC_H_  /* avoid multi-inclusion of this header */

#define _AC3DEC_H_

#include    <stdlib.h>

#ifdef NO_DLL   /* ac3dec APIs are none dll functions   */
#define     APICALL
#else           /* ac3dec APIs are dll functions        */
#ifdef WIN32
#define     APICALL             _declspec(dllexport)
#else
#define     APICALL
#endif
#endif

#define     AC3_UNKNOWN         -1      /* unknown parameter                */
#define     COMPR_SHIFT         16      /* scale of compr and compr2        */
#define     VERLEN              70      /* length of version string         */

/**** Sync Frame sizes ****/

#define     AC3MAXFRAME         1920    /* max input # words per Sync Frame */
#define     AC3NPCMCHANS        6       /* max # of output channels         */
#define     AC3NBLOCKS          6       /* number of blocks in Sync Frame   */
#define     AC3N                256     /* audio block size                 */
#define     AC3MAX_OUT_LENGTH   (AC3NPCMCHANS * AC3NBLOCKS * AC3N)
                                        /* Maximal # of PCM output samples  */
                                        /* for a single Sync Frame          */

/**** AC-3 channel ordering equates ****/
        /* specify the entries to ac3mode.interleav.index table */
#define     AC3LEFT             0       /* left channel                     */
#define     AC3CNTR             1       /* center channel                   */
#define     AC3RGHT             2       /* right channel                    */
#define     AC3LSUR             3       /* left surround channel            */
#define     AC3RSUR             4       /* right surround channel           */
#define     AC3LFE              5       /* low frequency effects channel    */
#define     AC3MSUR             3       /* mono surround channel            */
        /* karaoke channel ordering equates */
#define     AC3MLDY             1       /* guide melody (center) channel    */
#define     AC3VCL1             3       /* vocal 1 (left surround) channel  */
#define     AC3VCL2             4       /* vocal 2 (right surround) channel */

/**** Return Codes ****/

        /* Common error codes for all ac3dec APIs */
#define     AC3OK               0       /* No error.                        */
#define     AC3ERR_NULL         0x01    /* openac3dec(), closeac3dec() or   */
                                        /* ac3dec() received NULL pointer   */
                                        /* as one of it's entry argumets    */

        /* Error codes of openac3dec() */
#define     AC3ERR_MALLOC       0x02    /* Memory allocation error          */

        /* Invalid parameters - return codes of ac3dec() */
#define     AC3ERR_PAR_SWAP_B   0x03    /* errored swap_bytes               */
#define     AC3ERR_PAR_INWORDS  0x04    /* non-positive inwords             */
#define     AC3ERR_PAR_BUFSIZE  0x05    /* pcmbufsize too small             */
#define     AC3ERR_PAR_OUTMOD   0x06    /* errored outmod                   */
#define     AC3ERR_PAR_KARMOD   0x07    /* errored karaoke mode             */
#define     AC3ERR_PAR_KARCLEV  0x08    /* errored karaoke clev flag        */
#define     AC3ERR_PAR_COMPMOD  0x09    /* errored compmod                  */
#define     AC3ERR_PAR_DUAL     0x0a    /* errored dualmonomod              */
#define     AC3ERR_PAR_OUTLFE   0x0b    /* errored outlfe                   */
#define     AC3ERR_PAR_DYNHIGH  0x0c    /* errored dynscalehigh             */
#define     AC3ERR_PAR_DYNLOW   0x0d    /* errored dynscalelow              */
#define     AC3ERR_PAR_MUTE     0x0e    /* errored mute flag                */
#define     AC3ERR_PAR_INT_IDX  0x0f    /* errored interleaved indices      */
#define     AC3ERR_PAR_INT_FMT  0x10    /* errored interleaved format       */

        /* Streaming return codes of ac3dec() */
#define     AC3ERR_LESSTHANSI   0x11    /* Not enough input words to unpack */
                                        /* SI from the first found sync     */
                                        /* word                             */
#define     AC3ERR_SYNC         0x12    /* Couldn't find sync word          */

        /* Invalid bit stream - return codes of ac3dec() */
#define     AC3ERR_SAMPRATE     0x13    /* Invalid sample rate              */
#define     AC3ERR_DATARATE     0x14    /* Invalid data rate                */
#define     AC3ERR_REUSE_CPL    0x15    /* Trying to reuse coupling         */
                                        /* strategy in block 0              */
#define     AC3ERR_CPLMODE11    0x16    /* Can't couple in 1+1 dual mono    */
                                        /* mode                             */
#define     AC3ERR_REUSE_REMAT  0x17    /* Trying to reuse rematrix flags   */
                                        /* in block 0                       */
#define     AC3ERR_REUSE_CPLE   0x18    /* Trying to reuse CPL exp strategy */
                                        /* in block 0                       */
#define     AC3ERR_REUSE_EXP    0x19    /* Trying to reuse exponent         */
                                        /* strategy in block 0              */
#define     AC3ERR_REUSE_LFE    0x1a    /* Trying to reuse LFE exp strategy */
                                        /* in block 0                       */
#define     AC3ERR_CHBWCOD      0x1b    /* chbwcod too high                 */
#define     AC3ERR_REUSE_BAI    0x1c    /* Trying to reuse bit allocation   */
                                        /* info in block 0                  */
#define     AC3ERR_REUSE_SNR    0x1d    /* Trying to reuse SNR offsets in   */
                                        /* block 0                          */
#define     AC3ERR_REUSE_LEAK   0x1e    /* Trying to reuse cpl leak terms   */
                                        /* in block 0                       */
#define     AC3ERR_DELT_BA      0x1f    /* Delta bit alloc past end of      */
                                        /* array                            */

        /* Warnings - return codes of ac3dec() */
#define     AC3WRN_SWAP_BYTE    0x0080  /* A byte swapped sync word was     */
                                        /* found.                           */
#define     AC3WRN_REV          0x0100  /* Unsupported bitstream revision - */
                                        /* muting output signal.            */
#define     AC3WRN_CRC1         0x0200  /* CRC1 error detected - all audio  */
                                        /* blocks are repeated.             */
#define     AC3WRN_CRC2         0x0400  /* CRC2 error detected - 4 last     */
                                        /* audio blocks are repeated.       */
#define     AC3WRN_BLK5         0x0800  /* End of block 5 exceeds 3/8 of    */
                                        /* a frame                          */
#define     AC3WRN_BLK01        0x1000  /* Block 0 & 1 exceed 5/8 of a      */
                                        /* frame                            */
#define     AC3WRN_ADD_BSI      0x2000  /* Additional BSI skipped           */
#define     AC3WRN_INPUT_REQ    0x4000  /* Not enough input to process      */
                                        /* a sync. frame                    */


        /* Masking macros */
#define     AC3ERR_MASK         0x007f  /* Masking word - error             */
#define     AC3WRN_MASK         0xff80  /* Masking word - warning           */
#define     AC3ERR(retcode)     ((retcode) & AC3ERR_MASK)
#define     AC3WRN(retcode)     ((retcode) & AC3WRN_MASK)

/* Limit values for dynamic range scaling parameters */

#define		MIN_DYNSCALE	0.0				/* min dynamic range scaling		*/
#define		MAX_DYNSCALE	1.0				/* max dynamic range scaling		*/

/***** type definitions *****/

/* input audio modes */
typedef enum 
{   
    MODE11, MODE10, MODE20, MODE30, MODE21, MODE31, MODE22, MODE32
} AUDIO_MOD;

/* output audio modes */
typedef enum 
{   
    OUTMODE20_DOLBY_SUR,    /* Mode 2/0 Dolby Surround compatible */
    OUTMODE10, OUTMODE20, OUTMODE30, OUTMODE21, OUTMODE31, OUTMODE22, OUTMODE32, 
    OUTMODE_UNKNOWN
} OUT_MOD;

/* karaoke modes */
typedef enum 
{
    NO_VOCALS, LEFT_VOCAL, RIGHT_VOCAL, BOTH_VOCALS
} KARAOKE_MOD;

/* dual mono downmix mode */
typedef enum 
{   
    DUAL_STEREO, DUAL_LEFTMONO, DUAL_RGHTMONO, DUAL_MIXMONO 
} DUAL_MOD;

/* compression mode */
typedef enum 
{   
    COMP_CUSTOM_A, COMP_CUSTOM_D, COMP_LINE, COMP_RF 
} COMP_MOD;

/* channels interleaving format */
typedef enum
{
    AC3_PLAY, AC3_MUTE
} MUTE_FLAG;

/* channels interleaving format */
typedef enum
{
    AC3OUTFULL, AC3OUTPART
} AC3OUT_FMT;

/* flag (boolean variable) */
typedef enum
{
    AC3_OFF, AC3_ON
} AC3_FLG;

/* Bit stream info */                   /* Initialized to AC3_UNKNOWN       */
typedef struct{
    int         bsid;                   /* bitstream identification         */
    int         bsmod;                  /* bitstream mode                   */
    AUDIO_MOD   acmod;                  /* audio coding mode                */
    int         cmixlev;                /* center mix level                 */
    int         surmixlev;              /* surround mix level               */
    int         dsurmod;                /* Dolby surround mode              */
    int         lfeon;                  /* low frequency effects chan flag  */
    int         dialnorm;               /* dialog normalization word        */
    int         compre;                 /* channel comp word exists         */
    long        compr;                  /* channel comp word                */
                                        /* shifted left by 24               */
    int         langcode;               /* language code exists             */
    int         langcod;                /* language code                    */
    int         audprodie;              /* audio production info exists     */
    int         mixlevel;               /* mixing level                     */
    int         roomtyp;                /* room type                        */
    int         dialnorm2;              /* dialog normalization word #2     */
    int         compr2e;                /* channel comp word #2 exists      */
    long        compr2;                 /* channel comp word #2             */
                                        /* shifted left by 24               */
    int         langcod2e;              /* language code #2 exists          */
    int         langcod2;               /* language code #2                 */
    int         audprodi2e;             /* audio production info #2 exists  */
    int         mixlevel2;              /* mixing level #2                  */
    int         roomtyp2;               /* room type #2                     */
    int         copyrightb;             /* copyright bit                    */
    int         origbs;                 /* original bitstream flag          */
    int         timecod1e;              /* time code first half exists      */
    int         timecod1;               /* time code first half             */
    int         timecod2e;              /* time code second half exists     */
    int         timecod2;               /* time code second half            */
    int         addbsie;                /* additional BSI exists            */
    int         addbsil;                /* additional BSI length            */
            /* parameters which are not directly unpacked */
    int         nfchans;                /* number of full bw channels       */
    int         nchans;                 /* number of channels               */
    AC3_FLG     karaokeflag;            /* karaoke bitstream flag           */
} BSI;

/* parameters extracted from the bit stream */
typedef struct{
    int         fscod;          /* sampling rate code                               */
                                /* (AC3_UNKNOWN indicates unknown)                  */
    BSI         bsi;            /* bit stream information                           */
} AC3CODE_PAR;

/* ac3dec() Return structure */
typedef struct{
    AC3CODE_PAR code_par;       /* parameters extracted from the bit stream         */
    int         inwordsread;    /* Number of read input words from bit stream.      */
                                /* Including errored stream.                        */
    int         inwordsreq;     /* Number of required input words                   */
                                /* for processing an aditional single Sync Frame    */
                                /* (zero indicates unknown)                         */
                                /* In case of AC3ERR_LESSTHANSI, this number will   */
                                /* indicate the number of required input words for  */
                                /* SI npacking.                                     */
    int         pcmbufwrote;    /* number of wrote output pcm samples               */
} AC3DEC_RET;

/* output interleaving format */
typedef struct{
    int index[AC3NPCMCHANS];    /* indices of output channels in the                */
                                /* interleaved output PCM stream.                   */
                                /* Entry order: (L, C, R, l, r, s).                 */
                                /*          (l stands for mono surround in 2/1 or   */
                                /*           3/1 output modes.                      */
                                /*           L, R stands for the independent        */
                                /*          channels in 1+1 output mode).           */
                                /*          [refer to AC-3 channel ordering equates]*/
                                /* Example: if index = (0, x, 1, x, x, x)           */
                                /*          than the left bitstream channel is      */
                                /*          directed to the first interleaved       */
                                /*          channel and the right bitstream         */
                                /*          channel to the second.                  */
    AC3OUT_FMT  format;         /* AC3OUTFULL -                                     */
                                /*      for producing 6 PCM samples per time sample,*/
                                /*      unused channels remains zero.               */
                                /*      IT IS THE RESPONSIBILITY OF THE USER TO     */
                                /*      FILL WITH ZEROS UNUSED INTERLEAVED CHANNELS */
                                /* AC3OUTPART -                                     */
                                /*      for producing only n PCM samples per time   */
                                /*      sample, when                                */
                                /*                  n = MAX(index[chan_index]+1)    */
                                /*      and the maximization is over used channels  */
                                /*      according to the output mode.               */
                                /*      Examples:                                   */
                                /*          1.   when index = (0, x, 1, x, x, x)    */
                                /*               and outmode=2 (2/0),               */
                                /*               then n=2.                          */
                                /*          2.   when index = (0, 5, 2, x, x, x)    */
                                /*               and outmode=3 (3/0),               */
                                /*               then n=6.                          */
                                /* Note: use format=AC3OUTFULL for comparing to     */
                                /*       Dolby's decoder.                           */
                                /* Note: IT IS THE RESPONSIBILITY OF THE USER TO    */
                                /*       ZERO THE PCM BUFFER FOR UNUSED INTERLEAVED */
                                /*       CHANNELS                                   */
} INTERLEAVE;

/* ac3dec() user specified mode */
typedef struct{
    OUT_MOD     outmod;         /* output channels configuration                    */
    KARAOKE_MOD karaokemod;     /* karaoke mode                                     */
    AC3_FLG     karaoke_with_clev; /* if flag is on, use karaoke mode as in the     */
                                   /* Dolby's spec with clev, rather than following */
                                   /* Dolby's wrong source code which uses M3DB.    */
    COMP_MOD    compmod;        /* dynamic range compression mode                   */
    DUAL_MOD    dualmonomod;    /* Dual Mode                                        */ 
    AC3_FLG     outlfe;         /* output lfe channel flag                          */
    double      dynscalehigh;   /* dynamic range compression out scale factor       */
    double      dynscalelow;    /* dynamic range compression boost scale factor     */
    MUTE_FLAG   mute;           /* muting flag                                      */
                                /* (if case of AC3_MUTE, muting will be carried out */
                                /*  for the current frame and for the first audio   */
                                /*  block of the next frame).                       */
    INTERLEAVE  interleav;      /* channels interleaving format                     */
    AC3_FLG     swap_bytes;     /* swaping bytes in input stream                    */
} AC3MODE;

/*  ac3dec() user specified variables. */
typedef struct{
    short       *bitstream;     /* pointer to input bit stream                      */
    int         inwords;        /* # of available words in bitsteeam                */
    short       *pcmbufptr;     /* pointer to output buffer (cahnnels interleaved)  */
    int         pcmbufsize;     /* size of output buffer (available for writing)    */
    AC3MODE     ac3mode;        /* ac3dec() user specified mode                     */
} AC3DEC_IN;

/*  decoder version structure */
typedef struct{
    char string[VERLEN];
} AC3VER;

/**** function prototypes ****/

/*
 * Function name:   openac3dec
 *                   
 * Description  :   Initialization API for the AC3 decoder.
 *                  Memory allocation and pointers initializations.
 *
 * Arguments    :   p_ac3handler    -   Pointer to the returnded ac3 handler
 *                                      pointer.
 *                  malloc_func     -   Memory allocation function (this function
 *                                      should return NULL for error).
 *                                      When malloc_func=NULL, the default malloc()
 *                                      function is used.
 *                  ac3dec_version  -   Pointer to returned decoder version.
 *
 * Return value :   AC3OK
 *                  AC3ERR_NULL (NULL p_ac3handler or ac3dec_version)
 *                  AC3ERR_MALLOC
 */
#ifdef __cplusplus
extern "C"
{
#endif
 int     APICALL __cdecl openac3dec(void    **p_ac3handler, 
                            void    * __cdecl malloc_func(size_t),
                            AC3VER  *ac3dec_version);
#ifdef __cplusplus
}
#endif 

/*
 * Function name:   ac3dec
 *
 * Description  :   AC3 decoding of a single Sync Frame.
 *
 * Arguments    :   ac3handler  -   Handler.
 *                  ac3dec_in   -   Input parameters.
 *                  ac3dec_ret  -   Returned structure.
 *
 * Return value :       AC3OK
 *                  Errors :
 *                      AC3ERR_NULL (NULL ac3handler or ac3dec_in or ac3dec_ret
 *                                   or acrdec_in->bitstream or 
 *                                   ac3dec_in->pcmbufptr)
 *                      AC3ERR_PAR_SWAP_B
 *                      AC3ERR_PAR_INWORDS
 *                      AC3ERR_PAR_BUFSIZE
 *                      AC3ERR_PAR_OUTMOD
 *                      AC3ERR_PAR_KARMOD
 *                      AC3ERR_PAR_KARCLEV
 *                      AC3ERR_PAR_COMPMOD
 *                      AC3ERR_PAR_DUAL 
 *                      AC3ERR_PAR_OUTLFE
 *                      AC3ERR_PAR_DYNHIGH
 *                      AC3ERR_PAR_DYNLOW
 *                      AC3ERR_PAR_MUTE
 *                      AC3ERR_PAR_INT_IDX
 *                      AC3ERR_PAR_INT_FMT
 *                      AC3ERR_LESSTHANSI
 *                      AC3ERR_SYNC 
 *                      AC3ERR_SAMPRATE
 *                      AC3ERR_DATARATE
 *                      AC3ERR_REUSE_CPL
 *                      AC3ERR_CPLMODE11
 *                      AC3ERR_REUSE_REMAT
 *                      AC3ERR_REUSE_CPLE
 *                      AC3ERR_REUSE_EXP
 *                      AC3ERR_REUSE_LFE
 *                      AC3ERR_CHBWCOD
 *                      AC3ERR_REUSE_BAI
 *                      AC3ERR_REUSE_SNR
 *                      AC3ERR_REUSE_LEAK
 *                      AC3ERR_DELT_BA
 *                  Warnings:
 *                      AC3WRN_SWAP_BYTE 
 *                      AC3WRN_REV
 *                      AC3WRN_CRC1
 *                      AC3WRN_CRC2
 *                      AC3WRN_BLK5 
 *                      AC3WRN_BLK01 
 *                      AC3WRN_ADD_BSI
 *                      AC3WRN_INPUT_REQ
 */
#ifdef __cplusplus
extern "C"
{
#endif
 int     APICALL __cdecl ac3dec(void *ac3handler, AC3DEC_IN *ac3dec_in, AC3DEC_RET *ac3dec_ret);
#ifdef __cplusplus
}
#endif     

/*
 * Function name:   closeac3dec
 *                   
 * Description  :   Closing API for the AC3 decoder.
 *
 * Arguments    :   ac3handler      -   Pointer to the ac3 handler.
 *                  free_func       -   User defined memory free function.
 *                                      When free_func=NULL, the default free()
 *                                      function is used.
 *
 * Return value :   AC3OK
 *                  AC3ERR_NULL (NULL ac3handler)
 */
#ifdef __cplusplus
extern "C"
{
#endif
 int     APICALL __cdecl closeac3dec(void *ac3handler, void __cdecl free_func(void *));
#ifdef __cplusplus
}
#endif     

#endif /* _AC3DEC_H_ */

