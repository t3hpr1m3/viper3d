/**
 *	@class		UDP::VInput
 *
 *	@brief		Helper class for loading the specific Input System
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		2004-Sep-01
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
#if !defined(__VINPUT_H_INCLUDED__)
#define __VINPUT_H_INCLUDED__

#include "VDynamicLib.h"
#include "VInputSystem.h"

namespace UDP
{
	typedef void (*DLL_INPCREATE)(VInputSystem **ppInput);
	typedef void (*DLL_INPDESTROY)(VInputSystem *ppInput);

	class VInput
	{
	public:
		/*==================================*
		 *	   CONSTRUCTION/DESTRUCTION		*
		 *==================================*/
		VInput(void);
		virtual ~VInput(void);

		/*==================================*
		 *			  ATTRIBUTES			*
		 *==================================*/
	
		/*==================================*
		 *			  OPERATIONS			*
		 *==================================*/
		bool			CreateDevice(char *pcAPI);
		void			Release(void);
		VInputSystem*	GetDevice(void);

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
		VDynamicLib		m_inputLib;		/**< Dynamic library object	*/			
		VInputSystem	*m_pDevice;		/**< Actual InputSystem pointer	*/
		DLL_INPCREATE	m_pfCreate;		/**< Pointer to creation function */
		DLL_INPDESTROY	m_pfDestroy;	/**< Pointer to deletion function */

	};

} // End Namespace

#endif // __VINPUT_H_INCLUDED__

