/*============================================================================*
 *                                                                            *
 * 	This file is part of the Viper3D Game Engine.						  	  *
 *                                                                            *
 *	Copyright (C) 2004 UDP Games   All Rights Reserved.						  *
 *                                                                            *
 *============================================================================*/

/* System Headers */
#include <cstdlib> // For getenv()
#include <iostream>
#include <cstdarg>
#include <cstdio>

/* Local Headers */
#include "VXWindowSystem.h"

using std::cout;
using std::cerr;
using std::endl;

namespace UDP
{

/* creation functions */
extern "C" {

_ViperExport void Construct(VWindowSystem **pWins)
{
	*pWins = (VWindowSystem*)new VXWindowSystem();
}
_ViperExport void Destruct(VWindowSystem *pWins)
{
	delete (VXWindowSystem*)pWins;
}

} // extern "C"

/********************************************************************
 *          C O N S T R U C T I O N / D E S T R U C T I O N         *
 ********************************************************************/
VXWindowSystem::VXWindowSystem(void)
{
#ifndef BENCHMARK
	m_bDblBuffered = true;
#endif
	m_vInfo = NULL;
	m_bWinCreated = false;
	m_bInitialized = false;
	LoadKeyMap();
}

VXWindowSystem::~VXWindowSystem(void)
{
	if (m_bInitialized)
	{
		DestroyWindow();
		if (m_Win.ctx)
		{
			glXDestroyContext(m_Win.dpy, m_Win.ctx);
			m_Win.ctx = NULL;
		}
		XCloseDisplay(m_Win.dpy);
		XFree(m_Modes);
	}
	if (m_Log.is_open())
		m_Log.close();
}
/********************************************************************
 *                        A T T R I B U T E S                       *
 ********************************************************************/

/********************************************************************
 *                        O P E R A T I O N S                       *
 ********************************************************************/

bool VXWindowSystem::Initialize(void)
{
	char	*pcDisplay;
	int		vidModeMajVer, vidModeMinVer;
	int attrListSgl[] = {GLX_RGBA, GLX_RED_SIZE, 4,
							GLX_GREEN_SIZE, 4,
							GLX_BLUE_SIZE, 4,
							GLX_DEPTH_SIZE, 16,
							None};
	int attrListDbl[] = {GLX_RGBA, GLX_DOUBLEBUFFER,
							GLX_RED_SIZE, 4,
							GLX_GREEN_SIZE, 4,
							GLX_BLUE_SIZE, 4,
							GLX_DEPTH_SIZE, 16,
							None};

	/* try to open the trace file */
	m_Log.open("XWindow.log");
	if (!m_Log.is_open())
		return false;

	/* connect to the Xserver */
	pcDisplay = getenv("DISPLAY");
	if ((m_Win.dpy = XOpenDisplay(pcDisplay)) == NULL)
	{
		WriteLog("Unable to connect to X server\n");
		return false;
	}

	/* query X information */
	m_Win.screen = DefaultScreen(m_Win.dpy);
	XF86VidModeQueryVersion(m_Win.dpy, &vidModeMajVer, &vidModeMinVer);
	WriteLog("=====================\n");
	WriteLog("        X Info\n");
	WriteLog("X Version:  %d.%d\n", vidModeMajVer, vidModeMinVer);
	glXQueryVersion(m_Win.dpy, &vidModeMajVer, &vidModeMinVer);
	WriteLog("GL Version: %d.%d\n", vidModeMajVer, vidModeMinVer);

	/* select the best mode */
	XF86VidModeGetAllModeLines(m_Win.dpy, m_Win.screen, &m_nNumModes, &m_Modes);
	m_Win.deskMode = *m_Modes[0];

	/* try and obtain a double-buffered visual */
#ifndef BENCHMARK
	m_vInfo = glXChooseVisual(m_Win.dpy, m_Win.screen, attrListDbl);
	if (m_vInfo == NULL)
	{
#endif
		m_vInfo = glXChooseVisual(m_Win.dpy, m_Win.screen, attrListSgl);
		if (m_vInfo == NULL)
			return false;
		m_bDblBuffered = false;
		WriteLog("Mode: SingleBuffered\n");
#ifndef BENCHMARK
	}
	else
	{
		WriteLog("Mode: DoubleBuffered\n");
	}
#endif

	/* create the GL context for rendering */
	m_Win.ctx = glXCreateContext(m_Win.dpy, m_vInfo, 0, GL_TRUE);
	if (m_Win.ctx == NULL)
		return false;

	/* create the colormap */
	m_Win.attr.colormap = XCreateColormap(m_Win.dpy, RootWindow(m_Win.dpy, m_vInfo->screen),
						m_vInfo->visual, AllocNone);
	m_Win.attr.border_pixel = 0;

	/* check for direct rendering */
	if (glXIsDirect(m_Win.dpy, m_Win.ctx))
		WriteLog("Direct Rendering: true\n");
	else
		WriteLog("Direct Rendering: false\n");

	WriteLog("=====================\n");

	m_bInitialized = true;

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
bool VXWindowSystem::CreateWindow(const uint nWidth, const uint nHeight,
								bool bFullScreen/*=false*/)
{
	int					dpyWidth, dpyHeight;
	int					i;
	int					bestMode = 0;
	Atom				wmDelete;
	Window				winDummy;
	uint				borderDummy;

	m_bFullScreen = bFullScreen;

	if (!m_bInitialized)
	{
		WriteLog("CreateWindow() called with no context initialized\n");
		return false;
	}

	for (i = 0; i < m_nNumModes; i++)
	{
		if ((m_Modes[i]->hdisplay == nWidth) && (m_Modes[i]->vdisplay == nHeight))
		{
			bestMode = i;
		}
	}

	if (m_bFullScreen)
	{
		XF86VidModeSwitchToMode(m_Win.dpy, m_Win.screen, m_Modes[bestMode]);
		XF86VidModeSetViewPort(m_Win.dpy, m_Win.screen, 0, 0);
		dpyWidth = m_Modes[bestMode]->hdisplay;
		dpyHeight = m_Modes[bestMode]->vdisplay;
		m_Win.attr.override_redirect = True;
		m_Win.attr.event_mask = ExposureMask | KeyPressMask | ButtonPressMask |
								StructureNotifyMask;
		m_Win.win = XCreateWindow(m_Win.dpy, RootWindow(m_Win.dpy,
								m_vInfo->screen), 0, 0, dpyWidth, dpyHeight, 0,
								m_vInfo->depth, InputOutput, m_vInfo->visual,
								CWBorderPixel | CWColormap | CWEventMask |
								CWOverrideRedirect,	&m_Win.attr);
		XWarpPointer(m_Win.dpy, None, m_Win.win, 0, 0, 0, 0, 0, 0);
		XMapRaised(m_Win.dpy, m_Win.win);
		XGrabKeyboard(m_Win.dpy, m_Win.win, True, GrabModeAsync, GrabModeAsync,
								CurrentTime);
		XGrabPointer(m_Win.dpy, m_Win.win, True, ButtonPressMask,
				GrabModeAsync, GrabModeAsync, m_Win.win, None, CurrentTime);
	}
	else
	{
		m_Win.attr.event_mask = ExposureMask | KeyPressMask | ButtonPressMask |
								StructureNotifyMask;
		m_Win.win = XCreateWindow(m_Win.dpy, RootWindow(m_Win.dpy,
								m_vInfo->screen), 0, 0, nWidth, nHeight, 0,
								m_vInfo->depth, InputOutput, m_vInfo->visual,
								CWBorderPixel | CWColormap | CWEventMask,
								&m_Win.attr);
		wmDelete = XInternAtom(m_Win.dpy, "WM_DELETE_WINDOW", True);
		XSetWMProtocols(m_Win.dpy, m_Win.win, &wmDelete, 1);
		XSetStandardProperties(m_Win.dpy, m_Win.win, "", "", None, NULL, 0,
								NULL);
		XMapRaised(m_Win.dpy, m_Win.win);
	}

	if (!glXMakeCurrent(m_Win.dpy, m_Win.win, m_Win.ctx))
		return false;
	XGetGeometry(m_Win.dpy, m_Win.win, &winDummy, &m_Win.x, &m_Win.y,
					&m_nWidth, &m_nHeight, &borderDummy, &m_Win.depth);

	cout << "Running in " << (m_bFullScreen ? "fullscreen" : "window")
						<< " mode" << endl;
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	m_bWinCreated = true;

	return true;
}

void VXWindowSystem::DestroyWindow(void)
{
	if (m_bWinCreated)
	{
		if (!glXMakeCurrent(m_Win.dpy, None, NULL))
			WriteLog("Error changing GL context to default in DestroyWindow()\n");
		if (m_bFullScreen)
		{
			XF86VidModeSwitchToMode(m_Win.dpy, m_Win.screen, &m_Win.deskMode);
			XF86VidModeSetViewPort(m_Win.dpy, m_Win.screen, 0, 0);
		}
	}

	m_bWinCreated = false;
}

bool VXWindowSystem::Resize(const uint nWidth, const uint nHeight)
{
	if (nWidth != m_nWidth && nHeight != m_nHeight)
	{
		DestroyWindow();
		if (!CreateWindow(nWidth, nHeight, m_bFullScreen))
			return false;
	}

	return true;
}

bool VXWindowSystem::FullScreen(bool bFullScreen)
{
	if (bFullScreen != m_bFullScreen)
	{
		DestroyWindow();
		if (!CreateWindow(m_nWidth, m_nHeight, bFullScreen))
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
void VXWindowSystem::SetCaption(const char *pcCaption) const
{
	XStoreName(m_Win.dpy, m_Win.win, pcCaption);
}

void VXWindowSystem::SwapBuffers(void) const
{
	if (m_bDblBuffered)
		glXSwapBuffers(m_Win.dpy, m_Win.win);
}

bool VXWindowSystem::CaptureInput(ulong ulFlags) const
{
	XSelectInput(m_Win.dpy, m_Win.win, ulFlags);
	return true;
}

void VXWindowSystem::Update(void)
{
	XEvent xev;
	int num_events;
	bool ks = false;
	KeySym key;
	VKeyCode kc;
	VKeyEvent *event;
	_KeyMap::iterator it;

	XFlush(m_Win.dpy);
	num_events = XPending(m_Win.dpy);
	while (num_events != 0)
	{
		num_events--;
		XNextEvent(m_Win.dpy, &xev);
		switch (xev.type)
		{
			case EnterNotify:
				XAutoRepeatOff(m_Win.dpy);
				break;
			case LeaveNotify:
				XAutoRepeatOn(m_Win.dpy);
				break;
			case KeyPress:
			case KeyRelease:
				if (xev.type == KeyPress)
					ks = true;
				else
					ks = false;
				key = XLookupKeysym(&xev.xkey, 0);
				it = m_KeyMap.find(key);
				if (it != m_KeyMap.end())
				{
					kc = it->second;
					event = new VKeyEvent();
					event->action = (ks ? KEY_PRESS : KEY_RELEASE);
					event->code = kc;
					m_KeyEvents.push(event);
				}
				break;
			default:
				break;

		} /* switch() */

	} /* while() */

}

VKeyEvent* VXWindowSystem::GetEvent(void)
{
	if (m_KeyEvents.size() != 0)
	{
		VKeyEvent* evt = m_KeyEvents.front();
		m_KeyEvents.pop();
		return evt;
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
void VXWindowSystem::WriteLog(const char *pcText, ...)
{
	static char acBuffer[1024];
	va_list		args;

	memset(acBuffer, '\0', sizeof(acBuffer));

	va_start(args, pcText);
	vsprintf(acBuffer, pcText, args);
	va_end(args);
	m_Log << acBuffer;

#ifdef DEBUG
	m_Log.flush();
#endif
}
void VXWindowSystem::LoadKeyMap(void)
{
   	m_KeyMap.insert(_KeyMap::value_type(XK_Escape, KC_ESCAPE));
	m_KeyMap.insert(_KeyMap::value_type(XK_0, KC_0));
	m_KeyMap.insert(_KeyMap::value_type(XK_1, KC_1));
	m_KeyMap.insert(_KeyMap::value_type(XK_1, KC_1));
	m_KeyMap.insert(_KeyMap::value_type(XK_2, KC_2));
	m_KeyMap.insert(_KeyMap::value_type(XK_3, KC_3));
	m_KeyMap.insert(_KeyMap::value_type(XK_4, KC_4));
	m_KeyMap.insert(_KeyMap::value_type(XK_5, KC_5));
	m_KeyMap.insert(_KeyMap::value_type(XK_6, KC_6));
	m_KeyMap.insert(_KeyMap::value_type(XK_7, KC_7));
	m_KeyMap.insert(_KeyMap::value_type(XK_8, KC_8));
	m_KeyMap.insert(_KeyMap::value_type(XK_9, KC_9));
	m_KeyMap.insert(_KeyMap::value_type(XK_minus, KC_MINUS));
	m_KeyMap.insert(_KeyMap::value_type(XK_BackSpace, KC_BACK));
	m_KeyMap.insert(_KeyMap::value_type(XK_Tab, KC_TAB));
	m_KeyMap.insert(_KeyMap::value_type(XK_q, KC_Q));
	m_KeyMap.insert(_KeyMap::value_type(XK_w, KC_W));
	m_KeyMap.insert(_KeyMap::value_type(XK_e, KC_E));
	m_KeyMap.insert(_KeyMap::value_type(XK_R, KC_R));
	m_KeyMap.insert(_KeyMap::value_type(XK_t, KC_T));
	m_KeyMap.insert(_KeyMap::value_type(XK_y, KC_Y));
	m_KeyMap.insert(_KeyMap::value_type(XK_u, KC_U));
	m_KeyMap.insert(_KeyMap::value_type(XK_i, KC_I));
	m_KeyMap.insert(_KeyMap::value_type(XK_o, KC_O));
	m_KeyMap.insert(_KeyMap::value_type(XK_p, KC_P));
	m_KeyMap.insert(_KeyMap::value_type(XK_bracketleft, KC_LBRACKET));
	m_KeyMap.insert(_KeyMap::value_type(XK_Return, KC_RETURN));
	m_KeyMap.insert(_KeyMap::value_type(XK_Control_L, KC_LCONTROL));
	m_KeyMap.insert(_KeyMap::value_type(XK_a, KC_A));
	m_KeyMap.insert(_KeyMap::value_type(XK_s, KC_S));
	m_KeyMap.insert(_KeyMap::value_type(XK_d, KC_D));
	m_KeyMap.insert(_KeyMap::value_type(XK_f, KC_F));
	m_KeyMap.insert(_KeyMap::value_type(XK_g, KC_G));
	m_KeyMap.insert(_KeyMap::value_type(XK_h, KC_H));
    m_KeyMap.insert(_KeyMap::value_type(XK_j, KC_J));
	m_KeyMap.insert(_KeyMap::value_type(XK_k, KC_K));
	m_KeyMap.insert(_KeyMap::value_type(XK_l, KC_L));
	m_KeyMap.insert(_KeyMap::value_type(XK_semicolon, KC_SEMICOLON));
	m_KeyMap.insert(_KeyMap::value_type(XK_apostrophe, KC_APOSTROPHE));
	m_KeyMap.insert(_KeyMap::value_type(XK_grave, KC_GRAVE));
	m_KeyMap.insert(_KeyMap::value_type(XK_Shift_L, KC_LSHIFT));
	m_KeyMap.insert(_KeyMap::value_type(XK_backslash, KC_BACKSLASH));
	m_KeyMap.insert(_KeyMap::value_type(XK_z, KC_Z));
	m_KeyMap.insert(_KeyMap::value_type(XK_x, KC_X));
	m_KeyMap.insert(_KeyMap::value_type(XK_c, KC_C));
	m_KeyMap.insert(_KeyMap::value_type(XK_v, KC_V));
	m_KeyMap.insert(_KeyMap::value_type(XK_b, KC_B));
	m_KeyMap.insert(_KeyMap::value_type(XK_n, KC_N));
	m_KeyMap.insert(_KeyMap::value_type(XK_m, KC_M));
	m_KeyMap.insert(_KeyMap::value_type(XK_m, KC_M));
	m_KeyMap.insert(_KeyMap::value_type(XK_comma, KC_COMMA));
	m_KeyMap.insert(_KeyMap::value_type(XK_period, KC_PERIOD));
    m_KeyMap.insert(_KeyMap::value_type(XK_slash, KC_SLASH));
	m_KeyMap.insert(_KeyMap::value_type(XK_Shift_R, KC_RSHIFT));
	m_KeyMap.insert(_KeyMap::value_type(XK_KP_Multiply, KC_MULTIPLY));
    m_KeyMap.insert(_KeyMap::value_type(XK_Alt_L, KC_LMENU));
    m_KeyMap.insert(_KeyMap::value_type(XK_space, KC_SPACE));
	m_KeyMap.insert(_KeyMap::value_type(XK_F1, KC_F1));
	m_KeyMap.insert(_KeyMap::value_type(XK_F2, KC_F2));
	m_KeyMap.insert(_KeyMap::value_type(XK_F3, KC_F3));
	m_KeyMap.insert(_KeyMap::value_type(XK_F4, KC_F4));
	m_KeyMap.insert(_KeyMap::value_type(XK_F5, KC_F5));
	m_KeyMap.insert(_KeyMap::value_type(XK_F6, KC_F6));
	m_KeyMap.insert(_KeyMap::value_type(XK_F7, KC_F7));
	m_KeyMap.insert(_KeyMap::value_type(XK_F8, KC_F8));
	m_KeyMap.insert(_KeyMap::value_type(XK_F9, KC_F9));
	m_KeyMap.insert(_KeyMap::value_type(XK_F10, KC_F10));
	m_KeyMap.insert(_KeyMap::value_type(XK_F11, KC_F11));
	m_KeyMap.insert(_KeyMap::value_type(XK_F12, KC_F12));
    m_KeyMap.insert(_KeyMap::value_type(XK_Num_Lock, KC_NUMLOCK));
	m_KeyMap.insert(_KeyMap::value_type(XK_Scroll_Lock, KC_SCROLL));
	m_KeyMap.insert(_KeyMap::value_type(XK_KP_7, KC_NUMPAD7));
	m_KeyMap.insert(_KeyMap::value_type(XK_KP_8, KC_NUMPAD8));
	m_KeyMap.insert(_KeyMap::value_type(XK_KP_9, KC_NUMPAD9));
	m_KeyMap.insert(_KeyMap::value_type(XK_KP_Subtract, KC_SUBTRACT));
	m_KeyMap.insert(_KeyMap::value_type(XK_KP_4, KC_NUMPAD4));
	m_KeyMap.insert(_KeyMap::value_type(XK_KP_5, KC_NUMPAD5));
	m_KeyMap.insert(_KeyMap::value_type(XK_KP_6, KC_NUMPAD6));
	m_KeyMap.insert(_KeyMap::value_type(XK_KP_Add, KC_ADD));
	m_KeyMap.insert(_KeyMap::value_type(XK_KP_1, KC_NUMPAD1));
	m_KeyMap.insert(_KeyMap::value_type(XK_KP_2, KC_NUMPAD2));
	m_KeyMap.insert(_KeyMap::value_type(XK_KP_3, KC_NUMPAD3));
	m_KeyMap.insert(_KeyMap::value_type(XK_KP_0, KC_NUMPAD0));
	m_KeyMap.insert(_KeyMap::value_type(XK_KP_Decimal, KC_DECIMAL));
	m_KeyMap.insert(_KeyMap::value_type(XK_KP_Enter, KC_NUMPADENTER));
	m_KeyMap.insert(_KeyMap::value_type(XK_Control_R, KC_RCONTROL));
	m_KeyMap.insert(_KeyMap::value_type(XK_KP_Divide, KC_DIVIDE));
	m_KeyMap.insert(_KeyMap::value_type(XK_Sys_Req, KC_SYSRQ));
	m_KeyMap.insert(_KeyMap::value_type(XK_Alt_R, KC_RMENU));
	m_KeyMap.insert(_KeyMap::value_type(XK_Pause, KC_PAUSE));
	m_KeyMap.insert(_KeyMap::value_type(XK_Home, KC_HOME));
	m_KeyMap.insert(_KeyMap::value_type(XK_Up, KC_UP));
	m_KeyMap.insert(_KeyMap::value_type(XK_Page_Up, KC_PGUP));
	m_KeyMap.insert(_KeyMap::value_type(XK_Left, KC_LEFT));
	m_KeyMap.insert(_KeyMap::value_type(XK_Right, KC_RIGHT));
	m_KeyMap.insert(_KeyMap::value_type(XK_End, KC_END));
	m_KeyMap.insert(_KeyMap::value_type(XK_Down, KC_DOWN));
	m_KeyMap.insert(_KeyMap::value_type(XK_Page_Down, KC_PGDOWN));
	m_KeyMap.insert(_KeyMap::value_type(XK_Insert, KC_INSERT));
	m_KeyMap.insert(_KeyMap::value_type(XK_Delete, KC_DELETE));
}

} // End Namespace

