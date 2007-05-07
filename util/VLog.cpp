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
#include "VLog.h"

/* System Headers */

/* Local Headers */

/* Macros */

namespace UDP
{

/* Static Variables */
char*		VLog::mLogName = NULL;
ofstream	VLog::mLogFile;
bool		VLog::mFlush = false;

/********************************************************************
 *																	*
 *          C O N S T R U C T I O N / D E S T R U C T I O N         *
 *																	*
 ********************************************************************/
VLog::VLog()
{
	mFlush = false;
}

VLog::~VLog()
{
	if (mLogFile.is_open())
	{
		mLogFile.close();
	}

	if (mLogName != NULL)
	{
		delete[] mLogName;
		mLogName = NULL;
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
void VLog::SetName(const char *pName)
{
	if (mLogName == NULL)
	{
		mLogName = new char[strlen(pName) + 1];
		strcpy(mLogName, pName);
	}
}

void VLog::SetFlush(bool pFlush /*=true*/)
{
	mFlush = pFlush;
}

VLog& VLog::Get()
{
	static VLog vLog;

	if (!mLogFile.is_open())
		vLog.Init();

	return vLog;
}

void VLog::Write(const char *pText, ...) const
{
	char	vBuffer[1024];
	va_list	vArgs;

	va_start(vArgs, pText);
	vsnprintf(vBuffer, 1024, pText, vArgs);
	va_end(vArgs);

	if (mLogFile.is_open())
	{
		mLogFile << vBuffer;
		if (mFlush)
		{
			mLogFile.flush();
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
	mLogFile.open(mLogName, ios_base::app);
	if (mLogFile.is_open())
	{
		Write("************************************************\n");
		Write("*           Log Opened                         *\n");
		Write("************************************************\n");
	}

	return mLogFile.is_open();
}

} // End Namespace

/* vi: set ts=4: */
