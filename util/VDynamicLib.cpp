/*============================================================================*
 *																			  *
 *  This file is part of the Viper3D Game Engine.                             *
 *																			  *
 *	Copyright (C) 2004 UDP Games   All Rights Reserved.						  *
 *																			  *
 *============================================================================*/

/* System Headers */

/* Local Headers */
#include "VString.h"
#include "VDynamicLib.h"
#include "VLog.h"

namespace UDP
{

static char __CLASS__[] = "[ VDynamicLib  ]";

/********************************************************************
 *          C O N S T R U C T I O N / D E S T R U C T I O N         *
 ********************************************************************/
VDynamicLib::VDynamicLib(void)
{
	m_hInst = NULL;
	m_Name = "";
	m_strError = "";

}

VDynamicLib::~VDynamicLib(void)
{
	if (m_hInst != NULL)
		UnLoad();
}

/********************************************************************
 *                        A T T R I B U T E S                       *
 ********************************************************************/

/********************************************************************
 *                        O P E R A T I O N S                       *
 ********************************************************************/

/*------------------------------------------------------------------*
 *								 Load()								*
 *------------------------------------------------------------------*/
/**
 *	@brief		Loads the library into memory.
 *	@author		Josh Williams
 *	@date		25-Sep-2003
 *
 *	@param		path	Path (relative or absolute) to the library.
 *	@param		name	Base name of the library to be loaded.
 *
 *	@returns	bool	Library load success/failure
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
bool VDynamicLib::Load(const VString& path, const VString& name)
{
	BuildLibName(path, name);

	VTRACE(_CL("Loading %s\n"), m_Name.C_Str());

	m_hInst = (DYNLIB_HANDLE)DYNLIB_LOAD( m_Name.C_Str() );
	if (m_hInst == NULL)
	{
		VTRACE(_CL("Unable to load library.\n"));
		m_strError = DYNLIB_ERROR();
		VTRACE(_CL("Error: %s\n"), Error());
		return false;
	}

	return true;
}

/*------------------------------------------------------------------*
 *								UnLoad()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Frees memory allocated for this library object.
 *	@author		Josh Williams
 *	@date		25-Sep-2003
 *
 *	@returns	void
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VDynamicLib::UnLoad()
{
	if (m_hInst != NULL)
		DYNLIB_UNLOAD( m_hInst );

	m_hInst = NULL;
}

/*------------------------------------------------------------------*
 *							  GetSymbol()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Obtains a pointer to a symbol exported from the library.
 *	@author		Josh Williams
 *	@date		25-Sep-2003
 *
 *	@param		strName	Function to search for in the library.
 *
 *	@returns	What value this function returns, or void
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void* VDynamicLib::GetSymbol(const VString& strName) const
{
	if (m_hInst == NULL)
	{
		VTRACE(_CL("GetSymbol() called with no library loaded\n"));
		return NULL;
	}

	return DYNLIB_GETSYM( m_hInst, strName.C_Str());
}

/*------------------------------------------------------------------*
 *							  GetSymbol()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Retrieves the text for the last error encountered.
 *	@author		Josh Williams
 *	@date		25-Sep-2004
 *
 *	@returns	VString containing the error text
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
const char* VDynamicLib::Error(void) const
{
	return m_strError.C_Str();
}

/********************************************************************
 *                         C A L L B A C K S                        *
 ********************************************************************/

/********************************************************************
 *                         I N T E R N A L S                        *
 ********************************************************************/

/*------------------------------------------------------------------*
 *							 BuildLibName()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Builds the platform specific library name
 *	@author		Josh Williams
 *	@date		02-Sep-2004
 *
 *	@param		path	Path to the location of the library
 *	@param		name	Basename of the library.
 *
 *	@returns	void
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VDynamicLib::BuildLibName(const VString& path, const VString& name)
{
	m_Name = path;
#if VIPER_PLATFORM == PLATFORM_WINDOWS
	if (m_Name[m_Name.Length()-1] != '\\')
		m_Name += "\\";
	m_Name += name + ".dll";
#elif VIPER_PLATFORM == PLATFORM_LINUX
	if (m_Name[m_Name.Length()-1] != '/')
		m_Name += "/";
	m_Name += "lib";
	m_Name += name + ".so";
#endif
}

} // End Namespace
