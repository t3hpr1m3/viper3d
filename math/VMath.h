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

/* System Headers */
#include <iostream>

/* Local Headers */
#include "VGlobals.h"

using std::ostream;

/* Macros */
#define SQR(x)	((x) * (x))
#define LIMIT_RANGE(low, value, high)\
{\
	if (value < low)\
		value = low;\
	else if (value > high)\
		value = high;\
}
#define FLOAT_EQ(x,v) (((v) - 0.005f) < (x) && (x) < ((v) + 0.005f))

/* Defines */
#define VFRONT		0
#define VBACK		1
#define VPLANAR		2
#define VCLIPPED	3
#define VCULLED		4
#define VVISIBLE	5

namespace UDP
{

/* forward class declarations */
class VVector;
class VMatrix;
class VQuaternion;
class VRay;
class VPlane;
class VObb;
class VAabb;
class VPolygon;

/**
 *	@class		VMath
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
	static const VQuaternion QUATERNION_ZERO;
	static const VQuaternion QUATERNION_IDENTITY;
};

/*============================================================================*/

/**
 *	@class		VVector
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
	VVector(float _x = 0, float _y = 0, float _z = 0);
	VVector(const VVector &vec);
	~VVector();

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
	VVector			operator-() const;
	friend ostream&	operator<<(ostream& os, const VVector& vec);

public:
	/*==================================*
	 *			   VARIABLES			*
	 *==================================*/
	float	x, y, z, w;
	static const VVector VECTOR_ZERO;
	static const VVector VECTOR_UNIT_X;
	static const VVector VECTOR_UNIT_Y;
	static const VVector VECTOR_UNIT_Z;
	static const VVector VECTOR_UNIT_SCALE;
};

inline
VVector VVector::operator-() const
{
	return VVector(-x, -y, -z);
}

inline
ostream& operator<<(ostream& os, const VVector& vec)
{
	os << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w;
	return os;
}

/*============================================================================*/

/**
 *	@class		VMatrix
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
	~VMatrix() {}

	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/
	float* 			operator[](unsigned nRow);
	const float* const operator[](unsigned nRow) const;

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
								VVector vWorldUp = VVector::VECTOR_UNIT_Y);
	void			LookAt(const VVector& vPos, const VVector& vLookAt,
								VVector vWorldUp = VVector::VECTOR_UNIT_Y);
	void			TransposeOf(const VMatrix& mat);
	void			InverseOf(const VMatrix& mat);
	VMatrix			Transpose() const;

	/*==================================*
	 *			   OPERATORS			*
	 *==================================*/
	VMatrix			operator*(const VMatrix& mat) const;
	VVector			operator*(const VVector& vec) const;
	void			operator=(const VMatrix &mat);
	VMatrix			operator-() const;
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
public:
	static const VMatrix MATRIX_ZERO;
	static const VMatrix MATRIX_IDENTITY;
};

/*============================================================================*/

/**
 *	@class		VQuaternion
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
								const float& az);
	void			ToAxes(VVector* axes) const;
	void			ToRotationMatrix(VMatrix& rot) const;
	void			CreateMatrix(float *pMatrix) const;
	void			FromAngleAxis(const float& rAngle, const VVector& rAxis);
	void			Normalize();
	void			ToAxisAngle(VVector &vec, float &angle) const;
	void			Conjugate(const VQuaternion& q);
	void			GetEulerAngles(float *fRoll, float *fPitch,
								float *fYaw) const;
	void			Rotate(const VQuaternion& q1, const VQuaternion& q2);
	VVector			Rotate(const VVector& vec);
	

	/*==================================*
	 *			   OPERATORS			*
	 *==================================*/
	VQuaternion& 	operator=(const VQuaternion& q);

	VQuaternion&	operator*=(const float& s);
	VQuaternion		operator*(const float& s) const;
	VQuaternion&	operator/=(const float& s);
	VQuaternion		operator/(const float& s) const;

	//VQuaternion		operator*(const VVector& vec) const;
	VVector			operator*(const VVector& pVec) const;

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

/*============================================================================*/

/**
 *	@class		VRay
 *
 *	@brief		Basic ray class to test for intersection.
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		12-Sep-2003
 *	@remarks	Used mainly for collision detection.
 */
class VRay
{
public:
	/*==================================*
	 *	   CONSTRUCTION/DESTRUCTION		*
	 *==================================*/
	VRay();
	VRay(const VVector& vOrig, const VVector& vDir);
	virtual ~VRay();

	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/
	const VVector&	GetOrigin() const;
	const VVector&	GetDirection() const;	

	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	void			SetValues(const VVector& vOrig, const VVector& vDir);
	void			SetOrigin(const VVector& vOrig);
	void			SetDirection(const VVector& vDir);
	void			DeTransform(const VMatrix& mat);
	bool			Intersects(const VVector& vec0, const VVector& vec1,
								const VVector& vec2, bool bCull, float *t);
	bool			Intersects(const VVector& vec0, const VVector& vec1,
								const VVector& vec2, bool bCull, float fL,
								float *t);
	bool			Intersects(const VPlane& plane, bool bCull, float *t,
								VVector *vHit) const;
	bool			Intersects(const VPlane& plane, bool bCull, float fL,
								float *t, VVector *vHit) const;
	bool			Intersects(const VAabb& aabb, float *t);
	bool			Intersects(const VAabb& aabb, float fL, float *t);
	bool			Intersects(const VObb& obb, float *t);
	bool			Intersects(const VObb& obb, float fL, float *t);

	/*==================================*
	 *			   OPERATORS			*
	 *==================================*/

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
	VVector			m_vOrig;
	VVector			m_vDir;
};

inline
const VVector& VRay::GetOrigin() const
{
	return m_vOrig;
}

inline
const VVector& VRay::GetDirection() const
{
	return m_vDir;
}

inline
void VRay::SetOrigin(const VVector& vOrig)
{
	m_vOrig = vOrig;
}

inline
void VRay::SetDirection(const VVector& vDir)
{
	m_vDir = vDir;
}

/*============================================================================*/

/**
 *	@class		VPlane
 *
 *	@brief		Basic plane class.
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		12-Sep-2003
 *	@remarks	Used mainly for collision detection.
 */
class VPlane
{
public:
	/*==================================*
	 *	   CONSTRUCTION/DESTRUCTION		*
	 *==================================*/
	VPlane();
	VPlane(const VVector& vN, const VVector& vP);
	VPlane(const VVector& vN, const VVector& vP, const float& fD);
	VPlane(const VVector& v0, const VVector& v1, const VVector& v2);
	~VPlane();

	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/

	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	void			Set(const VVector& vN, const VVector& vP);
	void			Set(const VVector& vN, const VVector& vP, const float& fD);
	void			Set(const VVector& v0, const VVector& v1,
								const VVector& v2);
	float			Distance(const VVector& vPoint) const;
	int				Classify(const VVector& vPoint) const;
	int				Classify(const VPolygon& Polygon) const;
	bool			Clip(const VRay *pRay, const float& fL, VRay *pF,
								VRay *pB) const;
	bool			Intersects(const VVector& vec0, const VVector& vec1,
								const VVector& vec2) const;
	bool			Intersects(const VPlane& plane, VRay *pIntersection) const;
	bool			Intersects(VAabb& aabb) const;
	bool			Intersects(VObb& obb) const;

	/*==================================*
	 *			   OPERATORS			*
	 *==================================*/

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
	VVector			m_vN;
	VVector			m_vPoint;
	float			m_fD;
};

/*============================================================================*/

/**
 *	@class		VObb
 *
 *	@brief		Oriented bounding box.
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		12-Sep-2003
 *	@remarks	Used mainly for collision detection.
 */
class VObb
{
public:
	/*==================================*
	 *	   CONSTRUCTION/DESTRUCTION		*
	 *==================================*/
	VObb();
	virtual ~VObb();

	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/

	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	void			DeTransform(const VObb& obb, const VMatrix& mat);
	bool			Intersects(const VRay& ray, float *t);
	bool			Intersects(const VRay& ray, float fL, float *t);
	bool			Intersects(const VObb &obb);
	bool			Intersects(const VVector& v0, const VVector& v1,
								const VVector& v2);
	int				Cull(const VPlane *pPlanes, int nNumPlanes);

	/*==================================*
	 *			   OPERATORS			*
	 *==================================*/

protected:
	/*==================================*
	 *             CALLBACKS			*
	 *==================================*/

private:
	/*==================================*
	 *             INTERNALS            *
	 *==================================*/
	void			ObbProj(const VObb& obb, const VVector& vV,
								float *pfMin, float *pfMax);
	void			TriProj(const VVector& v0, const VVector& v1,
								const VVector& v2, const VVector& vV,
								float *pfMin, float *pfMax);

private:
	/*==================================*
	 *             VARIABLES            *
	 *==================================*/
public:
	float			fA0, fA1, fA2;	/**< Half axis length */
	VVector			vA0, vA1, vA2;	/**< Box axis */
	VVector			vCenter;		/**< centerpoint */
};

/*============================================================================*/

/**
 *	@class		VAabb
 *
 *	@brief		Axis-aligned bounding box
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		12-Sep-2003
 *	@remarks	Used mainly for collision detection.
 */
class VAabb
{
public:
	/*==================================*
	 *	   CONSTRUCTION/DESTRUCTION		*
	 *==================================*/
	VAabb();
	VAabb(const VVector& vMin, const VVector& vMax);
	virtual ~VAabb();

	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/
	const VVector&	GetMin() const;
	const VVector&	GetMax() const;
	const VVector&	GetCenter() const;
	void			GetPlanes(VPlane *pPlanes);

	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	void			Construct(const VObb *pObb);
	int				Cull(const VPlane *pPlanes, int nNumPlanes);
	bool			Contains(const VRay& ray, float fL);
	bool			Intersects(const VRay& ray, float *t);
	bool			Intersects(const VRay& ray, float fL, float *t);
	bool			Intersects(const VAabb& aabb);
	bool			Intersects(const VVector& v0);
	void			SetMin(const VVector& vMin);
	void			SetMax(const VVector& vMax);
	void			SetCenter(const VVector& vCenter);

	/*==================================*
	 *			   OPERATORS			*
	 *==================================*/

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
	VVector			m_vMin, m_vMax;	/**< Box extreme points */
	VVector			m_vCenter;	/**< centerpoint */
};

inline
const VVector& VAabb::GetMin() const
{
	return m_vMin;
}

inline
const VVector& VAabb::GetMax() const
{
	return m_vMax;
}

inline
const VVector& VAabb::GetCenter() const
{
	return m_vCenter;
}

inline
void VAabb::SetMin(const VVector& vMin)
{
	m_vMin = vMin;
}

inline
void VAabb::SetMax(const VVector& vMax)
{
	m_vMax = vMax;
}

inline
void VAabb::SetCenter(const VVector& vCenter)
{
	m_vCenter = vCenter;
}

/*============================================================================*/

/**
 *	@class		VPolygon
 *
 *	@brief		Basic polygon class.
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		12-Sep-2003
 *	@remarks	Used mainly for collision detection.
 */
class VPolygon
{
public:
	/*==================================*
	 *	   CONSTRUCTION/DESTRUCTION		*
	 *==================================*/
	VPolygon();
	VPolygon(const VPolygon& poly);
	virtual ~VPolygon();

	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/
	const int		GetNumPoints() const;
	const int		GetNumIndis() const;
	const VVector*	GetPoints() const;
	const VUINT*	GetIndices() const;
	const VPlane&	GetPlane() const;
	const VAabb&	GetAabb() const;
	const VUINT		GetFlag() const;

	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	void			Set(const VVector *pPoints, int nNumP, const VUINT *pIndis,
								int nNumI);
	void			Clip(const VPlane& plane, VPolygon *pFront,
								VPolygon *pBack);
	void			Clip(const VAabb& aabb);
	int				Cull(const VAabb& aabb);
	void			SwapFaces();
	bool			Intersects(const VRay& ray, bool bCull, float *t);
	bool			Intersects(const VRay& ray, bool bCull, float fL, float *t);
	void			SetFlag(VUINT n);

	/*==================================*
	 *			   OPERATORS			*
	 *==================================*/
	const VPolygon&	operator=(const VPolygon &poly);

protected:
	/*==================================*
	 *             CALLBACKS			*
	 *==================================*/

private:
	/*==================================*
	 *             INTERNALS            *
	 *==================================*/
	void			CalcBoundingBox(void);

private:
	/*==================================*
	 *             VARIABLES            *
	 *==================================*/
	VPlane			m_Plane;	/**< plane which poly lies in */
	VUINT			m_nNumP;	/**< number of points */
	VUINT			m_nNumI;	/**< number of indices */
	VAabb			m_Aabb;		/**< bounding box */
	VUINT			m_nFlag;	/**< user defined flag */
	VVector			*m_pPoints;	/**< list of points */
	VUINT			*m_pIndis;	/**< index list */
};

inline
const int VPolygon::GetNumPoints() const
{
	return m_nNumP;
}

inline
const int VPolygon::GetNumIndis() const
{
	return m_nNumI;
}

inline
const VVector* VPolygon::GetPoints() const
{
	return m_pPoints;
}

inline
const VUINT* VPolygon::GetIndices() const
{
	return m_pIndis;
}

inline
const VPlane& VPolygon::GetPlane() const
{
	return m_Plane;
}

inline
const VAabb& VPolygon::GetAabb() const
{
	return m_Aabb;
}

inline
const VUINT VPolygon::GetFlag() const
{
	return m_nFlag;
}

inline
void VPolygon::SetFlag(VUINT nFlag)
{
	m_nFlag = nFlag;
}

} // End Namespace

#endif // __MATH_H_INCLUDED__
