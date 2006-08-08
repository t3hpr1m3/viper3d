/*============================================================================*
 *                                                                            *
 * 	This source file is part of the Viper3D Game Engine.                      *
 *                                                                            *
 *	Copyright (C) 2004 UDP Games   All Rights Reserved.                       *
 *                                                                            *
 *============================================================================*/

/* System Headers */

/* Local Headers */
#include "VWindow.h"
#include "VLog.h"

namespace UDP
{

static char __CLASS__[] = "[   VWindow    ]";

/********************************************************************
 *          C O N S T R U C T I O N / D E S T R U C T I O N         *
 ********************************************************************/
VWindow::VWindow(void)
{
	m_pDevice = NULL;
}

VWindow::~VWindow(void)
{
	if (m_pDevice != NULL)
		Release();
}

/********************************************************************
 *                        A T T R I B U T E S                       *
 ********************************************************************/

/*------------------------------------------------------------------*
 *							  GetDevice()							*
 *------------------------------------------------------------------*/
/**	@brief		Returns a handle to the underlying VWindowSystem.
 *	@author		Josh Williams
 *	@date		01-Sep-2004
 *
 *	@remarks	Pointer returned can be used to perform window
 *				operations (resizine, fullscreen, etc).
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VWindowSystem* VWindow::GetDevice(void)
{
	return m_pDevice;
}

/********************************************************************
 *                        O P E R A T I O N S                       *
 ********************************************************************/

/*------------------------------------------------------------------*
 *							CreateDevice()							*
 *------------------------------------------------------------------*/
/**	@brief		Creates the specified VWindowSystem.
 *	@author		Josh Williams
 *	@date		01-Sep-2004
 *
 *	@param		pcAPI	Desired window system (X, Win32, etc)
 *
 *	@returns	Success/failure
 *
 *	@remarks	Loads the necessary library into memory and obtains
 *				pointers to the creation and deletion functions.
 *				If successful, function tries to create the specific
 *				VWindowSystem object.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
bool VWindow::CreateDevice(char *pcAPI)
{
	if (strcmp(pcAPI, "X") == 0)
	{
		/* try to load the X window library */
		VTRACE(_CL("Loading X window system library\n"));
		if (!m_windowLib.Load("./libs", "VXWindow"))
		{
			VTRACE(_CL("Unable to load window library\n"));
			return false;
		}
		VTRACE(_CL("Library loaded successfully\n"));

		/* obtain pointer to the creation function */
		m_pfCreate = (DLL_WINCREATE)m_windowLib.GetSymbol("Construct");
		if (m_pfCreate == NULL)
		{
			VTRACE(_CL("Unable to locate constructor.\n"));
			return false;
		}

		/* obtain pointer to the deletion function */
		m_pfDestroy = (DLL_WINDESTROY)m_windowLib.GetSymbol("Destruct");
		if (m_pfDestroy == NULL)
		{
			VTRACE(_CL("Unable to locate cleanup function.\n"));
			return false;
		}

		/* try and create the WindowSystem */
		m_pfCreate(&m_pDevice);
		if (m_pDevice == NULL)
		{
			VTRACE(_CL("Unable to create window device.\n"));
			return false;
		}
	}
	else
	{
		VTRACE(_CL("Unknown window system requested\n"));
		return false;
	}

	return true;
}

/*------------------------------------------------------------------*
 *								Release()							*
 *------------------------------------------------------------------*/
/**	@brief		Calls the destructor for the current VWindowSystem.
 *	@author		Josh Williams
 *	@date		01-Sep-2004
 *
 *	@remarks	Does not unload the underlying dynamic library from
 *				memory.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VWindow::Release(void)
{
	VTRACE(_CL("Releasing device...\n"));
	m_pfDestroy(m_pDevice);
	m_pDevice = NULL;
}
/********************************************************************
 *                         C A L L B A C K S                        *
 ********************************************************************/

/********************************************************************
 *                         I N T E R N A L S                        *
 ********************************************************************/

} // End Namespace

