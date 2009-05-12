/*============================================================================*
 *                                                                            *
 * 	This file is part of the Viper3D Game Engine.						  	  *
 *                                                                            *
 *	Copyright (C) 2004 UDP Games   All Rights Reserved.						  *
 *                                                                            *
 *============================================================================*/
#include "VXInputSystem.h"

/* System Headers */
#include <X11/Xlib.h>
#include <iostream>

/* Local Headers */
#include "VGlobals.h"

namespace UDP
{

/* creation functions */
class DLL_INPCREATE_IMPL : public DLL_INPCREATE
{
public:
	void operator()(VInputSystem **pInput)
	{
		*pInput = (VInputSystem*)new VXInputSystem();
	}
};
class DLL_INPDESTROY_IMPL : public DLL_INPDESTROY
{
public:
	void operator()(VInputSystem *pInput)
	{
		delete (VXInputSystem*)pInput;
	}
};

extern "C" {
_ViperExport
DLL_INPCREATE_IMPL Construct;
_ViperExport
DLL_INPDESTROY_IMPL Destruct;

/*
_ViperExport void Construct(VInputSystem **pInput)
{
	*pInput = (VInputSystem*)new VXInputSystem();
}
_ViperExport void Destruct(VInputSystem *pInput)
{
	delete (VXInputSystem*)pInput;
}
*/

} // extern "C"

/********************************************************************
 *          C O N S T R U C T I O N / D E S T R U C T I O N         *
 ********************************************************************/
VXInputSystem::VXInputSystem()
{
    std::cout << "VXInputSystem constructor" << std::endl;
}

VXInputSystem::~VXInputSystem()
{
	//XAutoRepeatOn(m_Display);
}

/********************************************************************
 *                        A T T R I B U T E S                       *
 ********************************************************************/

/*------------------------------------------------------------------*
 *							  IsKeyDown()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Returns whether or not the specified key is currently
 *				being pressed.
 *	@author		Josh Williams
 *	@date		24-Sep-2003
 *
 *	@param		pKc		KeyCode to check for press.
 *
 *	@returns	True/false
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
bool VXInputSystem::IsKeyDown(VKeyCode pKc)
{
	if (mKeyStates.find(pKc) == mKeyStates.end())
		return false; // Key hasn't been pressed yet
	else
		return mKeyStates[pKc];
}

/********************************************************************
 *                        O P E R A T I O N S                       *
 ********************************************************************/

/*------------------------------------------------------------------*
 *							Initialize()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Initializes the input system with the underlying
 *				OS window.
 *	@author		Josh Williams
 *	@date		24-Sep-2003
 *
 *	@param		pWins	Handle/pointer to the OS window for processing events
 *
 *	@returns	bool
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
bool VXInputSystem::Initialize(VWindowSystem *pWins)
{
	VULONG vFlags = ButtonPressMask | KeyPressMask | KeyReleaseMask |
					EnterWindowMask | LeaveWindowMask;
	mWins = pWins;
	mWins->CaptureInput(vFlags);
	//XAutoRepeatOff(m_Display);
	return true;
}

/*------------------------------------------------------------------*
 *								Update()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Causes a check of the keyboard/mouse state
 *	@author		Josh Williams
 *	@date		20-Sep-2003
 *
 *	@returns	void
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VXInputSystem::Update()
{
	VKeyEvent	*vEvent;
	bool		vKs;

	while ((vEvent = mWins->GetEvent()) != NULL)
	{
		vKs = (vEvent->mAction == KEY_PRESS ? true : false);
		mKeyStates[vEvent->mCode] = vKs;
		delete vEvent;
	}
}
		
/********************************************************************
 *                         C A L L B A C K S                        *
 ********************************************************************/

/********************************************************************
 *                         I N T E R N A L S                        *
 ********************************************************************/

} // End Namespace

