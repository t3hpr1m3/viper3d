/**
 *	@class		UDP::VXWindowSystem
 *
 *	@brief		Linux specific window handling routines.
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		26-Sep-2003
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
#if !defined(__VXWINDOWSYSTEM_H_INCLUDED__)
#define __VXWINDOWSYSTEM_H_INCLUDED__

/* System Headers */
#include <GL/gl.h>
#include <GL/glx.h>
#include <X11/extensions/xf86vmode.h>
#include <X11/keysym.h>
#include <map>
#include <fstream>

/* Local Headers */
#include "VWindowSystem.h"
#include "VString.h"

using std::map;

namespace UDP
{
class VXFont : public VFont
{
public:
	VXFont() {};
	virtual ~VXFont() {};

	VString	mFont;
	uint	mPitch;

	GLuint	mBase;
	GLuint	mFirst;
	GLuint	mCount;
};

typedef struct
{
	Display					*mDpy;
	int						mScreen;
	Window					mWin;
	GLXContext				mCtx;
	XSetWindowAttributes	mAttr;
	XF86VidModeModeInfo		mDeskMode;
	int						mX;
	int						mY;
	uint					mDepth;
} GLWindow;

typedef map<KeySym, VKeyCode> _KeyMap;	

class VXWindowSystem : public VWindowSystem
{
public:
	/*==================================*
	 *	   CONSTRUCTION/DESTRUCTION		*
	 *==================================*/
	VXWindowSystem(void);
	virtual ~VXWindowSystem(void);

	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/

	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	/**
	 *	@brief		Initializes the window system.
	 *	@author		Josh Williams
	 *	@date		02-Sep-2004
	 *
	 *	@returns	Success/failure
	 */
	bool			Initialize(void);
	/**
	 *	@brief		Creates the actual window (OS specific).
	 *	@author		Josh Williams
	 *	@date		22-Sep-2003
	 *
	 *	@param		pWidth
	 *	@param		pHeight		Dimensions for the window
	 *	@param		pFullScreen	Whether or not this should be a fullscreen
	 *							window.
	 *
	 *	@returns	(bool) Whether or not we could create the actual window.
	 */
	bool			CreateWindow(const uint pWidth, const uint pHeight,
									bool pFullScreen = false);
	/**
	 *	@brief		Closes the currently active window.
	 *	@author		Josh Williams
	 *	@date		02-Sep-2004
	 *
	 *	@returns	void
	 */
	void			DestroyWindow(void);
	/**
	 *	@brief		Adjusts the size (resolution) of the active window.
	 *	@author		Josh Williams
	 *	@date		02-Sep-2004
	 *
	 *	@param		pWidth
	 *	@param		pHeight		Dimensions for the window
	 *
	 *	@returns	(bool) Whether or not we could create the new window.
	 */
	bool			Resize(const uint pWidth, const uint pHeight);
	/**
	 *	@brief		Switches between windowed and fullscreen mode.
	 *	@author		Josh Williams
	 *	@date		02-Sep-2004
	 *
	 *	@param		pFullScreen	Screen mode desired.
	 *
	 *	@returns	(bool) Whether or not we could create the new window.
	 */
	bool			FullScreen(bool pFullScreen);
	/**
	 *	@brief		Sets the caption for the window.
	 *	@author		Josh Williams
	 *	@date		22-Sep-2003
	 *
	 *	@param		pCaption	Text string to be displayed for this window
	 *
	 *	@returns	void
	 */
	void			SetCaption(const char *pCaption) const;
	void			SwapBuffers(void) const;
	bool			CaptureInput(ulong pFlags) const;
	void			Update(void);
	VKeyEvent*		GetEvent(void);

protected:
	/*==================================*
	 *             CALLBACKS			*
	 *==================================*/

private:
	/*==================================*
	 *             INTERNALS            *
	 *==================================*/
protected:
	void			WriteLog(const char *pText, ...);
	void			LoadKeyMap(void);


private:
	/*==================================*
	 *             VARIABLES            *
	 *==================================*/
	_KeyMap				mKeyMap;
	bool				mWinCreated;
	bool				mInitialized;
	GLWindow			mWin;
	std::ofstream		mLogFile;
	XF86VidModeModeInfo	**mModes;
	int					mNumModes;
	XVisualInfo 		*mVInfo;
};

}

#endif // __VXWINDOWSYSTEM_H_INCLUDED__

