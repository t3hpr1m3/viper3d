/*============================================================================*
 *                                                                            *
 * 	This source file is part of the Viper3D Game Engine.					  *
 *                                                                            *
 *	Copyright (C) 2004 UDP Games   All Rights Reserved.						  *
 *                                                                            *
 *============================================================================*/

/* System Headers */
#include "math.h"

/* Local Headers */
#include "VMath.h"

namespace UDP
{

const float 	VMath::PI = float(4.0 * atan(1.0));
const float 	VMath::TWO_PI = float(2.0 * PI);
const float 	VMath::HALF_PI = float(0.5 * PI);

const VQuaternion VMath::QUATERNION_ZERO(0.0f, 0.0f, 0.0f, 0.0f);
const VQuaternion VMath::QUATERNION_IDENTITY(0.0f, 0.0f, 0.0f, 1.0f);

/********************************************************************
 *          C O N S T R U C T I O N / D E S T R U C T I O N         *
 ********************************************************************/

/********************************************************************
 *                        A T T R I B U T E S                       *
 ********************************************************************/

/********************************************************************
 *                        O P E R A T I O N S                       *
 ********************************************************************/

/*------------------------------------------------------------------*
 *								 Abs() 								*
 *------------------------------------------------------------------*/
/**
 *	@brief		Absolute value.
 *	@author		Josh Williams
 *	@date		11-Jan-1981
 *
 *	@param		fValue	scalar to process
 *
 *	@returns	(float) Absolute value of fValue.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
float VMath::Abs(float fValue)
{
	return fabsf(fValue);
}

/*------------------------------------------------------------------*
 *								 ACos()								*
 *------------------------------------------------------------------*/
/**
 *	@brief		ArcCosine
 *	@author		Josh Williams
 *	@date		11-Sep-2003
 *
 *	@param		fValue	scalar to process
 *
 *	@returns	(float) ArcCosine of fValue.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
float VMath::ACos(float fValue)
{
	//if (-1.0 < fValue)
	//{
	//	if (fValue < 1.0)
			return acosf(fValue);
	//	else
	//		return 0.0;
	//}
	//else
	//{
	//	return PI;
	//}
}

/*------------------------------------------------------------------*
 *								 ASin()								*
 *------------------------------------------------------------------*/
/**
 *	@brief		ArcSine
 *	@author		Josh Williams
 *	@date		11-Sep-2003
 *
 *	@param		fValue	scalar to process
 *
 *	@returns	(float) ArcSine of fValue.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
float VMath::ASin(float fValue)
{
	if (-1.0 < fValue)
	{
		if (fValue < 1.0)
			return asinf(fValue);
		else
			return -HALF_PI;
	}
	else
	{
		return HALF_PI;
	}
}

/*------------------------------------------------------------------*
 *								ATan() 								*
 *------------------------------------------------------------------*/
/**
 *	@brief		ArcTangent
 *	@author		Josh Williams
 *	@date		11-Sep-2003
 *
 *	@param		fValue	scalar to process
 *
 *	@returns	(float) Arc Tangent of fValue.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
float VMath::ATan(float fValue)
{
	return atanf(fValue);
}

/*------------------------------------------------------------------*
 *								 Cos()								*
 *------------------------------------------------------------------*/
/**
 *	@brief		Cosine
 *	@author		Josh Williams
 *	@date		11-Sep-2003
 *
 *	@param		fValue	scalar to process
 *
 *	@returns	(float) Cosine of fValue.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
float VMath::Cos(float fValue)
{
	return cosf(fValue);
}

/*------------------------------------------------------------------*
 *								 Sin() 								*
 *------------------------------------------------------------------*/
/**
 *	@brief		Sine
 *	@author		Josh Williams
 *	@date		11-Sep-2003
 *
 *	@param		fValue	scalar to process
 *
 *	@returns	(float) Sine of fValue.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
float VMath::Sin(float fValue)
{
	return sinf(fValue);
}

/*------------------------------------------------------------------*
 *								 Tan()								*
 *------------------------------------------------------------------*/
/**
 *	@brief		Tangent
 *	@author		Josh Williams
 *	@date		11-Sep-2003
 *
 *	@param		fValue	scalar to process
 *
 *	@returns	(float) Tangent of fValue.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
float VMath::Tan(float fValue)
{
	return tanf(fValue);
}

/*------------------------------------------------------------------*
 *								Sqrt() 								*
 *------------------------------------------------------------------*/
/**
 *	@brief		Square root
 *	@author		Josh Williams
 *	@date		11-Sep-2003
 *
 *	@param		fValue	scalar to process
 *
 *	@returns	(float) Square root of fValue.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
float VMath::Sqrt(float fValue)
{
	return sqrtf(fValue);
}

/*------------------------------------------------------------------*
 *							 DegToRad()								*
 *------------------------------------------------------------------*/
/**
 *	@brief		Convert degrees to radians
 *	@author		Josh Williams
 *	@date		11-Sep-2003
 *
 *	@param		degrees	scalar value to convert
 *
 *	@returns	(float) value of degrees converted to radians.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
float VMath::DegToRad(float degrees)
{
	static float fDeg2Rad = PI / 180.0f;

	return degrees * fDeg2Rad;
}

/*------------------------------------------------------------------*
 *						      RadToDeg()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Convert radians to degrees
 *	@author		Josh Williams
 *	@date		11-Sep-2003
 *
 *	@param		radians	scalar value to convert
 *
 *	@returns	(float) value of radians converted to degrees.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
float VMath::RadToDeg(float radians)
{
	return ((radians * 180.0f) / PI);
}

/*------------------------------------------------------------------*
 *							   Modulus()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Returns the modulus (remainder) of floating point division.
 *	@author		Josh Williams
 *	@date		13-Sep-2003
 *
 *	@remarks	This probably isn't needed, but I couldn't find a cleaner
 *				way to accomplish it.
 *
 *	@param		dividend	number to be divided
 *	@param		divisor		Number to be divided by
 *
 *	@returns	(float) Remainder of the division function.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
float VMath::Modulus(float dividend, int divisor)
{
	float dec = dividend - (int)dividend;
	int temp = (int)dividend % divisor;
	return temp + dec;
}

/********************************************************************
 *                         C A L L B A C K S                        *
 ********************************************************************/

/********************************************************************
 *                         I N T E R N A L S                        *
 ********************************************************************/

} // End Namespace
