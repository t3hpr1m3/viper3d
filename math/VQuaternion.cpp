/*============================================================================*
 *                                                                            *
 *  This source file is part of the Viper3D Game Engine.                      *
 *                                                                            *
 *  Copyright (C) 2004 UDP Games   All Rights Reserved.                       *
 *                                                                            *
 *============================================================================*/

/* System Headers */
#include <cmath>

/* Local Headers */
#include "VMath.h"

namespace UDP
{

/********************************************************************
 *          C O N S T R U C T I O N / D E S T R U C T I O N         *
 ********************************************************************/
VQuaternion::VQuaternion(float _x, float _y, float _z, float _w)
 : x(_x), y(_y), z(_z), w(_w)
{

}

VQuaternion::VQuaternion(const VQuaternion& q)
{
	x = q.x;
	y = q.y;
	z = q.z;
	w = q.w;
}

/********************************************************************
 *                        A T T R I B U T E S                       *
 ********************************************************************/

/*------------------------------------------------------------------*
 *							GetMagnitude()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Determines the current magnitude of this quaternion.
 *	@author		Josh Williams
 *	@date		10-Sep-2003
 *
 *	@returns	(float) VQuaternion magnitude.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
float VQuaternion::GetMagnitude() const
{
	return (float) VMath::Sqrt(w*w + x*x + y*y + z*z);
}

/*------------------------------------------------------------------*
 *							  GetVector()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Retuns the current vector for this quaternion.
 *	@author		Josh Williams
 *	@date		10-Sep-2003
 *
 *	@returns	(Vector) Current vector.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VVector VQuaternion::GetVector() const
{
	return VVector(x, y, z);
}

/*------------------------------------------------------------------*
 *							  GetScalar()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Returns the scalar part of this quaternion.
 *	@author		Josh Williams
 *	@date		10-Sep-2003
 *
 *	@returns	(float)
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
float VQuaternion::GetScalar() const
{
	return w;
}

/*------------------------------------------------------------------*
 *							   GetAngle()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Extracts the angle of rotation about the axis represented
 *				by this VQuaternion's vector component.
 *	@author		Josh Williams
 *	@date		11-Sep-2003
 *
 *	@returns	(float) Angle of rotation.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
float VQuaternion::GetAngle()
{
	return (float)(2 * VMath::ACos(w));
}

/********************************************************************
 *                        O P E R A T I O N S                       *
 ********************************************************************/

/*------------------------------------------------------------------*
 *								ToAxes()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Returns the axes for the three angles of rotation.
 *	@author		Josh Williams
 *	@date		11-Sep-2003
 *
 *	@remarks	Used mainly for calculating movement/rotation.
 *
 *	@param		axes	Pointer to hold the 3 axis vectors
 *
 *	@returns	void
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VQuaternion::ToAxes(VVector* axes) const
{
	VMatrix rot;
	ToRotationMatrix(rot);

	for (int nCol = 0; nCol < 3; nCol++)
	{
		axes[nCol].x = rot[0][nCol];
		axes[nCol].y = rot[1][nCol];
		axes[nCol].z = rot[2][nCol];
	}
}			

/*------------------------------------------------------------------*
 *						  ToRotationMatrix()						*
 *------------------------------------------------------------------*/
/**
 *	@brief		Converts this quaternion to an acceptable rotation matrix.
 *	@author		Josh Williams
 *	@date		11-Sep-2003
 *
 *	@param		rot		Matrix pointer to hold the result
 *
 *	@returns	void
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VQuaternion::ToRotationMatrix(VMatrix& rot) const
{
	float fTx	= 2.0f * x;
	float fTy	= 2.0f * y;
	float fTz	= 2.0f * z;
	float fTwx	= fTx * w;
	float fTwy	= fTy * w;
	float fTwz	= fTz * w;
	float fTxx	= fTx * x;
	float fTxy	= fTy * x;
	float fTxz	= fTz * x;
	float fTyy	= fTy * y;
	float fTyz	= fTz * y;
	float fTzz	= fTz * z;

	rot = VMatrix::MATRIX_IDENTITY;

	rot[0][0] = 1.0f - (fTyy + fTzz);
	rot[0][1] = fTxy - fTwz;
	rot[0][2] = fTxz + fTwy;
	rot[1][0] = fTxy + fTwz;
	rot[1][1] = 1.0f - (fTxx + fTzz);
	rot[1][2] = fTyz - fTwx;
	rot[2][0] = fTxz - fTwy;
	rot[2][1] = fTyz + fTwx;
	rot[2][2] = 1.0f - (fTxx + fTyy);
}

/*------------------------------------------------------------------*
 *							CreateMatrix()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Creates a 4x4 OpenGL acceptable matrix.
 *	@author		Josh Williams
 *	@date		04-Sep-2003
 *
 *	@param		pMatrix	Pointer to a float array to hold the actual
 *						matrix values
 *
 *	@returns	void
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VQuaternion::CreateMatrix(float *pMatrix) const
{
	if (!pMatrix)
		return;
	
	pMatrix[ 0] = 1.0f - 2.0f * (SQR(y) + SQR(z));
	pMatrix[ 1] = 2.0f * (x*y + z*w);
	pMatrix[ 2] = 2.0f * (x*z - y*w);
	pMatrix[ 3] = 0.0f;

	pMatrix[ 4] = 2.0f * (x*y - z*w);
	pMatrix[ 5] = 1.0f - 2.0f * (SQR(x) + SQR(z));
	pMatrix[ 6] = 2.0f * (z*y + x*w);
	pMatrix[ 7] = 0.0f;

	pMatrix[ 8] = 2.0f * (x*z + y*w);
	pMatrix[ 9] = 2.0f * (y*z - x*w);
	pMatrix[10] = 1.0f - 2.0f * (SQR(x) + SQR(y));
	pMatrix[11] = 0.0f;

	pMatrix[12] = 0.0f;
	pMatrix[13] = 0.0f;
	pMatrix[14] = 0.0f;
	pMatrix[15] = 1.0f;
}

/*------------------------------------------------------------------*
 *							FromAngleAxis()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Sets this quaternion = to a rotation about the axis
 *				specified.
 *	@author		Josh Williams
 *	@date		11-Sep-2003
 *
 *	@param		rAngle	Angle of rotation
 *	@param		rAxis	Axis about which to rotate
 *
 *	@returns	void
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VQuaternion::FromAngleAxis(const float& rAngle, const VVector& rAxis)
{
	float fHalfAngle = 0.5*rAngle;
	float fSin		= VMath::Sin(fHalfAngle);

	w = (float)VMath::Cos(fHalfAngle);

	x = float(rAxis.x*fSin);
	y = float(rAxis.y*fSin);
	z = float(rAxis.z*fSin);
}

/*------------------------------------------------------------------*
 *							FromEulerAngles()						*
 *------------------------------------------------------------------*/
/**
 *	@brief		Construct a quaternion from Euler angles.
 *	@author		Josh Williams
 *	@date		03-Sep-2003
 *
 *	@param		roll
 *	@param		pitch
 *	@param		yaw		Angles of rotation
 *
 *	@returns	void
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VQuaternion::FromEulerAngles(const float& roll, const float& pitch,
						const float& yaw)
{
	float cr, cp, cy, sr, sp, sy, cpcy, spsy; // Temp vars in roll, pitch, yaw

	cr = VMath::Cos(roll/2.0f);
	cp = VMath::Cos(pitch/2.0f);
	cy = VMath::Cos(yaw/2.0f);

	sr = VMath::Sin(roll/2.0f);
	sp = VMath::Sin(pitch/2.0f);
	sy = VMath::Sin(yaw/2.0f);

	cpcy = cp * cy;
	spsy = sp * sy;

	w = cr * cpcy + sr * spsy;
	x = sr * cpcy - cr * spsy;
	y = cr * sp * cy + sr * cp * sy;
	z = cr * cp * sy - sr * sp * cy;
}

/*------------------------------------------------------------------*
 *								Normalize()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Reduces this quaternion to a normal value.
 *	@author		Josh Williams
 *	@date		13-Sep-2003
 *
 *	@returns	void
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VQuaternion::Normalize()
{
	float m = VMath::Sqrt(SQR( x ) + SQR( y ) + SQR( z ) + SQR( w ));

	if (m != 0.0f)
	{
		x /= m;
		y /= m;
		z /= m;
		w /= m;
	}
}

/*------------------------------------------------------------------*
 *							  ToAxisAngle()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Converts this quaternion to an axis of rotation and
 *				rotation angle.
 *	@author		Josh Williams
 *	@date		03-Sep-2003
 *
 *	@param		vec		Var to hold the rotation axis
 *	@param		angle	Var to hold the angle of rotation
 *
 *	@returns	void
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VQuaternion::ToAxisAngle(VVector& vec, float& angle) const
{
	double temp_angle;
	double scale;

	temp_angle = VMath::ACos(w);

	scale = (float)VMath::Sqrt(SQR(x) + SQR(y) + SQR(z));
	if (FLOAT_EQ(0.0f, scale))
	{
		angle = 0.0f;
		vec.SetValues(0.0f, 0.0f, 0.0f);
	}
	else
	{
		angle = (float)(temp_angle * 2.0);
		vec.SetValues(float(x / scale), float(y / scale), float(z / scale));
		vec.Normalize();
	}
}

void VQuaternion::Conjugate(const VQuaternion& q)
{
	x = -q.x;
	y = -q.y;
	z = -q.z;
	w = q.w;
}

void VQuaternion::GetEulerAngles(float *fRoll, float *fPitch, float *fYaw) const
{
	double r11, r21, r31, r32, r33, r12, r13;
	double q00, q11, q22, q33;
	double temp;

	q00 = SQR( w );
	q11 = SQR( x );
	q22 = SQR( y );
	q33 = SQR( z );

	r11 = q00 + q11 - q22 - q33;
	r21 = 2 * (x*y + w*z);
	r31 = 2 * (x*z - w*y);
	r32 = 2 * (y*z + w*x);
	r33 = q00 - q11 - q22 + q33;

	temp = VMath::Abs(r31);
	if (temp > 0.999999)
	{
		r12 = 2 * (x*y - w*z);
		r13 = 2 * (x*z + w*y);

		*fRoll	= (float)atan2(-r12, -r31*r13);
		*fPitch	= 0.0f;
		*fYaw	= (float)-(VMath::HALF_PI * r31/temp);
	}
	else
	{
		*fRoll	= (float)atan2(r21, r11);
		*fPitch	= (float)atan2(r32, r33);
		*fYaw	= (float)asin(-r31);
	}
}

void VQuaternion::Rotate(const VQuaternion& q1, const VQuaternion& q2)
{
	VQuaternion t = q1*q2*(~q1);
	*this = t;
}

VVector VQuaternion::Rotate(const VVector& vec)
{
	VQuaternion t(*this);
	VQuaternion r = t*vec*(~t);
	return VVector(r.x, r.y, r.z);
}

/********************************************************************
 *                          O P E R A T O R S                       *
 ********************************************************************/

/*------------------------------------------------------------------*
 *							   operator=							*
 *------------------------------------------------------------------*/
/**
 *	@brief		VQuaternion assignment.
 *	@author		Josh Williams
 *	@date		11-Sep-2003
 *
 *	@param		q	VQuaternion to copy
 *
 *	@returns	(VQuaternion&) Result of the assignment.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VQuaternion& VQuaternion::operator=(const VQuaternion& q)
{
	w = q.w;
	x = q.x;
	y = q.y;
	z = q.z;
	return *this;
}

/*------------------------------------------------------------------*
 *							  operator*=							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Performs VQuaternion scaling.
 *	@author		Josh Williams
 *	@date		10-Sep-2003
 *
 *	@param		s	scalar value to scale by
 *
 *	@returns	(VQuaternion&) Value of this object after scaling.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VQuaternion& VQuaternion::operator*=(const float& s)
{
	w *= s;
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

/*------------------------------------------------------------------*
 *							 operator* (float)						*
 *------------------------------------------------------------------*/
/**
 *	@brief		Performs scalar multiplication without modifying this
 *				instance.
 *	@author		Josh Williams
 *	@date		11-Sep-2003
 *
 *	@param		s	Scalar value to multiply by
 *
 *	@returns	(VQuaternion) Result of the multiplication.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VQuaternion VQuaternion::operator*(const float& s) const
{
	return VQuaternion(w*s, x*s, y*s, z*s);
}

/*------------------------------------------------------------------*
 *							  operator/=							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Performs quaternion division.
 *	@author		Josh Williams
 *	@date		10-Sep-2003
 *
 *	@param		s	scalar value to divide by.
 *
 *	@returns	(VQuaternion&) Value of this object after division.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VQuaternion& VQuaternion::operator/=(const float& s)
{
	w /= s;
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

/*------------------------------------------------------------------*
 *							  operator/								*
 *------------------------------------------------------------------*/
/**
 *	@brief		Performs vector multiplication without modifying this
 *				instance.
 *	@author		Josh Williams
 *	@date		11-Sep-2003
 *
 *	@param		s	scalar to divide by
 *
 *	@returns	(VQuaternion) Product of scalar division.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VQuaternion VQuaternion::operator/(const float& s) const
{
	return VQuaternion(w/s, x/s, y/s, z/s);
}

/*------------------------------------------------------------------*
 *							  operator* (Vector)					*
 *------------------------------------------------------------------*/
/**
 *	@brief		Performs vector multiplication without modifying this
 *				instance.
 *	@author		Josh Williams
 *	@date		11-Sep-2003
 *
 *	@param		vec		Vector we should multiply by
 *
 *	@returns	(VQuaternion) Product of vector multiplication.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
/*
VQuaternion VQuaternion::operator*(const VVector &vec) const
{
	return VQuaternion(	w*vec.x + y*vec.z - z*vec.y,
						w*vec.y + z*vec.x - x*vec.z,
						w*vec.z + x*vec.y - y*vec.x,
					  -(x*vec.x + y*vec.y + z*vec.z));
}
*/

VVector VQuaternion::operator*(const VVector &pVec) const
{
	VVector	vUv, vUUv;
	VVector	vQVec(x, y, z);
	vUv = vQVec.CrossProduct(pVec);
	vUUv = vQVec.CrossProduct(vUv);
	vUv *= (2.0f * w);
	vUUv *= 2.0f;

	return pVec+vUv+vUUv;
}

/*------------------------------------------------------------------*
 *							   operator+=							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Performs quaternion addition.
 *	@author		Josh Williams
 *	@date		10-Sep-2003
 *
 *	@remarks	Adds the two quaternions on a component by
 *				component basis.
 *
 *	@param		q	VQuaternion we should add to ourselves
 *
 *	@returns	(VQuaternion&) Value of this object after addition.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VQuaternion& VQuaternion::operator+=(const VQuaternion& q)
{
	w	+= q.w;
	x	+= q.x;
	y	+= q.y;
	z	+= q.z;
	return *this;
}

/*------------------------------------------------------------------*
 *							  operator+								*
 *------------------------------------------------------------------*/
/**
 *	@brief		Performs quaternion addition without modifying
 *				this instance.
 *	@author		Josh Williams
 *	@date		11-Sep-2003
 *
 *	@param		q	VQuaternion we should add to ourselves
 *
 *	@returns	(VQuaternion) Sum of this quaternion and q.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VQuaternion VQuaternion::operator+(const VQuaternion& q) const
{
	return VQuaternion(w + q.w,
						x + q.x,
						y + q.y,
						z + q.z);
}

/*------------------------------------------------------------------*
 *							   operator-=							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Performs quaternion subtraction.
 *	@author		Josh Williams
 *	@date		10-Sep-2003
 *
 *	@remarks	The exact inverse of addition.
 *
 *	@param		q	VQuaternion we should subtract from ourselves
 *
 *	@returns	(VQuaternion&) Value of this object after subtraction.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VQuaternion& VQuaternion::operator-=(const VQuaternion& q)
{
	w -= q.w;
	x -= q.x;
	y -= q.y;
	z -= q.z;
	return *this;
}

/*------------------------------------------------------------------*
 *							  operator-								*
 *------------------------------------------------------------------*/
/**
 *	@brief		Performs quaternion subtraction without modifying
 *				this instance.
 *	@author		Josh Williams
 *	@date		11-Sep-2003
 *
 *	@param		q	VQuaternion we should subtract from ourselves
 *
 *	@returns	(VQuaternion) Difference in the two quaternions.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VQuaternion VQuaternion::operator-(const VQuaternion& q) const
{
	return VQuaternion(w - q.w,
						x - q.x,
						y - q.y,
						z - q.z);
}

/*------------------------------------------------------------------*
 *							  operator*=							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Multiplies this quaternion by another.
 *	@author		Josh Williams
 *	@date		14-Sep-2003
 *
 *	@param		q	VQuaternion to multiply by.
 *
 *	@returns	(VQuaternion) Result of multiplication.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VQuaternion& VQuaternion::operator*=(const VQuaternion& q)
{
	w = q.w*w - q.x*x - q.y*y - q.z*z;
	x = q.w*x + q.x*w + q.y*z - q.z*y;
	y = q.w*y - q.x*z + q.y*w + q.z*x;
	z = q.w*z + q.x*y - q.y*x + q.z*w;

	return *this;
}

/*------------------------------------------------------------------*
 *							 operator* (VQuaternion)				*
 *------------------------------------------------------------------*/
/**
 *	@brief		Performs quaternion multiplication without modifying
 *				this instance.
 *	@author		Josh Williams
 *	@date		11-Sep-2003
 *
 *	@param		q	VQuaternion we should multiply by ourselves.
 *
 *	@returns	(VQuaternion) Product of the two quaternions.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VQuaternion VQuaternion::operator*(const VQuaternion& q) const
{
	return VQuaternion(
		w*q.w - x*q.x - y*q.y - z*q.z,
		w*q.x + x*q.w + y*q.z - z*q.y,
		w*q.y + y*q.w + z*q.x - x*q.z,
		w*q.z + z*q.w + x*q.y - y*q.x);
}

/*------------------------------------------------------------------*
 *							  operator~								*
 *------------------------------------------------------------------*/
/**
 *	@brief		Computes the conjugate of this VQuaternion.
 *	@author		Josh Williams
 *	@date		11-Sep-2003
 *
 *	@returns	(VQuaternion) This VQuaternion's conjugate.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VQuaternion VQuaternion::operator~() const
{
	return VQuaternion(w, -x, -y, -z);
}

/********************************************************************
 *                         C A L L B A C K S                        *
 ********************************************************************/

/********************************************************************
 *                         I N T E R N A L S                        *
 ********************************************************************/

} // End Namespace
