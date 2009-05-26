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
#include <viper3d/Input.h>

/* System Headers */

/* Local Headers */
#include <viper3d/util/Log.h>

namespace UDP
{

static char __CLASS__[] = "[    VInput    ]";

/********************************************************************
 *          C O N S T R U C T I O N / D E S T R U C T I O N         *
 ********************************************************************/
VInput::VInput(void)
{
	mMouseState.mXabs = 0;
	mMouseState.mYabs = 0;
	mMouseState.mXrel = 0;
	mMouseState.mYrel = 0;
	mMouseState.mXdelta = 0;
	mMouseState.mYdelta = 0;
}

VInput::~VInput(void)
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

