/**
 *	@class		UDP::VXInputSystem
 *
 *	@brief		Linux platform-specific Input implementation.
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		25-Sep-2003
 */
/*============================================================================*
 *																			  *
 * 	This file is part of the Viper3D Game Engine.							  *
 *																			  *
 *	Copyright (C) 2004 UDP Games   All Rights Reserved.						  *
 *																			  *
 *============================================================================*
 *                                  CHANGELOG                                 *
 *    Date      Description                                    Author         *
 * -----------  ---------------------------------------------  -------------- *
 *																			  *
 *============================================================================*/
#if !defined(__VXINPUTSYSTEM_H_INCLUDED__)
#define __VXINPUTSYSTEM_H_INCLUDED__

#include <GL/gl.h>
#include <GL/glx.h>
#include <X11/keysym.h>
#include "VInputSystem.h"

namespace UDP
{
	class VXInputSystem : public VInputSystem
	{
	public:
		/*==================================*
		 *	   CONSTRUCTION/DESTRUCTION		*
		 *==================================*/
		VXInputSystem();
		virtual ~VXInputSystem();

		/*==================================*
		 *			  ATTRIBUTES			*
		 *==================================*/
		bool			IsKeyDown(VKeyCode kc);

		/*==================================*
		 *			  OPERATIONS			*
		 *==================================*/
		bool			Initialize(VWindowSystem *pWins);
		virtual void 	Update();

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
	protected:
		VWindowSystem	*m_pWins;
	};

}

#endif // __VXINPUTSYSTEM_H_INCLUDED__

