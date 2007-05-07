/*============================================================================*
 *                                                                            *
 * 	This file is part of the Viper3D Game Engine.						  	  *
 *                                                                            *
 *	Copyright (C) 2004 UDP Games   All Rights Reserved.						  *
 *                                                                            *
 *============================================================================*/
#include "VXWindowSystem.h"

/* System Headers */
#include <cstdlib> // For getenv()
#include <iostream>
#include <cstdarg>
#include <cstdio>

/* Local Headers */

using std::cout;
using std::cerr;
using std::endl;

namespace UDP
{

class DLL_WINCREATE_IMPL : public DLL_WINCREATE
{
public:
	void operator()(VWindowSystem **pWins)
	{
		*pWins = (VWindowSystem*)new VXWindowSystem();
	}
};
class DLL_WINDESTROY_IMPL : public DLL_WINDESTROY
{
public:
	void operator()(VWindowSystem *pWins)
	{
		delete (VXWindowSystem*)pWins;
	}
};

/* creation functions */
extern "C" {
_ViperExport
DLL_WINCREATE_IMPL Construct;
_ViperExport
DLL_WINDESTROY_IMPL Destruct;

/*
_ViperExport void Construct(VWindowSystem **pWins)
{
	*pWins = (VWindowSystem*)new VXWindowSystem();
}
_ViperExport void Destruct(VWindowSystem *pWins)
{
	delete (VXWindowSystem*)pWins;
}
*/

} // extern "C"

/********************************************************************
 *          C O N S T R U C T I O N / D E S T R U C T I O N         *
 ********************************************************************/
VXWindowSystem::VXWindowSystem(void)
{
#ifndef BENCHMARK
	mDblBuffered = true;
#endif
	mVInfo = NULL;
	mWinCreated = false;
	mInitialized = false;
	LoadKeyMap();
}

VXWindowSystem::~VXWindowSystem(void)
{
	printf("VXWindowSystem DTOR\n");
	if (mInitialized)
	{
		DestroyWindow();
		if (mWin.mCtx)
		{
			glXDestroyContext(mWin.mDpy, mWin.mCtx);
			mWin.mCtx = NULL;
		}
		XCloseDisplay(mWin.mDpy);
		XFree(mModes);
	}
	if (mLog.is_open())
		mLog.close();
}
/********************************************************************
 *                        A T T R I B U T E S                       *
 ********************************************************************/

/********************************************************************
 *                        O P E R A T I O N S                       *
 ********************************************************************/

bool VXWindowSystem::Initialize(void)
{
	char	*vDisplay;
	int		vVidModeMajVer, vVidModeMinVer;
	int		vAttrListSgl[] = {GLX_RGBA, GLX_RED_SIZE, 4,
							GLX_GREEN_SIZE, 4,
							GLX_BLUE_SIZE, 4,
							GLX_DEPTH_SIZE, 16,
							None};
	int		vAttrListDbl[] = {GLX_RGBA, GLX_DOUBLEBUFFER,
							GLX_RED_SIZE, 4,
							GLX_GREEN_SIZE, 4,
							GLX_BLUE_SIZE, 4,
							GLX_DEPTH_SIZE, 16,
							None};

	/* try to open the trace file */
	mLog.open("XWindow.log");
	if (!mLog.is_open())
		return false;

	/* connect to the Xserver */
	vDisplay = getenv("DISPLAY");
	if ((mWin.mDpy = XOpenDisplay(vDisplay)) == NULL)
	{
		WriteLog("Unable to connect to X server\n");
		return false;
	}

	/* query X information */
	mWin.mScreen = DefaultScreen(mWin.mDpy);
	XF86VidModeQueryVersion(mWin.mDpy, &vVidModeMajVer, &vVidModeMinVer);
	WriteLog("=====================\n");
	WriteLog("        X Info\n");
	WriteLog("X Version:  %d.%d\n", vVidModeMajVer, vVidModeMinVer);
	glXQueryVersion(mWin.mDpy, &vVidModeMajVer, &vVidModeMinVer);
	WriteLog("GL Version: %d.%d\n", vVidModeMajVer, vVidModeMinVer);

	/* select the best mode */
	XF86VidModeGetAllModeLines(mWin.mDpy, mWin.mScreen, &mNumModes, &mModes);
	mWin.mDeskMode = *mModes[0];

	/* try and obtain a double-buffered visual */
#ifndef BENCHMARK
	mVInfo = glXChooseVisual(mWin.mDpy, mWin.mScreen, vAttrListDbl);
	if (mVInfo == NULL)
	{
#endif
		mVInfo = glXChooseVisual(mWin.mDpy, mWin.mScreen, vAttrListSgl);
		if (mVInfo == NULL)
			return false;
		mDblBuffered = false;
		WriteLog("Mode: SingleBuffered\n");
#ifndef BENCHMARK
	}
	else
	{
		WriteLog("Mode: DoubleBuffered\n");
	}
#endif

	/* create the GL context for rendering */
	mWin.mCtx = glXCreateContext(mWin.mDpy, mVInfo, 0, GL_TRUE);
	if (mWin.mCtx == NULL)
		return false;

	/* create the colormap */
	mWin.mAttr.colormap = XCreateColormap(mWin.mDpy, RootWindow(mWin.mDpy, mVInfo->screen),
						mVInfo->visual, AllocNone);
	mWin.mAttr.border_pixel = 0;

	/* check for direct rendering */
	if (glXIsDirect(mWin.mDpy, mWin.mCtx))
		WriteLog("Direct Rendering: true\n");
	else
		WriteLog("Direct Rendering: false\n");

	WriteLog("=====================\n");

	mInitialized = true;

	return true;
}

/*------------------------------------------------------------------*
 *							CreateWindow()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
bool VXWindowSystem::CreateWindow(const uint pWidth, const uint pHeight,
								bool pFullScreen/*=false*/)
{
	int					vDpyWidth, vDpyHeight;
	int					vBestMode = 0;
	Atom				vWMDelete;
	Window				vWinDummy;
	uint				vBorderDummy;

	mFullScreen = pFullScreen;

	if (!mInitialized)
	{
		WriteLog("CreateWindow() called with no context initialized\n");
		return false;
	}

	for (int i = 0; i < mNumModes; i++)
	{
		if ((mModes[i]->hdisplay == pWidth) && (mModes[i]->vdisplay == pHeight))
		{
			vBestMode = i;
		}
	}

	if (mFullScreen)
	{
		XF86VidModeSwitchToMode(mWin.mDpy, mWin.mScreen, mModes[vBestMode]);
		XF86VidModeSetViewPort(mWin.mDpy, mWin.mScreen, 0, 0);
		vDpyWidth = mModes[vBestMode]->hdisplay;
		vDpyHeight = mModes[vBestMode]->vdisplay;
		mWin.mAttr.override_redirect = True;
		mWin.mAttr.event_mask = ExposureMask | KeyPressMask | ButtonPressMask |
								StructureNotifyMask;
		mWin.mWin = XCreateWindow(mWin.mDpy, RootWindow(mWin.mDpy,
								mVInfo->screen), 0, 0, vDpyWidth, vDpyHeight, 0,
								mVInfo->depth, InputOutput, mVInfo->visual,
								CWBorderPixel | CWColormap | CWEventMask |
								CWOverrideRedirect,	&mWin.mAttr);
		XWarpPointer(mWin.mDpy, None, mWin.mWin, 0, 0, 0, 0, 0, 0);
		XMapRaised(mWin.mDpy, mWin.mWin);
		XGrabKeyboard(mWin.mDpy, mWin.mWin, True, GrabModeAsync, GrabModeAsync,
								CurrentTime);
		XGrabPointer(mWin.mDpy, mWin.mWin, True, ButtonPressMask,
				GrabModeAsync, GrabModeAsync, mWin.mWin, None, CurrentTime);
	}
	else
	{
		mWin.mAttr.event_mask = ExposureMask | KeyPressMask | ButtonPressMask |
								StructureNotifyMask;
		mWin.mWin = XCreateWindow(mWin.mDpy, RootWindow(mWin.mDpy,
								mVInfo->screen), 0, 0, pWidth, pHeight, 0,
								mVInfo->depth, InputOutput, mVInfo->visual,
								CWBorderPixel | CWColormap | CWEventMask,
								&mWin.mAttr);
		vWMDelete = XInternAtom(mWin.mDpy, "WM_DELETE_WINDOW", True);
		XSetWMProtocols(mWin.mDpy, mWin.mWin, &vWMDelete, 1);
		XSetStandardProperties(mWin.mDpy, mWin.mWin, "", "", None, NULL, 0,
								NULL);
		XMapRaised(mWin.mDpy, mWin.mWin);
	}

	if (!glXMakeCurrent(mWin.mDpy, mWin.mWin, mWin.mCtx))
		return false;
	XGetGeometry(mWin.mDpy, mWin.mWin, &vWinDummy, &mWin.mX, &mWin.mY,
					&mWidth, &mHeight, &vBorderDummy, &mWin.mDepth);

	cout << "Running in " << (mFullScreen ? "fullscreen" : "window")
						<< " mode" << endl;
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	mWinCreated = true;

	return true;
}

void VXWindowSystem::DestroyWindow(void)
{
	if (mWinCreated)
	{
		if (!glXMakeCurrent(mWin.mDpy, None, NULL))
			WriteLog("Error changing GL context to default in DestroyWindow()\n");
		if (mFullScreen)
		{
			XF86VidModeSwitchToMode(mWin.mDpy, mWin.mScreen, &mWin.mDeskMode);
			XF86VidModeSetViewPort(mWin.mDpy, mWin.mScreen, 0, 0);
		}
	}

	mWinCreated = false;
}

bool VXWindowSystem::Resize(const uint pWidth, const uint pHeight)
{
	if (pWidth != mWidth && pHeight != mHeight)
	{
		DestroyWindow();
		if (!CreateWindow(pWidth, pHeight, mFullScreen))
			return false;
	}

	return true;
}

bool VXWindowSystem::FullScreen(bool pFullScreen)
{
	if (pFullScreen != mFullScreen)
	{
		DestroyWindow();
		if (!CreateWindow(mWidth, mHeight, pFullScreen))
			return false;
	}

	return true;
}
		

/*------------------------------------------------------------------*
 *							  SetCaption()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VXWindowSystem::SetCaption(const char *pCaption) const
{
	XStoreName(mWin.mDpy, mWin.mWin, pCaption);
}

void VXWindowSystem::SwapBuffers(void) const
{
	if (mDblBuffered)
		glXSwapBuffers(mWin.mDpy, mWin.mWin);
}

bool VXWindowSystem::CaptureInput(ulong pFlags) const
{
	XSelectInput(mWin.mDpy, mWin.mWin, pFlags);
	return true;
}

void VXWindowSystem::Update(void)
{
	XEvent				vXev;
	int					vNumEvents;
	bool				vKs = false;
	KeySym				vKey;
	VKeyCode			vKc;
	VKeyEvent			*vEvent;
	_KeyMap::iterator	vIt;

	XFlush(mWin.mDpy);
	vNumEvents = XPending(mWin.mDpy);
	while (vNumEvents != 0)
	{
		vNumEvents--;
		XNextEvent(mWin.mDpy, &vXev);
		switch (vXev.type)
		{
			case EnterNotify:
				XAutoRepeatOff(mWin.mDpy);
				break;
			case LeaveNotify:
				XAutoRepeatOn(mWin.mDpy);
				break;
			case KeyPress:
			case KeyRelease:
				if (vXev.type == KeyPress)
					vKs = true;
				else
					vKs = false;
				vKey = XLookupKeysym(&vXev.xkey, 0);
				vIt = mKeyMap.find(vKey);
				if (vIt != mKeyMap.end())
				{
					vKc = vIt->second;
					vEvent = new VKeyEvent();
					vEvent->mAction = (vKs ? KEY_PRESS : KEY_RELEASE);
					vEvent->mCode = vKc;
					mKeyEvents.push(vEvent);
				}
				break;
			default:
				break;

		} /* switch() */

	} /* while() */

}

VKeyEvent* VXWindowSystem::GetEvent(void)
{
	if (mKeyEvents.size() != 0)
	{
		VKeyEvent* vEvt = mKeyEvents.front();
		mKeyEvents.pop();
		return vEvt;
	}
	else
		return NULL;
}
		

/********************************************************************
 *                         C A L L B A C K S                        *
 ********************************************************************/

/********************************************************************
 *                         I N T E R N A L S                        *
 ********************************************************************/
void VXWindowSystem::WriteLog(const char *pText, ...)
{
	static char vBuffer[1024];
	va_list		vArgs;

	memset(vBuffer, '\0', sizeof(vBuffer));

	va_start(vArgs, pText);
	vsprintf(vBuffer, pText, vArgs);
	va_end(vArgs);
	mLog << vBuffer;

#ifdef DEBUG
	mLog.flush();
#endif
}
void VXWindowSystem::LoadKeyMap(void)
{
   	mKeyMap.insert(_KeyMap::value_type(XK_Escape, KC_ESCAPE));
	mKeyMap.insert(_KeyMap::value_type(XK_0, KC_0));
	mKeyMap.insert(_KeyMap::value_type(XK_1, KC_1));
	mKeyMap.insert(_KeyMap::value_type(XK_1, KC_1));
	mKeyMap.insert(_KeyMap::value_type(XK_2, KC_2));
	mKeyMap.insert(_KeyMap::value_type(XK_3, KC_3));
	mKeyMap.insert(_KeyMap::value_type(XK_4, KC_4));
	mKeyMap.insert(_KeyMap::value_type(XK_5, KC_5));
	mKeyMap.insert(_KeyMap::value_type(XK_6, KC_6));
	mKeyMap.insert(_KeyMap::value_type(XK_7, KC_7));
	mKeyMap.insert(_KeyMap::value_type(XK_8, KC_8));
	mKeyMap.insert(_KeyMap::value_type(XK_9, KC_9));
	mKeyMap.insert(_KeyMap::value_type(XK_minus, KC_MINUS));
	mKeyMap.insert(_KeyMap::value_type(XK_BackSpace, KC_BACK));
	mKeyMap.insert(_KeyMap::value_type(XK_Tab, KC_TAB));
	mKeyMap.insert(_KeyMap::value_type(XK_q, KC_Q));
	mKeyMap.insert(_KeyMap::value_type(XK_w, KC_W));
	mKeyMap.insert(_KeyMap::value_type(XK_e, KC_E));
	mKeyMap.insert(_KeyMap::value_type(XK_R, KC_R));
	mKeyMap.insert(_KeyMap::value_type(XK_t, KC_T));
	mKeyMap.insert(_KeyMap::value_type(XK_y, KC_Y));
	mKeyMap.insert(_KeyMap::value_type(XK_u, KC_U));
	mKeyMap.insert(_KeyMap::value_type(XK_i, KC_I));
	mKeyMap.insert(_KeyMap::value_type(XK_o, KC_O));
	mKeyMap.insert(_KeyMap::value_type(XK_p, KC_P));
	mKeyMap.insert(_KeyMap::value_type(XK_bracketleft, KC_LBRACKET));
	mKeyMap.insert(_KeyMap::value_type(XK_Return, KC_RETURN));
	mKeyMap.insert(_KeyMap::value_type(XK_Control_L, KC_LCONTROL));
	mKeyMap.insert(_KeyMap::value_type(XK_a, KC_A));
	mKeyMap.insert(_KeyMap::value_type(XK_s, KC_S));
	mKeyMap.insert(_KeyMap::value_type(XK_d, KC_D));
	mKeyMap.insert(_KeyMap::value_type(XK_f, KC_F));
	mKeyMap.insert(_KeyMap::value_type(XK_g, KC_G));
	mKeyMap.insert(_KeyMap::value_type(XK_h, KC_H));
    mKeyMap.insert(_KeyMap::value_type(XK_j, KC_J));
	mKeyMap.insert(_KeyMap::value_type(XK_k, KC_K));
	mKeyMap.insert(_KeyMap::value_type(XK_l, KC_L));
	mKeyMap.insert(_KeyMap::value_type(XK_semicolon, KC_SEMICOLON));
	mKeyMap.insert(_KeyMap::value_type(XK_apostrophe, KC_APOSTROPHE));
	mKeyMap.insert(_KeyMap::value_type(XK_grave, KC_GRAVE));
	mKeyMap.insert(_KeyMap::value_type(XK_Shift_L, KC_LSHIFT));
	mKeyMap.insert(_KeyMap::value_type(XK_backslash, KC_BACKSLASH));
	mKeyMap.insert(_KeyMap::value_type(XK_z, KC_Z));
	mKeyMap.insert(_KeyMap::value_type(XK_x, KC_X));
	mKeyMap.insert(_KeyMap::value_type(XK_c, KC_C));
	mKeyMap.insert(_KeyMap::value_type(XK_v, KC_V));
	mKeyMap.insert(_KeyMap::value_type(XK_b, KC_B));
	mKeyMap.insert(_KeyMap::value_type(XK_n, KC_N));
	mKeyMap.insert(_KeyMap::value_type(XK_m, KC_M));
	mKeyMap.insert(_KeyMap::value_type(XK_m, KC_M));
	mKeyMap.insert(_KeyMap::value_type(XK_comma, KC_COMMA));
	mKeyMap.insert(_KeyMap::value_type(XK_period, KC_PERIOD));
    mKeyMap.insert(_KeyMap::value_type(XK_slash, KC_SLASH));
	mKeyMap.insert(_KeyMap::value_type(XK_Shift_R, KC_RSHIFT));
	mKeyMap.insert(_KeyMap::value_type(XK_KP_Multiply, KC_MULTIPLY));
    mKeyMap.insert(_KeyMap::value_type(XK_Alt_L, KC_LMENU));
    mKeyMap.insert(_KeyMap::value_type(XK_space, KC_SPACE));
	mKeyMap.insert(_KeyMap::value_type(XK_F1, KC_F1));
	mKeyMap.insert(_KeyMap::value_type(XK_F2, KC_F2));
	mKeyMap.insert(_KeyMap::value_type(XK_F3, KC_F3));
	mKeyMap.insert(_KeyMap::value_type(XK_F4, KC_F4));
	mKeyMap.insert(_KeyMap::value_type(XK_F5, KC_F5));
	mKeyMap.insert(_KeyMap::value_type(XK_F6, KC_F6));
	mKeyMap.insert(_KeyMap::value_type(XK_F7, KC_F7));
	mKeyMap.insert(_KeyMap::value_type(XK_F8, KC_F8));
	mKeyMap.insert(_KeyMap::value_type(XK_F9, KC_F9));
	mKeyMap.insert(_KeyMap::value_type(XK_F10, KC_F10));
	mKeyMap.insert(_KeyMap::value_type(XK_F11, KC_F11));
	mKeyMap.insert(_KeyMap::value_type(XK_F12, KC_F12));
    mKeyMap.insert(_KeyMap::value_type(XK_Num_Lock, KC_NUMLOCK));
	mKeyMap.insert(_KeyMap::value_type(XK_Scroll_Lock, KC_SCROLL));
	mKeyMap.insert(_KeyMap::value_type(XK_KP_7, KC_NUMPAD7));
	mKeyMap.insert(_KeyMap::value_type(XK_KP_8, KC_NUMPAD8));
	mKeyMap.insert(_KeyMap::value_type(XK_KP_9, KC_NUMPAD9));
	mKeyMap.insert(_KeyMap::value_type(XK_KP_Subtract, KC_SUBTRACT));
	mKeyMap.insert(_KeyMap::value_type(XK_KP_4, KC_NUMPAD4));
	mKeyMap.insert(_KeyMap::value_type(XK_KP_5, KC_NUMPAD5));
	mKeyMap.insert(_KeyMap::value_type(XK_KP_6, KC_NUMPAD6));
	mKeyMap.insert(_KeyMap::value_type(XK_KP_Add, KC_ADD));
	mKeyMap.insert(_KeyMap::value_type(XK_KP_1, KC_NUMPAD1));
	mKeyMap.insert(_KeyMap::value_type(XK_KP_2, KC_NUMPAD2));
	mKeyMap.insert(_KeyMap::value_type(XK_KP_3, KC_NUMPAD3));
	mKeyMap.insert(_KeyMap::value_type(XK_KP_0, KC_NUMPAD0));
	mKeyMap.insert(_KeyMap::value_type(XK_KP_Decimal, KC_DECIMAL));
	mKeyMap.insert(_KeyMap::value_type(XK_KP_Enter, KC_NUMPADENTER));
	mKeyMap.insert(_KeyMap::value_type(XK_Control_R, KC_RCONTROL));
	mKeyMap.insert(_KeyMap::value_type(XK_KP_Divide, KC_DIVIDE));
	mKeyMap.insert(_KeyMap::value_type(XK_Sys_Req, KC_SYSRQ));
	mKeyMap.insert(_KeyMap::value_type(XK_Alt_R, KC_RMENU));
	mKeyMap.insert(_KeyMap::value_type(XK_Pause, KC_PAUSE));
	mKeyMap.insert(_KeyMap::value_type(XK_Home, KC_HOME));
	mKeyMap.insert(_KeyMap::value_type(XK_Up, KC_UP));
	mKeyMap.insert(_KeyMap::value_type(XK_Page_Up, KC_PGUP));
	mKeyMap.insert(_KeyMap::value_type(XK_Left, KC_LEFT));
	mKeyMap.insert(_KeyMap::value_type(XK_Right, KC_RIGHT));
	mKeyMap.insert(_KeyMap::value_type(XK_End, KC_END));
	mKeyMap.insert(_KeyMap::value_type(XK_Down, KC_DOWN));
	mKeyMap.insert(_KeyMap::value_type(XK_Page_Down, KC_PGDOWN));
	mKeyMap.insert(_KeyMap::value_type(XK_Insert, KC_INSERT));
	mKeyMap.insert(_KeyMap::value_type(XK_Delete, KC_DELETE));
}

} // End Namespace

