/**
 *	@class		UDP::VWindow
 *
 *	@brief		Helper class for loading the specific Window System
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		2004-Sep-02
 */
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
#if !defined(__VWINDOW_H_INCLUDED__)
#define __VWINDOW_H_INCLUDED__

#include "VDynamicLib.h"
#include "VWindowSystem.h"

namespace UDP
{
	typedef void (*DLL_WINCREATE)(VWindowSystem **ppWindow);
	typedef void (*DLL_WINDESTROY)(VWindowSystem *ppWindow);

	class VWindow
	{
	public:
		/*==================================*
		 *	   CONSTRUCTION/DESTRUCTION		*
		 *==================================*/
		VWindow(void);
		virtual ~VWindow(void);

		/*==================================*
		 *			  ATTRIBUTES			*
		 *==================================*/
	
		/*==================================*
		 *			  OPERATIONS			*
		 *==================================*/
		bool CreateDevice(char *pcAPI);
		void Release(void);
		VWindowSystem*	GetDevice(void);

	protected:
		/*==================================*
		 *             CALLBACKS			*
		 *==================================*/

	private:
		/*==================================*
		 *             INTERNALS            *
		 *==================================*/

	
	private:
		/*==================================*
		 *             VARIABLES            *
		 *==================================*/
		VDynamicLib			m_windowLib;
		VWindowSystem		*m_pDevice;
		DLL_WINCREATE		m_pfCreate;
		DLL_WINDESTROY		m_pfDestroy;

	};

} // End Namespace

#endif // __VWINDOW_H_INCLUDED__

