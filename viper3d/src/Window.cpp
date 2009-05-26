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
#include <viper3d/Window.h>

/* System Headers */

/* Local Headers */
#include <viper3d/RenderSystem.h>

namespace UDP
{

static char __CLASS__[] = "[   VWindow    ]";

/********************************************************************
 *          C O N S T R U C T I O N / D E S T R U C T I O N         *
 ********************************************************************/
VWindow::VWindow()
#if VIPER_PLATFORM == PLATFORM_WINDOWS
	: mWin(NULL)
#elif VIPER_PLATFORM == PLATFORM_MAC
#elif VIPER_PLATFORM == PLATFORM_LINUX
	: mDpy(NULL), mScreen(0), mWin(-1)
#endif
{
	mOpts.mFullScreen	= false;
	mOpts.mWidth		= 0;
	mOpts.mHeight		= 0;
}

VWindow::~VWindow(void)
{
}

/********************************************************************
 *                        A T T R I B U T E S                       *
 ********************************************************************/

/********************************************************************
 *                        O P E R A T I O N S                       *
 ********************************************************************/

/********************************************************************
 *                         C A L L B A C K S                        *
 ********************************************************************/

/********************************************************************
 *                         I N T E R N A L S                        *
 ********************************************************************/

} // End Namespace
