/**
 *	@class		UDP::VInputSystem
 *
 *	@brief		Defines the interface for our input handling class.
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		20-Sep-2003
 *	@remarks	This class will be overridden by platform dependent
 *				implementations, such as X or DirectInput.
 */
/*============================================================================*
 *                                                                            *
 * 	This file is part of the Viper3D Game Engine.                             *
 *                                                                            *
 *	Copyright (C) 2004 UDP Games   All Rights Reserved.						  *
 *                                                                            *
 *============================================================================*
 *                                  CHANGELOG                                 *
 *    Date      Description                                     Author        *
 * -----------  ----------------------------------------------	------------- *
 *                                                                            *
 *============================================================================*/
#if !defined(__VINPUTSYSTEM_H_INCLUDED__)
#define __VINPUTSYSTEM_H_INCLUDED__

/* System Headers */
#include <map>

/* Local Headers */
#include "VGlobals.h"
#include "VWindowSystem.h"
#include "VTypes.h"

namespace UDP
{

typedef std::map<VKeyCode, bool> _KeyStates;

class VMouseState
{
public:
	long mXabs, mYabs, mZabs;
	long mXrel, mYrel, mZrel;

	long mButtons;
	inline long IsButtonDown(unsigned char pButton) const
	{
		return mButtons & (1 << pButton);
	}
};

class VInputSystem
{
public:
	/*==================================*
	 *	   CONSTRUCTION/DESTRUCTION		*
	 *==================================*/
	VInputSystem() {};
	virtual ~VInputSystem() {};

	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/
	virtual bool	IsKeyDown(VKeyCode pKc) = 0;

	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	/**
	 *	@brief		Initializes the input system with the underlying
	 *				OS window.
	 *	@author		Josh Williams
	 *	@date		24-Sep-2003
	 *
	 *	@param		pWins	Handle/pointer to the OS window for
	 *						processing events
	 *
	 *	@returns	bool
	 */
	virtual bool	Initialize(VWindowSystem *pWins) = 0;
	/**
	 *	@brief		Causes a check of the keyboard/mouse state
	 *	@author		Josh Williams
	 *	@date		20-Sep-2003
	 *
	 *	@returns	void
	 */
	virtual void 	Update() = 0;

protected:
	/*==================================*
	 *             CALLBACKS			*
	 *==================================*/

private:
	/*==================================*
	 *             INTERNALS            *
	 *==================================*/
protected:

private:
	/*==================================*
	 *             VARIABLES            *
	 *==================================*/
protected:
	VMouseState		mMouseState;
	_KeyStates		mKeyStates;
	static bool		mKeysInitialized;
	int				mMouseCenterX;
	int				mMouseCenterY;
};

} // End Namespace

#endif // __VINPUTSYSTEM_H_INCLUDED__
