/*============================================================================*
 *                                                                            *
 *  This source file is part of the Viper3D Game Engine.                      *
 *                                                                            *
 *	Copyright (C) 2004 UDP Games   All Rights Reserved.                       *
 *                                                                            *
 *============================================================================*/

/* System Headers */

/* Local Headers */
#include "VMath.h"

namespace UDP
{

/********************************************************************
 *          C O N S T R U C T I O N / D E S T R U C T I O N         *
 ********************************************************************/
VObb::VObb()
{

}

VObb::~VObb()
{

}

/********************************************************************
 *                        A T T R I B U T E S                       *
 ********************************************************************/

/********************************************************************
 *                        O P E R A T I O N S                       *
 ********************************************************************/
void VObb::DeTransform(const VObb& obb, const VMatrix& mat)
{
	VMatrix m = mat;
	VVector vT;

	// erase translation from matrix
	vT.SetValues(m[3][0], m[3][1], m[3][2]);
	m[3][0] = m[3][1] = m[3][2] = 0.0f;

	// rotate center and axis to matrix coordinate space
	vCenter = m * obb.vCenter;
	vA0		= m * obb.vA0;
	vA1		= m * obb.vA1;
	vA2		= m * obb.vA2;

	// set translation
	vCenter += vT;

	// copy axis length
	fA0 = obb.fA0;
	fA1 = obb.fA1;
	fA2 = obb.fA2;
}

bool VObb::Intersects(const VRay& ray, float *t)
{
	float e, f, t1, t2, temp;
	float tmin = -99999.9f;
	float tmax = +99999.9f;

	VVector vP = vCenter - ray.GetOrigin();

	// 1st slap
	e = vA0 * vP;
	f = vA0 * ray.GetDirection();
	if (VMath::Abs(f) > 0.00001f)
	{
		t1 = (e + fA0) / f;
		t2 = (e - fA0) / f;

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
	else if (((-e - fA0) > 0.0f) || ((-e + fA0) < 0.0f))
		return false;

	// 2nd slap
	e = vA1 * vP;
	f = vA1 * ray.GetDirection();
	if (VMath::Abs(f) > 0.00001f)
	{
		t1 = (e + fA1) / f;
		t2 = (e - fA1) / f;

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
	else if (((-e - fA1) > 0.0f) || ((-e + fA1) < 0.0f))
		return false;

	// 3rd slap
	e = vA2 * vP;
	f = vA2 * ray.GetDirection();
	if (VMath::Abs(f) > 0.00001f)
	{
		t1 = (e + fA2) / f;
		t2 = (e - fA2) / f;

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
	else if (((-e - fA2) > 0.0f) || ((-e + fA2) < 0.0f))
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

bool VObb::Intersects(const VRay& ray, float fL, float *t)
{
	float e, f, t1, t2, temp;
	float tmin = -99999.9f;
	float tmax = +99999.9f;

	VVector vP = vCenter - ray.GetOrigin();

	// 1st slap
	e = vA0 * vP;
	f = vA0 * ray.GetDirection();
	if (VMath::Abs(f) > 0.00001f)
	{
		t1 = (e + fA0) / f;
		t2 = (e - fA0) / f;

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
	else if (((-e - fA0) > 0.0f) || ((-e + fA0) < 0.0f))
		return false;

	// 2nd slap
	e = vA1 * vP;
	f = vA1 * ray.GetDirection();
	if (VMath::Abs(f) > 0.00001f)
	{
		t1 = (e + fA1) / f;
		t2 = (e - fA1) / f;

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
	else if (((-e - fA1) > 0.0f) || ((-e + fA1) < 0.0f))
		return false;

	// 3rd slap
	e = vA2 * vP;
	f = vA2 * ray.GetDirection();
	if (VMath::Abs(f) > 0.00001f)
	{
		t1 = (e + fA2) / f;
		t2 = (e - fA2) / f;

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
	else if (((-e - fA2) > 0.0f) || ((-e + fA2) < 0.0f))
		return false;

	if ((tmin > 0.0f) && (tmin <= fL))
	{
		if (t)
			*t = tmin;
		return true;
	}

	// intersection on line but not on segment
	if (tmax > fL)
		return false;

	if (t)
		*t = tmax;

	return true;
}

bool VObb::Intersects(const VObb &obb)
{
	float T[3];

	// diference vector between bot oob's
	VVector vD = obb.vCenter - vCenter;

	float	matM[3][3];	// B's axis in relation to A
	float	ra,			// radius A
			rb,			// radius B
			t;			// absolute values from T[]

	// Obb A's axis as separation axis
	// ===============================
	// first axis vA0
	matM[0][0] = vA0 * obb.vA0;
	matM[0][1] = vA0 * obb.vA1;
	matM[0][2] = vA0 * obb.vA2;
	ra	= fA0;
	rb	=	obb.fA0 * VMath::Abs(matM[0][0]) +
			obb.fA1 * VMath::Abs(matM[0][1]) +
			obb.fA2 * VMath::Abs(matM[0][2]);

	T[0]	= vD * vA0;
	t		= VMath::Abs(T[0]);
	if (t > (ra + rb))
		return false;

	// second axis vA1
	matM[1][0] = vA1 * obb.vA0;
	matM[1][1] = vA1 * obb.vA1;
	matM[1][2] = vA1 * obb.vA2;
	ra	=	fA1;
	rb	=	obb.fA0 * VMath::Abs(matM[1][0]) +
			obb.fA1 * VMath::Abs(matM[1][1]) +
			obb.fA2 * VMath::Abs(matM[1][2]);
	T[1]	= vD * vA1;
	t		= VMath::Abs(T[1]);
	if (t > (ra + rb))
		return false;
	return true;

	// third axis vA2
	matM[2][0] = vA2 * obb.vA0;
	matM[2][1] = vA2 * obb.vA1;
	matM[2][2] = vA2 * obb.vA2;
	ra	=	fA2;
	rb	=	obb.fA0 * VMath::Abs(matM[2][0]) +
			obb.fA1 * VMath::Abs(matM[2][1]) +
			obb.fA2 * VMath::Abs(matM[2][2]);
	T[2]	= vD * vA2;
	t		= VMath::Abs(T[2]);
	if (t > (ra + rb))
		return false;
	return true;

	// Obb B's axis as separation axis
	// ===============================
	// first axis vA0
	ra	= 	fA0 * VMath::Abs(matM[0][0]) +
			fA1 * VMath::Abs(matM[1][0]) +
			fA2 * VMath::Abs(matM[2][0]);
	rb	=	obb.fA0;
	t	=	VMath::Abs(T[0]*matM[0][0] + T[1]*matM[1][0] + T[2]*matM[2][0]);
	if (t > (ra + rb))
		return false;

	// second axis vA1
	ra	= 	fA0 * VMath::Abs(matM[0][1]) +
			fA1 * VMath::Abs(matM[1][1]) +
			fA2 * VMath::Abs(matM[2][1]);
	rb	=	obb.fA1;
	t	=	VMath::Abs(T[0]*matM[0][1] + T[1]*matM[1][1] + T[2]*matM[2][1]);
	if (t > (ra + rb))
		return false;

	// third axis vA2
	ra	= 	fA0 * VMath::Abs(matM[0][2]) +
			fA1 * VMath::Abs(matM[1][2]) +
			fA2 * VMath::Abs(matM[2][2]);
	rb	=	obb.fA2;
	t	=	VMath::Abs(T[0]*matM[0][2] + T[1]*matM[1][2] + T[2]*matM[2][2]);
	if (t > (ra + rb))
		return false;

	// other candidates: cross products of axis:
	// =========================================
	// axis A0xB0
	ra = fA1*VMath::Abs(matM[2][0]) + fA2*VMath::Abs(matM[1][0]);
	rb = obb.fA1*VMath::Abs(matM[0][2]) + obb.fA2*VMath::Abs(matM[0][1]);
	t = VMath::Abs(T[2]*matM[1][0] - T[1]*matM[2][0]);
	if (t > ra + rb)
		return false;

	// axis A0xB1
	ra = fA1*VMath::Abs(matM[2][1]) + fA2*VMath::Abs(matM[1][1]);
	rb = obb.fA0*VMath::Abs(matM[0][2]) + obb.fA2*VMath::Abs(matM[0][0]);
	t = VMath::Abs(T[2]*matM[1][1] - T[1]*matM[2][1]);
	if (t > ra + rb)
		return false;

	// axis A0xB2
	ra = fA1*VMath::Abs(matM[2][2]) + fA2*VMath::Abs(matM[1][2]);
	rb = obb.fA0*VMath::Abs(matM[0][1]) + obb.fA1*VMath::Abs(matM[0][0]);
	t = VMath::Abs(T[2]*matM[1][2] - T[1]*matM[2][2]);
	if (t > ra + rb)
		return false;

	// axis A1xB0
	ra = fA0*VMath::Abs(matM[2][0]) + fA2*VMath::Abs(matM[0][0]);
	rb = obb.fA1*VMath::Abs(matM[1][2]) + obb.fA2*VMath::Abs(matM[1][1]);
	t = VMath::Abs(T[0]*matM[2][0] - T[2]*matM[0][0]);
	if (t > ra + rb)
		return false;

	// axis A1xB1
	ra = fA0*VMath::Abs(matM[2][1]) + fA2*VMath::Abs(matM[0][1]);
	rb = obb.fA0*VMath::Abs(matM[1][2]) + obb.fA2*VMath::Abs(matM[1][0]);
	t = VMath::Abs(T[0]*matM[2][1] - T[2]*matM[0][1]);
	if (t > ra + rb)
		return false;

	// axis A1xB2
	ra = fA0*VMath::Abs(matM[2][2]) + fA2*VMath::Abs(matM[0][2]);
	rb = obb.fA0*VMath::Abs(matM[1][1]) + obb.fA1*VMath::Abs(matM[1][0]);
	t = VMath::Abs(T[0]*matM[2][2] - T[2]*matM[0][2]);
	if (t > ra + rb)
		return false;

	// axis A2xB0
	ra = fA0*VMath::Abs(matM[1][0]) + fA1*VMath::Abs(matM[0][0]);
	rb = obb.fA1*VMath::Abs(matM[2][2]) + obb.fA2*VMath::Abs(matM[2][0]);
	t = VMath::Abs(T[1]*matM[0][0] - T[0]*matM[1][0]);
	if (t > ra + rb)
		return false;

	// axis A2xB1
	ra = fA0*VMath::Abs(matM[1][1]) + fA1*VMath::Abs(matM[0][1]);
	rb = obb.fA0*VMath::Abs(matM[2][2]) + obb.fA2*VMath::Abs(matM[2][0]);
	t = VMath::Abs(T[1]*matM[0][1] - T[0]*matM[1][1]);
	if (t > ra + rb)
		return false;

	// axis A2xB2
	ra = fA0*VMath::Abs(matM[1][2]) + fA1*VMath::Abs(matM[0][2]);
	rb = obb.fA0*VMath::Abs(matM[2][1]) + obb.fA1*VMath::Abs(matM[2][0]);
	t = VMath::Abs(T[1]*matM[0][2] - T[0]*matM[1][2]);
	if (t > ra + rb)
		return false;

	// no separation axis found => intersection
	return true;
}

bool VObb::Intersects(const VVector& v0, const VVector& v1,
							const VVector& v2)
{
	float	fMin0, fMax0, fMin1, fMax1;
	float	fD_C;
	VVector	vV, vTriEdge[3], vA[3];

	// just for looping
	vA[0] = vA0;
	vA[1] = vA1;
	vA[2] = vA2;

	// direction of tri-normals
	vTriEdge[0] = v1 - v0;
	vTriEdge[1] = v2 - v0;

	vV.Cross(vTriEdge[0], vTriEdge[1]);

	fMin0 = vV * v0;
	fMax0 = fMin0;

	ObbProj((*this), vV, &fMin1 ,&fMax1);
	if (fMax1 < fMin0 || fMax0 < fMin1)
		return true;

	// direction of obb planes
	// =======================
	// axis 1:
	vV = vA0;
	TriProj(v0, v1, v2, vV, &fMin0, &fMax0);
	fD_C = vV * vCenter;
	fMin1 = fD_C - fA0;
	fMax1 = fD_C + fA0;
	if (fMax1 < fMin0 || fMax0 < fMin1)
		return true;

	// axis 2:
	vV = vA1;
	TriProj(v0, v1, v2, vV, &fMin0, &fMax0);
	fD_C = vV * vCenter;
	fMin1 = fD_C - fA1;
	fMax1 = fD_C + fA1;
	if (fMax1 < fMin0 || fMax0 < fMin1)
		return true;

	// axis 3:
	vV = vA2;
	TriProj(v0, v1, v2, vV, &fMin0, &fMax0);
	fD_C = vV * vCenter;
	fMin1 = fD_C - fA2;
	fMax1 = fD_C + fA2;
	if (fMax1 < fMin0 || fMax0 < fMin1)
		return true;

	// direction of tri-obb edge crossproducts
	vTriEdge[2] = vTriEdge[1] - vTriEdge[0];
	for (int j = 0; j < 3; j++)
	{
		for (int k = 0; k < 3; k++)
		{
			vV.Cross(vTriEdge[j], vA[k]);
			TriProj(v0, v1, v2, vV, &fMin0, &fMax0);
			ObbProj((*this), vV, &fMin1, &fMax1);

			if ((fMax1 < fMin0) || (fMax0 < fMin1))
				return true;
		}
	}

	return true;
}

int VObb::Cull(const VPlane *pPlanes, int nNumPlanes)
{
	VVector vN;
	int		nResult = VVISIBLE;
	float	fRadius, fTest;

	// for all planes
	for (int i = 0; i < nNumPlanes; i++)
	{
		// frustrum normals pointing outwards, we need inwards
		vN = pPlanes[i].m_vN * -1.0f;

		// calculate projected box radius
		fRadius =	VMath::Abs(fA0 * (vN * vA0))
				+	VMath::Abs(fA1 * (vN * vA1))
				+	VMath::Abs(fA2 * (vN * vA2));

		// testvalue: (N*C - d) (#)
		fTest = vN * vCenter - pPlanes[i].m_fD;

		// obb totally outside of at least one plane: (#) < -r
		if (fTest < -fRadius)
			return VCULLED;
		// or maybe intersecting this plane?
		else if (!(fTest > fRadius))
			nResult = VCLIPPED;
	}

	return nResult;
}

/********************************************************************
 *                         O P E R A T O R S                       	*
 ********************************************************************/

/********************************************************************
 *                         C A L L B A C K S                        *
 ********************************************************************/

/********************************************************************
 *                         I N T E R N A L S                        *
 ********************************************************************/
void VObb::ObbProj(const VObb& obb, const VVector& vV,
								float *pfMin, float *pfMax)
{
	float fDP = vV * obb.vCenter;
	float fR =	obb.fA0 * VMath::Abs(vV * obb.vA0) +
				obb.fA0 * VMath::Abs(vV * obb.vA1) +
				obb.fA1 * VMath::Abs(vV * obb.vA2);

	*pfMin = fDP - fR;
	*pfMax = fDP + fR;
}

void VObb::TriProj(const VVector& v0, const VVector& v1, const VVector& v2,
								const VVector& vV, float *pfMin, float *pfMax)
{
	*pfMin = vV * v0;
	*pfMax = *pfMin;

	float fDP = vV * v1;
	if (fDP < *pfMin)
		*pfMin = fDP;
	else if (fDP > *pfMax)
		*pfMax = fDP;

	fDP = vV * v2;
	if (fDP < *pfMin)
		*pfMin = fDP;
	else if (fDP > *pfMax)
		*pfMax = fDP;
}

} // End Namespace
