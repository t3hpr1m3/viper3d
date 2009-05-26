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
#include "VCamera.h"

/* System Headers */
#include <GL/gl.h>

/* Local Headers */
#include "VProfiler.h"

namespace UDP
{

/********************************************************************
 *          C O N S T R U C T I O N / D E S T R U C T I O N         *
 ********************************************************************/
VCamera::VCamera()
{
	SetPosition(VVector(0.0, 0.0, 0.0));
	SetVelocity(VVector(0.0, 0.0, 0.0));
	SetAcceleration(VVector(0.0, 0.0, 0.0));
	mUpdateView = true;
	mUpdateFrustum = true;
	mOrientation = VMath::QUATERNION_IDENTITY;
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

/*------------------------------------------------------------------*
 *							GetDirection()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VVector VCamera::GetDirection()
{
	return mOrientation * -VVector::VECTOR_UNIT_Z;
}

/********************************************************************
 *                        O P E R A T I O N S                       *
 ********************************************************************/

/*------------------------------------------------------------------*
 *								LookAt()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VCamera::LookAt(VNode *pObject)
{
	this->SetDirection(pObject->GetPosition() - GetPosition());
}

/*------------------------------------------------------------------*
 *							    LookAt()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VCamera::LookAt(const VVector& pVector)
{
	this->SetDirection(pVector - GetPosition());
}

/*------------------------------------------------------------------*
 *								LookAt()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VCamera::LookAt(scalar_t pX, scalar_t pY, scalar_t pZ)
{
	VVector vTemp(pX, pY, pZ);
	this->LookAt(vTemp);
}

/*------------------------------------------------------------------*
 *							 SetDirection()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *		If a zero vector was passed in								*
 *			bail (nothing to do)									*
 *		Normalize the inverse vector								*
 *		If the inverse is equal to our current inverse vector		*
 *			Use yaw rotation										*
 *		Else														*
 *			Find the shortest arc									*
 *		Update our orientation										*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VCamera::SetDirection(const VVector& pVec)
{
	if (pVec == VVector::VECTOR_ZERO)
		return;

	VVector vZAdjustVec = -pVec;
	vZAdjustVec.Normalize();

	VVector vAxes[3];
	UpdateView();
	mOrientation.ToAxes(vAxes);
	VQuaternion vRotQuat;

	if (-vZAdjustVec == vAxes[2])
	{
		/*
		 * 180 degree turn (infinite possible rotation axes)
		 * Default to yaw ie. use current UP
		 */
		vRotQuat.FromAngleAxis(VMath::PI, vAxes[1]);
	}
	else
	{
		/*
		 * Derive shortest arc to new direction.
		 */
		vRotQuat = vAxes[2].GetRotationTo(vZAdjustVec);
	}

	mOrientation = vRotQuat * mOrientation;

	mUpdateView = true;
}

/*------------------------------------------------------------------*
 *								 Move()								*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VCamera::Move(const VVector& pVector)
{
	SetPosition(GetPosition() + pVector);
	mUpdateView = true;
}

/*------------------------------------------------------------------*
 *							MoveRelative()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VCamera::MoveRelative(const VVector& pVec)
{
	// Transform the axes of the relative vector by camera's local axes
	VVector vTrans = mOrientation * pVec;

	SetPosition(GetPosition() + vTrans);
	mUpdateView = true;
}

/*------------------------------------------------------------------*
 *								MoveTo()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VCamera::MoveTo(VNode *pObject)
{
	SetPosition(pObject->GetPosition());
	mUpdateView = true;
}

/*------------------------------------------------------------------*
 *								MoveTo()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VCamera::MoveTo(const VVector& pVec)
{
	SetPosition(pVec);
	mUpdateView = true;
}

/*------------------------------------------------------------------*
 *								MoveTo()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VCamera::MoveTo(scalar_t pX, scalar_t pY, scalar_t pZ)
{
	SetPosition(VVector(pX, pY, pZ));
	mUpdateView = true;
}

/*------------------------------------------------------------------*
 *							 RotateYaw()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VCamera::RotateYaw(scalar_t pDegrees)
{
	VVector vYAxis = mOrientation * VVector::VECTOR_UNIT_Y;
	Rotate(vYAxis, pDegrees);
}

/*------------------------------------------------------------------*
 *							RotatePitch()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VCamera::RotatePitch(scalar_t pDegrees)
{
	VVector vXAxis = mOrientation * VVector::VECTOR_UNIT_X;
	Rotate(vXAxis, pDegrees);
}

/*------------------------------------------------------------------*
 *							RotateRoll()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VCamera::RotateRoll(scalar_t pDegrees)
{
	VVector vZAxis = mOrientation * VVector::VECTOR_UNIT_Z;
	Rotate(vZAxis, pDegrees);
}

/*------------------------------------------------------------------*
 *							  Rotate()								*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VCamera::Rotate(const VVector& pAxis, scalar_t pDegrees)
{
	VQuaternion vQ;
	vQ.FromAngleAxis(VMath::DegToRad(pDegrees), pAxis);
	Rotate(vQ);
}

/*------------------------------------------------------------------*
 *							  Rotate()								*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VCamera::Rotate(const VQuaternion& pQ)
{
	mOrientation = pQ * mOrientation;
	mUpdateView = true;
}

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
