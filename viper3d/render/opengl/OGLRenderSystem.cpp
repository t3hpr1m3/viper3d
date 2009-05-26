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
#include "OGLRenderSystem.h"

/* System Headers */
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <viper3d/util/Log.h>

/* Local Headers */
#include "OGLWindow.h"

/* Macros */

namespace UDP
{

class DLL_RENDERCREATE_IMPL : public DLL_RENDERCREATE
{
public:
	void operator()(VRenderSystem **pRender)
	{
		*pRender = dynamic_cast<VRenderSystem*>(new VOGLRenderSystem());
	}
};

class DLL_RENDERDESTROY_IMPL : public DLL_RENDERDESTROY
{
public:
	void operator()(VRenderSystem *pRender)
	{
		delete dynamic_cast<VRenderSystem*>(pRender);
	}
};

/* creation functions */
extern "C" {
_ViperExport
DLL_RENDERCREATE_IMPL Construct;
_ViperExport
DLL_RENDERDESTROY_IMPL Destruct;
} // extern "C"
		

/* Static Variables */
static char __CLASS__[] = "[   Viper3D    ]";

/********************************************************************
 *																	*
 *          C O N S T R U C T I O N / D E S T R U C T I O N         *
 *																	*
 ********************************************************************/
VOGLRenderSystem::VOGLRenderSystem()
{
}

VOGLRenderSystem::~VOGLRenderSystem()
{
	Shutdown();
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
bool VOGLRenderSystem::Init(void)
{
#if VIPER_PLATFORM == PLATFORM_WINDOWS
#elif VIPER_PLATFORM == PLATFORM_MAC
#elif VIPER_PLATFORM == PLATFORM_LINUX
	char	*vDisplay;
	int		vVidModeMajVer, vVidModeMinVer;
	int		vAttrListSgl[] = {GLX_RGBA, GLX_RED_SIZE, 4,
							GLX_GREEN_SIZE, 4,
							GLX_BLUE_SIZE, 4,
							GLX_DEPTH_SIZE, 16,
							None};
	int		vAttrListDbl[] = {GLX_RGBA, GLX_DOUBLEBUFFER,
							GLX_RED_SIZE, 4,
							GLX_GREEN_SIZE, 4,
							GLX_BLUE_SIZE, 4,
							GLX_DEPTH_SIZE, 16,
							None};

	/* connect to the X server */
	vDisplay = getenv("DISPLAY");
	if ((mDpy = XOpenDisplay(vDisplay)) == NULL)
	{
		VTRACE(_CL("Unable to connect to X server.\n"));
		return false;
	}

	/* query X information */
	mScreen = DefaultScreen(mDpy);
	XF86VidModeQueryVersion(mDpy, &vVidModeMajVer, &vVidModeMinVer);
	VTRACE(_CL("====================\n"));
	VTRACE(_CL("        X Info\n"));
	VTRACE(_CL("X Version:  %d.%d\n"), vVidModeMajVer, vVidModeMinVer);
	glXQueryVersion(mDpy, &vVidModeMajVer, &vVidModeMinVer);
	VTRACE(_CL("GL Version: %d.%d\n"), vVidModeMajVer, vVidModeMinVer);

	/* select the best mode */
	XF86VidModeGetAllModeLines(mDpy, mScreen, &(mNumModes), &(mModes));

	/* try and obtain a double-buffered visual */
	mVInfo = glXChooseVisual(mDpy, mScreen, vAttrListDbl);
	if (mVInfo == NULL)
	{
		mVInfo = glXChooseVisual(mDpy, mScreen, vAttrListSgl);
		if (mVInfo == NULL)
			return false;

		mDblBuffered = false;
		VTRACE(_CL("Mode: SingleBuffered\n"));
	}
	else
	{
		mDblBuffered = true;
		VTRACE(_CL("Mode: DoubleBuffered\n"));
	}
#endif
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glFlush();

	return true;
}

void VOGLRenderSystem::Shutdown(void)
{
#if VIPER_PLATFORM == PLATFORM_WINDOWS
#elif VIPER_PLATFORM == PLATFORM_MAC
#elif VIPER_PLATFORM == PLATFORM_LINUX
	VTRACE(_CL("Destroying mModes\n"));
	if (mModes != NULL)
	{
		XFree(mModes);
		mModes = NULL;
	}
	glXMakeCurrent(mDpy, None, NULL);
	VTRACE(_CL("Destroying display\n"));
	if (mDpy != NULL)
	{
		XCloseDisplay(mDpy);
		mDpy = NULL;
	}
#endif
}

VWindow* VOGLRenderSystem::CreateWindow(VWindowOpts *pOpts)
{
#if VIPER_PLATFORM == PLATFORM_WINDOWS
#elif VIPER_PLATFORM == PLATFORM_MAC
#elif VIPER_PLATFORM == PLATFORM_LINUX
	XF86VidModeModeInfo	*vBestMode = NULL;

	if (pOpts->mFullScreen)
	{
		for (int i = 0; i < mNumModes; i++)
		{
			if ((mModes[i]->hdisplay == pOpts->mWidth) && (mModes[i]->vdisplay == pOpts->mHeight))
				vBestMode = mModes[i];
		}

		if (vBestMode == NULL)
			return NULL;

		pOpts->mWidth = vBestMode->hdisplay;
		pOpts->mHeight = vBestMode->vdisplay;
	}

	VOGLWindow *vWindow = new VOGLWindow();
	vWindow->mVInfo = mVInfo;
	vWindow->mDpy = mDpy;
	vWindow->mScreen = mScreen;
	if (pOpts->mFullScreen)
		vWindow->mMode = vBestMode;

	if (vWindow->Create(pOpts))
	{
		glViewport(0, 0,vWindow->mOpts.mWidth, vWindow->mOpts.mHeight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		return vWindow;
	}
	else
		delete vWindow;
			
	return NULL;
#endif
}

void VOGLRenderSystem::DestroyWindow(VWindow *pWin)
{
	pWin->Destroy();
	delete pWin;
	return;
}

bool VOGLRenderSystem::Render(VWindow *pWin, VCamera *pCamera)
{
	int count = 2000;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	pCamera->Render();
	{ GLint err = glGetError(); if (err != GL_NO_ERROR) VTRACE(_CL("OpenGL Error: %d\n"), err); }

	//glLoadIdentity();
	
	for (int i = -count; i <= count; i+=50)
	{
		glBegin(GL_LINES);
			// Front
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(i, count, count);
			glVertex3f(i, -count, count);
			glVertex3f(count, i, count);
			glVertex3f(-count, i, count);
			// Back
			glColor3f(0.0, 1.0, 0.0);
			glVertex3f(i, count, -count);
			glVertex3f(i, -count, -count);
			glVertex3f(count, i, -count);
			glVertex3f(-count, i, -count);
			// Left
			glColor3f(0.0, 0.0, 1.0);
			glVertex3f(-count, i, count);
			glVertex3f(-count, i, -count);
			glVertex3f(-count, count, i);
			glVertex3f(-count, -count, i);
			// Right
			glColor3f(1.0, 1.0, 0.0);
			glVertex3f(count, i, count);
			glVertex3f(count, i, -count);
			glVertex3f(count, count, i);
			glVertex3f(count, -count, i);
			// Floor
			glColor3f(0.0, 1.0, 1.0);
			glVertex3f(count, -count, i);
			glVertex3f(-count, -count, i);
			glVertex3f(i, -count, count);
			glVertex3f(i, -count, -count);
			// Ceiling
			glColor3f(1.0, 0.0, 1.0);
			glVertex3f(count, count, i);
			glVertex3f(-count, count, i);
			glVertex3f(i, count, count);
			glVertex3f(i, count, -count);
		glEnd();

	}

	glTranslatef(0.0f, 0.0f, -20.0f);
	glBegin(GL_QUADS);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(10.0f, 10.0f, -10.0f);
		glVertex3f(-10.0f, 10.0f, -10.0f);
		glVertex3f(-10.0f, 10.0f, 10.0f);
		glVertex3f(10.0f, 10.0f, 10.0f);

		glColor3f(1.0f, 0.5f, 0.0f);
		glVertex3f(10.0f, -10.0f, -10.0f);
		glVertex3f(-10.0f, -10.0f, -10.0f);
		glVertex3f(-10.0f, -10.0f, 10.0f);
		glVertex3f(10.0f, -10.0f, 10.0f);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(10.0f, 10.0f, 10.0f);
		glVertex3f(-10.0f, 10.0f, 10.0f);
		glVertex3f(-10.0f, -10.0f, 10.0f);
		glVertex3f(10.0f, -10.0f, 10.0f);

		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(10.0f, -10.0f, -10.0f);
		glVertex3f(-10.0f, -10.0f, -10.0f);
		glVertex3f(-10.0f, 10.0f, -10.0f);
		glVertex3f(10.0f, 10.0f, -10.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-10.0f, 10.0f, 10.0f);
		glVertex3f(-10.0f, 10.0f, -10.0f);
		glVertex3f(-10.0f, -10.0f, -10.0f);
		glVertex3f(-10.0f, -10.0f, 10.0f);

		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(10.0f, 10.0f, -10.0f);
		glVertex3f(10.0f, 10.0f, 10.0f);
		glVertex3f(10.0f, -10.0f, 10.0f);
		glVertex3f(10.0f, -10.0f, -10.0f);
	glEnd();

	if (mDblBuffered)
		pWin->SwapBuffers();
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
