/*============================================================================*
 *                                                                            *
 * 	This source file is part of the Viper3D Game Engine.                      *
 *                                                                            *
 *	Copyright (C) 2004 UDP Games   All Rights Reserved.                       *
 *                                                                            *
 *============================================================================*/

/* System Headers */
#include <cstdio>
#include <cstdarg>

/* Local Headers */
#include "Globals.h"
#include "VLogger.h"

namespace UDP
{

ofstream	VLogger::m_logFile;
bool		VLogger::m_bOpen;
/********************************************************************
 *          C O N S T R U C T I O N / D E S T R U C T I O N         *
 ********************************************************************/
VLogger::VLogger()
{
	m_bOpen = false;
}

VLogger::~VLogger()
{
	if (m_bOpen)
		m_logFile.close();
	m_bOpen = false;
}

/********************************************************************
 *                        A T T R I B U T E S                       *
 ********************************************************************/

/********************************************************************
 *                        O P E R A T I O N S                       *
 ********************************************************************/

/*------------------------------------------------------------------*
 *								  Get()								*
 *------------------------------------------------------------------*/
/**
 *	@brief		Returns the local static instance of the VLogger
 *				class.  This allows a single trace file to be shared
 *				among several objects.
 *	@author		Josh Williams
 *	@date		10-Sep-2004
 *
 *	@returns	(const char*) Requested characters.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VLogger& VLogger::Get()
{
	static VLogger log;

	if (!m_bOpen)
		log.Init();

	return log;
}

/*------------------------------------------------------------------*
 *								 Write()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Performs the actual output to the log file.  Allows
 *				for parameter substitution.
 *	@author		Josh Williams
 *	@date		10-Sep-2004
 *
 *	@param		pcText	Test to be output to the log file.
 *
 *	@returns	void
 *
 *	@remarks	If this is a debug build, output is flushed immediately.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VLogger::Write(const char *pcText, ...) const
{
	char	buffer[1024];
	va_list	args;

	va_start(args, pcText);
	vsnprintf(buffer, 1024, pcText, args);
	va_end(args);

	if (m_bOpen)
	{
		m_logFile << buffer;
#ifdef DEBUG
		m_logFile.flush();
#endif
	}
}	

/********************************************************************
 *                         C A L L B A C K S                        *
 ********************************************************************/

/********************************************************************
 *                         I N T E R N A L S                        *
 ********************************************************************/

/*------------------------------------------------------------------*
 *								  Init()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Opens the log file, if possible.
 *	@author		Josh Williams
 *	@date		10-Sep-2004
 *
 *	@returns	Success/failure
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
bool VLogger::Init(void)
{
	m_logFile.open("Viper3D.log");
	if (m_logFile.is_open())
		m_bOpen = true;

	return m_bOpen;
}

} // End Namespace

