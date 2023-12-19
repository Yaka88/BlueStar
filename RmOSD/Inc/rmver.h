/////////////////////////////////////////////////////////////////////////////
// rmver.h : REALmagic version number
// REALmagic drivers
// Copyright Sigma Designs Inc
// Sigma Designs Proprietary and confidential
// Created on 04/11/96

#ifndef __RMVER_H__
#define __RMVER_H__

// Generic
#define RM_COMPANYNAME          "Sigma Designs Inc.\0"
#define RM_LEGALCOPYRIGHT       "Copyright Sigma Designs Inc. © 2002\0"
#define RM_LEGALTRADEMARKS      "Sigma Designs Inc.\0"
#define RM_COMMENTS             "Release Version\0"

// Windows9x/2k products versions.
#define RM_VERSION					4
#define RM_REVISION					06
#define RM_BUILD					142
#define RM_RELEASE					04
#define RM_PRODUCTVERSION			"4.06.142.04 (Build 142_04)\0"

// Hardware library versions.
#define RM_HWLIB_VERSION				12
#define RM_HWLIB_VERSION_STR			"12"

// WindowsCE products versions.
#define RM_CE_VERSION			1					// major version
#define RM_CE_REVISION			0					// minor version
#define RM_CE_BUILD				5					// build number
#define RM_CE_RELEASE			RM_HWLIB_VERSION	// hwlib version
#define RM_CE_PRODUCTVERSION	"1.0.4.12\0"		// text equivalent

// CARIBBEAN products versions.
#define RM_CARIBBEAN_VERSION	1
#define RM_CARIBBEAN_REVISION	3
#define RM_CARIBBEAN_BUILD	60
#define RM_CARIBBEAN_RELEASE	2
#define RM_CARIBBEAN_PRODUCTVERSION "based on CARIBBEAN-1.3.60.2\0"

#endif // __RMVER_H__
