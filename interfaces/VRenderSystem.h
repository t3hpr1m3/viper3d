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
#if !defined(__VRENDERSYSTEM_H_INCLUDED__)
#define __VRENDERSYSTEM_H_INCLUDED__

/* System Headers */

/* Local Headers */

namespace UDP
{

/**
 *	@class		VRenderSystem
 *
 *	@brief		Abstract interface for the platform specific renderers.
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		2004-Aug-31
 *	@remarks	All of the specific render devices (OpenGL, DirectX, etc) will
 *				derive from this base class.
 */
class VRenderSystem
{
public:
	/*==================================*
	 *	   CONSTRUCTION/DESTRUCTION		*
	 *==================================*/
	VRenderSystem(void) {};
	virtual ~VRenderSystem(void) {};

	/*==================================*
	 *	        INITIALIZATION			*
	 *==================================*/
	virtual bool	Init(VWindowSystem *pWin, bool pSaveLog) = 0;

	/*==================================*
	 *	           CLEANUP    			*
	 *==================================*/
	virtual void	Release(void) = 0;

	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/
	virtual void	IsRunning(void) = 0;

	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	virtual bool	UseWindow(VWindowSystem *pWin) = 0;
	virtual bool	BeginRendering(bool pClearPixel, bool pClearDepth,
							bool pClearStencil) = 0;
	virtual void	EndRendering(void) = 0;
	virtual bool	Clear(bool pClearPixel, bool pClearDepth,
							bool pClearStencil) = 0;
	virtual void	SetClearColor(float pRed, float pGreen,
							float pBlue) = 0;

protected:
	/*==================================*
	 *             CALLBACKS			*
	 *==================================*/

private:
	/*==================================*
	 *             INTERNALS            *
	 *==================================*/


private:
	/*==================================*
	 *             VARIABLES            *
	 *==================================*/
	VWindowSystem			*mWindow;
	ulong					mWidth;
	ulong					mHeight;
	bool					mWindowed;
	bool					mRunning;
};

} // End Namespace

#endif // __VRENDERSYSTEM_H_INCLUDED__

