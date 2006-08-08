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
#if !defined(__VMATH_H_INCLUDED__)
#define __VMATH_H_INCLUDED__

#include "Globals.h"

#define SQR(x)	((x) * (x))
#define LIMIT_RANGE(low, value, high)\
{\
	if (value < low)\
		value = low;\
	else if (value > high)\
		value = high;\
}
#define FLOAT_EQ(x,v) (((v) - 0.005f) < (x) && (x) < ((v) + 0.005f))

namespace UDP
{

/**
 *	@class		UDP::VMath
 *
 *	@brief		Collection of math related functions.
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		11-Sep-2003
 *	@remarks	Most of these are just wrappers around the standard C calls.
 *				I collected them here in case we find more effecient ways to
 *				handle trigonometry.
 */
class VMath
{
public:
	/*==================================*
	 *	   CONSTRUCTION/DESTRUCTION		*
	 *==================================*/
private:
	VMath() {}
	virtual ~VMath() {};

public:
	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/
public:	
	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	static float	Abs(float fValue);
	static float	ACos(float fValue);
	static float	ASin(float fValue);
	static float	ATan(float fValue);
	static float	Cos(float fValue);
	static float	Sin(float fValue);
	static float	Tan(float fValue);
	static float	Sqrt(float fValue);
	static float	DegToRad(float degrees);
	static float	RadToDeg(float radians);
	static float	Modulus(float dividend, int divisor);

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
public:
	static const float PI;
	static const float TWO_PI;
	static const float HALF_PI;
	static const VVector VECTOR_ZERO;
	static const VVector VECTOR_UNIT_X;
	static const VVector VECTOR_UNIT_Y;
	static const VVector VECTOR_UNIT_Z;
	static const VVector VECTOR_UNIT_SCALE;
	static const VMatrix MATRIX_ZERO;
	static const VMatrix MATRIX_IDENTITY;
	static const VQuaternion QUATERNION_ZERO;
	static const VQuaternion QUATERNION_IDENTITY;
};

/**
 *	@class		UDP::VVector
 *
 *	@brief		Represents a vector in world space
 *	@author		Josh Williams <volzman19@yahoo.com>
 *	@version	0.1.0
 *	@date		10-Sep-2004
 */
class VVector
{
public:
	/*==================================*
	 *	   CONSTRUCTION/DESTRUCTION		*
	 *==================================*/
	VVector();
	VVector(float _x = 0, float _y = 0, float _z = 0);
	VVector(const VVector &vec);
	virtual ~VVector();

	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/
 	float			Length();
	float			SquaredLength() const;
	VVector			UnitVector();
	
	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	void			SetValues(float _x, float _y, float _z, float _w = 0);
	void			Negate();
	void			Normalize();
	float			AngleWith(VVector& v);
	VVector			Rotate(const float angle, const VVector &normal) const;
	void			RotateWith(const VMatrix& m);
	void			InvRotateWith(const VMatrix& m);
	void			Difference(const VVector& v1, const VVector& v2);
	VVector			CrossProduct(const VVector &vec) const;
	void			Cross(const VVector& v1, const VVector& v2);
	float			DotProduct(const VVector &vec) const;
	VQuaternion		GetRotationTo(const VVector& dest) const;

	/*==================================*
	 *			   OPERATORS			*
	 *==================================*/
	const VVector&	operator=(const VVector &vec);
	bool			operator==(const VVector &vec) const;
	bool			operator!=(const VVector &vec) const;
	const VVector&	operator+=(const VVector &vec);
	const VVector&	operator-=(const VVector &vec);
	const VVector&	operator*=(const float &s);
	const VVector&	operator/=(const float &s);
	const VVector&	operator+=(const float &s);
	const VVector&	operator-=(const float &s);
	float			operator*(const VVector& v) const;
	VVector			operator*(const float& s) const;
	VVector			operator/(const float& s) const;
	VVector			operator+(const float& s) const;
	VVector			operator-(const float& s) const;
	VQuaternion		operator*(const VQuaternion& q) const;
	VVector			operator*(const VMatrix& m) const;
	VVector			operator+(const VVector &vec) const;
	VVector			operator-(const VVector &vec) const;

public:
	/*==================================*
	 *			   VARIABLES			*
	 *==================================*/
	float	x;
	float	y;
	float	z;
	float	w;
};

/**
 *	@class		UDP::VMatrix
 *
 *	@brief		Represents a 4x4 matrix, used in GL routines.
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		11-Sep-2004
 */
class VMatrix
{
public:
	/*==================================*
	 *	   CONSTRUCTION/DESTRUCTION		*
	 *==================================*/
	VMatrix();
	VMatrix(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33);
	virtual ~VMatrix() {}

	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/
	float* 			operator[](unsigned nRow);
	const float*	operator[](unsigned nRow) const;

	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	void			RotaX(const float& a);
	void			RotaY(const float& a);
	void			RotaZ(const float& a);
	void			Rota(const VVector &v);
	void			Rota(const float& x, const float& y, const float& z);
	void			RotaArbi(const VVector& vAxis, const float& a);
	void			ApplyInverseRota(VVector *pVec);
	void			Translate(const float& dx, const float& dy, const float& dz);
	void			SetTranslation(const VVector& vc, bool EraseContent=false);
	VVector			GetTranslation();
	void			Billboard(const VVector& vPos, const VVector& vDir,
								VVector vWorldUp = VMath::VECTOR_UNIT_Y);
	void			LookAt(const VVector& vPos, const VVector& vLookAt,
								VVector vWorldUp = VMath::VECTOR_UNIT_Y);
	void			TransposeOf(const VMatrix& mat);
	void			InverseOf(const VMatrix& mat);

	/*==================================*
	 *			   OPERATORS			*
	 *==================================*/
	VMatrix			operator*(const VMatrix& mat) const;
	VVector			operator*(const VVector& vec) const;
	void			operator=(const VMatrix &mat);
	

	/**
	 *	@brief		Converts this matrix to a GL matrix (float array)
	 *	@author		Josh Williams
	 *	@date		12-Sep-2003
	 *
	 *	@remarks	OpenGL expects an array of float value instead of an
	 *				actual matrix.
	 *
	 *	@param		mat4	Matrix to be converted to array
	 *
	 *	@returns	void
	 */
	void			MakeGLMatrix(float gl_matrix[16]);

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
protected:
	union
	{
		float m[4][4];
		float _m[16];
	};
};

/**
 *	@class		UDP::VQuaternion
 *
 *	@brief		Represents rotation around an axis.
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		10-Sep-2003
 *	@remarks	Used to handle rotations fo rigid 3D bodies.
 */
class VQuaternion
{
public:
	/*==================================*
	 *	   CONSTRUCTION/DESTRUCTION		*
	 *==================================*/
	VQuaternion(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f,
						float _w = 0.0f);
	VQuaternion(const VQuaternion& q);
	virtual ~VQuaternion() {};

	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/
	float 			GetMagnitude() const;
	VVector			GetVector() const;
	float			GetScalar() const;
	float			GetAngle();

	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	void			FromEulerAngles(const float& ax, const float& ay,
								const float az);
	void			ToAxes(VVector* axes);
	void			ToRotationMatrix(VMatrix& rot) const;
	void			CreateMatrix(float *pMatrix) const;
	void			FromAngleAxis(const float& rAngle, const VVector& rAxis);
	void			Normalize();
	void			ToAxisAngle(VVector &vec, float &angle) const;
	void			Conjugate(const VQuaternion& q);
	void			GetEulerAngles(float *fRoll, float *fPitch,
								float *fYaw) const;
	void			Rotate(const VQuaternion& q1, const VQuaternion q2);
	VVector			Rotate(const VVector& vec);
	

	/*==================================*
	 *			   OPERATORS			*
	 *==================================*/
	VQuaternion& 	operator=(const VQuaternion& q);

	VQuaternion&	operator*=(const float& s);
	VQuaternion		operator*(const float& s);
	VQuaternion&	operator/=(const float& s);
	VQuaternion		operator/(const float& s);

	VQuaternion		operator*(const VVector& vec) const;

	VQuaternion&	operator+=(const VQuaternion& q);
	VQuaternion		operator+(const VQuaternion& q) const;
	VQuaternion&	operator-=(const VQuaternion& q);
	VQuaternion		operator-(const VQuaternion& q) const;
	VQuaternion&	operator*=(const VQuaternion& q);
	VQuaternion		operator*(const VQuaternion& q) const;
	VQuaternion		operator~() const;

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
public:
	float		x;
	float		y;
	float		z;
	float		w;
};


} // End Namespace

#endif // __MATH_H_INCLUDED__
