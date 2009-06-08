/*============================================================================*
 *                                                                            *
 * 	This file is part of the Viper3D Game Engine.							  *
 *                                                                            *
 *	Copyright (C) 2004 UDP Games   All Rights Reserved.						  *
 *                                                                            *
 *============================================================================*
 *                                  CHANGELOG                                 *
 *    Date      Description                                     Author        *
 * -----------  ----------------------------------------------	------------- *
 *                                                                            *
 *============================================================================*/
#include <viper3d/Math.h>

/* System Headers */
#include <iostream>

/* Local Headers */
#include <viper3d/util/CPU.h>

using std::cout;
using std::endl;

namespace UDP
{

const VVector	VVector::VECTOR_ZERO(0, 0, 0, 0);
const VVector	VVector::VECTOR_UNIT_X(1, 0, 0, 1);
const VVector	VVector::VECTOR_UNIT_Y(0, 1, 0, 1);
const VVector	VVector::VECTOR_UNIT_Z(0, 0, 1, 1);
const VVector	VVector::VECTOR_DIR_X(1, 0, 0, 0);
const VVector	VVector::VECTOR_DIR_Y(0, 1, 0, 0);
const VVector	VVector::VECTOR_DIR_Z(0, 0, 1, 0);
const VVector	VVector::VECTOR_UNIT_SCALE(1, 1, 1, 1);

/********************************************************************
 *          C O N S T R U C T I O N / D E S T R U C T I O N         *
 ********************************************************************/
VVector::VVector(float _x /*=0*/, float _y /*=0*/, float _z /*=0*/, float _w /*=0*/)
: x(_x), y(_y), z(_z), w(_w)
{
}

VVector::VVector(const VVector& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	w = vec.w;
}

VVector::~VVector()
{

}

/********************************************************************
 *                        A T T R I B U T E S                       *
 ********************************************************************/

/*------------------------------------------------------------------*
 *								Length()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Calculates the length of this vector, using assembly
 *				if available.
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 *	@returns	(float) Length of the vector.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
float VVector::Length()
{
	float f = 0;

	if (VCPU::HaveSSE())
	{
		w = 0.0f;
#if VIPER_PLATFORM == PLATFORM_WINDOWS
		__asm {
			mov		esi,	this
			movups	xmm0,	[esi]
			mulps	xmm0,	xmm0
			movaps	xmm1,	xmm0
			shufps	xmm1,	xmm1,	4Eh
			addps	xmm0,	xmm1
			movaps	xmm1,	xmm0
			shufps	xmm1,	xmm1,	11h
			addps	xmm0,	xmm1
			sqrtss	xmm0,	xmm0
			movss	f,		xmm0
		}
#elif VIPER_PLATFORM == PLATFORM_APPLE
#elif VIPER_PLATFORM == PLATFORM_LINUX
		__asm__ __volatile__ (
			"movups	%1, %%xmm0\n\t"
			"mulps	%%xmm0, %%xmm0\n\t"
			"movaps	%%xmm0, %%xmm1\n\t"
			"shufps $0x4E, %%xmm1, %%xmm1\n\t"
			"addps	%%xmm1, %%xmm0\n\t"
			"movaps %%xmm0, %%xmm1\n\t"
			"shufps $0x11, %%xmm1, %%xmm1\n\t"
			"addps	%%xmm1, %%xmm0\n\t"
			"sqrtss	%%xmm0, %%xmm0\n\t"
			"movss	%%xmm0, %0\n\t"
			: "=m" (f)
			: "m" (*this)
			: "memory"
		);
#endif
		w = 1.0f;
	}
	else
	{
		f = (float)VMath::Sqrt(x*x + y*y + z*z);
	}

	return f;
}

/*------------------------------------------------------------------*
 *							 SquaredLength()						*
 *------------------------------------------------------------------*/
/**
 *	@brief		Calculates the squared length of the vector.
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 *	@returns	(float) Squared length of the vector.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
float VVector::SquaredLength() const
{
	return (float)(x*x + y*y + z*z);
}

/*------------------------------------------------------------------*
 *								UnitVector()						*
 *------------------------------------------------------------------*/
/**
 *	@brief		Converts this vector to a unit vector (length = 1).
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 *	@returns	(VVector) This VVector converted to unit.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VVector VVector::UnitVector()
{
	return (*this) / Length();
}

/********************************************************************
 *                        O P E R A T I O N S                       *
 ********************************************************************/

/*------------------------------------------------------------------*
 *							  SetValues()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Quick assignment function.
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 *	@param		_x
 *	@param		_y
 *	@param		_z
 *	@param		_w	New values to use.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VVector::SetValues(float _x, float _y, float _z, float _w/*=1.0f*/)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

/*------------------------------------------------------------------*
 *								Negate()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Multiplies all 3 coordinates by -1.
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VVector::Negate()
{
	x = -x;
	y = -y;
	z = -z;
}

/*------------------------------------------------------------------*
 *							  Normailize()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Normalizes this vector (gives it a length of 1).
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VVector::Normalize()
{
	if (VCPU::HaveSSE())
	{
		w = 0.0f;
#if VIPER_PLATFORM == PLATFORM_WINDOWS
		__asm {
			mov		esi,	this
			movups	xmm0,	[esi]
			movaps	xmm2,	xmm0
			mulps	xmm0,	xmm0
			movaps	xmm1,	xmm0
			shufps	xmm1,	xmm1,	4Eh
			addps	xmm0,	xmm1
			movaps	xmm1,	xmm0
			shufps	xmm1,	xmm1,	11h
			addps	xmm0,	xmm1
			rsqrtps	xmm0,	xmm1
			mulps	xmm2,	xmm0
			movups	[esi],	xmm2
		}
#elif VIPER_PLATFORM == PLATFORM_APPLE
#elif VIPER_PLATFORM == PLATFORM_LINUX
		__asm__ __volatile__ (
			"movups	%0,			%%xmm0\n\t"
			"movaps %%xmm0,		%%xmm2\n\t"
			"mulps	%%xmm0,		%%xmm0\n\t"
			"movaps %%xmm0,		%%xmm1\n\t"
			"shufps	$0x4E,		%%xmm1,	%%xmm1\n\t"
			"addps	%%xmm1,		%%xmm0\n\t"
			"movaps	%%xmm0,		%%xmm1\n\t"
			"shufps $0x11,		%%xmm1,	%%xmm1\n\t"
			"addps	%%xmm1,		%%xmm0\n\t"
			"rsqrtps	%%xmm0,	%%xmm0\n\t"
			"mulps	%%xmm0,		%%xmm2\n\t"
			"movups %%xmm2,		%0\n\t"
			:
			: "m" (*this)
			: "memory"
		);
#endif
		w = 1.0f;
	}
	else
	{
		float fLength = VMath::Sqrt(SQR(x) + SQR(y) + SQR(z));
		if (fLength != 0.0f)
		{
			x /= fLength;
			y /= fLength;
			z /= fLength;
		}
	}
}

/*------------------------------------------------------------------*
 *								AngleWith()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Computes the angle, in radians, between this VVector
 *				and the supplied VVector reference.
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 *	@param		v	VVector to compute angle with.
 *
 *	@returns	(float) Angle of separation, in radians.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
float VVector::AngleWith(VVector& v)
{
	return (float)VMath::ACos(((*this) * v) / (Length() * v.Length()));
}

/*------------------------------------------------------------------*
 *								RotateWith()						*
 *------------------------------------------------------------------*/
/**
 *	@brief		Applies the rotation part of the given VMatrix to this
 *				vector.
 *	@author		Josh Williams
 *	@date		14-Sep-2004
 *
 *	@param		mat	VMatrix for rotation
 *
 *	@returns	void
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VVector::RotateWith(const VMatrix& mat)
{
	float _x = x * mat[0][0] + y * mat[1][0] + z * mat[2][0];
	float _y = x * mat[0][1] + y * mat[1][1] + z * mat[2][1];
	float _z = x * mat[0][2] + y * mat[1][2] + z * mat[2][2];
	x = _x;
	y = _y;
	z = _z;
}

/*------------------------------------------------------------------*
 *							InvRotateWith()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Applies the inverse rotation of the supplied VMatrix.
 *	@author		Josh Williams
 *	@date		14-Sep-2004
 *
 *	@param		mat	Matrix to use for rotation.
 *
 *	@returns	void
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VVector::InvRotateWith(const VMatrix& mat)
{
	float _x = x * mat[0][0] + y * mat[0][1] + z * mat[0][2];
	float _y = x * mat[1][0] + y * mat[1][1] + z * mat[1][2];
	float _z = x * mat[2][0] + y * mat[2][1] + z * mat[2][2];
	x = _x;
	y = _y;
	z = _z;
}

/*------------------------------------------------------------------*
 *							Difference()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Sets this vector to be the vector that is the difference
 *				of the two supplied vectors.
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 *	@param		v1
 *	@param		v2	VVectors for calculation
 *
 *	@returns	void
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VVector::Difference(const VVector& v1, const VVector& v2)
{
	x = v2.x - v1.x;
	y = v2.y - v1.y;
	z = v2.z - v1.z;
	w = 1.0f;
}

/*------------------------------------------------------------------*
 *							CrossProduct()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Computes the cross product between this vector and
 *				the	supplied VVector object.
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 *	@param		vec	VVector for calculation
 *
 *	@returns	(VVector)	Result of cross product calculation.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VVector VVector::CrossProduct(const VVector& vec) const
{
	VVector temp;
	temp.Cross(*this, vec);
	return temp;
}

/*------------------------------------------------------------------*
 *								Cross()								*
 *------------------------------------------------------------------*/
/**
 *	@brief		Build the cross product of two VVectors, using SSE
 *				if available.  Note that none of the parameters values 
 *				is changed.
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 *	@param		v1
 *	@param		v2	VVectors for calculation.
 *
 *	@returns	void
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VVector::Cross(const VVector& v1, const VVector& v2)
{
	w = 0.0f;
	if (VCPU::HaveSSE())
	{
#if VIPER_PLATFORM == PLATFORM_WINDOWS
		__asm {
			mov		esi,	v1
			mov		edi,	v2

			movups	xmm0,	[esi]
			movups	xmm1,	[edi]
			movaps	xmm2,	xmm0
			movaps	xmm3,	xmm1

			shufps	xmm0,	xmm0,	0xC9
			shufps	xmm1,	xmm1,	0xD2
			mulps	xmm0,	xmm1

			shufps	xmm2,	xmm2,	0xD2
			shufps	xmm3,	xmm3,	0xC9
			mulps	xmm2,	xmm3

			subps	xmm0,	xmm2

			mov		esi,	this
			movups	[esi],	xmm0
		}
#elif VIPER_PLATFORM == PLATFORM_APPLE
#elif VIPER_PLATFORM == PLATFORM_LINUX
		__asm__ __volatile__ (
			"movups	%0,			%%xmm0\n\t"
			"movups %1,			%%xmm1\n\t"

			"movaps %%xmm0,		%%xmm2\n\t"
			"movaps %%xmm1,		%%xmm3\n\t"

			"shufps	$0xc9,		%%xmm0,	%%xmm0\n\t"
			"shufps $0xd2,		%%xmm1,	%%xmm1\n\t"
			"mulps	%%xmm1,		%%xmm0\n\t"

			"shufps	$0xd2,		%%xmm2,	%%xmm2\n\t"
			"shufps $0xc9,		%%xmm3,	%%xmm3\n\t"
			"mulps	%%xmm3,		%%xmm2\n\t"

			"subps	%%xmm2,		%%xmm0\n\t"
			"movups %%xmm0,		%2\n\t"
			:
			: "m" (v1),
			  "m" (v2),
			  "m" (*this)
			: "memory"
		);
#endif
		w = 1.0f;
	}
	else
	{
		x = v1.y * v2.z - v1.z * v2.y;
		y = v1.z * v2.x - v1.x * v2.z;
		z = v1.x * v2.y - v1.y * v2.x;
		w = 1.0f;
	}
}

/*------------------------------------------------------------------*
 *								Cross()								*
 *------------------------------------------------------------------*/
/**
 *	@brief		Computes the dot product of this VVector and the 
 *				supplied VVector object.
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 *	@param		vec	Vector for calculation.
 *
 *	@returns	(float) The dot product of the two VVectors.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
float VVector::DotProduct(const VVector& vec) const
{
	return x*vec.x + y*vec.y + z*vec.z;
}

/*------------------------------------------------------------------*
 *							GetRotationTo()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Computes a rotation Quaternion that represents the
 *				shortest arc to rotate this VVector to the
 *				destination vector.
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 *	@param		vDest	Desired destination vector.
 *
 *	@returns	(VQuaternion)	Rotation quaternion.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VQuaternion VVector::GetRotationTo(const VVector& vDest) const
{
	VVector v0 = *this;
	VVector v1 = vDest;
	v0.Normalize();
	v1.Normalize();

	VVector c = v0.CrossProduct(v1);

	float d = v0.DotProduct(v1);

	if (d >= 1.0f)
	{
		return VMath::QUATERNION_IDENTITY;
	}

	float s = VMath::Sqrt((1+d)*2);
	float invs = 1/s;

	VQuaternion q(s*0.5, c.x*invs, c.y*invs, c.z*invs);
	return q;
}

/********************************************************************
 *                          O P E R A T O R S                       *
 ********************************************************************/

/*------------------------------------------------------------------*
 *								operator=							*
 *------------------------------------------------------------------*/
/**
 *	@brief		VVector assignment.
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 *	@param		vec	Vector whose values we are to inherit.
 *
 *	@returns	(VVector)	This VVector after assignment.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
const VVector& VVector::operator=(const VVector& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	w = vec.w;

	return *this;
}

/*------------------------------------------------------------------*
 *								operator==							*
 *------------------------------------------------------------------*/
/**
 *	@brief		VVector equality testing.
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 *	@param		vec	Vector to test against for equality.
 *
 *	@returns	(bool)	Whether or not the two vectors are equal.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
bool VVector::operator==(const VVector& vec) const
{
	return ((x == vec.x) && (y == vec.z) && (z == vec.z));
}

/*------------------------------------------------------------------*
 *								operator!=							*
 *------------------------------------------------------------------*/
/**
 *	@brief		VVector inequality testing.
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 *	@param		vec	Vector to test against for inequality.
 *
 *	@returns	(bool)	Whether or not the two vectors are unequal.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
bool VVector::operator!=(const VVector& vec) const
{
	return !(*this == vec);
}

/*------------------------------------------------------------------*
 *								operator+=							*
 *------------------------------------------------------------------*/
/**
 *	@brief		VVector addition.
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 *	@param		vec	Vector to add to this vector.
 *
 *	@returns	(VVector&)	This VVector after addition.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
const VVector& VVector::operator+=(const VVector& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	return *this;
}

/*------------------------------------------------------------------*
 *								operator-=							*
 *------------------------------------------------------------------*/
/**
 *	@brief		VVector decrement.
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 *	@param		vec	Vector to subtract from this vector.
 *
 *	@returns	(VVector&)	This VVector after subtraction.
 *
 *	@remarks	This is faster than '-' due to the extra constructor.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
const VVector& VVector::operator-=(const VVector& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;

	return *this;
}

/*------------------------------------------------------------------*
 *								operator*=							*
 *------------------------------------------------------------------*/
/**
 *	@brief		VVector scalar multiplication.
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 *	@param		s	Scalar value to multiply by.
 *
 *	@returns	(VVector&)	This VVector after multiplication.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
const VVector& VVector::operator*=(const float& s)
{
	x *= s;
	y *= s;
	z *= s;

	return *this;
}

/*------------------------------------------------------------------*
 *								operator/=							*
 *------------------------------------------------------------------*/
/**
 *	@brief		VVector scalar division.
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 *	@param		s	Scalar value to divide by.
 *
 *	@returns	(VVector&)	This VVector after division.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
const VVector& VVector::operator/=(const float& s)
{
	x /= s;
	y /= s;
	z /= s;

	return *this;
}

/*------------------------------------------------------------------*
 *								operator+=							*
 *------------------------------------------------------------------*/
/**
 *	@brief		VVector scalar addition.
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 *	@param		s	Scalar value to add to this VVector.
 *
 *	@returns	(VVector&)	This VVector after addition.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
const VVector& VVector::operator+=(const float& s)
{
	x += s;
	y += s;
	z += s;

	return *this;
}

/*------------------------------------------------------------------*
 *								operator-=							*
 *------------------------------------------------------------------*/
/**
 *	@brief		VVector scalar division.
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 *	@param		s	Scalar value to subtract.
 *
 *	@returns	(VVector&)	This VVector after subtraction.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
const VVector& VVector::operator-=(const float& s)
{
	x -= s;
	y -= s;
	z -= s;

	return *this;
}

/*------------------------------------------------------------------*
 *								operator*							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Dot product calculation.
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 *	@param		v	VVector to compute dot product with.
 *
 *	@returns	(float)	Dot product of the two vectors.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
float VVector::operator*(const VVector& v) const
{
	return (v.x*x + v.y*y + v.z*z);
}

/*------------------------------------------------------------------*
 *								operator*							*
 *------------------------------------------------------------------*/
/**
 *	@brief		VVector scaling
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 *	@param		s	Scalar value to multiply by.
 *
 *	@returns	(VVector) Result of the multiplication.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VVector VVector::operator*(const float& s) const
{
	return VVector(x*s, y*s, z*s);
}

/*------------------------------------------------------------------*
 *								operator/							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Vector scalar division.
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 *	@param		s	Scalar value to divide by.
 *
 *	@returns	(VVector)	Result of the division.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VVector VVector::operator/(const float& s) const
{
	return VVector(x/s, y/s, z/s);
}

/*------------------------------------------------------------------*
 *								operator+							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Vector scalar addition.
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 *	@param		s	Scalar value to add
 *
 *	@returns	(VVector)	Result of the addition.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VVector VVector::operator+(const float& s) const
{
	return VVector(x+s, y+s, z+s);
}

/*------------------------------------------------------------------*
 *								operator-							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Vector scalar subtraction.
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 *	@param		s	Scalar value to subtract.
 *
 *	@returns	(VVector)	Result of the subtraction.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VVector VVector::operator-(const float& s) const
{
	return VVector(x-s, y-s, z-s);
}

/*------------------------------------------------------------------*
 *								operator*							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Quaternion multiplication.
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 *	@param		q	VQuaternion to multiply by.
 *
 *	@returns	(VQuaternion)	Result of the multiplicaiton.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VQuaternion VVector::operator*(const VQuaternion& q) const
{
	return VQuaternion(q.w*x + q.z*y - q.y*z,
						q.w*y + q.x*z - q.z*x,
						q.w*z + q.y*x - q.x*y,
						-(q.x*x + q.y*y + q.z*z));
}

/*------------------------------------------------------------------*
 *								operator*							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Vector/Matrix multiplication.
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 *	@param		mat	VMatrix to multiply by.
 *
 *	@returns	(VVector)	Result of the multiplication.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VVector VVector::operator*(const VMatrix& mat) const
{
	VVector result;

	result.x = x*mat[0][0] + y*mat[1][0] + z*mat[2][0] + mat[3][0];
	result.y = x*mat[0][1] + y*mat[1][1] + z*mat[2][1] + mat[3][1];
	result.z = x*mat[0][2] + y*mat[1][2] + z*mat[2][2] + mat[3][2];
	result.w = x*mat[0][3] + y*mat[1][3] + z*mat[3][3] + mat[3][3];

	result.x = result.x / result.w;
	result.y = result.y / result.w;
	result.z = result.z / result.w;
	result.w = 1.0f;

	return result;
}


















/*------------------------------------------------------------------*
 *								operator+							*
 *------------------------------------------------------------------*/
/**
 *	@brief		VVector addition.
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 *	@param		vec	Vector to add to this vector.
 *
 *	@returns	(VVector&)	New vector representing the sum of the
 *							two VVectors.
 *
 *	@remarks	This is slower than '+=' due to the extra constructor.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VVector VVector::operator+(const VVector& vec) const
{
	return VVector(x + vec.x, y + vec.y, z + vec.z, 1.0f);
}

/*------------------------------------------------------------------*
 *								operator-							*
 *------------------------------------------------------------------*/
/**
 *	@brief		VVector subtraction.
 *	@author		Josh Williams
 *	@date		11-Sep-2004
 *
 *	@param		vec	Vector to subtract from this vector.
 *
 *	@returns	(VVector&)	VVector representing the difference of
 *							the two vectors.
 *
 *	@remarks	This is slower than '-=' due to the extra constructor.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VVector	VVector::operator-(const VVector& vec) const
{
	return VVector(x - vec.x, y - vec.y, z - vec.z);
}

/********************************************************************
 *                         C A L L B A C K S                        *
 ********************************************************************/

/********************************************************************
 *                         I N T E R N A L S                        *
 ********************************************************************/

} // End Namespace
