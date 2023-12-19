/*****************************************************************
*** Copyright (c) 2001 Sigma Designs Inc. All rights reserved. ***
*****************************************************************/

/**
   @defgroup types Types definition
   You can find related documentation in @ref typespage .
*/ 


/**
  @file   rmbasictypes.h
  @ingroup types
  @brief  Describes all the basic types used by all the drivers.

  Each type begins with RM, and the rest is always in low case.
  if it is a pointer appends a P after RM. 
  
  @author Julien Soulier, Emmanuel Michon
  @date   2001-01-29
*/

/**
   @page typespage Types declaration specifications

   To increase portability and flexibility of the source code we 
   impose and enforce some rules concerning the types used in CARIBBEAN.  

   @subsection system_abstraction System abstraction 
   The first (and most important) step is to
   prevent the programmer from using the types provided by the operating system or
   the compiler.

   For instance, this ensures that when we request a 32 bits signed integer RMint32, 
   we will actually get one, whatever the operating system or compiler. So, instead of
   writing this :

   @code 
     int a; 
     unsigned long b;
     char c;
     short *d;
   @endcode

   We will write :

   @code 
     RMint32 a;
     RMuint32 b;
     RMint8 c;
     RMint16 * d;
   @endcode 
 
   Afterwards we have to abstract all the OS-dependent functions, such as:
     - Semaphores
     - Events
     - Threads
     - Critical Sections
     - I/O calls
     - ...

   Actual implementation can be found in the matching part of the Library.

   @subsection types_naming Types naming conventions
   All types begin with RM or PRM for types and pointer respectively. 
   The name then is short, explicit and in low case.
   All the integer types follow the format RMsintxx :
     - s  : is either u or nothing, meaning unsigned or signed respectively.
     - xx : is the number of bits in the types : 8, 16, 32, 64.
   All number types have their own min and max following the format MaxRMsintxx or MinRMsintxx.
   
   All function pointers end with the suffix func like RMfunc, PRMtestFunc...
   
   @subsection types_architecture Types architecture
   The architecture used to declare types is also very important because it allows to 
   create complex structures with minimum work regarding to the included headers. The 
   types are divided in 3 categories.
     -# Enumerated types\n
   These types are completely standalone, because they do not require any previous declaration.
   They are declared in the file enumtypes.h, which should be the first one included. 
     -# Basic types\n
   The basic types are the common C types, OS types, function pointers... All are defined
   in the file basictypes.h. Let alone function pointers, these types have the particularity to be
   only a renamed compiler type. For example a RMthread is just a void *. No structure
   are include in the basic types. The basic types are the only types for which the declaration 
   can differ according to the compiler. For example the RMuin64 is not declared the same way with 
   gcc and visual studio. For this purpose there is a preprocessor condition to declare the types
   the correct way. This is the only part where types declarations can be OS or compiler dependent, 
   all the other types should be independent from the system. In addition to these simple types there 
   are the function pointer types. Function pointer should only reference basic types and enumerate 
   types. In this respect they can be defined at the end of the basictypes.h file. The basictypes.h 
   file should be included just after the enumtypes because it does not need any other file. 
     -# Composed types\n
   This last category included all the structures that could be called in a program. They can 
   reference enumerate types, basic types and function pointer. They are the most ellaborate 
   types in the hierarchy. They are declared in the composedtypes.h, which should the third file
   included, just after enumtypes.h and basictypes.h.

   @subsection adding_type Adding a new type
   The architecture described above works only for the RM_LIBRARY_IMPORT_EXPORTal types, it means types which can
   be declared in other modules. As it is shown in the @ref headers page source code must not include 
   system headers, it follows then that none of the types specifications can reference a system type. 
   The proper way to do it is to declare a generic pointer for the RM_LIBRARY_IMPORT_EXPORTal type and in the corresponding 
   library (OS dependent) to cast the generic type to the proper system type. You can have a look to the 
   rmsemaphores.h to see an example of this.Internal types should be declared in the module they are used, 
   and certainly not available for all the users. When you want to add an RM_LIBRARY_IMPORT_EXPORTal type you must 
   add it in its corresponding file. This implies to separate the interface definition and the types
   definition. The reason of this separation is best shown with an example :
     - Suppose the module rmprint associated with rmprint.h and rmprint.c declare the type filehandle, 
   and export a function that take a debugwindow as argument.
     -  And the module rmdebug associated with the files rmdebug.h and rmdebug.c declares the type 
   windowdebug needs the declaration of a filehandle to output in a file. 

   If the types declaration are stuck with the API declaration such a dependency can't be done :
     - rmprint.h must include rmdebug.h to access the windowdebug types.
     - rmdebug.h must include rmprint.h to access the filehandle types. 

   Whereas by separating the API from the types declaration as shown above this can be done easily.
*/   

#ifndef __RMBASICTYPES_H__
#define __RMBASICTYPES_H__


/** Generic pointer */
#ifndef NULL
/** pointer not defined */
#define NULL (void *)(0)
#endif // NULL

/** Boolean type */
typedef unsigned char RMbool;
#ifndef TRUE
#define TRUE (RMbool)1
#define FALSE (RMbool)0
#endif // TRUE

/** 8 bits long unsigned integer */
typedef unsigned char RMuint8;
#define MaxRMuint8 ((RMuint8) 255)
#define MinRMuint8 ((RMuint8) 0)

/** 8 bits long integer */
typedef          char RMint8;
#define MaxRMint8 ((RMint8) 127)
#define MinRMint8 ((RMint8) -128)

/** 16 bits long unsigned integer */
typedef unsigned short RMuint16;
#define MaxRMuint16 ((RMuint16)65535)
#define MinRMuint16 ((RMuint16)0)

/** 16 bits long integer */
typedef          short RMint16;
#define MaxRMint16 ((RMint16)32767)
#define MinRMint16 ((RMint16)-32768)

/** 32 bits long unsigned integer */
typedef unsigned long RMuint32;
/* constants are in OS dependent headers 
   because big types require postfixes like UL L ULL LL */

/** 32 bits long integer */
typedef          long RMint32;
/* constants are in OS dependent headers 
   because big types require postfixes like UL L ULL LL */

/** floating point number */
typedef double RMreal;

/** 7 bit us-ascii character */
typedef RMint8 RMascii;

/** to use when the argument is not handled in the OS you are working for */
#define UNUSED_ARG 0xdeadbeef

/// 
/**
   returns the lowest 32 bits from a 64 bits long unsigned integer.
*/
#define RMuint32LSBfromRMuint64(l)     ( (RMuint32)   (l)                      )

/// 
/**
   returns the highest 32 bits from a 64 bits long unsigned integer.
*/
#define RMuint32MSBfromRMuint64(l)     ( (RMuint32) ( ((l)>>32) & 0xffffffff ) )

/// 
/**
   Constructs a 64 bits integer from 2 32 bits integer.
*/
#define RMuint64from2RMuint32(MSB,LSB) ( (RMuint64) ( (((RMuint64)MSB)<<32) + ((RMuint64)LSB) )      )

#endif // __RMBASICTYPES_H__
