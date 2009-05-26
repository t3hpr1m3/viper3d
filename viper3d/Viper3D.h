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
#if !defined(__VIPER3D_H_INCLUDED__)
#define __VIPER3D_H_INCLUDED__

/* System Headers */

/* Local Headers */
#include <viper3d/Globals.h>
#include <viper3d/util/DynamicLib.h>

/* Macros */

namespace UDP
{

class VRenderSystem;

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
	VRenderSystem*		CreateRenderer(char *pAPI);
	void				DestroyRenderer();
	 /*
	bool				Create(int pWidth = 800, int pHeight = 600, bool pFullScreen = false);
	void				MainLoop();
	*/

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
	 /*
	VCamera*			CreateCamera(const VVector &pPos = VVector::VECTOR_ZERO,
										const VVector &pDir = VVector::VECTOR_UNIT_Z);
	*/

private:
	/*==================================*
	 *             VARIABLES            *
	 *==================================*/
	VDynamicLib			mRenderLib;
	VRenderSystem		*mRenderer;
	 /*
	VInput				*mInput;
	VWindow				*mWindow;
	VCamera				*mCamera;
	*/
};



/********************************************************************
 *																	*
 *							I N L I N E S							*
 *																	*
 ********************************************************************/

} // End Namespace

#endif // __VIPER3D_H_INCLUDED__

/* vi: set ts=4: */
