/**
 *	@class		UDP::VDynamicLib
 *
 *	@brief		Represents a dynamically loaded library (.dll/.so)
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		25-Sep-2003
 *	@remarks	Allows a dynamic library to be loaded and function pointers
 *				obtained.  Handles cross-platform logic internally.
 */
/*============================================================================*
 *																			  *
 * 	This file is part of the Viper3D Game Engine.							  *
 *																			  *
 *	Copyright (C) 2004 UDP Games   All Rights Reserved.						  *
 *																			  *
 *============================================================================*
 *                                  CHANGELOG                                 *
 *    Date      Description                                   	Author        *
 * -----------  ----------------------------------------------	------------- *
 *																			  *
 *============================================================================*/
#if !defined(__VDYNAMICLIB_H_INCLUDED__)
#define __VDYNAMICLIB_H_INCLUDED__

#include "VGlobals.h"
#include "VString.h"

#if VIPER_PLATFORM == PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define DYNLIB_HANDLE			hInstance
#define DYNLIB_LOAD( a )		LoadLibrary( a )
#define DYNLIB_GETSYM( a, b )	GetProcAddress( a, b )
#define DYNLIB_UNLOAD( a )		!FreeLibrary( a )
#define DYNLIB_ERROR( )			strerror(errno)
#elif VIPER_PLATFORM == PLATFORM_LINUX
#include <dlfcn.h>
#define DYNLIB_HANDLE			void*
#define DYNLIB_LOAD( a )		dlopen( a, RTLD_NOW)
#define DYNLIB_GETSYM( a, b )	dlsym( a, b )
#define DYNLIB_UNLOAD( a )		dlclose( a )
#define DYNLIB_ERROR( )			dlerror( )
#endif

namespace UDP
{

class VDynamicLib
{
public:
	/*==================================*
	 *	   CONSTRUCTION/DESTRUCTION		*
	 *==================================*/
	VDynamicLib(void);
	~VDynamicLib(void);

	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/

	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	bool			Load(const VString &path, const VString& name);
	void			UnLoad(void);
	void*			GetSymbol(const VString& strName) const;
	const char*		Error(void) const;

protected:
	/*==================================*
	 *             CALLBACKS			*
	 *==================================*/

private:
	/*==================================*
	 *             INTERNALS            *
	 *==================================*/
	void			BuildLibName(const VString &path, 
											const VString& strName);

private:
	/*==================================*
	 *             VARIABLES            *
	 *==================================*/
	DYNLIB_HANDLE	m_hInst;		/**< OS specific library handle */
	VString			m_Name;			/**< full name of the library to load */
	VString			m_strError;		/**< Last error encountered */
};

} // End Namespace

#endif // __VDYNAMICLIB_H_INCLUDED__