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
#if !defined(__OGLRENDERSYSTEM_H_INCLUDED__)
#define __OGLRENDERSYSTEM_H_INCLUDED__

/* System Headers */

/* Local Headers */
#include <viper3d/RenderSystem.h>

namespace UDP
{

/**
 *	@class		VOGLRenderSystem
 *
 *	@brief		Abstract interface for the platform specific renderers.
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		2004-Aug-31
 *	@remarks	All of the specific render devices (OpenGL, DirectX, etc) will
 *				derive from this base class.
 */
class VOGLRenderSystem : public VRenderSystem
{
public:
	/*==================================*
	 *	   CONSTRUCTION/DESTRUCTION		*
	 *==================================*/
	VOGLRenderSystem(void);
	virtual ~VOGLRenderSystem(void);

	/*==================================*
	 *	        INITIALIZATION			*
	 *==================================*/
	bool			Init(void);

	/*==================================*
	 *	           CLEANUP    			*
	 *==================================*/
	void			Shutdown(void);

	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/

	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	VWindow*		CreateWindow(VWindowOpts *pOpts);
	void			DestroyWindow(VWindow *pWin);
	bool			Render(VWindow *pWin, VCamera *pCamera);

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
	
};

} // End Namespace

#endif // __VRENDERSYSTEM_H_INCLUDED__

