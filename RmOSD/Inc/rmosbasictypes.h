/*****************************************************************
*** Copyright (c) 2001 Sigma Designs Inc. All rights reserved. ***
*****************************************************************/

/**
   @defgroup types Types definition
   You can find related documentation in @ref typespage .
*/ 


/**
  @file   rmosbasictypes.h
  @ingroup typesgroup
  @brief  Describes OS specific basic types

  @author Mathieu Lacage
  @date   2001-09-10
*/


#ifndef __RMOSBASICTYPES_H__
#define __RMOSBASICTYPES_H__

#define MaxRMuint32 ((RMuint32)4294967295)
#define MinRMuint32 ((RMuint32)0)

#define MaxRMint32 ((RMint32)2147483647)
#define MinRMint32 ((RMint32)-2147483647-1)

/** 64 bits long unsigned integer */
typedef unsigned __int64 RMuint64;
#define MaxRMuint64 ((RMuint64)18446744073709551615)
#define MinRMuint64 ((RMuint64)0)

/** 64 bits long integer */
typedef __int64 RMint64;
#define MaxRMint64 ((RMint64)9223372036854775807)
#define MinRMint64 ((RMint64)-9223372036854775807-1)

typedef unsigned int RMnewOperatorSize;

#endif // __RMOSBASICTYPES_H__
