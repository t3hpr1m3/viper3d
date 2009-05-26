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
#if !defined(__INPUT_H_INCLUDED__)
#define __INPUT_H_INCLUDED__

/* System Headers */
#include <viper3d/Viper3D.h>
#include <map>

/* Local Headers */

namespace UDP
{

class VWindow;

class VMouseState
{
public:
	long mXabs, mYabs;
	long mXrel, mYrel;
	long mXdelta, mYdelta;

	long mButtons;
	inline long IsButtonDown(unsigned char pButton) const
	{
		return mButtons & (1 << pButton);
	}
};

typedef std::map<VKeyCode, bool> VKeyStates;

/**
 *	@class		VInput
 *
 *	@brief		Helper class for loading the specific Input System
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		2004-Sep-01
 */
class VInput
{
public:
	/*==================================*
	 *	   CONSTRUCTION/DESTRUCTION		*
	 *==================================*/
	VInput(void);
	virtual ~VInput(void);

	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/
	virtual bool	IsKeyDown(VKeyCode pKc);
	virtual const VMouseState&	GetMouseState(void);

	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	virtual bool	StartCapture(VWindow *pWin) = 0;
	virtual bool	EndCapture(void) = 0;

	virtual bool	Update(void) = 0;

protected:
	/*==================================*
	 *             CALLBACKS			*
	 *==================================*/

private:
	/*==================================*
	 *             INTERNALS            *
	 *==================================*/


protected:
	/*==================================*
	 *             VARIABLES            *
	 *==================================*/
	VWindow			*mWin;			/**< Window handle */
	VKeyStates		mKeyStates;
	VMouseState		mMouseState;

};

inline
bool VInput::IsKeyDown(VKeyCode pKc)
{
	VKeyStates::iterator	vIt;
	if ((vIt = mKeyStates.find(pKc)) == mKeyStates.end())
		return false;
	else
		return vIt->second;
}

inline
const VMouseState& VInput::GetMouseState(void)
{
	return mMouseState;
}

} // End Namespace

#endif // __INPUT_H_INCLUDED__

