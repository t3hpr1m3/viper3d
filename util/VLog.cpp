/*============================================================================*
 *                                                                            *
 * 	This source file is part of the Viper3D Game Engine.                      *
 *                                                                            *
 *	Copyright (C) 2004 UDP Games   All Rights Reserved.                       *
 *                                                                            *
 *============================================================================*/
#include "VLog.h"

/* System Headers */

/* Local Headers */

/* Macros */

namespace UDP
{

/* Static Variables */
char*		VLog::m_logName = NULL;
ofstream	VLog::m_logFile;
bool		VLog::m_bFlush = false;

/********************************************************************
 *																	*
 *          C O N S T R U C T I O N / D E S T R U C T I O N         *
 *																	*
 ********************************************************************/
VLog::VLog()
{
	m_bFlush = false;
}

VLog::~VLog()
{
	if (m_logFile.is_open())
	{
		m_logFile.close();
	}

	if (m_logName != NULL)
	{
		delete[] m_logName;
		m_logName = NULL;
	}
}

/********************************************************************
 *																	*
 *                        A T T R I B U T E S                       *
 *																	*
 ********************************************************************/

/********************************************************************
 *																	*
 *                        O P E R A T I O N S                       *
 *																	*
 ********************************************************************/
void VLog::SetName(const char *pcName)
{
	if (m_logName == NULL)
	{
		m_logName = new char[strlen(pcName) + 1];
		strcpy(m_logName, pcName);
	}
}

void VLog::SetFlush(bool bFlush /*=true*/)
{
	m_bFlush = bFlush;
}

VLog& VLog::Get()
{
	static VLog log;

	if (!m_logFile.is_open())
		log.Init();

	return log;
}

void VLog::Write(const char *pcText, ...) const
{
	char	buffer[1024];
	va_list	args;

	va_start(args, pcText);
	vsnprintf(buffer, 1024, pcText, args);
	va_end(args);

	if (m_logFile.is_open())
	{
		m_logFile << buffer;
		if (m_bFlush)
		{
			m_logFile.flush();
		}
	}
}

/********************************************************************
 *																	*
 *                          O P E R A T O R S                       *
 *																	*
 ********************************************************************/

/********************************************************************
 *																	*
 *                          C A L L B A C K S                       *
 *																	*
 ********************************************************************/

/********************************************************************
 *																	*
 *                          I N T E R N A L S                       *
 *																	*
 ********************************************************************/
bool VLog::Init()
{
	m_logFile.open(m_logName, ios_base::app);
	if (m_logFile.is_open())
	{
		Write("************************************************\n");
		Write("*           Log Opened                         *\n");
		Write("************************************************\n");
	}

	return m_logFile.is_open();
}

} // End Namespace

/* vi: set ts=4: */
