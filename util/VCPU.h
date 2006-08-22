/**
 *	@class		UDP::VCPU
 *
 *	@brief		Extracts information about the CPU's capabilities.
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		2004-Sep-09
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
#if !defined(__VCPU_H_INCLUDED__)
#define __VCPU_H_INCLUDED__

/* System Headers */

/* Local Headers */

namespace UDP
{

class VCPU
{
protected:
	/*==================================*
	 *	   CONSTRUCTION/DESTRUCTION		*
	 *==================================*/
	VCPU(void);
	virtual ~VCPU(void);

public:
	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/
	static bool		HaveSSE();

	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	static void		Init();

protected:
	/*==================================*
	 *             CALLBACKS			*
	 *==================================*/

private:
	/*==================================*
	 *             INTERNALS            *
	 *==================================*/
	static void		GetCPUVendor();
	static void		GetBaseFeatures();
	static void		GetExtFeatures();
	static void		GetIntelInfo(int *Pn);
	static void		GetAMDInfo(int *Pn);

private:
	/*==================================*
	 *             VARIABLES            *
	 *==================================*/
	static bool		mSSE;
	static bool		mSSE2;
	static bool		m3DNOW;
	static bool		mMMX;
	static bool		mEXT;
	static bool		mMMXEX;
	static bool		m3DNOWEX;
	static char		mVendor[13];
	static char		mName[48];
public:
	static bool		mOSSSE;
};

} // End Namespace

#endif // __VCPU_H_INCLUDED__

