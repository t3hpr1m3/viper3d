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
#include "Viper3D.h"

/* System Headers */
#include <sys/time.h>
#include <GL/gl.h>

/* Local Headers */
#include "VLog.h"
#include "VProfiler.h"

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
	mInput = NULL;
	mWindow = NULL;
	mCamera = NULL;
}

Viper3D::~Viper3D()
{
	if (mInput != NULL)
	{
		mInput->Release();
		delete mInput;
	}

	if (mWindow != NULL)
	{
		mWindow->Release();
		delete mWindow;
	}

	if (mCamera != NULL)
	{
		delete mCamera;
	}
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
bool Viper3D::Create(int pWidth/*=800*/, int pHeight/*=600*/, bool pFullScreen/*=false*/)
{
	mWindow = new VWindow();
	if (!mWindow->CreateDevice("X"))
	{
		VTRACE(_CL("Unable to create window device\n"));
		return false;
	}

	if (!mWindow->GetDevice()->Initialize())
	{
		VTRACE(_CL("UNable to initialize window\n"));
		return false;
	}

	if (!mWindow->GetDevice()->CreateWindow(pWidth, pHeight, pFullScreen))
	{
		VTRACE(_CL("Unable to create window\n"));
		return false;
	}

	mInput = new VInput();
	if (!mInput->CreateDevice("X"))
	{
		VTRACE(_CL("Unable to create input device\n"));
		return false;
	}

	if (!mInput->GetDevice()->Initialize(mWindow->GetDevice()))
	{
		VTRACE(_CL("Unable to initialize input\n"));
		return false;
	}

	CreateCamera();

	glViewport(0, 0, pWidth, pHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	mWindow->GetDevice()->SetCaption("Viper3D Engine");

	return true;
}

void Viper3D::MainLoop()
{
	struct timeval		vCurTime;
	struct timeval		vLastTime;
	float				vFramesPerSecond = 0.0f;
	static char			vFrameRate[50];
	struct timeval		vTimeDiff;
	double				vTimingDiff = 0.0f;

	gettimeofday(&vLastTime, NULL);

	if (1 == 1)
	{
		PROFILE("Main engine loop");
		for (;;)
		{
			gettimeofday(&vCurTime, NULL);
			++vFramesPerSecond;
			vTimeDiff.tv_sec = vCurTime.tv_sec - vLastTime.tv_sec;
			vTimeDiff.tv_usec = vCurTime.tv_usec - vLastTime.tv_usec;
			if (vTimeDiff.tv_usec < 0)
			{
				vTimeDiff.tv_usec--;
				vTimeDiff.tv_usec += 1000000;
			}
			vTimingDiff = static_cast<double>(vTimeDiff.tv_sec) +
							static_cast<double>(vTimeDiff.tv_usec*1e-6);
	
			if (vTimingDiff > 1.0f)
			{
				vLastTime = vCurTime;
				sprintf(vFrameRate, "CurrentFPS: %d", static_cast<int>(vFramesPerSecond));
				mWindow->GetDevice()->SetCaption(vFrameRate);
				vFramesPerSecond = 0;
			}
			if (1 == 1)
			{
				PROFILE("INPUT");
				mWindow->GetDevice()->Update();
				mInput->GetDevice()->Update();
				if (mInput->GetDevice()->IsKeyDown(UDP::KC_Q) == true)
					break;
			}
	
			if (1 == 1)
			{
				PROFILE("Clearing");
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			}
	
			if (1 == 1)
			{
				PROFILE("Camera");
				mCamera->Render();
			}
	
			if (1 == 1)
			{
				PROFILE("Rendering!");
				glPushMatrix();
				glLoadIdentity();
				glTranslatef(0.0f, 0.0f, -10.0f);
				glColor3f(1.0f, 1.0f, 1.0f);
				glBegin(GL_QUADS);
					glVertex3f(0.5f, 0.5f, 0.0f);
					glVertex3f(-0.5f, 0.5f, 0.0f);
					glVertex3f(-0.5f, -0.5f, 0.0f);
					glVertex3f(0.5f, -0.5f, 0.0f);
				glEnd();
				glPopMatrix();
			}
	
			if (1 == 1)
			{
				PROFILE("Swapping buffers");
				mWindow->GetDevice()->SwapBuffers();
			}
				
		}
	}
	PROFILE_OUTPUT();
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
VCamera* Viper3D::CreateCamera(const VVector &pPos /*=VVector::VECTOR_ZERO*/,
								const VVector &pDir /*-VVector::VECTOR_UNIT_Z*/)
{
	mCamera = new VCamera();
	mCamera->SetPosition(pPos);
	mCamera->SetDirection(pDir);
	return mCamera;
}

} // End Namespace

/* vi: set ts=4: */
