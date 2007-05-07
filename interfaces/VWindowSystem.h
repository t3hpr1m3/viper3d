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
#if !defined(__VWINDOWSYSTEM_H_INCLUDED__)
#define __VWINDOWSYSTEM_H_INCLUDED__

/* System Headers */
#include <queue>
#include <fstream>

/* Local Headers */
#include "VGlobals.h"
#include "VTypes.h"

namespace UDP
{

typedef std::queue<VKeyEvent*>	VKeyEvents;

class VFont
{
public:
	VFont() {};
	virtual ~VFont() {};

	uint mFontID;
};

/**
 *	@class		VWindowSystem
 *
 *	@brief		Interface for the platform specific Window Systems.
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		02-Sep-2004
 */
class VWindowSystem
{
public:
	/*==================================*
	 *	   CONSTRUCTION/DESTRUCTION		*
	 *==================================*/
	VWindowSystem() {};
	virtual ~VWindowSystem() {};

	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/

	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	/**
	 *	@brief		Initializes the window system.
	 *	@author		Josh Williams
	 *	@date		02-Sep-2004
	 *
	 *	@returns	Success/failure
	 */
	virtual bool	Initialize(void) = 0;
	/**
	 *	@brief		Creates the actual window (OS specific).
	 *	@author		Josh Williams
	 *	@date		22-Sep-2003
	 *
	 *	@param		nWidth
	 *	@param		nHeight		Dimensions for the window
	 *	@param		bFullScreen	Whether or not this should be a fullscreen
	 *				window.
	 *
	 *	@returns	(bool) Whether or not we could create the actual window.
	 */
	virtual bool	CreateWindow(const uint pWidth, const uint pHeight,
									bool pFullScreen = false) = 0;

	virtual void	DestroyWindow() = 0;

	virtual bool	Resize(const uint pWidth, const uint pHeight) = 0;

	virtual bool	FullScreen(bool pFullScreen) = 0;
	/**
	 *	@brief		Sets the caption for the window.
	 *	@author		Josh Williams
	 *	@date		22-Sep-2003
	 *
	 *	@param		pcCaption	Text string to be displayed for this window
	 *
	 *	@returns	void
	 */
	virtual void	SetCaption(const char *pCaption) const = 0;

	virtual void	SwapBuffers() const = 0;

	virtual bool	CaptureInput(ulong pFlags) const = 0;

	virtual void	Update() = 0;

	virtual VKeyEvent*	GetEvent() = 0;

protected:
	/*==================================*
	 *             CALLBACKS			*
	 *==================================*/

private:
	/*==================================*
	 *             INTERNALS            *
	 *==================================*/
protected:
	virtual void	WriteLog(const char *pText, ...) = 0;
	virtual void	LoadKeyMap() = 0;


private:
	/*==================================*
	 *             VARIABLES            *
	 *==================================*/
protected:
	uint			mWidth;
	uint			mHeight;
	bool			mDblBuffered;
	bool			mFullScreen;
	VKeyEvents		mKeyEvents;
	std::ofstream	mLog;
};

class DLL_WINCREATE
{
public:
	virtual ~DLL_WINCREATE() {}
	virtual void operator()(VWindowSystem **pWins) {}
};
class DLL_WINDESTROY
{
public:
	virtual ~DLL_WINDESTROY() {}
	virtual void operator()(VWindowSystem *pWins) {}
};

} // End Namespace

#endif // __VWINDOWSYSTEM_H_INCLUDED__
