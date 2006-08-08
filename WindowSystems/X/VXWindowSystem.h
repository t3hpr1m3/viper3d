/**
 *	@class		UDP::VXWindowSystem
 *
 *	@brief		Linux specific window handling routines.
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		26-Sep-2003
 */
/*============================================================================*
 *																			  *
 * 	This file is part of the Viper3D Game Engine.							  *
 *																			  *
 *	Copyright (C) 2004 UDP Games   All Rights Reserved.						  *
 *																			  *
 *============================================================================*
 *                                  CHANGELOG                                 *
 *    Date      Description                                    Author         *
 * -----------  ---------------------------------------------  -------------- *
 *																			  *
 *============================================================================*/
#if !defined(__VXWINDOWSYSTEM_H_INCLUDED__)
#define __VXWINDOWSYSTEM_H_INCLUDED__

#include <GL/gl.h>
#include <GL/glx.h>
#include <X11/extensions/xf86vmode.h>
#include <X11/keysym.h>
#include "VWindowSystem.h"
#include <map>
#include <fstream>
#include "VString.h"

using std::map;

namespace UDP
{
	class VXFont : public VFont
	{
	public:
		VXFont() {};
		virtual ~VXFont() {};

		VString	m_strFont;
		uint	m_pitch;

		GLuint	m_base;
		GLuint	m_first;
		GLuint	m_count;
	};

	typedef struct
	{
		Display					*dpy;
		int						screen;
		Window					win;
		GLXContext				ctx;
		XSetWindowAttributes	attr;
		XF86VidModeModeInfo		deskMode;
		int						x;
		int						y;
		uint					depth;
	} GLWindow;

	typedef map<KeySym, VKeyCode> _KeyMap;	

	class VXWindowSystem : public VWindowSystem
	{
	public:
		/*==================================*
		 *	   CONSTRUCTION/DESTRUCTION		*
		 *==================================*/
		VXWindowSystem(void);
		virtual ~VXWindowSystem(void);

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
		bool			Initialize(void);
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
		bool			CreateWindow(const uint nWidth, const uint nHeight,
										bool bFullScreen = false);
		/**
		 *	@brief		Closes the currently active window.
		 *	@author		Josh Williams
		 *	@date		02-Sep-2004
		 *
		 *	@returns	void
		 */
		void			DestroyWindow(void);
		/**
		 *	@brief		Adjusts the size (resolution) of the active window.
		 *	@author		Josh Williams
		 *	@date		02-Sep-2004
		 *
		 *	@param		nWidth
		 *	@param		nHeight		Dimensions for the window
		 *
		 *	@returns	(bool) Whether or not we could create the new window.
		 */
		bool			Resize(const uint nWidth, const uint nHeight);
		/**
		 *	@brief		Switches between windowed and fullscreen mode.
		 *	@author		Josh Williams
		 *	@date		02-Sep-2004
		 *
		 *	@param		bFullScreen	Screen mode desired.
		 *
		 *	@returns	(bool) Whether or not we could create the new window.
		 */
		bool			FullScreen(bool bFullScreen);
		/**
		 *	@brief		Sets the caption for the window.
		 *	@author		Josh Williams
		 *	@date		22-Sep-2003
		 *
		 *	@param		pcCaption	Text string to be displayed for this window
		 *
		 *	@returns	void
		 */
		void			SetCaption(const char *pcCaption) const;
		void			SwapBuffers(void) const;
		bool			CaptureInput(ulong ulFlags) const;
		void			Update(void);
		VKeyEvent*		GetEvent(void);

	protected:
		/*==================================*
		 *             CALLBACKS			*
		 *==================================*/

	private:
		/*==================================*
		 *             INTERNALS            *
		 *==================================*/
	protected:
		void			WriteLog(const char *pcText, ...);
		void			LoadKeyMap(void);


	private:
		/*==================================*
		 *             VARIABLES            *
		 *==================================*/
		_KeyMap				m_KeyMap;
		bool				m_bWinCreated;
		bool				m_bInitialized;
		GLWindow			m_Win;
		std::ofstream		m_LogFile;
		XF86VidModeModeInfo	**m_Modes;
		int					m_nNumModes;
		XVisualInfo 		*m_vInfo;
	};

}

#endif // __VXWINDOWSYSTEM_H_INCLUDED__

