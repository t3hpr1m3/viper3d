/**
 *	@class		UDP::VMatrix
 *
 *	@brief		Represents a 4x4 matrix, used in GL routines.
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		11-Sep-2004
 */
/*============================================================================*
 *                                                                            *
 *  This file is part of the Viper3D Game Engine.                             *
 *																			  *
 *  Copyright (C) 2004 UDP Games   All Rights Reserved.						  *
 *                                                                            *
 *============================================================================*
 *                                  CHANGELOG                                 *
 *    Date      Description                                     Author        *
 * -----------  ----------------------------------------------  ------------- *
 *                                                                            *
 *============================================================================*/
#if !defined(__VMATRIX_H_INCLUDED__)
#define __VMATRIX_H_INCLUDED__

#include "Globals.h"
#include "VMath.h"

namespace UDP
{

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

} // End Namespace

#endif // __MATRIX4_H_INCLUDED__
