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

/* System Headers */

/* Local Headers */
#include "VDynamicLib.h"
#include "VInputSystem.h"

namespace UDP
{
typedef void (*DLL_INPCREATE)(VInputSystem **pInput);
typedef void (*DLL_INPDESTROY)(VInputSystem *pInput);

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
	bool			CreateDevice(char *pAPI);
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
	VDynamicLib		mInputLib;		/**< Dynamic library object	*/			
	VInputSystem	*mDevice;		/**< Actual InputSystem pointer	*/
	DLL_INPCREATE	mCreate;		/**< Pointer to creation function */
	DLL_INPDESTROY	mDestroy;		/**< Pointer to deletion function */

};

} // End Namespace

#endif // __VINPUT_H_INCLUDED__

