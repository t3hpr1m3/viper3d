/*============================================================================*
 *                                                                            *
 *	This file is part of the Zoto Software Suite.  							  *
 *																			  *
 *	Copyright (C) 2004 Zoto, Inc.  123 South Hudson, OKC, OK  73102			  *
 *																			  *
 *  This program is free software; you can redistribute it and/or modify      *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation; either version 2 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  This program is distributed in the hope that it will be useful,           *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with this program; if not, write to the Free Software               *
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA *
 *                                                                            *
 *============================================================================*
 *                                  CHANGELOG                                 *
 *   Date       Description                                    Author         *
 * -----------  ---------------------------------------------  -------------- *
 *                                                                            *
 *============================================================================*/
#include "Viper3D.h"

/* System Headers */

/* Local Headers */
#include "VLog.h"

/* Macros */

namespace UDP
{

/* Static Variables */
static char __CLASS__[] = "[   Viper3D    ]";

/********************************************************************
 *																	*
 *          C O N S T R U C T I O N / D E S T R U C T I O N         *
 *																	*
 ********************************************************************/
Viper3D::Viper3D()
{

}

Viper3D::~Viper3D()
{
	mInput.Release();
	mWindow.Release();
}

/********************************************************************
 *																	*
 *                        A T T R I B U T E S                       *
 *																	*
 ********************************************************************/

/********************************************************************
 *																	*
 *                        O P E R A T I O N S                       *
 *																	*
 ********************************************************************/
bool Viper3D::Create()
{
	if (!mWindow.CreateDevice("X"))
	{
		VTRACE(_CL("Unable to create window device\n"));
		return false;
	}

	if (!mWindow.GetDevice()->Initialize())
	{
		VTRACE(_CL("UNable to initialize window\n"));
		return false;
	}

	if (!mWindow.GetDevice()->CreateWindow(800, 600, false))
	{
		VTRACE(_CL("Unable to create window\n"));
		return false;
	}

	if (!mInput.CreateDevice("X"))
	{
		VTRACE(_CL("Unable to create input device\n"));
		return false;
	}

	if (!mInput.GetDevice()->Initialize(mWindow.GetDevice()))
	{
		VTRACE(_CL("Unable to initialize input\n"));
		return false;
	}

	return true;
}


/********************************************************************
 *																	*
 *                          O P E R A T O R S                       *
 *																	*
 ********************************************************************/

/********************************************************************
 *																	*
 *                          C A L L B A C K S                       *
 *																	*
 ********************************************************************/

/********************************************************************
 *																	*
 *                          I N T E R N A L S                       *
 *																	*
 ********************************************************************/

} // End Namespace

/* vi: set ts=4: */
