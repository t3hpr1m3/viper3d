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
VAabb::VAabb()
{

}

VAabb::VAabb(const VVector& vMin, const VVector& vMax)
{
	m_vMin = vMin;
	m_vMax = vMax;
	m_vCenter = (vMax - vMin) / 2.0f;
}

VAabb::~VAabb()
{

}

/********************************************************************
 *                        A T T R I B U T E S                       *
 ********************************************************************/
void VAabb::GetPlanes(VPlane *pPlanes)
{
	VVector vN;

	if (!pPlanes)
		return;

	// right side
	vN.SetValues(1.0f, 0.0f, 0.0f);
	pPlanes[0].Set(vN, m_vMax);

	// left side
	vN.SetValues(-1.0f, 0.0f, 0.0f);
	pPlanes[1].Set(vN, m_vMin);

	// front side
	vN.SetValues(0.0f, 0.0f, -1.0f);
	pPlanes[2].Set(vN, m_vMin);

	// back side
	vN.SetValues(0.0f, 0.0f, 1.0f);
	pPlanes[3].Set(vN, m_vMax);

	// top side
	vN.SetValues(0.0f, 1.0f, 0.0f);
	pPlanes[4].Set(vN, m_vMax);

	// bottom side
	vN.SetValues(0.0f, -1.0f, 0.0f);
	pPlanes[5].Set(vN, m_vMin);
}

/********************************************************************
 *                        O P E R A T I O N S                       *
 ********************************************************************/
void VAabb::Construct(const VObb *pObb)
{
	VVector vA0, vA1, vA2;

	vA0 = pObb->vA0 * pObb->fA0;
	vA1 = pObb->vA1 * pObb->fA1;
	vA2 = pObb->vA2 * pObb->fA2;

	// find x extensions
	if (vA0.x > vA1.x)
	{
		if (vA0.x > vA2.x)
		{
			m_vMax.x =  vA0.x;
			m_vMin.x = -vA0.x;
		}
		else
		{
			m_vMax.x =  vA2.x;
			m_vMin.x = -vA2.x;
		}
	}
	else
	{
		if (vA1.x > vA2.x)
		{
			m_vMax.x =  vA1.x;
			m_vMin.x = -vA1.x;
		}
		else
		{
			m_vMax.x =  vA2.x;
			m_vMin.x = -vA2.x;
		}
	}

	// find y extensions
	if (vA0.y > vA1.y)
	{
		if (vA0.y > vA2.y)
		{
			m_vMax.y =  vA0.y;
			m_vMin.y = -vA0.y;
		}
		else
		{
			m_vMax.y =  vA2.y;
			m_vMin.y = -vA2.y;
		}
	}
	else
	{
		if (vA1.y > vA2.y)
		{
			m_vMax.y =  vA1.y;
			m_vMin.y = -vA1.y;
		}
		else
		{
			m_vMax.y =  vA2.y;
			m_vMin.y = -vA2.y;
		}
	}

	// find z extensions
	if (vA0.z > vA1.z)
	{
		if (vA0.z > vA2.z)
		{
			m_vMax.z =  vA0.z;
			m_vMin.z = -vA0.z;
		}
		else
		{
			m_vMax.z =  vA2.z;
			m_vMin.z = -vA2.z;
		}
	}
	else
	{
		if (vA1.z > vA2.z)
		{
			m_vMax.z =  vA1.z;
			m_vMin.z = -vA1.z;
		}
		else
		{
			m_vMax.z =  vA2.z;
			m_vMin.z = -vA2.z;
		}
	}

	m_vMax = m_vMax + pObb->vCenter;
	m_vMin = m_vMin + pObb->vCenter;
}

int VAabb::Cull(const VPlane *pPlanes, int nNumPlanes)
{
	VVector	vMin, vMax;
	bool	bIntersects = false;

	// find and test extreme points
	for (int i = 0; i < nNumPlanes; i++)
	{
		// x coordinate
		if (pPlanes[i].m_vN.x >= 0.0f)
		{
			vMin.x = m_vMin.x;
			vMax.x = m_vMax.x;
		}
		else
		{
			vMin.x = m_vMax.x;
			vMax.x = m_vMin.x;
		}
		// y coordinate
		if (pPlanes[i].m_vN.y >= 0.0f)
		{
			vMin.y = m_vMin.y;
			vMax.y = m_vMax.y;
		}
		else
		{
			vMin.y = m_vMax.y;
			vMax.y = m_vMin.y;
		}
		// z coordinate
		if (pPlanes[i].m_vN.z >= 0.0f)
		{
			vMin.z = m_vMin.z;
			vMax.z = m_vMax.z;
		}
		else
		{
			vMin.z = m_vMax.z;
			vMax.z = m_vMin.z;
		}

		if (((pPlanes[i].m_vN * vMin) + pPlanes[i].m_fD) > 0.0f)
			return VCULLED;

		if (((pPlanes[i].m_vN * vMax) + pPlanes[i].m_fD) >= 0.0f)
			bIntersects = true;
	}

	if (bIntersects)
		return VCLIPPED;

	return VVISIBLE;
}

bool VAabb::Contains(const VRay& ray, float fL)
{
	VVector vEnd = ray.GetOrigin() + (ray.GetDirection() * fL);

	return (Intersects(ray.GetOrigin()) && Intersects(vEnd));
}

bool VAabb::Intersects(const VRay& ray, float *t)
{
	float	t0, t1, tmp;
	float	tNear = -999999.9f;
	float	tFar  =  999999.9f;
	float	epsilon = 0.00001f;
	VVector	MaxT;

	// first pair of planes
	if (VMath::Abs(ray.GetDirection().x) < epsilon)
	{
		if ((ray.GetOrigin().x < m_vMin.x) ||
			(ray.GetOrigin().x > m_vMax.x))
			return false;
	}

	t0 = (m_vMin.x - ray.GetOrigin().x) / ray.GetDirection().x;
	t1 = (m_vMax.x - ray.GetOrigin().x) / ray.GetDirection().x;
	if (t0 > t1)
	{
		tmp	= t0;
		t0	= t1;
		t1	= tmp;
	}
	if (t0 > tNear)
		tNear = t0;
	if (t1 < tFar)
		tFar = t1;
	if (tNear > tFar)
		return false;
	if (tFar < 0)
		return false;

	// second pair of planes
	if (VMath::Abs(ray.GetDirection().y) < epsilon)
	{
		if ((ray.GetOrigin().y < m_vMin.y) ||
			(ray.GetOrigin().y > m_vMax.y))
			return false;
	}

	t0 = (m_vMin.y - ray.GetOrigin().y) / ray.GetDirection().y;
	t1 = (m_vMax.y - ray.GetOrigin().y) / ray.GetDirection().y;
	if (t0 > t1)
	{
		tmp	= t0;
		t0	= t1;
		t1	= tmp;
	}
	if (t0 > tNear)
		tNear = t0;
	if (t1 < tFar)
		tFar = t1;
	if (tNear > tFar)
		return false;
	if (tFar < 0)
		return false;

	// third pair of planes
	if (VMath::Abs(ray.GetDirection().z) < epsilon)
	{
		if ((ray.GetOrigin().z < m_vMin.z) ||
			(ray.GetOrigin().z > m_vMax.z))
			return false;
	}

	t0 = (m_vMin.z - ray.GetOrigin().z) / ray.GetDirection().z;
	t1 = (m_vMax.z - ray.GetOrigin().z) / ray.GetDirection().z;
	if (t0 > t1)
	{
		tmp	= t0;
		t0	= t1;
		t1	= tmp;
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

bool VAabb::Intersects(const VRay& ray, float fL, float *t)
{
	float	t0, t1, tmp, tFinal;
	float	tNear = -999999.9f;
	float	tFar  =  999999.9f;
	float	epsilon = 0.00001f;
	VVector	MaxT;

	// first pair of planes
	if (VMath::Abs(ray.GetDirection().x) < epsilon)
	{
		if ((ray.GetOrigin().x < m_vMin.x) ||
			(ray.GetOrigin().x > m_vMax.x))
			return false;
	}

	t0 = (m_vMin.x - ray.GetOrigin().x) / ray.GetDirection().x;
	t1 = (m_vMax.x - ray.GetOrigin().x) / ray.GetDirection().x;
	if (t0 > t1)
	{
		tmp	= t0;
		t0	= t1;
		t1	= tmp;
	}
	if (t0 > tNear)
		tNear = t0;
	if (t1 < tFar)
		tFar = t1;
	if (tNear > tFar)
		return false;
	if (tFar < 0)
		return false;

	// second pair of planes
	if (VMath::Abs(ray.GetDirection().y) < epsilon)
	{
		if ((ray.GetOrigin().y < m_vMin.y) ||
			(ray.GetOrigin().y > m_vMax.y))
			return false;
	}

	t0 = (m_vMin.y - ray.GetOrigin().y) / ray.GetDirection().y;
	t1 = (m_vMax.y - ray.GetOrigin().y) / ray.GetDirection().y;
	if (t0 > t1)
	{
		tmp	= t0;
		t0	= t1;
		t1	= tmp;
	}
	if (t0 > tNear)
		tNear = t0;
	if (t1 < tFar)
		tFar = t1;
	if (tNear > tFar)
		return false;
	if (tFar < 0)
		return false;

	// third pair of planes
	if (VMath::Abs(ray.GetDirection().z) < epsilon)
	{
		if ((ray.GetOrigin().z < m_vMin.z) ||
			(ray.GetOrigin().z > m_vMax.z))
			return false;
	}

	t0 = (m_vMin.z - ray.GetOrigin().z) / ray.GetDirection().z;
	t1 = (m_vMax.z - ray.GetOrigin().z) / ray.GetDirection().z;
	if (t0 > t1)
	{
		tmp	= t0;
		t0	= t1;
		t1	= tmp;
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

bool VAabb::Intersects(const VAabb& aabb)
{
	if ((m_vMin.x > aabb.GetMax().x) || (aabb.GetMin().x > m_vMax.x))
		return false;
	if ((m_vMin.y > aabb.GetMax().y) || (aabb.GetMin().y > m_vMax.y))
		return false;
	if ((m_vMin.z > aabb.GetMax().z) || (aabb.GetMin().z > m_vMax.z))
		return false;

	return true;
}

bool VAabb::Intersects(const VVector& v0)
{
	if (v0.x > m_vMax.x)
		return false;
	if (v0.y > m_vMax.y)
		return false;
	if (v0.z > m_vMax.z)
		return false;
	if (v0.x < m_vMin.x)
		return false;
	if (v0.y < m_vMin.y)
		return false;
	if (v0.z < m_vMin.z)
		return false;
	return true;
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
