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
#if !defined(__RAWINPUT_H_INCLUDED__)
#define __RAWINPUT_H_INCLUDED__

/* System Headers */
#include <viper3d/Viper3D.h>
#include <viper3d/Input.h>
#if VIPER_PLATFORM == PLATFORM_WINDOWS
#elif VIPER_PLATFORM == PLATFORM_MAC
#elif VIPER_PLATFORM == PLATFORM_LINUX
#include <X11/Xlib.h>
/*
#include <X11/keysym.h>
*/
#endif
#include <map>

/* Local Headers */

namespace UDP
{

#if VIPER_PLATFORM == PLATFORM_WINDOWS
typedef std::map<int, VKeyCode> VKeyMap;
#elif VIPER_PLATFORM == PLATFORM_MAC
#elif VIPER_PLATFORM == PLATFORM_LINUX
typedef std::map<KeySym, VKeyCode> VKeyMap;
#endif

/**
 *	@class		VRawInput
 *
 *	@brief		Bare-bones input access.
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		2009-May-14
 */
class VRawInput : public VInput
{
public:
	/*==================================*
	 *	   CONSTRUCTION/DESTRUCTION		*
	 *==================================*/
	VRawInput(void);
	virtual ~VRawInput(void);

	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/

	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	bool			StartCapture(VWindow *pWin);
	void			EndCapture(void);

	bool			Update(void);

protected:
	/*==================================*
	 *             CALLBACKS			*
	 *==================================*/

private:
	/*==================================*
	 *             INTERNALS            *
	 *==================================*/
	void			LoadKeyMap(void);


private:
	/*==================================*
	 *             VARIABLES            *
	 *==================================*/
	VWindow			*mWin;			/**< Window handle */
	VKeyMap			mKeyMap;

};

} // End Namespace

#endif // __INPUT_H_INCLUDED__

