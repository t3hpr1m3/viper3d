/**
 *	@class		UDP::VQuaternion
 *
 *	@brief		Represents rotation around an axis.
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		10-Sep-2003
 *	@remarks	Used to handle rotations fo rigid 3D bodies.
 */
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
#if !defined(__VQUATERNION_H_INCLUDED__)
#define __VQUATERNION_H_INCLUDED__

#include "Globals.h"
#include "VMath.h"

namespace UDP
{

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

#endif // __VQUATERNION_H_INCLUDED__

