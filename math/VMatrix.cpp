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
#include "VCPU.h"
#include "VTypes.h"

namespace UDP
{

/********************************************************************
 *          C O N S T R U C T I O N / D E S T R U C T I O N         *
 ********************************************************************/
VMatrix::VMatrix()
{

}
VMatrix::VMatrix(float m00, float m01, float m02, float m03,
				float m10, float m11, float m12, float m13,
				float m20, float m21, float m22, float m23,
				float m30, float m31, float m32, float m33)
{
	m[0][0] = m00;
	m[0][1] = m01;
	m[0][2] = m02;
	m[0][3] = m03;
	m[1][0] = m10;
	m[1][1] = m11;
	m[1][2] = m12;
	m[1][3] = m13;
	m[2][0] = m20;
	m[2][1] = m21;
	m[2][2] = m22;
	m[2][3] = m23;
	m[3][0] = m30;
	m[3][1] = m31;
	m[3][2] = m32;
	m[3][3] = m33;
}

/********************************************************************
 *                        A T T R I B U T E S                       *
 ********************************************************************/
float* VMatrix::operator[](unsigned nRow)
{
	return m[nRow];
}

const float* const VMatrix::operator[](unsigned nRow) const
{
	return m[nRow];
}

/********************************************************************
 *                        O P E R A T I O N S                       *
 ********************************************************************/
void VMatrix::RotaX(const float& a)
{
	float fCos = VMath::Cos(a);
	float fSin = VMath::Sin(a);

	m[1][1] = fCos;
	m[1][2] = fSin;
	m[2][1] = -fSin;
	m[2][2] = fCos;

	m[0][0] = m[3][3] = 1.0f;
	m[0][1] = m[0][2] = m[0][3] = m[1][0] = m[1][3] = m[2][0] = m[2][3] =
				m[3][0] = m[3][1] = m[3][2] = 0.0f;
}

void VMatrix::RotaY(const float& a)
{
	float fCos = VMath::Cos(a);
	float fSin = VMath::Sin(a);

	m[0][0] = fCos;
	m[0][2] = -fSin;
	m[2][0] = fSin;
	m[2][2] = fCos;

	m[1][1] = m[3][3] = 1.0f;
	m[0][1] = m[1][2] = m[0][3] = m[1][0] = m[1][3] = m[2][1] = m[2][3] =
				m[3][0] = m[3][1] = m[3][2] = 0.0f;
}

void VMatrix::RotaZ(const float& a)
{
	float fCos = VMath::Cos(a);
	float fSin = VMath::Sin(a);

	m[0][0] = fCos;
	m[0][1] = fSin;
	m[1][0] = -fSin;
	m[1][1] = fCos;

	m[2][2] = m[3][3] = 1.0f;
	m[0][2] = m[0][3] = m[1][2] = m[1][3] = m[2][0] = m[2][1] = m[2][3] =
				m[3][0] = m[3][1] = m[3][2] = 0.0f;
}

void VMatrix::Rota(const float& x, const float& y, const float& z)
{
	Rota(VVector(x, y, z));
}

void VMatrix::Rota(const VVector &vec)
{
	float sr, sp, sy, cr, cp, cy;

	*this = VMath::MATRIX_IDENTITY;

	sy = VMath::Sin(vec.z);
	cy = VMath::Cos(vec.z);
	sp = VMath::Sin(vec.y);
	cp = VMath::Cos(vec.y);
	sr = VMath::Sin(vec.x);
	cr = VMath::Cos(vec.x);

	m[0][0] = cp * cy;
	m[0][1] = cp * sy;
	m[0][2] = -sp;
	m[1][0] = sr * sp * cy + cr * -sy;
	m[1][1] = sr * sp * sy + cr * cy;
	m[1][2] = sr * cp;
	m[2][0] = cr * sp * cy + -sr * -sy;
	m[2][1] = cr * sp * sy + -sr * cy;
	m[2][2] = cr * cp;
}

void VMatrix::RotaArbi(const VVector& vAxis, const float& a)
{
	VVector _vAxis = vAxis;
	float fCos = VMath::Cos(a);
	float fSin = VMath::Sin(a);
	float fSum = 1.0f - fCos;

	if (_vAxis.SquaredLength() != 1.0f)
		_vAxis.Normalize();

	m[0][0] = (_vAxis.x * _vAxis.x) * fSum + fCos;
	m[0][1] = (_vAxis.x * _vAxis.y) * fSum - (_vAxis.z * fSin);
	m[0][2] = (_vAxis.x * _vAxis.z) * fSum + (_vAxis.y * fSin);

	m[1][0] = (_vAxis.y * _vAxis.x) * fSum + (_vAxis.z * fSin);
	m[1][1] = (_vAxis.y * _vAxis.y) * fSum + fCos;
	m[1][2] = (_vAxis.y * _vAxis.z) * fSum - (_vAxis.x * fSin);

	m[2][0] = (_vAxis.z * _vAxis.x) * fSum - (_vAxis.y * fSin);
	m[2][1] = (_vAxis.z * _vAxis.y) * fSum + (_vAxis.x * fSin);
	m[2][2] = (_vAxis.z * _vAxis.z) * fSum + fCos;

	m[0][3] = m[1][3] = m[2][3] = m[3][0] = m[3][1] = m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}

void VMatrix::ApplyInverseRota(VVector *pVec)
{
	pVec->x = pVec->x * m[0][0] + pVec->y * m[0][1] + pVec->z * m[0][2];
	pVec->y = pVec->x * m[1][0] + pVec->y * m[1][1] + pVec->z * m[1][2];
	pVec->z = pVec->x * m[2][0] + pVec->y * m[2][1] + pVec->z * m[2][2];
	pVec->w = 1.0f;
}

void VMatrix::Translate(const float& dx, const float& dy, const float& dz)
{
	m[3][0] = dx;
	m[3][1] = dy;
	m[3][2] = dz;
}

void VMatrix::SetTranslation(const VVector& vec, bool EraseContent /*=false*/)
{
	if (EraseContent)
		*this = VMath::MATRIX_IDENTITY;

	m[3][0] = vec.x;
	m[3][1] = vec.y;
	m[3][2] = vec.z;
}

VVector VMatrix::GetTranslation()
{
	return VVector(m[3][0], m[3][1], m[3][2]);
}

void VMatrix::Billboard(const VVector& vPos, const VVector& vDir,
							VVector vWorldUp /*= VMath::VECTOR_UNIT_Y*/)
{
	VVector vUp, vRight;
	float	fAngle = 0.0f;

	fAngle = vWorldUp * vDir;

	vUp = vWorldUp - (vDir * fAngle);
	vUp.Normalize();

	vRight.Cross(vUp, vDir);

	m[0][0] = vRight.x;
	m[1][0] = vUp.x;
	m[2][0] = vDir.x;

	m[0][1] = vRight.y;
	m[1][1] = vUp.y;
	m[2][1] = vDir.y;

	m[0][2] = vRight.z;
	m[1][2] = vUp.z;
	m[2][2] = vDir.z;

	m[3][0] = vPos.x;
	m[3][1] = vPos.y;
	m[3][2] = vPos.z;

	m[0][3] = m[1][3] = m[2][3] = 0.0f;
	m[3][3] = 1.0f;
}

void VMatrix::LookAt(const VVector& vPos, const VVector& vLookAt,
						VVector vWorldUp /*= VMath::VECTOR_UNIT_Y*/)
{
	VVector vDir = vLookAt - vPos;
	vDir.Normalize();

	Billboard(vPos, vDir, vWorldUp);
}

void VMatrix::TransposeOf(const VMatrix& mat)
{
	m[0][0] = mat[0][0];
	m[1][0] = mat[0][1];
	m[2][0] = mat[0][2];
	m[3][0] = mat[0][3];

	m[0][1] = mat[1][0];
	m[1][1] = mat[1][1];
	m[2][1] = mat[1][2];
	m[3][1] = mat[1][3];

	m[0][2] = mat[2][0];
	m[1][2] = mat[2][1];
	m[2][2] = mat[2][2];
	m[3][2] = mat[2][3];

	m[0][3] = mat[3][0];
	m[1][3] = mat[3][1];
	m[2][3] = mat[3][2];
	m[3][3] = mat[3][3];
}

void VMatrix::InverseOf(const VMatrix& mat)
{
	VMatrix mTrans;
	float	fTemp[12];
	float	fDet;

	mTrans.TransposeOf(mat);

	fTemp[ 0] = mTrans[2][2] * mTrans[3][3];
	fTemp[ 1] = mTrans[2][3] * mTrans[3][2];
	fTemp[ 2] = mTrans[2][1] * mTrans[3][3];
	fTemp[ 3] = mTrans[2][3] * mTrans[3][1];
	fTemp[ 4] = mTrans[2][1] * mTrans[3][2];
	fTemp[ 5] = mTrans[2][2] * mTrans[3][1];
	fTemp[ 6] = mTrans[2][0] * mTrans[3][3];
	fTemp[ 7] = mTrans[2][3] * mTrans[3][0];
	fTemp[ 8] = mTrans[2][0] * mTrans[3][2];
	fTemp[ 9] = mTrans[2][2] * mTrans[3][0];
	fTemp[10] = mTrans[2][0] * mTrans[3][1];
	fTemp[11] = mTrans[2][1] * mTrans[3][0];

	m[0][0]  = fTemp[0] * mTrans[1][1] + fTemp[3] * mTrans[1][2]
					+ fTemp[4] * mTrans[1][3];
	m[0][0] -= fTemp[1] * mTrans[1][1] + fTemp[2] * mTrans[1][2]
					+ fTemp[5] * mTrans[1][3];
	m[0][1]  = fTemp[1] * mTrans[1][0] + fTemp[6] * mTrans[1][2]
					+ fTemp[9] * mTrans[1][3];
	m[0][1] -= fTemp[0] * mTrans[1][0] + fTemp[7] * mTrans[1][2]
					+ fTemp[8] * mTrans[1][3];
	m[0][2]  = fTemp[2] * mTrans[1][0] + fTemp[7] * mTrans[1][1]
					+ fTemp[10] * mTrans[1][3];
	m[0][2] -= fTemp[3] * mTrans[1][0] + fTemp[6] * mTrans[1][1]
					+ fTemp[11] * mTrans[1][3];
	m[0][3]  = fTemp[5] * mTrans[1][0] + fTemp[8] * mTrans[1][1]
					+ fTemp[11] * mTrans[1][2];
	m[0][3] -= fTemp[4] * mTrans[1][0] + fTemp[9] * mTrans[1][1]
					+ fTemp[10] * mTrans[1][2];
	m[1][0]  = fTemp[1] * mTrans[0][1] + fTemp[2] * mTrans[0][2]
					+ fTemp[5] * mTrans[0][3];
	m[1][0] -= fTemp[0] * mTrans[0][1] + fTemp[3] * mTrans[0][2]
					+ fTemp[4] * mTrans[0][3];
	m[1][1]  = fTemp[0] * mTrans[0][0] + fTemp[7] * mTrans[0][2]
					+ fTemp[8] * mTrans[0][3];
	m[1][1] -= fTemp[1] * mTrans[0][0] + fTemp[6] * mTrans[0][2]
					+ fTemp[9] * mTrans[0][3];
	m[1][2]  = fTemp[3] * mTrans[0][0] + fTemp[6] * mTrans[0][1]
					+ fTemp[11] * mTrans[0][3];
	m[1][2] -= fTemp[2] * mTrans[0][0] + fTemp[7] * mTrans[0][1]
					+ fTemp[10] * mTrans[0][3];
	m[1][3]  = fTemp[4] * mTrans[0][0] + fTemp[9] * mTrans[0][1]
					+ fTemp[10] * mTrans[0][2];
	m[1][3] -= fTemp[5] * mTrans[0][0] + fTemp[8] * mTrans[0][1]
					+ fTemp[11] * mTrans[0][2];

	fTemp[ 0] = mTrans[0][2] * mTrans[1][3];
	fTemp[ 1] = mTrans[0][3] * mTrans[1][2];
	fTemp[ 2] = mTrans[0][1] * mTrans[1][3];
	fTemp[ 3] = mTrans[0][3] * mTrans[1][1];
	fTemp[ 4] = mTrans[0][1] * mTrans[1][2];
	fTemp[ 5] = mTrans[0][2] * mTrans[1][1];
	fTemp[ 6] = mTrans[0][0] * mTrans[1][3];
	fTemp[ 7] = mTrans[0][3] * mTrans[1][0];
	fTemp[ 8] = mTrans[0][0] * mTrans[1][2];
	fTemp[ 9] = mTrans[0][2] * mTrans[1][0];
	fTemp[10] = mTrans[0][0] * mTrans[1][1];
	fTemp[11] = mTrans[0][1] * mTrans[1][0];

	m[2][0]  = fTemp[0] * mTrans[3][1] + fTemp[3] * mTrans[3][2]
					+ fTemp[4] * mTrans[3][3];
	m[2][0] -= fTemp[1] * mTrans[3][1] + fTemp[2] * mTrans[3][2]
					+ fTemp[5] * mTrans[3][3];
	m[2][1]  = fTemp[1] * mTrans[3][0] + fTemp[6] * mTrans[3][2]
					+ fTemp[9] * mTrans[3][3];
	m[2][1] -= fTemp[0] * mTrans[3][0] + fTemp[7] * mTrans[3][2]
					+ fTemp[8] * mTrans[3][3];
	m[2][2]  = fTemp[2] * mTrans[3][0] + fTemp[7] * mTrans[3][1]
					+ fTemp[10] * mTrans[3][3];
	m[2][2] -= fTemp[3] * mTrans[3][0] + fTemp[6] * mTrans[3][1]
					+ fTemp[11] * mTrans[3][3];
	m[2][3]  = fTemp[5] * mTrans[3][0] + fTemp[8] * mTrans[3][1]
					+ fTemp[11] * mTrans[3][2];
	m[2][3] -= fTemp[4] * mTrans[3][0] + fTemp[9] * mTrans[3][1]
					+ fTemp[10] * mTrans[3][2];
	m[3][0]  = fTemp[2] * mTrans[2][2] + fTemp[5] * mTrans[2][3]
					+ fTemp[1] * mTrans[2][1];
	m[3][0] -= fTemp[4] * mTrans[2][3] + fTemp[0] * mTrans[2][1]
					+ fTemp[3] * mTrans[2][2];
	m[3][1]  = fTemp[8] * mTrans[2][3] + fTemp[0] * mTrans[2][0]
					+ fTemp[7] * mTrans[2][2];
	m[3][1] -= fTemp[6] * mTrans[2][2] + fTemp[9] * mTrans[2][3]
					+ fTemp[1] * mTrans[2][0];
	m[3][2]  = fTemp[6] * mTrans[2][1] + fTemp[11] * mTrans[2][3]
					+ fTemp[3] * mTrans[2][0];
	m[3][2] -= fTemp[10] * mTrans[2][3] + fTemp[2] * mTrans[2][0]
					+ fTemp[7] * mTrans[2][1];
	m[3][3]  = fTemp[10] * mTrans[2][2] + fTemp[4] * mTrans[2][0]
					+ fTemp[9] * mTrans[2][1];
	m[3][3] -= fTemp[8] * mTrans[2][1] + fTemp[11] * mTrans[2][2]
					+ fTemp[5] * mTrans[2][0];

	fDet =	mTrans[0][0] * m[0][0] +
			mTrans[0][1] * m[0][1] +
			mTrans[0][2] * m[0][2] +
			mTrans[0][3] * m[0][3];

	m[0][0] *= fDet;
	m[0][1] *= fDet;
	m[0][2] *= fDet;
	m[0][3] *= fDet;

	m[1][0] *= fDet;
	m[1][1] *= fDet;
	m[1][2] *= fDet;
	m[1][3] *= fDet;

	m[2][0] *= fDet;
	m[2][1] *= fDet;
	m[2][2] *= fDet;
	m[2][3] *= fDet;

	m[3][0] *= fDet;
	m[3][1] *= fDet;
	m[3][2] *= fDet;
	m[3][3] *= fDet;
}

/********************************************************************
 *                          O P E R A T O R S                       *
 ********************************************************************/

VMatrix VMatrix::operator*(const VMatrix& mat) const
{
	VMatrix mResult;

	if (VCPU::HaveSSE())
	{
		float *pA = (float*)this;
		float *pB = (float*)&m;
		float *pM = (float*)&mResult;

		memset(pM, 0, sizeof(VMatrix));

		for(unsigned char i=0; i<4; i++)
		{
			for(unsigned char j=0; j<4; j++)
			{
				pM[4*i+j] += pA[4*i]   * pB[j];
				pM[4*i+j] += pA[4*i+1] * pB[4+j];
				pM[4*i+j] += pA[4*i+2] * pB[8+j];
				pM[4*i+j] += pA[4*i+3] * pB[12+j];
			}
		}
/* Commented until I can figure out a way to do this on *nix */
#if VIPER_PLATFORM == PLATFORM_WINDOWS
		__asm {
			mov edx, dword ptr [esp+4] ; src1
			mov eax, dword ptr [esp+0Ch] ; dst
			mov ecx, dword ptr [esp+8] ; src2
			movss xmm0, dword ptr [edx]
			movups xmm1, xmmword ptr [ecx]
			shufps xmm0, xmm0, 0
			movss xmm2, dword ptr [edx+4]
			mulps xmm0, xmm1
			shufps xmm2, xmm2, 0
			movups xmm3, xmmword ptr [ecx+10h]
			movss xmm7, dword ptr [edx+8]
			mulps xmm2, xmm3
			shufps xmm7, xmm7, 0
			addps xmm0, xmm2
			movups xmm4, xmmword ptr [ecx+20h]
			movss xmm2, dword ptr [edx+0Ch]
			mulps xmm7, xmm4
			shufps xmm2, xmm2, 0
			addps xmm0, xmm7
			movups xmm5, xmmword ptr [ecx+30h]
			movss xmm6, dword ptr [edx+10h]
			mulps xmm2, xmm5
			movss xmm7, dword ptr [edx+14h]
			shufps xmm6, xmm6, 0
			addps xmm0, xmm2
			shufps xmm7, xmm7, 0
			movlps qword ptr [eax], xmm0
			movhps qword ptr [eax+8], xmm0
			mulps xmm7, xmm3
			movss xmm0, dword ptr [edx+18h]
			mulps xmm6, xmm1
			shufps xmm0, xmm0, 0
			addps xmm6, xmm7
			mulps xmm0, xmm4
			movss xmm2, dword ptr [edx+24h]
			addps xmm6, xmm0
			movss xmm0, dword ptr [edx+1Ch]
			movss xmm7, dword ptr [edx+20h]
			shufps xmm0, xmm0, 0
			shufps xmm7, xmm7, 0
			mulps xmm0, xmm5
			mulps xmm7, xmm1
			addps xmm6, xmm0
			shufps xmm2, xmm2, 0
			movlps qword ptr [eax+10h], xmm6
			movhps qword ptr [eax+18h], xmm6
			mulps xmm2, xmm3
			movss xmm6, dword ptr [edx+28h]
			addps xmm7, xmm2
			shufps xmm6, xmm6, 0
			movss xmm2, dword ptr [edx+2Ch]
			mulps xmm6, xmm4
			shufps xmm2, xmm2, 0
			addps xmm7, xmm6
			mulps xmm2, xmm5
			movss xmm0, dword ptr [edx+34h]
			addps xmm7, xmm2
			shufps xmm0, xmm0, 0
			movlps qword ptr [eax+20h], xmm7
			movss xmm2, dword ptr [edx+30h]
			movhps qword ptr [eax+28h], xmm7
			mulps xmm0, xmm3
			shufps xmm2, xmm2, 0
			movss xmm6, dword ptr [edx+38h]
			mulps xmm2, xmm1
			shufps xmm6, xmm6, 0
			addps xmm2, xmm0
			mulps xmm6, xmm4
			movss xmm7, dword ptr [edx+3Ch]
			shufps xmm7, xmm7, 0
			addps xmm2, xmm6
			mulps xmm7, xmm5
			addps xmm2, xmm7
			movups xmmword ptr [eax+30h], xmm2
			ret
		}
#elif VIPER_PLATFORM == PLATFORM_APPLE
#elif VIPER_PLATFORM == PLATFORM_LINUX
		const VMatrix *pSrc1 = this;
		const VMatrix *pSrc2 = &mat;
		VMatrix *pDest = &mResult;
		__asm__ __volatile__ (
			".intel_syntax noprefix\n\t"
			"mov %0, 	%%edx\n\t"
			"mov %1,	%%ecx\n\t"
			"mov %2,	%%eax\n\t"
			"movss xmm0, dword ptr [edx]\n\t"
			"movups xmm1, xmmword ptr [ecx]\n\t"
			"shufps xmm0, xmm0, 0\n\t"
			"movss xmm2, dword ptr [edx+4]\n\t"
			"mulps xmm0, xmm1\n\t"
			"shufps xmm2, xmm2, 0\n\t"
			"movups xmm3, xmmword ptr [ecx+10h]\n\t"
			"movss xmm7, dword ptr [edx+8]\n\t"
			"mulps xmm2, xmm3\n\t"
			"shufps xmm7, xmm7, 0\n\t"
			"addps xmm0, xmm2\n\t"
			"movups xmm4, xmmword ptr [ecx+20h]\n\t"
			"movss xmm2, dword ptr [edx+0Ch]n\t"
			"mulps xmm7, xmm4\n\t"
			"shufps xmm2, xmm2, 0\n\t"
			"addps xmm0, xmm7\n\t"
			"movups xmm5, xmmword ptr [ecx+30h]\n\t"
			"movss xmm6, dword ptr [edx+10h]\n\t"
			"mulps xmm2, xmm5\n\t"
			"movss xmm7, dword ptr [edx+14h]\n\t"
			"shufps xmm6, xmm6, 0\n\t"
			"addps xmm0, xmm2\n\t"
			"shufps xmm7, xmm7, 0\n\t"
			"movlps qword ptr [eax], xmm0\n\t"
			"movhps qword ptr [eax+8], xmm0\n\t"
			"mulps xmm7, xmm3\n\t"
			"movss xmm0, dword ptr [edx+18h]\n\t"
			"mulps xmm6, xmm1\n\t"
			"shufps xmm0, xmm0, 0\n\t"
			"addps xmm6, xmm7\n\t"
			"mulps xmm0, xmm4\n\t"
			"movss xmm2, dword ptr [edx+24h]\n\t"
			"addps xmm6, xmm0\n\t"
			"movss xmm0, dword ptr [edx+1Ch]\n\t"
			"movss xmm7, dword ptr [edx+20h]\n\t"
			"shufps xmm0, xmm0, 0\n\t"
			"shufps xmm7, xmm7, 0\n\t"
			"mulps xmm0, xmm5\n\t"
			"mulps xmm7, xmm1\n\t"
			"addps xmm6, xmm0\n\t"
			"shufps xmm2, xmm2, 0\n\t"
			"movlps qword ptr [eax+10h], xmm6\n\t"
			"movhps qword ptr [eax+18h], xmm6\n\t"
			"mulps xmm2, xmm3\n\t"
			"movss xmm6, dword ptr [edx+28h]\n\t"
			"addps xmm7, xmm2\n\t"
			"shufps xmm6, xmm6, 0\n\t"
			"movss xmm2, dword ptr [edx+2Ch]\n\t"
			"mulps xmm6, xmm4\n\t"
			"shufps xmm2, xmm2, 0\n\t"
			"addps xmm7, xmm6\n\t"
			"mulps xmm2, xmm5\n\t"
			"movss xmm0, dword ptr [edx+34h]\n\t"
			"addps xmm7, xmm2\n\t"
			"shufps xmm0, xmm0, 0\n\t"
			"movlps qword ptr [eax+20h], xmm7\n\t"
			"movss xmm2, dword ptr [edx+30h]\n\t"
			"movhps qword ptr [eax+28h], xmm7\n\t"
			"mulps xmm0, xmm3\n\t"
			"shufps xmm2, xmm2, 0\n\t"
			"movss xmm6, dword ptr [edx+38h]\n\t"
			"mulps xmm2, xmm1\n\t"
			"shufps xmm6, xmm6, 0\n\t"
			"addps xmm2, xmm0\n\t"
			"mulps xmm6, xmm4\n\t"
			"movss xmm7, dword ptr [edx+3Ch]\n\t"
			"shufps xmm7, xmm7, 0\n\t"
			"addps xmm2, xmm6\n\t"
			"mulps xmm7, xmm5\n\t"
			"addps xmm2, xmm7\n\t"
			"movups xmmword ptr [eax+30h], xmm2\n\t"
			"ret"
			:
			: "m" (pSrc1),
			  "m" (pSrc2),
			  "m" (pDest)
			: "eax", "edx", "ecx", "memory"
		);

#endif
	}
	else
	{
		for (byte i = 0; i < 4; i++)
		{
			for (byte j = 0; j < 4; j++)
			{
				mResult[i][j] += m[i][0] * mat[0][j];
				mResult[i][j] += m[i][1] * mat[1][j];
				mResult[i][j] += m[i][2] * mat[2][j];
				mResult[i][j] += m[i][3] * mat[3][j];
			}
		}
	}
	return mResult;
}

VVector VMatrix::operator*(const VVector& vec) const
{
	VVector vResult;

	vResult.x = vec.x * m[0][0] + vec.y * m[1][0] + vec.z * m[2][0] + m[3][0];
	vResult.y = vec.x * m[0][1] + vec.y * m[1][1] + vec.z * m[2][1] + m[3][1];
	vResult.z = vec.x * m[0][2] + vec.y * m[1][2] + vec.z * m[2][2] + m[3][2];
	vResult.w = vec.x * m[0][3] + vec.y * m[1][3] + vec.z * m[2][3] + m[3][3];

	vResult.x = vResult.x / vResult.w;
	vResult.y = vResult.y / vResult.w;
	vResult.z = vResult.z / vResult.w;
	vResult.w = 1.0f;

	return vResult;
}

/*------------------------------------------------------------------*
 *							  operator=()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VMatrix::operator=(const VMatrix& mat)
{
	m[0][0] = mat[0][0];
	m[0][1] = mat[0][1];
	m[0][2] = mat[0][2];
	m[0][3] = mat[0][3];

	m[1][0] = mat[1][0];
	m[1][1] = mat[1][1];
	m[1][2] = mat[1][2];
	m[1][3] = mat[1][3];

	m[2][0] = mat[2][0];
	m[2][1] = mat[2][1];
	m[2][2] = mat[2][2];
	m[2][3] = mat[2][3];

	m[3][0] = mat[3][0];
	m[3][1] = mat[3][1];
	m[3][2] = mat[3][2];
	m[3][3] = mat[3][3];
}

/*------------------------------------------------------------------*
 *							MakeGLMatrix()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Converts this matrix to a GL matrix (float array)
 *	@author		Josh Williams
 *	@date		12-Sep-2003
 *
 *	@remarks	OpenGL expects an array of float value instead of an
 *				actual matrix.
 *
 *	@param		gl_matrix	Array to be populated with values from
 *							this VMatrix.
 *
 *	@returns	void
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VMatrix::MakeGLMatrix(float gl_matrix[16])
{
	for (int i = 0; i < 16; i++)
	{
		gl_matrix[i]  =_m[i];
	}
}

/********************************************************************
 *                         C A L L B A C K S                        *
 ********************************************************************/

/********************************************************************
 *                         I N T E R N A L S                        *
 ********************************************************************/

} // End Namespace
