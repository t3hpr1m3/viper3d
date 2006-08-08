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
VPlane::VPlane()
{

}

VPlane::VPlane(const VVector& vN, const VVector& vP)
 : m_vN(vN), m_vPoint(vP)
{
	m_fD = -(vN * vP);
}

VPlane::VPlane(const VVector& vN, const VVector& vP, const float& fD)
 : m_vN(vN), m_vPoint(vP), m_fD(fD)
{

}

VPlane::VPlane(const VVector& v0, const VVector& v1, const VVector& v2)
 : m_vPoint(v0)
{
	VVector vEdge1 = v1 - v0;
	VVector vEdge2 = v2 - v0;

	m_vN.Cross(vEdge1, vEdge2);
	m_vN.Normalize();
	m_fD = -(m_vN * v0);
}

/********************************************************************
 *                        A T T R I B U T E S                       *
 ********************************************************************/

/********************************************************************
 *                        O P E R A T I O N S                       *
 ********************************************************************/
void VPlane::Set(const VVector& vN, const VVector& vP)
{
	m_fD		= -(vN * vP);
	m_vN		= vN;
	m_vPoint	= vP;
}

void VPlane::Set(const VVector& vN, const VVector& vP, const float& fD)
{
	m_vN		= vN;
	m_vPoint	= vP;
	m_fD		= fD;
}

void VPlane::Set(const VVector& v0, const VVector& v1, const VVector& v2)
{
	VVector vEdge1 = v1 - v0;
	VVector vEdge2 = v2 - v0;

	m_vN.Cross(vEdge1, vEdge2);
	m_vN.Normalize();
	m_fD = -(m_vN * v0);
	m_vPoint = v0;
}
inline
float VPlane::Distance(const VVector& vPoint) const
{
	return (VMath::Abs((m_vN * vPoint) - m_fD));
}
inline
int VPlane::Classify(const VVector& vPoint) const
{
	float f = (vPoint * m_vN) + m_fD;

	if (f > 0.00001)
		return VFRONT;
	else if (f < -0.00001)
		return VBACK;
	else
		return VPLANAR;	
}

int VPlane::Classify(const VPolygon& Polygon) const
{
	int nNumFront = 0, nNumBack = 0, nNumPlanar = 0;
	int nClass;

	//const VPolygon *pPoly = dynamic_cast<const VPolygon*>(&Polygon);

	int nNumPoints = Polygon.GetNumPoints();

	// Loop through all points
	for (int i = 0; i < nNumPoints; i++)
	{
		nClass = Classify(Polygon.GetPoints()[i]);

		if (nClass == VFRONT)
			nNumFront++;
		else if (nClass == VBACK)
			nNumBack++;
		else
		{
			nNumFront++;
			nNumBack++;
			nNumPlanar++;
		}
	}

	if (nNumPlanar == nNumPoints)
		return VPLANAR;		// all points are planar
	else if (nNumFront == nNumPoints)
		return VFRONT;		// all points are in front of the plane
	else if (nNumBack == nNumPoints)
		return VBACK;		// all points are on the backside of the plane
	else
		return VCLIPPED;	// polygon is intersecting the plane
}

bool VPlane::Clip(const VRay *pRay, const float& fL, VRay *pF, VRay *pB) const
{
	VVector vHit(0.0f, 0.0f, 0.0f);

	if (!pRay->Intersects(*this, false, fL, NULL, &vHit))
		return false;

	int n = Classify(pRay->GetOrigin());

	// ray comes from plane's backside
	if (n == VBACK)
	{
		if (pB)
			pB->SetValues(pRay->GetOrigin(), pRay->GetDirection());
		if (pF)
			pF->SetValues(vHit, pRay->GetDirection());
		}
	// ray comes from plane's front side
	else
	{
		if (pF)
			pF->SetValues(pRay->GetOrigin(), pRay->GetDirection());
		if (pB)
			pB->SetValues(vHit, pRay->GetDirection());
	}

	return true;
}

bool VPlane::Intersects(const VVector& vec0, const VVector& vec1,
						const VVector& vec2) const
{
	int n = Classify(vec0);

	if ((n == Classify(vec1)) &&
		(n == Classify(vec2)))
		return false;

	return true;
}

bool VPlane::Intersects(const VPlane& plane, VRay *pIntersection) const
{
	VVector vCross;
	float	fSqrLength;

	vCross.Cross(m_vN, plane.m_vN);
	fSqrLength = vCross.SquaredLength();

	if (fSqrLength < 1e-08f)
		return false;

	// find line of intersection
	if (pIntersection)
	{
		float fN00 = m_vN.SquaredLength();
		float fN01 = m_vN * plane.m_vN;
		float fN11 = plane.m_vN.SquaredLength();
		float fDet = fN00*fN11 - SQR( fN01 );

		if (VMath::Abs(fDet) < 1e-08f)
			return false;

		float fInvDet = 1.0f/fDet;
		float fC0 = (fN11*m_fD - fN01*plane.m_fD) * fInvDet;
		float fC1 = (fN00*plane.m_fD - fN01*m_fD) * fInvDet;

		pIntersection->SetDirection(vCross);
		pIntersection->SetOrigin(m_vN*fC0 + plane.m_vN*fC1);
	}

	return true;
}

bool VPlane::Intersects(VAabb& aabb) const
{
	VVector Vmin, Vmax;

	// x component
	if (m_vN.x >= 0.0f)
	{
		Vmin.x = aabb.GetMin().x;
		Vmax.x = aabb.GetMax().x;
	}
	else
	{
		Vmin.x = aabb.GetMax().x;
		Vmax.x = aabb.GetMin().x;
	}

	// y component
	if (m_vN.y >= 0.0f)
	{
		Vmin.y = aabb.GetMin().y;
		Vmax.y = aabb.GetMax().y;
	}
	else
	{
		Vmin.y = aabb.GetMax().y;
		Vmax.y = aabb.GetMin().y;
	}

	// z component
	if (m_vN.z >= 0.0f)
	{
		Vmin.z = aabb.GetMin().z;
		Vmax.z = aabb.GetMax().z;
	}
	else
	{
		Vmin.z = aabb.GetMax().z;
		Vmax.z = aabb.GetMin().z;
	}

	if (((m_vN * Vmin) + m_fD) > 0.0f)
		return false;

	if (((m_vN * Vmax) + m_fD) >= 0.0f)
		return true;

	return false;
}

bool VPlane::Intersects(VObb& obb) const
{
	float fRadius = VMath::Abs(obb.fA0 * (m_vN * obb.vA0))
					+ VMath::Abs(obb.fA1 * (m_vN * obb.vA1))
					+ VMath::Abs(obb.fA2 * (m_vN * obb.vA2));

	float fDistance = Distance(obb.vCenter);

	return (fDistance <= fRadius);
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

} // End Namespace
