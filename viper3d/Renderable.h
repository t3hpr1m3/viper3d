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
#if !defined(__VRENDERABLE_H_INCLUDED__)
#define __VRENDERABLE_H_INCLUDED__

#include "VGlobals.h"
#include "VTypes.h"
#include "VMath.h"

namespace UDP
{

enum VRenderMethod {
	RENDER_POINTS,
	RENDER_WIREFRAME,
	RENDER_SOLID
};

/**
 *	@class		VRenderable
 *
 *	@brief		Represents a renderable object in the game world.
 *	@author		Josh Williams <volzman19@yahoo.com>
 *	@version	0.1.1
 *	@date		09-Sep-2003
 */
class VRenderable
{
public:
	/*==================================*
	 *	   CONSTRUCTION/DESTRUCTION		*
	 *==================================*/
protected:
	/**
	 *	@brief		Default constructor
	 *	@author		Josh Williams
	 *	@date		09-Sep-2003
	 *
	 *	@remarks	Constructor is protected to prevent instances of this class
	 *				from being created directly.  Derived classes should be used.
	 */
	VRenderable() { }
	virtual ~VRenderable() {};		

public:
	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/
	/**
	 *	@brief		Returns the method used to render this object.
	 *	@author		Josh Williams
	 *	@date		09-Sep-2003
	 *
	 *	@returns	(VRendorMethod) Type of rendering to be performed.
	 */
	VRenderMethod	GetRenderMethod() { return mRenderMethod; }
	/**
	 *	@brief		Returns the local coordinate position of this object.
	 *	@author		Josh Williams
	 *	@date		09-Sep-2003
	 *
	 *	@returns	(VVector) Position of this object relative to its
	 *				parent.
	 */
	VVector			GetPosition() { return mPosition; }
	/**
	 *	@brief		Returns the size specified for this object (bounding box)
	 *	@author		Josh Williams
	 *	@date		09-Sep-2003
	 *
	 *	@returns	(scalar_t) Size assigned to this object.
	 */
	scalar_t		GetSize() { return mSize; }

public:
	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	/**
	 *	@brief		Wrapper around the OnRender() function.
	 *	@author		Josh Williams
	 *	@date		09-Sep-2003
	 *
	 *	@remarks	Each time Render is called, the callback OnRender() is fired.  Any object
	 *				deriving from Renderable must implement this function.  Render will be
	 *				overridden in class Node, allowing an object and all of it's children
	 *				to be rendered.
	 *
	 *	@returns	void
	 */
	virtual void	Render()
	{
		OnRender();
	}
	/**
	 *	@brief		Sets this object's position relative to it's parent.
	 *	@author		Josh Williams
	 *	@date		09-Sep-2003
	 *
	 *	@param		pNewPosition	Vectory specifying this object's position in space.
	 *
	 *	@returns	(VVector) The object's original position.
	 */
	VVector			SetPosition(VVector pNewPosition)
	{
		VVector vOld = mPosition;
		mPosition = pNewPosition;
		return vOld;
	}
	/**
	 *	@brief		Sets the size for this object (bounding box)
	 *	@author		Josh Williams
	 *	@date		09-Sep-2003
	 *
	 *	@param		pNewSize	New size for this object.
	 *
	 *	@returns	(scalar_t) Original size for this object.
	 */
	scalar_t		SetSize(scalar_t pNewSize)
	{
		scalar_t vOld = mSize;
		mSize = pNewSize;
		return vOld;
	}
	/**
	 *	@brief		Updates the method used to render this object.
	 *	@author		Josh Williams
	 *	@date		09-Sep-2003
	 *
	 *	@param		pMethod	Render method to be used
	 *
	 *	@returns	(VRenderMethod) The original render method.
	 */
	VRenderMethod	SetRenderMethod(VRenderMethod pMethod)
	{
		VRenderMethod vTemp = mRenderMethod;
		mRenderMethod = pMethod;
		return vTemp;
	}

protected:
	/*==================================*
	 *             CALLBACKS			*
	 *==================================*/
	/**
	 *	@brief		Performs actual object rendering on the screen/buffer.
	 *	@author		Josh Williams
	 *	@date		12-Sep-2003
	 *
	 *	@remarks	Must be implemented in any class deriving from Renderable.
	 *
	 *	@returns	void
	 */
	virtual void	OnRender() = 0;

private:
	/*==================================*
	 *			   INTERNALS			*
	 *==================================*/

private:
	/*==================================*
	 *			   VARIABLES			*
	 *==================================*/
protected:
	VVector			mPosition;		/**< This object's position within the world. */
	scalar_t		mSize;			/**< Size of this object relative to the world. */
	VRenderMethod	mRenderMethod;	/**< Method to use when rendering this object. */

	bool			mDelete;		/**< Flag indicating this object should be deleted *
										 next frame.
									*/
};

} // End Namespace

#endif // __VRENDERABLE_H_INCLUDED__
