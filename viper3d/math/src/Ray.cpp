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

/* Local Headers */

namespace UDP
{

/********************************************************************
 *          C O N S T R U C T I O N / D E S T R U C T I O N         *
 ********************************************************************/
VRay::VRay()
{

}

VRay::VRay(const VVector& vOrig, const VVector& vDir)
{
	m_vOrig = vOrig;
	m_vDir	= vDir;
}

VRay::~VRay()
{

}

/********************************************************************
 *                        A T T R I B U T E S                       *
 ********************************************************************/

/********************************************************************
 *                        O P E R A T I O N S                       *
 ********************************************************************/

/*------------------------------------------------------------------*
 *							  SetValues()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Quick assignment function.
 *	@author		Josh Williams
 *	@date		12-Sep-2004
 *
 *	@param		vOrig	New origin vector.
 *	@param		vDir	New direction vector.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VRay::SetValues(const VVector& vOrig, const VVector& vDir)
{
	m_vOrig = vOrig;
	m_vDir	= vDir;
}

/*------------------------------------------------------------------*
 *							  DeTransform()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Transforms this Ray to the coordinate system
 *				represented by the supplied VMatrix.
 *	@author		Josh Williams
 *	@date		12-Sep-2004
 *
 *	@param		mat		VMatrix representation of destination
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VRay::DeTransform(const VMatrix& mat)
{
	VMatrix mInv;
	VMatrix mTmp = mat;

	/* invert translation */
	m_vOrig.x -= mTmp[3][0];
	m_vOrig.y -= mTmp[3][1];
	m_vOrig.z -= mTmp[3][2];

	/* delete transformation from matrix */
	mTmp[3][0] = mTmp[3][1] = mTmp[3][2] = 0.0f;

	/* invert matrix and apply it to this VRay */
	mInv.InverseOf(mTmp);

	m_vOrig = m_vOrig * mInv;
	m_vDir	= m_vDir * mInv;
}

/*------------------------------------------------------------------*
 *							  Intersects()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Tests for intersection with a triangle.
 *	@author		Josh Williams
 *	@date		12-Sep-2004
 *
 *	@param		vec0
 *	@param		vec1
 *	@param		vec2	VVectors representing the triangle.
 *	@param		bCull	Perform front/back face culling?
 *	@param		t		Optional pointer to receive the point on the
 *						ray where intersection occurs.
 *
 *	@returns	(bool)	Whether or not intersection occurs.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
bool VRay::Intersects(const VVector& vec0, const VVector& vec1,
						const VVector& vec2, bool bCull, float *t)
{
	VVector pvec, tvec, qvec;

	VVector edge1 = vec1 - vec0;
	VVector edge2 = vec2 - vec0;

	pvec.Cross(m_vDir, edge2);

	/* if close to 0, ray is parallel */
	float det = edge1 * pvec;
	if ((bCull) && (det < 0.0001f))
		return false;
	else if ((det < 0.0001f) && (det > -0.0001f))
		return false;

	/* distance to plane, <0 means beyond plane */
	tvec = m_vOrig - vec0;
	float u = tvec * pvec;
	if (u < 0.0f || u > det)
		return false;

	qvec.Cross(tvec, edge1);
	float v = m_vDir * qvec;
	if (v < 0.0f || u+v > det)
		return false;

	if (t)
	{
		*t = edge2 * qvec;
		float fInvDet = 1.0f / det;
		*t *= fInvDet;
	}

	return true;
}

/**
 *	@overload
 *
 *	@param		vec0
 *	@param		vec1
 *	@param		vec2	VVectors representing the triangle.
 *	@param		bCull	Perform front/back face culling?
 *	@param		fL		Line segment end-point.
 *	@param		t		Optional pointer to receive the point on the
 *						ray where intersection occurs.
 */
bool VRay::Intersects(const VVector& vec0, const VVector& vec1,
						const VVector& vec2, bool bCull, float fL, float *t)
{
	VVector pvec, tvec, qvec;

	VVector edge1 = vec1 - vec0;
	VVector edge2 = vec2 - vec0;

	pvec.Cross(m_vDir, edge2);

	/* if close to 0, ray is parallel */
	float det = edge1 * pvec;
	if ((bCull) && (det < 0.0001f))
		return false;
	else if ((det < 0.0001f) && (det > -0.0001f))
		return false;

	/* distance to plane, <0 means beyond plane */
	tvec = m_vOrig - vec0;
	float u = tvec * pvec;
	if (u < 0.0f || u > det)
		return false;

	qvec.Cross(tvec, edge1);
	float v = m_vDir * qvec;
	if (v < 0.0f || u+v > det)
		return false;

	if (t)
	{
		*t = edge2 * qvec;
		float fInvDet = 1.0f / det;
		*t *= fInvDet;
		/* collision but not on segment? */
		if (*t > fL)
			return false;
	}
	else
	{
		/* collision but not on segment? */
		float f = (edge2*qvec) * (1.0f / det);
		if (f > fL)
			return false;
	}

	return true;
}

/*------------------------------------------------------------------*
 *							  Intersects()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Tests for intersection with a Plane.
 *	@author		Josh Williams
 *	@date		12-Sep-2004
 *
 *	@param		plane	Used for intersection testing.
 *	@param		bCull	Perform front/back face culling?
 *	@param		t		Optional pointer to receive the point on the
 *						ray where intersection occurs.
 *	@param		vHit	Point at which intersection occurred.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
bool VRay::Intersects(const VPlane& plane, bool bCull, float *t,
						VVector *vHit) const
{
	float Vd = plane.m_vN * m_vDir;

	/* ray parallel to plane */
	if (VMath::Abs(Vd) < 0.00001f)
		return false;

   /* normal pointing away from ray dir */
   /* => intersection backface if any	*/
   if (bCull && (Vd > 0.0f))
      return false;

	float Vo = -((plane.m_vN * m_vOrig) + plane.m_fD);

	float _t = Vo / Vd;

	/* intersection behind ray origin */
	if (_t < 0.0f)
		return false;

	if (vHit)
	{
		(*vHit) = m_vOrig + (m_vDir * _t);
	}

	if (t)
      (*t) = _t;

	return true;
}

/**
 *	@overload
 *
 *	@param		plane	Used for intersection testing.
 *	@param		bCull	Perform front/back face culling?
 *	@param		fL		Line segment end-point.
 *	@param		t		Optional pointer to receive the point on the
 *						ray where intersection occurs.
 *	@param		vHit	Point at which intersection occurred.
 */
bool VRay::Intersects(const VPlane& plane, bool bCull, float fL,
						float *t, VVector *vHit) const
{
	float Vd = plane.m_vN * m_vDir;

	/* ray parallel to plane */
	if (VMath::Abs(Vd) < 0.00001f)
		return false;

	/* normal pointing away from ray dir	*/
	/* => intersection backface if any		*/
	if (bCull && (Vd > 0.0f))
		return false;

	float Vo = -((plane.m_vN * m_vOrig) + plane.m_fD);

	float _t = Vo / Vd;

	/* intersection behind ray origin or beyond valid range */
	if ((_t < 0.0f) || (_t > fL))
		return false;

	if (vHit)
	{
		(*vHit) = m_vOrig + (m_vDir * _t);
	}

	if (t)
		(*t) = _t;

   return true;
}

/*------------------------------------------------------------------*
 *							  Intersects()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Tests for intersection with a VAabb.
 *	@author		Josh Williams
 *	@date		12-Sep-2004
 *
 *	@param		aabb	Target of testing.
 *	@param		t		Optional pointer to receive the point on the
 *						ray where intersection occurs.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
bool VRay::Intersects(const VAabb& aabb, float *t)
{
	float t0, t1, tmp;
	float tNear = -999999.9f;
	float tFar  =  999999.9f;
	float epsilon = 0.00001f;
	VVector MaxT;

	/* first pair of planes */
	if (VMath::Abs(m_vDir.x) < epsilon)
	{
		if ((m_vOrig.x < aabb.GetMin().x) ||
			(m_vOrig.x > aabb.GetMax().x))
			return false;
	}
	t0 = (aabb.GetMin().x - m_vOrig.x) / m_vDir.x;
	t1 = (aabb.GetMax().x - m_vOrig.x) / m_vDir.x;
	if (t0 > t1)
	{
		tmp=t0;
		t0=t1;
		t1=tmp;
	}
	if (t0 > tNear)
		tNear = t0;
	if (t1 < tFar)
		tFar = t1;
	if (tNear > tFar)
		return false;
	if (tFar < 0)
		return false;

	/* second pair of planes */
	if (VMath::Abs(m_vDir.y) < epsilon)
	{
		if ((m_vOrig.y < aabb.GetMin().y) ||
			(m_vOrig.y > aabb.GetMax().y))
			return false;
	}
	t0 = (aabb.GetMin().y - m_vOrig.y) / m_vDir.y;
	t1 = (aabb.GetMax().y - m_vOrig.y) / m_vDir.y;
	if (t0 > t1)
	{
		tmp=t0;
		t0=t1;
		t1=tmp;
	}
	if (t0 > tNear)
		tNear = t0;
	if (t1 < tFar)
		tFar = t1;
	if (tNear > tFar)
		return false;
	if (tFar < 0)
		return false;

	/* third pair of planes */
	if (VMath::Abs(m_vDir.z) < epsilon)
	{
		if ((m_vOrig.z < aabb.GetMin().z) ||
			(m_vOrig.z > aabb.GetMax().z))
			return false;
	}
	t0 = (aabb.GetMin().z - m_vOrig.z) / m_vDir.z;
	t1 = (aabb.GetMax().z - m_vOrig.z) / m_vDir.z;
	if (t0 > t1)
	{
		tmp=t0;
		t0=t1;
		t1=tmp;
	}
	if (t0 > tNear)
		tNear = t0;
	if (t1 < tFar)
		tFar = t1;
	if (tNear > tFar)
		return false;
	if (tFar < 0)
		return false;

	if (tNear > 0)
	{
		if (t)
			*t = tNear;
	}
	else
	{
		if (t)
			*t = tFar;
	}
	return true;
}

/**
 *	@overload
 *
 *	@param		aabb	Target of testing.
 *	@param		fL		Line segment end-point.
 *	@param		t		Optional pointer to receive the point on the
 *						ray where intersection occurs.
 */
bool VRay::Intersects(const VAabb& aabb, float fL, float *t)
{
	float t0, t1, tmp, tFinal;
	float tNear = -999999.9f;
	float tFar  =  999999.9f;
	float epsilon = 0.00001f;
	VVector MaxT;

	/* first pair of planes */
	if (VMath::Abs(m_vDir.x) < epsilon)
	{
		if ((m_vOrig.x < aabb.GetMin().x) ||
			(m_vOrig.x > aabb.GetMax().x))
			return false;
	}
	t0 = (aabb.GetMin().x - m_vOrig.x) / m_vDir.x;
	t1 = (aabb.GetMax().x - m_vOrig.x) / m_vDir.x;
	if (t0 > t1)
	{
		tmp = t0;
		t0 = t1;
		t1 = tmp;
	}
	if (t0 > tNear)
		tNear = t0;
	if (t1 < tFar)
		tFar = t1;
	if (tNear > tFar)
		return false;
	if (tFar < 0)
		return false;

	/* second pair of planes */
	if (VMath::Abs(m_vDir.y) < epsilon)
	{
		if ((m_vOrig.y < aabb.GetMin().y) ||
			(m_vOrig.y > aabb.GetMax().y))
			return false;
	}
	t0 = (aabb.GetMin().y - m_vOrig.y) / m_vDir.y;
	t1 = (aabb.GetMax().y - m_vOrig.y) / m_vDir.y;
	if (t0 > t1)
	{
		tmp = t0;
		t0 = t1;
		t1 = tmp;
	}
	if (t0 > tNear)
		tNear = t0;
	if (t1 < tFar)
		tFar = t1;
	if (tNear > tFar)
		return false;
	if (tFar < 0)
		return false;

	/* third pair of planes */
	if (VMath::Abs(m_vDir.z) < epsilon)
	{
		if ((m_vOrig.z < aabb.GetMin().z) ||
			(m_vOrig.z > aabb.GetMax().z))
			return false;
	}
	t0 = (aabb.GetMin().z - m_vOrig.z) / m_vDir.z;
	t1 = (aabb.GetMax().z - m_vOrig.z) / m_vDir.z;
	if (t0 > t1)
	{
		tmp = t0;
		t0 = t1;
		t1 = tmp;
	}
	if (t0 > tNear)
		tNear = t0;
	if (t1 < tFar)
		tFar = t1;
	if (tNear > tFar)
		return false;
	if (tFar < 0)
		return false;

	if (tNear > 0)
		tFinal = tNear;
	else
		tFinal = tFar;

	if (tFinal > fL)
		return false;
	if (t)
		*t = tFinal;

	return true;
}

/*------------------------------------------------------------------*
 *							  Intersects()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Tests for intersection with an Obb.
 *	@author		Josh Williams
 *	@date		12-Sep-2004
 *
 *	@param		obb	Target of testing.
 *	@param		t	Optional pointer to receive the point on the
 *					ray where intersection occurs.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
bool VRay::Intersects(const VObb& obb, float *t)
{
	float e, f, t1, t2, temp;
	float tmin = -99999.9f, tmax = +99999.9f;

	VVector vP = obb.vCenter - m_vOrig;

	/* 1st slap */
	e = obb.vA0 * vP;
	f = obb.vA0 * m_vDir;
	if (VMath::Abs(f) > 0.00001f)
	{
		t1 = (e + obb.fA0) / f;
		t2 = (e - obb.fA0) / f;

		if (t1 > t2)
		{
			temp = t1;
			t1 = t2;
			t2 = temp;
		}
		if (t1 > tmin)
			tmin = t1;
		if (t2 < tmax)
			tmax = t2;
		if (tmin > tmax)
			return false;
		if (tmax < 0.0f)
			return false;
	}
	else if (((-e - obb.fA0) > 0.0f) || ((-e + obb.fA0) < 0.0f))
		return false;

	/* 2nd slap */
	e = obb.vA1 * vP;
	f = obb.vA1 * m_vDir;
	if (VMath::Abs(f) > 0.00001f)
	{
		t1 = (e + obb.fA1) / f;
		t2 = (e - obb.fA1) / f;

		if (t1 > t2)
		{
			temp = t1;
			t1 = t2;
			t2 = temp;
		}
		if (t1 > tmin)
			tmin = t1;
		if (t2 < tmax)
			tmax = t2;
		if (tmin > tmax)
			return false;
		if (tmax < 0.0f)
			return false;
	}
	else if (((-e - obb.fA1) > 0.0f) || ((-e + obb.fA1) < 0.0f))
		return false;

	/* 3rd slap */
	e = obb.vA2 * vP;
	f = obb.vA2 * m_vDir;
	if (VMath::Abs(f) > 0.00001f)
	{
		t1 = (e + obb.fA2) / f;
		t2 = (e - obb.fA2) / f;

		if (t1 > t2)
		{
			temp = t1;
			t1 = t2;
			t2 = temp;
		}
		if (t1 > tmin)
			tmin = t1;
		if (t2 < tmax)
			tmax = t2;
		if (tmin > tmax)
			return false;
		if (tmax < 0.0f)
			return false;
	}
	else if (((-e - obb.fA2) > 0.0f) || ((-e + obb.fA2) < 0.0f))
		return false;

	if (tmin > 0.0f)
	{
		if (t)
			*t = tmin;
		return true;
	}

	if (t)
		*t = tmax;

	return true;
}

/**
 *	@overload
 *
 *	@param		obb	Target of testing.
 *	@param		fL	Line segment end-point.
 *	@param		t	Optional pointer to receive the point on the
 *					ray where intersection occurs.
 */
bool VRay::Intersects(const VObb& obb, float fL, float *t)
{
	float e, f, t1, t2, temp;
	float tmin = -99999.9f, tmax = +99999.9f;

	VVector vP = obb.vCenter - m_vOrig;

	/* 1st slap */
	e = obb.vA0 * vP;
	f = obb.vA0 * m_vDir;
	if (VMath::Abs(f) > 0.00001f)
	{
		t1 = (e + obb.fA0) / f;
		t2 = (e - obb.fA0) / f;

		if (t1 > t2)
		{
			temp = t1;
			t1 = t2;
			t2 = temp;
		}
		if (t1 > tmin)
			tmin = t1;
		if (t2 < tmax)
			tmax = t2;
		if (tmin > tmax)
			return false;
		if (tmax < 0.0f)
			return false;
	}
	else if (((-e - obb.fA0) > 0.0f) || ((-e + obb.fA0) < 0.0f))
		return false;

	/* 2nd slap */
	e = obb.vA1 * vP;
	f = obb.vA1 * m_vDir;
	if (VMath::Abs(f) > 0.00001f)
	{
		t1 = (e + obb.fA1) / f;
		t2 = (e - obb.fA1) / f;

		if (t1 > t2)
		{
			temp = t1;
			t1 = t2;
			t2 = temp;
		}
		if (t1 > tmin)
			tmin = t1;
		if (t2 < tmax)
			tmax = t2;
		if (tmin > tmax)
			return false;
		if (tmax < 0.0f)
			return false;
	}
	else if (((-e - obb.fA1) > 0.0f) || ((-e + obb.fA1) < 0.0f))
		return false;

	/* 3rd slap */
	e = obb.vA2 * vP;
	f = obb.vA2 * m_vDir;
	if (VMath::Abs(f) > 0.00001f)
	{
		t1 = (e + obb.fA2) / f;
		t2 = (e - obb.fA2) / f;

		if (t1 > t2)
		{
			temp = t1;
			t1 = t2;
			t2 = temp;
		}
		if (t1 > tmin)
			tmin = t1;
		if (t2 < tmax)
			tmax = t2;
		if (tmin > tmax)
			return false;
		if (tmax < 0.0f)
			return false;
	}
	else if (((-e - obb.fA2) > 0.0f) || ((-e + obb.fA2) < 0.0f))
		return false;

	if ((tmin > 0.0f) && (tmin <= fL))
	{
		if (t)
			*t = tmin;
		return true;
	}

	/* intersection on line but not on segment */
	if (tmax > fL)
		return false;

	if (t)
		*t = tmax;

	return true;
}

/********************************************************************
 *                          O P E R A T O R S                       *
 ********************************************************************/

/********************************************************************
 *                         C A L L B A C K S                        *
 ********************************************************************/

/********************************************************************
 *                         I N T E R N A L S                        *
 ********************************************************************/

} // End Namespace
