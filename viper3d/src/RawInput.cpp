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
#include <viper3d/RawInput.h>

/* System Headers */
#if VIPER_PLATFORM == PLATFORM_WINDOWS
#elif VIPER_PLATFORM == PLATFORM_MAC
#elif VIPER_PLATFORM == PLATFORM_LINUX
#include <X11/keysym.h>
#endif
#include <viper3d/Window.h>
#include <viper3d/util/Log.h>

/* Local Headers */

namespace UDP
{

static char __CLASS__[] = "[  VRawInput   ]";

/********************************************************************
 *          C O N S T R U C T I O N / D E S T R U C T I O N         *
 ********************************************************************/
VRawInput::VRawInput(void)
	: mWin(NULL)
{
	LoadKeyMap();

}

VRawInput::~VRawInput(void)
{

}

/********************************************************************
 *                        A T T R I B U T E S                       *
 ********************************************************************/
/********************************************************************
 *                        O P E R A T I O N S                       *
 ********************************************************************/
bool VRawInput::StartCapture(VWindow *pWin)
{
	mWin = pWin;

	if (mWin->IsFullScreen())
	{
#if VIPER_PLATFORM == PLATFORM_WINDOWS
#elif VIPER_PLATFORM == PLATFORM_MAC
#elif VIPER_PLATFORM == PLATFORM_LINUX
		XWarpPointer(mWin->mDpy, None, mWin->mWin, 0, 0, 0, 0, 0, 0);
		XGrabKeyboard(mWin->mDpy, mWin->mWin, True, GrabModeAsync, GrabModeAsync, CurrentTime);
		XGrabPointer(mWin->mDpy, mWin->mWin, True, ButtonPressMask, GrabModeAsync,
			GrabModeAsync, mWin->mWin, None, CurrentTime);
#endif
	}
	else
	{
#if VIPER_PLATFORM == PLATFORM_WINDOWS
#elif VIPER_PLATFORM == PLATFORM_MAC
#elif VIPER_PLATFORM == PLATFORM_LINUX
		VULONG vFlags = ButtonPressMask | KeyPressMask | KeyReleaseMask | EnterWindowMask | LeaveWindowMask;
		XSelectInput(mWin->mDpy, mWin->mWin, vFlags);	
#endif
	}
	return true;
}

bool VRawInput::EndCapture(void)
{
#if VIPER_PLATFORM == PLATFORM_WINDOWS
#elif VIPER_PLATFORM == PLATFORM_MAC
#elif VIPER_PLATFORM == PLATFORM_LINUX
	XAutoRepeatOn(mWin->mDpy);
#endif
}

bool VRawInput::Update(void)
{
#if VIPER_PLATFORM == PLATFORM_WINDOWS
#elif VIPER_PLATFORM == PLATFORM_MAC
#elif VIPER_PLATFORM == PLATFORM_LINUX
	XEvent					vXev;
	int						vNumEvents;
	KeySym					vKey;
	VKeyCode				vKc;
	VKeyEvent				*vEvent;
	VKeyMap::iterator		vIt;
	long					x, y;

	mMouseState.mXdelta = 0;
	mMouseState.mYdelta = 0;

	XFlush(mWin->mDpy);
	vNumEvents = XPending(mWin->mDpy);
	while (vNumEvents != 0)
	{
		vNumEvents--;
		XNextEvent(mWin->mDpy, &vXev);
		switch (vXev.type)
		{
			case EnterNotify:
				XAutoRepeatOff(mWin->mDpy);
				XGrabPointer(mWin->mDpy, mWin->mWin, true, PointerMotionMask, GrabModeAsync, GrabModeAsync, mWin->mWin, None, CurrentTime);
				break;
			case LeaveNotify:
				XAutoRepeatOn(mWin->mDpy);
				XUngrabPointer(mWin->mDpy, CurrentTime);
				break;
			case KeyPress:
			case KeyRelease:
				vKey = XLookupKeysym(&vXev.xkey, 0);
				vIt = mKeyMap.find(vKey);
				if (vIt != mKeyMap.end())
				{
					vKc = vIt->second;
					mKeyStates[vKc] = (vXev.type == KeyPress);
				}
				break;
			case MotionNotify:
				x = vXev.xmotion.x;
				y = vXev.xmotion.y;
				if (mMouseState.mXabs == -1)
					mMouseState.mXabs = x;
				else
				{
					mMouseState.mXdelta = x - mMouseState.mXabs;
					mMouseState.mXabs = x;
				}
				if (mMouseState.mYabs == -1)
					mMouseState.mYabs = y;
				else
				{
					mMouseState.mYdelta = y - mMouseState.mYabs;
					mMouseState.mYabs = y;
				}
				break;
			default:
				break;
		}
	}

#endif
	return true;
}
/********************************************************************
 *                         C A L L B A C K S                        *
 ********************************************************************/

/********************************************************************
 *                         I N T E R N A L S                        *
 ********************************************************************/
void VRawInput::LoadKeyMap(void)
{
#if VIPER_PLATFORM == PLATFORM_WINDOWS
#elif VIPER_PLATFORM == PLATFORM_MAC
#elif VIPER_PLATFORM == PLATFORM_LINUX
   	mKeyMap.insert(VKeyMap::value_type(XK_Escape, KC_ESCAPE));
	mKeyMap.insert(VKeyMap::value_type(XK_0, KC_0));
	mKeyMap.insert(VKeyMap::value_type(XK_1, KC_1));
	mKeyMap.insert(VKeyMap::value_type(XK_1, KC_1));
	mKeyMap.insert(VKeyMap::value_type(XK_2, KC_2));
	mKeyMap.insert(VKeyMap::value_type(XK_3, KC_3));
	mKeyMap.insert(VKeyMap::value_type(XK_4, KC_4));
	mKeyMap.insert(VKeyMap::value_type(XK_5, KC_5));
	mKeyMap.insert(VKeyMap::value_type(XK_6, KC_6));
	mKeyMap.insert(VKeyMap::value_type(XK_7, KC_7));
	mKeyMap.insert(VKeyMap::value_type(XK_8, KC_8));
	mKeyMap.insert(VKeyMap::value_type(XK_9, KC_9));
	mKeyMap.insert(VKeyMap::value_type(XK_minus, KC_MINUS));
	mKeyMap.insert(VKeyMap::value_type(XK_BackSpace, KC_BACK));
	mKeyMap.insert(VKeyMap::value_type(XK_Tab, KC_TAB));
	mKeyMap.insert(VKeyMap::value_type(XK_q, KC_Q));
	mKeyMap.insert(VKeyMap::value_type(XK_w, KC_W));
	mKeyMap.insert(VKeyMap::value_type(XK_e, KC_E));
	mKeyMap.insert(VKeyMap::value_type(XK_R, KC_R));
	mKeyMap.insert(VKeyMap::value_type(XK_t, KC_T));
	mKeyMap.insert(VKeyMap::value_type(XK_y, KC_Y));
	mKeyMap.insert(VKeyMap::value_type(XK_u, KC_U));
	mKeyMap.insert(VKeyMap::value_type(XK_i, KC_I));
	mKeyMap.insert(VKeyMap::value_type(XK_o, KC_O));
	mKeyMap.insert(VKeyMap::value_type(XK_p, KC_P));
	mKeyMap.insert(VKeyMap::value_type(XK_bracketleft, KC_LBRACKET));
	mKeyMap.insert(VKeyMap::value_type(XK_Return, KC_RETURN));
	mKeyMap.insert(VKeyMap::value_type(XK_Control_L, KC_LCONTROL));
	mKeyMap.insert(VKeyMap::value_type(XK_a, KC_A));
	mKeyMap.insert(VKeyMap::value_type(XK_s, KC_S));
	mKeyMap.insert(VKeyMap::value_type(XK_d, KC_D));
	mKeyMap.insert(VKeyMap::value_type(XK_f, KC_F));
	mKeyMap.insert(VKeyMap::value_type(XK_g, KC_G));
	mKeyMap.insert(VKeyMap::value_type(XK_h, KC_H));
    mKeyMap.insert(VKeyMap::value_type(XK_j, KC_J));
	mKeyMap.insert(VKeyMap::value_type(XK_k, KC_K));
	mKeyMap.insert(VKeyMap::value_type(XK_l, KC_L));
	mKeyMap.insert(VKeyMap::value_type(XK_semicolon, KC_SEMICOLON));
	mKeyMap.insert(VKeyMap::value_type(XK_apostrophe, KC_APOSTROPHE));
	mKeyMap.insert(VKeyMap::value_type(XK_grave, KC_GRAVE));
	mKeyMap.insert(VKeyMap::value_type(XK_Shift_L, KC_LSHIFT));
	mKeyMap.insert(VKeyMap::value_type(XK_backslash, KC_BACKSLASH));
	mKeyMap.insert(VKeyMap::value_type(XK_z, KC_Z));
	mKeyMap.insert(VKeyMap::value_type(XK_x, KC_X));
	mKeyMap.insert(VKeyMap::value_type(XK_c, KC_C));
	mKeyMap.insert(VKeyMap::value_type(XK_v, KC_V));
	mKeyMap.insert(VKeyMap::value_type(XK_b, KC_B));
	mKeyMap.insert(VKeyMap::value_type(XK_n, KC_N));
	mKeyMap.insert(VKeyMap::value_type(XK_m, KC_M));
	mKeyMap.insert(VKeyMap::value_type(XK_m, KC_M));
	mKeyMap.insert(VKeyMap::value_type(XK_comma, KC_COMMA));
	mKeyMap.insert(VKeyMap::value_type(XK_period, KC_PERIOD));
    mKeyMap.insert(VKeyMap::value_type(XK_slash, KC_SLASH));
	mKeyMap.insert(VKeyMap::value_type(XK_Shift_R, KC_RSHIFT));
	mKeyMap.insert(VKeyMap::value_type(XK_KP_Multiply, KC_MULTIPLY));
    mKeyMap.insert(VKeyMap::value_type(XK_Alt_L, KC_LMENU));
    mKeyMap.insert(VKeyMap::value_type(XK_space, KC_SPACE));
	mKeyMap.insert(VKeyMap::value_type(XK_F1, KC_F1));
	mKeyMap.insert(VKeyMap::value_type(XK_F2, KC_F2));
	mKeyMap.insert(VKeyMap::value_type(XK_F3, KC_F3));
	mKeyMap.insert(VKeyMap::value_type(XK_F4, KC_F4));
	mKeyMap.insert(VKeyMap::value_type(XK_F5, KC_F5));
	mKeyMap.insert(VKeyMap::value_type(XK_F6, KC_F6));
	mKeyMap.insert(VKeyMap::value_type(XK_F7, KC_F7));
	mKeyMap.insert(VKeyMap::value_type(XK_F8, KC_F8));
	mKeyMap.insert(VKeyMap::value_type(XK_F9, KC_F9));
	mKeyMap.insert(VKeyMap::value_type(XK_F10, KC_F10));
	mKeyMap.insert(VKeyMap::value_type(XK_F11, KC_F11));
	mKeyMap.insert(VKeyMap::value_type(XK_F12, KC_F12));
    mKeyMap.insert(VKeyMap::value_type(XK_Num_Lock, KC_NUMLOCK));
	mKeyMap.insert(VKeyMap::value_type(XK_Scroll_Lock, KC_SCROLL));
	mKeyMap.insert(VKeyMap::value_type(XK_KP_7, KC_NUMPAD7));
	mKeyMap.insert(VKeyMap::value_type(XK_KP_8, KC_NUMPAD8));
	mKeyMap.insert(VKeyMap::value_type(XK_KP_9, KC_NUMPAD9));
	mKeyMap.insert(VKeyMap::value_type(XK_KP_Subtract, KC_SUBTRACT));
	mKeyMap.insert(VKeyMap::value_type(XK_KP_4, KC_NUMPAD4));
	mKeyMap.insert(VKeyMap::value_type(XK_KP_5, KC_NUMPAD5));
	mKeyMap.insert(VKeyMap::value_type(XK_KP_6, KC_NUMPAD6));
	mKeyMap.insert(VKeyMap::value_type(XK_KP_Add, KC_ADD));
	mKeyMap.insert(VKeyMap::value_type(XK_KP_1, KC_NUMPAD1));
	mKeyMap.insert(VKeyMap::value_type(XK_KP_2, KC_NUMPAD2));
	mKeyMap.insert(VKeyMap::value_type(XK_KP_3, KC_NUMPAD3));
	mKeyMap.insert(VKeyMap::value_type(XK_KP_0, KC_NUMPAD0));
	mKeyMap.insert(VKeyMap::value_type(XK_KP_Decimal, KC_DECIMAL));
	mKeyMap.insert(VKeyMap::value_type(XK_KP_Enter, KC_NUMPADENTER));
	mKeyMap.insert(VKeyMap::value_type(XK_Control_R, KC_RCONTROL));
	mKeyMap.insert(VKeyMap::value_type(XK_KP_Divide, KC_DIVIDE));
	mKeyMap.insert(VKeyMap::value_type(XK_Sys_Req, KC_SYSRQ));
	mKeyMap.insert(VKeyMap::value_type(XK_Alt_R, KC_RMENU));
	mKeyMap.insert(VKeyMap::value_type(XK_Pause, KC_PAUSE));
	mKeyMap.insert(VKeyMap::value_type(XK_Home, KC_HOME));
	mKeyMap.insert(VKeyMap::value_type(XK_Up, KC_UP));
	mKeyMap.insert(VKeyMap::value_type(XK_Page_Up, KC_PGUP));
	mKeyMap.insert(VKeyMap::value_type(XK_Left, KC_LEFT));
	mKeyMap.insert(VKeyMap::value_type(XK_Right, KC_RIGHT));
	mKeyMap.insert(VKeyMap::value_type(XK_End, KC_END));
	mKeyMap.insert(VKeyMap::value_type(XK_Down, KC_DOWN));
	mKeyMap.insert(VKeyMap::value_type(XK_Page_Down, KC_PGDOWN));
	mKeyMap.insert(VKeyMap::value_type(XK_Insert, KC_INSERT));
	mKeyMap.insert(VKeyMap::value_type(XK_Delete, KC_DELETE));
#endif
}

} // End Namespace

