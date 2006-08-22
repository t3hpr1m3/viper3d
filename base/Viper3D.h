/*============================================================================*
 *                                                                            *
 *	This file is part of the Zoto Software Suite.  							  *
 *																			  *
 *	Copyright (C) 2004, 2005 Zoto, Inc.  123 South Hudson, OKC, OK  73102	  *
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
#if !defined(__VIPER3D_H_INCLUDED__)
#define __VIPER3D_H_INCLUDED__

/* System Headers */

/* Local Headers */
#include "VInput.h"
#include "VWindow.h"
#include "VCamera.h"

/* Macros */

namespace UDP
{

/**
 *  @class     	Viper3D
 *  @brief      Big Dawg.  This is the man.
 *  @author     Josh Williams (V-Man@udpviper.com)
 *  @version    0.1.0
 *  @date		21-Aug-2006
 */
class Viper3D
{
public:
	/*==================================*
	 *	   CONSTRUCTION/DESTRUCTION		*
	 *==================================*/
	Viper3D();
	virtual ~Viper3D();

public:
	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/

public:
	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	bool				Create(int pWidth = 800, int pHeight = 600, bool pFullScreen = false);
	void				MainLoop();

public:
	/*==================================*
	 *			   OPERATORS			*
	 *==================================*/

protected:
	/*==================================*
	 *			   CALLBACKS			*
	 *==================================*/

private:
	/*==================================*
	 *			   INTERNALS			*
	 *==================================*/
	VCamera*			CreateCamera(const VVector &pPos = VVector::VECTOR_ZERO,
										const VVector &pDir = VVector::VECTOR_UNIT_Z);

private:
	/*==================================*
	 *             VARIABLES            *
	 *==================================*/
	VInput				*mInput;
	VWindow				*mWindow;
	VCamera				*mCamera;
};



/********************************************************************
 *																	*
 *							I N L I N E S							*
 *																	*
 ********************************************************************/

} // End Namespace

#endif // __VIPER3D_H_INCLUDED__

/* vi: set ts=4: */
