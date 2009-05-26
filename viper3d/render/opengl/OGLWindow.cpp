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
#include "OGLWindow.h"

/* System Headers */
#include <viper3d/util/Log.h>

/* Local Headers */


namespace UDP
{

static char __CLASS__[] = "[  VOGLWindow  ]";

/********************************************************************
 *          C O N S T R U C T I O N / D E S T R U C T I O N         *
 ********************************************************************/
VOGLWindow::VOGLWindow()
{
#if VIPER_PLATFORM == PLATFORM_WINDOWS
#elif VIPER_PLATFORM == PLATFORM_MAC
#elif VIPER_PLATFORM == PLATFORM_LINUX
	mAttr.border_pixel = 0;
#endif
}

VOGLWindow::~VOGLWindow(void)
{
#if VIPER_PLATFORM == PLATFORM_WINDOWS
#elif VIPER_PLATFORM == PLATFORM_MAC
#elif VIPER_PLATFORM == PLATFORM_LINUX
	if (mWin != -1)
		Destroy();
#endif
}

/********************************************************************
 *                        A T T R I B U T E S                       *
 ********************************************************************/

/********************************************************************
 *                        O P E R A T I O N S                       *
 ********************************************************************/
bool VOGLWindow::Create(VWindowOpts *pOpts)
{
#if VIPER_PLATFORM == PLATFORM_WINDOWS
#elif VIPER_PLATFORM == PLATFORM_MAC
#elif VIPER_PLATFORM == PLATFORM_LINUX
	Atom	vWMDelete;
	Window	vWinDmmy;
	VUINT	vBorderDummy;

	mOpts.mFullScreen = pOpts->mFullScreen;
	mOpts.mWidth = pOpts->mWidth;
	mOpts.mHeight = pOpts->mHeight;

	mAttr.colormap = XCreateColormap(mDpy, RootWindow(mDpy, mVInfo->screen),
						mVInfo->visual, AllocNone);

	mAttr.event_mask = ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask;

	if (mOpts.mFullScreen)
	{
		XF86VidModeSwitchToMode(mDpy, mScreen, mMode);
		XF86VidModeSetViewPort(mDpy, mScreen, 0, 0);
		mAttr.override_redirect = True;
		mWin = XCreateWindow(mDpy, RootWindow(mDpy, mVInfo->screen),
			0, 0, mOpts.mWidth, mOpts.mHeight, 0, mVInfo->depth, InputOutput, mVInfo->visual,
			CWBorderPixel | CWColormap | CWEventMask | CWOverrideRedirect, &mAttr
		);
	}
	else
	{
		mWin = XCreateWindow(mDpy, RootWindow(mDpy, mVInfo->screen),
			0, 0, mOpts.mWidth, mOpts.mHeight, 0, mVInfo->depth, InputOutput, mVInfo->visual,
			CWBorderPixel | CWColormap | CWEventMask, &mAttr
		);
		vWMDelete = XInternAtom(mDpy, "WM_DELETE_WINDOW", True);
		XSetWMProtocols(mDpy, mWin, &vWMDelete, 1);
		XSetStandardProperties(mDpy, mWin, "", "", None, NULL, 0, NULL);
	}
	XMapRaised(mDpy, mWin);

	mCtx = glXCreateContext(mDpy, mVInfo, 0, GL_TRUE);
	if (mCtx == NULL)
	{
		VTRACE(_CL("Unable to create context\n"));
		return false;
	}

	if (!glXMakeCurrent(mDpy, mWin, mCtx))
		return false;

	if (glXIsDirect(mDpy, mCtx))
		VTRACE(_CL("Direct Rendering: true\n"));
	else
		VTRACE(_CL("Direct Rendering: false\n"));
#endif

	return true;
}

void VOGLWindow::Destroy(void)
{
#if VIPER_PLATFORM == PLATFORM_WINDOWS
#elif VIPER_PLATFORM == PLATFORM_MAC
#elif VIPER_PLATFORM == PLATFORM_LINUX
	XDestroyWindow(mDpy, mWin);
	glXDestroyContext(mDpy, mCtx);
	mWin = -1;
#endif
}

bool VOGLWindow::Resize(VWindowOpts *pOpts)
{
#if VIPER_PLATFORM == PLATFORM_WINDOWS
#elif VIPER_PLATFORM == PLATFORM_MAC
#elif VIPER_PLATFORM == PLATFORM_LINUX
#endif
}

void VOGLWindow::SetCaption(const char *pCaption)
{
#if VIPER_PLATFORM == PLATFORM_WINDOWS
#elif VIPER_PLATFORM == PLATFORM_MAC
#elif VIPER_PLATFORM == PLATFORM_LINUX
	XStoreName(mDpy, mWin, pCaption);
#endif
}

bool VOGLWindow::SwapBuffers(void) const
{
#if VIPER_PLATFORM == PLATFORM_WINDOWS
#elif VIPER_PLATFORM == PLATFORM_MAC
#elif VIPER_PLATFORM == PLATFORM_LINUX
	glXSwapBuffers(mDpy, mWin);
#endif
}

/********************************************************************
 *                         C A L L B A C K S                        *
 ********************************************************************/

/********************************************************************
 *                         I N T E R N A L S                        *
 ********************************************************************/

} // End Namespace

