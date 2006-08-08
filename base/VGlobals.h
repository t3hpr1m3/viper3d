/*============================================================================*
 *                                                                            *
 *  This file is part of the Viper3D Game Engine.                             *
 *                                                                            *
 *  Copyright (C) 2004 UDP Games   All Rights Reserved.                       *
 *                                                                            *
 *============================================================================*
 *                                  CHANGELOG                                 *
 *    Date      Description                                     Author        *
 * -----------  ----------------------------------------------  ------------- *
 *                                                                            *
 *============================================================================*/
#if !defined(__GLOBALS_H_INCLUDED__)
#define __GLOBALS_H_INCLUDED__

#define PLATFORM_WINDOWS	1
#define PLATFORM_APPLE		2
#define PLATFORM_LINUX		3

#if defined(__WIN32__) || defined(_WIN32)
#include <windows.h>
#define VIPER_PLATFORM PLATFORM_WINDOWS
#elif defined(__APPLE_CC__)
#define VIPER_PLATFORM PLATFORM_APPLE
#else
#define VIPER_PLATFORM PLATFORM_LINUX
#endif

#if VIPER_PLATFORM == PLATFORM_WINDOWS
#define _ViperExport __declspec( dllexport )
#elif VIPER_PLATFORM == PLATFORM_APPLE
#elif VIPER_PLATFORM == PLATFORM_LINUX
#define _ViperExport
#endif

#endif // __GLOBALS_H_INCLUDED__
	
