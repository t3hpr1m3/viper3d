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
#include <viper3d/Movable.h>

/* System Headers */

/* Local Headers */
#include <viper3d/util/Log.h>

namespace UDP
{

/********************************************************************
 *          C O N S T R U C T I O N / D E S T R U C T I O N         *
 ********************************************************************/
VMovable::VMovable()
{
	SetPosition(VVector(0.0f, 0.0f, 0.0f, 1.0f));
	SetDirection(-VVector::VECTOR_UNIT_Z);
	mOrientation = VMath::QUATERNION_IDENTITY;
}

/********************************************************************
 *                        A T T R I B U T E S                       *
 ********************************************************************/

/*------------------------------------------------------------------*
 *							GetPosition()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Returns the local coordinate position of this object.
 *	@author		Josh Williams
 *	@date		09-Sep-2003
 *
 *	@returns	(VVector) Position of this object relative to its
 *				parent.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
const VVector& VMovable::GetPosition() const
{
	return mPosition;
}

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
VVector VMovable::GetDirection() const
{
	return mOrientation * -VVector::VECTOR_UNIT_Z;
}

/********************************************************************
 *                        O P E R A T I O N S                       *
 ********************************************************************/

/*------------------------------------------------------------------*
 *							SetPosition()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Sets this object's position relative to its parent.
 *	@author		Josh Williams
 *	@date		09-Sep-2003
 *
 *	@returns	(VVector) The object's original position.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VVector VMovable::SetPosition(const VVector& pNewPosition)
{
	VVector vOld = mPosition;
	mPosition = pNewPosition;
	OnMove();
	return vOld;
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
void VMovable::LookAt(VMovable *pObject)
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
void VMovable::LookAt(const VVector& pVector)
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
void VMovable::LookAt(scalar_t pX, scalar_t pY, scalar_t pZ)
{
	this->LookAt(VVector(pX, pY, pZ));
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
void VMovable::SetDirection(const VVector& pVec)
{
	if (pVec == VVector::VECTOR_ZERO)
		return;

	VVector vZAdjustVec = -pVec;
	vZAdjustVec.Normalize();

	VVector vAxes[3];
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

	OnRotate();
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
void VMovable::Move(const VVector& pVector)
{
	SetPosition(GetPosition() + pVector);
	OnMove();
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
void VMovable::MoveRelative(const VVector& pVec)
{
	// Transform the axes of the relative vector by camera's local axes
	VVector vTrans = mOrientation * pVec;

	SetPosition(GetPosition() + vTrans);
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
void VMovable::MoveTo(VMovable *pObject)
{
	SetPosition(pObject->GetPosition());
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
void VMovable::MoveTo(const VVector& pVec)
{
	SetPosition(pVec);
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
void VMovable::MoveTo(scalar_t pX, scalar_t pY, scalar_t pZ)
{
	SetPosition(VVector(pX, pY, pZ));
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
void VMovable::RotateYaw(scalar_t pDegrees)
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
void VMovable::RotatePitch(scalar_t pDegrees)
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
void VMovable::RotateRoll(scalar_t pDegrees)
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
void VMovable::Rotate(const VVector& pAxis, scalar_t pDegrees)
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
void VMovable::Rotate(const VQuaternion& pQ)
{
	mOrientation = pQ * mOrientation;
	OnRotate();
}


/********************************************************************
 *                         C A L L B A C K S                        *
 ********************************************************************/

/********************************************************************
 *                         I N T E R N A L S                        *
 ********************************************************************/

} // End Namespace
