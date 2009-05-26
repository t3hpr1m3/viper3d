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
#if !defined(__RENDERSYSTEM_H_INCLUDED__)
#define __RENDERSYSTEM_H_INCLUDED__

/* System Headers */
#include <viper3d/Viper3D.h>
#include <viper3d/Window.h>
#include <viper3d/Camera.h>
#if VIPER_PLATFORM == PLATFORM_WINDOWS
#elif VIPER_PLATFORM == PLATFORM_MAC
#elif VIPER_PLATFORM == PLATFORM_LINUX
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/xf86vmode.h>
#endif
#include <vector>

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
	friend class VOGLWindow;
public:
	/*==================================*
	 *	   CONSTRUCTION/DESTRUCTION		*
	 *==================================*/
	VRenderSystem(void);
	virtual ~VRenderSystem(void);

	/*==================================*
	 *	        INITIALIZATION			*
	 *==================================*/
	virtual bool			Init(void) = 0;

	/*==================================*
	 *	           CLEANUP    			*
	 *==================================*/
	virtual void			Shutdown(void) = 0;

	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/

	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	virtual VWindow *		CreateWindow(VWindowOpts *pOpts) = 0;
	virtual void			DestroyWindow(VWindow *pWin) = 0;
	virtual bool			Render(VWindow *pWin, VCamera *pCamera) = 0;

protected:
	/*==================================*
	 *             CALLBACKS			*
	 *==================================*/

private:
	/*==================================*
	 *             INTERNALS            *
	 *==================================*/


protected:
	/*==================================*
	 *             VARIABLES            *
	 *==================================*/
	std::vector<VWindow*>	mWindows;
	bool					mDblBuffered;
#if VIPER_PLATFORM == PLATFORM_WINDOWS
#elif VIPER_PLATFORM == PLATFORM_MAC
#elif VIPER_PLATFORM == PLATFORM_LINUX
	Display					*mDpy;
	int						mScreen;
	XF86VidModeModeInfo		**mModes;
	int						mNumModes;
	XVisualInfo				*mVInfo;
#endif
};

class DLL_RENDERCREATE
{
public:
	virtual ~DLL_RENDERCREATE(){}
	virtual void operator()(VRenderSystem **pRender){}
};
class DLL_RENDERDESTROY
{
public:
	virtual ~DLL_RENDERDESTROY(){}
	virtual void operator()(VRenderSystem *pRender){}
};

} // End Namespace

#endif // __VRENDERSYSTEM_H_INCLUDED__

