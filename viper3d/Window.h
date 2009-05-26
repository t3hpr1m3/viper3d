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

/* System Headers */

/* Local Headers */
#include "VDynamicLib.h"
#include "VWindowSystem.h"

namespace UDP
{

/**
 *	@class		VWindow
 *
 *	@brief		Helper class for loading the specific Window System
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		2004-Sep-02
 */
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
	bool CreateDevice(char *pAPI);
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
	VDynamicLib			mWindowLib;
	VWindowSystem		*mDevice;
	DLL_WINCREATE		*mCreate;
	DLL_WINDESTROY		*mDestroy;

};

} // End Namespace

#endif // __VWINDOW_H_INCLUDED__

