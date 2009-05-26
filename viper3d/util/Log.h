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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

/* System Headers */
#include <cstdarg>
#include <iostream>
#include <fstream>

/* Local Headers */

using std::ofstream;
using std::ios_base;
using std::cout;
using std::endl;

#define _CL( a ) "%s "a, __CLASS__
#ifdef TRACE_ENABLE
#define VTRACES VLog::Get() 
#define VTRACE VLog::Get().Write
#else
#define VTRACE 1 ? (void)0 : (void)
#endif

namespace UDP
{

/**
 *	@class		VLog
 *
 *	@brief		Quick and dirty logging class.
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		2004-Aug-31
 */
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
	typedef enum
	{
		NEWLINE
	} Endline;
	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	static void		SetName(const char *pName);
	static void		SetFlush(bool pFlush = true);
	static VLog&	Get();
	void			Write(const char *pText, ...) const;
	VLog&			operator<<(Endline pEndline)
	{
		mLogFile << std::endl;
		cout << std::endl;
	}

	template <typename T>
	VLog&			operator<<(const T &pObj)
	{
		mLogFile << pObj;
		std::cout << pObj;
		return *this;
	}
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
	static char		*mLogName;
	static ofstream	mLogFile;

	static bool		mFlush;
};

} // End Namespace

#endif // __VLOG_H_INCLUDED__

