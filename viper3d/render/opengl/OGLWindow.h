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
#if !defined(__OGLWINDOW_H_INCLUDED__)
#define __OGLWINDOW_H_INCLUDED__

/* System Headers */
#include <GL/gl.h>
#include <GL/glx.h>

/* Local Headers */
#include <viper3d/Window.h>

namespace UDP
{

/**
 *	@class		VOLWindow
 *
 *	@brief		OpenGL specific window handle.
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		2004-Sep-02
 */
class VOGLWindow : public VWindow
{
public:
	/*==================================*
	 *	   CONSTRUCTION/DESTRUCTION		*
	 *==================================*/
	VOGLWindow();
	virtual ~VOGLWindow();

	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/

	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	bool				Create(VWindowOpts *pOpts);
	void				Destroy(void);
	bool				Resize(VWindowOpts *pOpts);
	void				SetCaption(const char *pCaption);
	bool				SwapBuffers(void) const;

protected:
	/*==================================*
	 *             CALLBACKS			*
	 *==================================*/

private:
	/*==================================*
	 *             INTERNALS            *
	 *==================================*/


public:
	/*==================================*
	 *             VARIABLES            *
	 *==================================*/
#if VIPER_PLATFORM == PLATFORM_WINDOWS
	HGLRC				mCtx;
#elif VIPER_PLATFORM == PLATFORM_MAC
#elif VIPER_PLATFORM == PLATFORM_LINUX
	GLXContext			mCtx;
#endif
};

} // End Namespace

#endif // __OGLWINDOW_H_INCLUDED__

