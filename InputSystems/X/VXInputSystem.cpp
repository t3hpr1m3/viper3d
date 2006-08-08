/*============================================================================*
 *                                                                            *
 * 	This file is part of the Viper3D Game Engine.						  	  *
 *                                                                            *
 *	Copyright (C) 2004 UDP Games   All Rights Reserved.						  *
 *                                                                            *
 *============================================================================*/

/* System Headers */
#include <X11/Xlib.h>
#include <iostream>

/* Local Headers */
#include "VGlobals.h"
#include "VXInputSystem.h"

namespace UDP
{

/* creation functions */
extern "C" {

_ViperExport void Construct(VInputSystem **pInput)
{
	*pInput = (VInputSystem*)new VXInputSystem();
}
_ViperExport void Destruct(VInputSystem *pInput)
{
	delete (VXInputSystem*)pInput;
}

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
 *	@param		kc	KeyCode to check for press.
 *
 *	@returns	True/false
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
bool VXInputSystem::IsKeyDown(VKeyCode kc)
{
	if (m_KeyStates.find(kc) == m_KeyStates.end())
		return false; // Key hasn't been pressed yet
	else
		return m_KeyStates[kc];
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
	ulong ulFlags = ButtonPressMask | KeyPressMask | KeyReleaseMask |
					EnterWindowMask | LeaveWindowMask;
	m_pWins = pWins;
	m_pWins->CaptureInput(ulFlags);
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
	VKeyEvent	*event;
	bool		ks;

	while ((event = m_pWins->GetEvent()) != NULL)
	{
		ks = (event->action == KEY_PRESS ? true : false);
		m_KeyStates[event->code] = ks;
		delete event;
	}
}
		
/********************************************************************
 *                         C A L L B A C K S                        *
 ********************************************************************/

/********************************************************************
 *                         I N T E R N A L S                        *
 ********************************************************************/

} // End Namespace

