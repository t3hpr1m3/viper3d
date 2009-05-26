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
#include <viper3d/Camera.h>

/* System Headers */
#include <GL/gl.h>

/* Local Headers */
#include <viper3d/Profiler.h>
#include <viper3d/util/Log.h>
#include <iostream>

using std::cout;
using std::endl;

namespace UDP
{

/* Static Variables */
static char __CLASS__[] = "[    Camera    ]";

/********************************************************************
 *          C O N S T R U C T I O N / D E S T R U C T I O N         *
 ********************************************************************/
VCamera::VCamera()
	: VMovable()
{
	mUpdateFrustum = true;
	mViewMatrix = VMatrix::MATRIX_ZERO;
	mFOV = 45.0f;
	mNear = 0.1f;
	mFar = 10000.0f;
	mAspect = 1.33333333333f;
	mFrustrumW = 0.0f;
	mFrustrumH = 0.0f;
}

VCamera::~VCamera()
{

}

/********************************************************************
 *                        A T T R I B U T E S                       *
 ********************************************************************/

/********************************************************************
 *                        O P E R A T I O N S                       *
 ********************************************************************/

/*------------------------------------------------------------------*
 *							UpdateView()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VCamera::UpdateView()
{
	if (mUpdateView)
	{
		VMatrix vRot;
		mOrientation.ToRotationMatrix(vRot);

		// Make the translation relative to the new axes;
		VMatrix vRotT = vRot.Transpose();
		VVector vTrans = -vRotT * mPosition;

		// Make the final matrix
		mViewMatrix = vRotT;
		mViewMatrix[0][3] = vTrans.x;
		mViewMatrix[1][3] = vTrans.y;
		mViewMatrix[2][3] = vTrans.z;
		mViewMatrix[3][3] = 1.0f;
	}
	mUpdateView = false;
}

/*------------------------------------------------------------------*
 *							UpdateFrustum()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VCamera::UpdateFrustum()
{
	if (mUpdateFrustum)
	{
		mFrustrumH = VMath::Tan(mFOV / 180 * VMath::PI) * mNear / 2;
		mFrustrumW = mFrustrumH * mAspect;
	}
	mUpdateFrustum = false;
}

/*------------------------------------------------------------------*
 *							  	Render()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VCamera::Render()
{
	PROFILE("Camera rendering");
	OnRender();
}

/********************************************************************
 *                         C A L L B A C K S                        *
 ********************************************************************/

/*------------------------------------------------------------------*
 *							   OnRender()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VCamera::OnRender()
{
	/* TODO: Move the API specific logic here to the renderer */
	UpdateView();
	UpdateFrustum();

	GLfloat	 vGLMatrix[16];
	mViewMatrix.MakeGLMatrix(vGLMatrix);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-mFrustrumW, mFrustrumW, -mFrustrumH, mFrustrumH, mNear, mFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(vGLMatrix);
}

/********************************************************************
 *                         I N T E R N A L S                        *
 ********************************************************************/

} // End Namespace
