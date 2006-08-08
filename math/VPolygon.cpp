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
VPolygon::VPolygon()
{
	m_pPoints	= NULL;
	m_pIndis	= NULL;
	m_nNumP		= 0;
	m_nNumI		= 0;
	m_nFlag		= 0;
	memset(&m_Aabb, 0, sizeof(VAabb));
}

VPolygon::VPolygon(const VPolygon& poly)
{
	Set(poly.GetPoints(), poly.GetNumPoints(),
						poly.GetIndices(), poly.GetNumIndis());
}	

VPolygon::~VPolygon()
{
	if (m_pPoints)
	{
		delete[] m_pPoints;
		m_pPoints = NULL;
	}

	if (m_pIndis)
	{
		delete[] m_pIndis;
		m_pIndis = NULL;
	}
}		

/********************************************************************
 *                        A T T R I B U T E S                       *
 ********************************************************************/

/********************************************************************
 *                        O P E R A T I O N S                       *
 ********************************************************************/
void VPolygon::Set(const VVector *pPoints, int nNumP, const uint *pIndis,
								int nNumI)
{
	VVector vEdge0, vEdge1;
	bool bGotEm = false;

	if (m_pPoints)
	{
		delete[] m_pPoints;
		m_pPoints = NULL;
	}

	if (m_pIndis)
	{
		delete[] m_pIndis;
		m_pIndis = NULL;
	}

	m_pPoints = new VVector[nNumP];
	m_pIndis  = new uint[nNumI];

	m_nNumP = nNumP;
	m_nNumI = nNumI;

	memcpy(m_pPoints, pPoints, sizeof(VVector)*nNumP);
	memcpy(m_pIndis,  pIndis,  sizeof(uint)*nNumI);

	vEdge0 = m_pPoints[m_pIndis[1]] - m_pPoints[m_pIndis[0]];

	// calculate its plane
	for (int i = 2; bGotEm == false; i++)
	{
		if (static_cast<uint>(i + 1) > m_nNumI)
			break;

		vEdge1 = m_pPoints[m_pIndis[i]] - m_pPoints[m_pIndis[0]];

		vEdge0.Normalize();
		vEdge1.Normalize();

		// edges must not be parallel
		if (vEdge0.AngleWith(vEdge1) != 0.0)
			bGotEm = true;
	}

	m_Plane.m_vN.Cross(vEdge0, vEdge1);
	m_Plane.m_vN.Normalize();
	m_Plane.m_fD = -(m_Plane.m_vN * m_pPoints[0]);
	m_Plane.m_vPoint = m_pPoints[0];

	CalcBoundingBox();
}

void VPolygon::Clip(const VPlane& plane, VPolygon *pFront, VPolygon *pBack)
{
	if (!pFront && !pBack)
		return;

	VVector vHit, vA, vB;
	VRay    ray;

	// cast away const
	VPlane  *pPlane = const_cast<VPlane*>(&plane);

	uint	nNumFront=0,     // number points on frontside
			nNumBack=0,      // number points on backside
			nLoop=0,
			nCurrent=0;

	VVector *pvFront = new VVector[m_nNumP*3];
	VVector *pvBack  = new VVector[m_nNumP*3];

	// classify the first vertex and fill to appropriate list
	switch (pPlane->Classify(m_pPoints[0]))
	{
		case VFRONT:
			pvFront[nNumFront++] = m_pPoints[0];
			break;
		case VBACK:
			pvBack[nNumBack++] = m_pPoints[0];
			break;
		case VPLANAR:
			pvBack[nNumBack++]	= m_pPoints[0];
			pvFront[nNumFront++] = m_pPoints[0];
			break;
		default:
			return;
	}

	// loop through all points of the polygon
	for (nLoop = 1; nLoop < (m_nNumP+1); nLoop++)
	{
		if (nLoop == m_nNumP)
			nCurrent = 0;
		else
			nCurrent = nLoop;

		// take two neighboring points from the poly
		vA = m_pPoints[nLoop-1];
		vB = m_pPoints[nCurrent];

		// classify points with respect to the plane
		int nClass  = pPlane->Classify(vB);
		int nClassA = pPlane->Classify(vA);

		// if planar then put him to both sides
		if (nClass == VPLANAR)
		{
			pvBack[nNumBack++] = m_pPoints[nCurrent];
			pvFront[nNumFront++] = m_pPoints[nCurrent];
		}
		// else check if this edge intersects the plane
		else
		{
			ray.SetOrigin(vA);
			ray.SetDirection(vB - vA);

			float fLength = const_cast<VVector&>(ray.GetDirection()).Length();

			if (fLength != 0.0f)
				ray.SetDirection(ray.GetDirection() / fLength);

			if (ray.Intersects(plane, false, fLength, 0, &vHit)
				&& (nClassA != VPLANAR))
			{
				// put the intersection point as new point for both
				pvBack[nNumBack++] = vHit;
				pvFront[nNumFront++] = vHit;

				// then sort the current point
				if (nClass == VFRONT)
				{
					if (nCurrent != 0)
						pvFront[nNumFront++] = m_pPoints[nCurrent];
				} // if [FRONT]
				else if (nClass == VBACK)
				{
					if (nCurrent != 0)
						pvBack[nNumBack++] = m_pPoints[nCurrent];
				} // else [BACK]
			}
			// if no intersection then just sort this point
			else
			{
				if (nCurrent == 0)
					continue;

				if (nClass == VFRONT)
				{
					pvFront[nNumFront++] = m_pPoints[nCurrent];
				}
				else if (nClass == VBACK)
				{
					pvBack[nNumBack++] = m_pPoints[nCurrent];
				}
				else
				{
					return; // should not happen
				}
			}
		}
	} // for [NumP]

	//	now we have the vertices for both new polys ready.
 	//	lets take care of the index lists now

	uint I0 = 0, I1 = 0, I2 = 0;

	uint *pnFront = NULL;
	uint *pnBack  = NULL;

	if (nNumFront > 2)
	{
		pnFront = new uint[(nNumFront-2)*3];

		for (nLoop = 0; nLoop < (nNumFront-2); nLoop++)
		{
			if (nLoop == 0)
			{
				I0=0;
				I1=1;
				I2=2;
			}
			else
			{
				I1=I2;
				I2++;
			}
			pnFront[(nLoop*3)   ] = I0;
			pnFront[(nLoop*3) +1] = I1;
			pnFront[(nLoop*3) +2] = I2;
		}
	}

	if (nNumBack > 2)
	{
		pnBack  = new uint[(nNumBack-2)*3];

		for (nLoop = 0; nLoop < (nNumBack-2); nLoop++)
		{
			if (nLoop==0)
			{
				I0=0;
				I1=1;
				I2=2;
			}
			else
			{
				I1=I2;
				I2++;
			}
			pnBack[(nLoop*3)   ] = I0;
			pnBack[(nLoop*3) +1] = I1;
			pnBack[(nLoop*3) +2] = I2;
		}
	}

	// now fuel in the information to the new poly objects
	if (pFront && pnFront)
	{
		pFront->Set(pvFront, nNumFront, pnFront, (nNumFront-2)*3);

		// make sure new one has same orientation as original
		if (pFront->GetPlane().m_vN * m_Plane.m_vN < 0.0f)
			pFront->SwapFaces();
	}

	if (pBack && pnBack)
	{
		pBack->Set(pvBack, nNumBack, pnBack, (nNumBack-2)*3);

		// make sure new one has same orientation as original
		if (pBack->GetPlane().m_vN * m_Plane.m_vN < 0.0f)
			pBack->SwapFaces();
	}

	// free temporary memory
	if (pvFront)
	{
		delete[] pvFront;
	}
	if (pvBack)
	{
		delete [] pvBack;
	}
	if (pnFront)
	{
		delete [] pnFront;
	}
	if (pnBack)
	{
		delete [] pnBack;
	}
}

void VPolygon::Clip(const VAabb& aabb)
{
	VPolygon	BackPoly, ClippedPoly;
	VPlane		Planes[6];
	bool		bClipped = false;

	// cast away const
	VAabb *pAabb = const_cast<VAabb*>(&aabb);

	// get the planes of the aabb, note that
	// the normals are pointing outwards
	pAabb->GetPlanes(Planes);

	// make a copy of this polygon
	ClippedPoly = *this;

	// now clip the poly against the planes
	for (int i = 0; i < 6; i++)
	{
		if (Planes[i].Classify(ClippedPoly) == VCLIPPED)
		{
			ClippedPoly.Clip(Planes[i], NULL, &BackPoly);
			ClippedPoly = BackPoly;
			bClipped = true;
		}
	}

	// set this poly to the final clip output
	if (bClipped)
	{
		*this = ClippedPoly;
	}
}

int VPolygon::Cull(const VAabb& aabb)
{
	VPlane	Planes[6];
	uint	nInside=0, nCurrent=0;
	bool	bFirst=true;
	VRay	ray;

	// cast away const
	VAabb *pAabb = const_cast<VAabb*>(&aabb);

	// get the planes of the aabb, note that
	// the normals are pointing outwards
	pAabb->GetPlanes(Planes);

	// check if polys aabb is roughly intersecting at all
	if (!m_Aabb.Intersects(aabb))
		return VCULLED; // no way

	// now polygon is eventually but not
	// necessarily intersecting the aabb
	for (int p = 0; p < 6; p++)
	{
		// one time check if all points are inside the aabb
		if (bFirst)
		{
			for (uint i = 0; i < m_nNumP; i++)
			{
				if (pAabb->Intersects(m_pPoints[i]))
					nInside++;
			}
			bFirst = false;

			// all points inside => poly totally inside aabb
			if (nInside  == m_nNumP) return VVISIBLE;
		}

		// check for intersection of poly with aabb plane
		for (uint nLoop = 1; nLoop < (m_nNumP+1); nLoop++)
		{
			if (nLoop == m_nNumP)
				nCurrent = 0;
			else
				nCurrent = nLoop;

			// build ray from two neighboring points
			ray.SetOrigin(m_pPoints[nLoop-1]);
			ray.SetDirection(m_pPoints[nCurrent] - m_pPoints[nLoop-1]);

			float fLength = const_cast<VVector&>(ray.GetDirection()).Length();
			if (fLength != 0.0f)
				ray.SetDirection(ray.GetDirection() / fLength);

			if (ray.Intersects(Planes[p], false, fLength, 0, NULL))
				/* NEED TO CHECK WHETHER INTERSECTION POINT IS INSIDE AABB AT ALL */
				return VCLIPPED;
		}
	}

	// no intersection
	return VCULLED;
}

void VPolygon::SwapFaces()
{
	uint *pIndis = new unsigned int[m_nNumI];

	// change index ordering
	for (uint i = 0; i < m_nNumI; i++)
		pIndis[m_nNumI - i - 1] = m_pIndis[i];

	// change normal orientation
	m_Plane.m_vN *= -1.0f;
	m_Plane.m_fD *= -1.0f;

	delete[] m_pIndis;
	m_pIndis = pIndis;
}

bool VPolygon::Intersects(const VRay& ray, bool bCull, float *t)
{
	VRay *pRay = const_cast<VRay*>(&ray);

	for (uint i = 0; i < m_nNumI; i += 3)
	{
		if (pRay->Intersects(m_pPoints[m_pIndis[i]],
							m_pPoints[m_pIndis[i+1]],
							m_pPoints[m_pIndis[i+2]],
							false, t))
		{
			return true;
		}

		if (!bCull)
		{
			if (pRay->Intersects(m_pPoints[m_pIndis[i+2]],
								m_pPoints[m_pIndis[i+1]],
								m_pPoints[m_pIndis[i]],
								false, t))
			{
				return true;
			}
		}
	}

	return false;
}

bool VPolygon::Intersects(const VRay& ray, bool bCull, float fL, float *t)
{
	VRay *pRay = const_cast<VRay*>(&ray);

	for (uint i = 0; i < m_nNumI; i += 3)
	{
		if (pRay->Intersects(m_pPoints[m_pIndis[i]],
							m_pPoints[m_pIndis[i+1]],
							m_pPoints[m_pIndis[i+2]],
							false, fL, t))
		{
			return true;
		}

		if (!bCull)
		{
			if (pRay->Intersects(m_pPoints[m_pIndis[i+2]],
								m_pPoints[m_pIndis[i+1]],
								m_pPoints[m_pIndis[i]],
								false, fL, t))
			{
				return true;
			}
		}
	}

	return false;

}

/********************************************************************
 *                         O P E R A T O R S                       	*
 ********************************************************************/
const VPolygon& VPolygon::operator=(const VPolygon &poly)
{
	Set(poly.GetPoints(), poly.GetNumPoints(),
						poly.GetIndices(), poly.GetNumIndis());
	return *this;
}

/********************************************************************
 *                         C A L L B A C K S                        *
 ********************************************************************/

/********************************************************************
 *                         I N T E R N A L S                        *
 ********************************************************************/
void VPolygon::CalcBoundingBox()
{
	VVector vMax, vMin;

	// pick random start value from poly
	vMax = vMin = m_pPoints[0];

	// seek final values for each coordinate
	for (uint i = 0; i < m_nNumP; i++)
	{
		if (m_pPoints[i].x > vMax.x)
			vMax.x = m_pPoints[i].x;
		else if (m_pPoints[i].x < vMin.x)
			vMin.x = m_pPoints[i].x;

		if (m_pPoints[i].y > vMax.y)
			vMax.y = m_pPoints[i].y;
		else if (m_pPoints[i].y < vMin.y)
			vMin.y = m_pPoints[i].y;

		if (m_pPoints[i].z > vMax.z)
			vMax.z = m_pPoints[i].z;
		else if (m_pPoints[i].z < vMin.z)
			vMin.z = m_pPoints[i].z;
	}

	m_Aabb.SetMax(vMax);
	m_Aabb.SetMin(vMin);
	m_Aabb.SetCenter((vMax + vMin) / 2.0f);
}

} // End Namespace
