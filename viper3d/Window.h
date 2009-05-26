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
#if !defined(__WINDOW_H_INCLUDED__)
#define __WINDOW_H_INCLUDED__

/* System Headers */
#include <viper3d/Viper3D.h>
#if VIPER_PLATFORM == PLATFORM_WINDOWS
#elif VIPER_PLATFORM == PLATFORM_MAC
#elif VIPER_PLATFORM == PLATFORM_LINUX
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/xf86vmode.h>
#endif

/* Local Headers */

namespace UDP
{

class VWindowOpts
{
public:
	int			mWidth;
	int			mHeight;
	bool		mFullScreen;
};

class VRenderSystem;

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
	VWindow();
	virtual ~VWindow();

	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/
	bool				IsFullScreen(void) const;

	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	virtual bool		Create(VWindowOpts *pOpts) = 0;
	virtual void		Destroy(void) = 0;
	virtual bool		Resize(VWindowOpts *pOpts) = 0;
	virtual void		SetCaption(const char *pCaption) = 0;
	virtual bool		SwapBuffers(void) const = 0;

protected:
	/*==================================*
	 *             CALLBACKS			*
	 *==================================*/

private:
	/*==================================*
	 *             INTERNALS            *
	 *==================================*/

public:
	/*==================================*
	 *             VARIABLES            *
	 *==================================*/
#if VIPER_PLATFORM == PLATFORM_WINDOWS
	HWND					mWin;
#elif VIPER_PLATFORM == PLATFORM_MAC
#elif VIPER_PLATFORM == PLATFORM_LINUX
	Display					*mDpy;
	int						mScreen;
	Window					mWin;
	XVisualInfo				*mVInfo;
	XSetWindowAttributes	mAttr;
	XF86VidModeModeInfo		*mMode;
#endif
	VWindowOpts				mOpts;
};

inline
bool VWindow::IsFullScreen(void) const
{
	return mOpts.mFullScreen;
}

} // End Namespace

#endif // __WINDOW_H_INCLUDED__

