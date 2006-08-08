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
	static void		GetIntelInfo(int *n);
	static void		GetAMDInfo(int *n);

private:
	/*==================================*
	 *             VARIABLES            *
	 *==================================*/
	static bool		m_bSSE;
	static bool		m_bSSE2;
	static bool		m_b3DNOW;
	static bool		m_bMMX;
	static bool		m_bEXT;
	static bool		m_bMMXEX;
	static bool		m_b3DNOWEX;
	static char		m_Vendor[13];
	static char		m_Name[48];
public:
	static bool		m_bOSSSE;
};

} // End Namespace

#endif // __VCPU_H_INCLUDED__

