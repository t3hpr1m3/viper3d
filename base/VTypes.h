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
#if !defined(__VTYPES_H_INCLUDED__)
#define __VTYPES_H_INCLUDED__

#if VIPER_PLATFORM == PLATFORM_WINDOWS
typedef unsigned __int64		ulonglong;
#elif VIPER_PLATFORM == PLATFORM_APPLE
#elif VIPER_PLATFORM == PLATFORM_LINUX
typedef unsigned short			ushort;
typedef unsigned int			uint;
typedef unsigned long			ulong;
typedef unsigned char			byte;
#endif

namespace UDP
{

enum VInputEvents
{
	KEY_PRESS = 1,
	KEY_RELEASE,
	MOUSE1_PRESS,
	MOUSE2_PRESS,
	MOUSE3_PRESS,
	MOUSE4_PRESS,
	MOUSE5_PRESS,
	MOUSE1_RELEASE,
	MOUSE2_RELEASE,
	MOUSE3_RELEASE,
	MOUSE4_RELEASE,
	MOUSE5_RELEASE
};

enum VKeyCode
{
	KC_ESCAPE          = 0x01,
	KC_0               = 0x02,
	KC_1               = 0x03,
	KC_2               = 0x04,
	KC_3               = 0x05,
	KC_4               = 0x06,
	KC_5               = 0x07,
	KC_6               = 0x08,
	KC_7               = 0x09,
	KC_8               = 0x0A,
	KC_9               = 0x0B,
	KC_MINUS           = 0x0C,
	KC_EQUALS          = 0x0D,
	KC_BACK            = 0x0E,
	KC_TAB             = 0x0F,
	KC_Q               = 0x10,
	KC_W               = 0x11,
	KC_E               = 0x12,
	KC_R               = 0x13,
	KC_T               = 0x14,
	KC_Y               = 0x15,
	KC_U               = 0x16,
	KC_I               = 0x17,
	KC_O               = 0x18,
	KC_P               = 0x19,
	KC_LBRACKET        = 0x1A,
	KC_RBRACKET        = 0x1B,
	KC_RETURN          = 0x1C,
	KC_LCONTROL        = 0x1D,
	KC_A               = 0x1E,
	KC_S               = 0x1F,
	KC_D               = 0x20,
	KC_F               = 0x21,
	KC_G               = 0x22,
	KC_H               = 0x23,
	KC_J               = 0x24,
	KC_K               = 0x25,
	KC_L               = 0x26,
	KC_SEMICOLON       = 0x27,
	KC_APOSTROPHE      = 0x28,
	KC_GRAVE           = 0x29,
	KC_LSHIFT          = 0x2A,
	KC_BACKSLASH       = 0x2B,
	KC_Z               = 0x2C,
	KC_X               = 0x2D,
	KC_C               = 0x2E,
	KC_V               = 0x2F,
	KC_B               = 0x30,
	KC_N               = 0x31,
	KC_M               = 0x32,
	KC_COMMA           = 0x33,
	KC_PERIOD          = 0x34,
	KC_SLASH           = 0x35,
	KC_RSHIFT          = 0x36,
	KC_MULTIPLY        = 0x37,
	KC_LMENU           = 0x38,
	KC_SPACE           = 0x39,
	KC_F1              = 0x3A,
	KC_F2              = 0x3B,
	KC_F3              = 0x3C,
	KC_F4              = 0x3D,
	KC_F5              = 0x3E,
	KC_F6              = 0x3F,
	KC_F7              = 0x40,
	KC_F8              = 0x41,
	KC_F9              = 0x42,
	KC_F10             = 0x43,
	KC_NUMLOCK         = 0x44,
	KC_SCROLL          = 0x45,
	KC_NUMPAD7         = 0x46,
	KC_NUMPAD8         = 0x47,
	KC_NUMPAD9         = 0x48,
	KC_SUBTRACT        = 0x49,
	KC_NUMPAD4         = 0x4A,
	KC_NUMPAD5         = 0x4B,
	KC_NUMPAD6         = 0x4C,
	KC_ADD             = 0x4D,
	KC_NUMPAD1         = 0x4E,
	KC_NUMPAD2         = 0x4F,
	KC_NUMPAD3         = 0x50,
	KC_NUMPAD0         = 0x51,
	KC_DECIMAL         = 0x52,
	KC_F11             = 0x53,
	KC_F12             = 0x54,
	KC_NUMPADENTER     = 0x55,
	KC_RCONTROL        = 0x56,
	KC_DIVIDE          = 0x57,
	KC_SYSRQ           = 0x58,
	KC_RMENU           = 0x59,
	KC_PAUSE           = 0x5A,
	KC_HOME            = 0x5B,
	KC_UP              = 0x5C,
	KC_PGUP            = 0x5D,
	KC_LEFT            = 0x5E,
	KC_RIGHT           = 0x5F,
	KC_END             = 0x60,
	KC_DOWN            = 0x61,
	KC_PGDOWN          = 0x62,
	KC_INSERT          = 0x63,
	KC_DELETE          = 0x64	
};

class VKeyEvent
{
public:
	int			mAction;
	VKeyCode	mCode;
};

} // End Namespace

#endif
