/**
 *	@class		UDP::VLog
 *
 *	@brief		Quick and dirty logging class.
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		2004-Aug-31
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
#if !defined(__VLOG_H_INCLUDED__)
#define __VLOG_H_INCLUDED__

#include <cstdarg>
#include <fstream>

using std::ofstream;
using std::ios_base;

#define _CL( a ) "%s "a, __CLASS__
#ifdef DEBUG
#define VTRACE VLog::Get().Write
#else
#define VTRACE (void)0
#endif

namespace UDP
{

class VLog
{
protected:
	/*==================================*
	 *	   CONSTRUCTION/DESTRUCTION		*
	 *==================================*/
	VLog();
	virtual ~VLog();

	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/
public:
	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	static void		SetName(const char *pcName);
	static void		SetFlush(bool bFlush = true);
	static VLog&	Get();
	void			Write(const char *pcText, ...) const;
protected:
	/*==================================*
	 *             CALLBACKS			*
	 *==================================*/

private:
	/*==================================*
	 *             INTERNALS            *
	 *==================================*/
	bool			Init();
	
private:
	/*==================================*
	 *             VARIABLES            *
	 *==================================*/
	static char		*m_logName;
	static ofstream	m_logFile;

	static bool		m_bFlush;
};

} // End Namespace

#endif // __VLOG_H_INCLUDED__

