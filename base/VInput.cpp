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
#include "VInput.h"

/* System Headers */

/* Local Headers */
#include "VLog.h"

namespace UDP
{

static char __CLASS__[] = "[    VInput    ]";

/********************************************************************
 *          C O N S T R U C T I O N / D E S T R U C T I O N         *
 ********************************************************************/
VInput::VInput(void)
{
	mDevice = NULL;
}

VInput::~VInput(void)
{
	if (mDevice != NULL)
		Release();
}

/********************************************************************
 *                        A T T R I B U T E S                       *
 ********************************************************************/

/*------------------------------------------------------------------*
 *							  GetDevice()							*
 *------------------------------------------------------------------*/
/**	@brief		Returns a handle to the underlying VInputSystem.
 *	@author		Josh Williams
 *	@date		01-Sep-2004
 *
 *	@remarks	Pointer returned can be used to perform input
 *				checking.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VInputSystem* VInput::GetDevice(void)
{
	return mDevice;
}
/********************************************************************
 *                        O P E R A T I O N S                       *
 ********************************************************************/

/*------------------------------------------------------------------*
 *							CreateDevice()							*
 *------------------------------------------------------------------*/
/**	@brief		Creates the specified VInputSystem.
 *	@author		Josh Williams
 *	@date		01-Sep-2004
 *
 *	@param		pAPI	Desired input system (X, DirectInput, etc)
 *
 *	@returns	Success/failure
 *
 *	@remarks	Loads the necessary library into memory and obtains
 *				pointers to the creation and deletion functions.
 *				If successful, function tries to create the specific
 *				VInputSystem object.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
bool VInput::CreateDevice(char *pAPI)
{
	if (strcmp(pAPI, "X") == 0)
	{
		/* try to load the X input library */
		VTRACE(_CL("Loading X input system\n"));
		if (!mInputLib.Load("./libs", "VXInput"))
		{
			VTRACE(_CL("Unable to load input library\n"));
			return false;
		}
		VTRACE(_CL("Library loaded successfully\n"));

		/* obtain pointer to the creation function */
		mCreate = static_cast<DLL_INPCREATE*>(mInputLib.GetSymbol("Construct"));
		if (mCreate == NULL)
		{
			VTRACE(_CL("Unable to locate constructor.\n"));
			return false;
		}

		/* obtain pointer to the deletion function */
		mDestroy = static_cast<DLL_INPDESTROY*>(mInputLib.GetSymbol("Destruct"));
		if (mDestroy == NULL)
		{
			VTRACE(_CL("Unable to locate destructor.\n"));
			return false;
		}

		/* try to create the actual input device */
		(*mCreate)(&mDevice);
		if (mDevice == NULL)
		{
			VTRACE(_CL("Unable to create input device.\n"));
			return false;
		}
	}
	else
	{
		VTRACE(_CL("Unknown input system requested\n"));
		return false;
	}

	return true;
}

/*------------------------------------------------------------------*
 *								Release()							*
 *------------------------------------------------------------------*/
/**	@brief		Calls the destructor for the current VInputSystem.
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
void VInput::Release(void)
{
	VTRACE(_CL("Releasing device...\n"));
	(*mDestroy)(mDevice);
	mDevice = NULL;
}
/********************************************************************
 *                         C A L L B A C K S                        *
 ********************************************************************/

/********************************************************************
 *                         I N T E R N A L S                        *
 ********************************************************************/

} // End Namespace

