/*============================================================================*
 *                                                                            *
 *  This file is part of the UDP Game Engine.                                 *
 *                                                                            *
 *  Copyright (C) 2003 UDP Games   All Rights Reserved.                       *
 *                                                                            *
 *============================================================================*
 *                                  CHANGELOG                                 *
 *    Date      Description                                     Author        *
 * -----------  ----------------------------------------------  ------------- *
 *																			  *
 *============================================================================*/
#if !defined(__VMOVABLE_H_INCLUDED__)
#define __VMOVABLE_H_INCLUDED__

#include "VGlobals.h"
#include "VMath.h"
#include "VNode.h"

namespace UDP
{
/**
 *	@class		VMovable
 *	@brief		Any object within our world that can go in motion.
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		09-Sep-2003
 *	@remarks	Motion can be either rotation, directional, or an increase
 *				in size.
 */
class VMovable : public VNode
{
public:
	/*==================================*
	 *	   CONSTRUCTION/DESTRUCTION		*
	 *==================================*/
protected:
	VMovable() {}
public:
	virtual ~VMovable() {};
	
	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/
	/**
	 *	@brief		Returns the velocity of this object.
	 *	@author		Josh Williams
	 *	@date		07-Sep-2003
	 *
	 *	@returns	(VVector) Current velocity of this object.
	 */
	VVector			GetVelocity() { return mVelocity; }
	/**
	 *	@brief		Returns the acceleration of this object.
	 *	@author		Josh Williams
	 *	@date		07-Sep-2003
	 *
	 *	@returns	(VVector) Current acceleration of this object.
	 */
	VVector			GetAcceleration() { return mAcceleration; }

	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	/**
	 *	@brief		Processes any preparation needed for this object.
	 *	@author		Josh Williams
	 *	@date		12-Sep-2003
	 *
	 *	@remarks	Default implementation is to call collision detection
	 *				routine for this object and all of it's children/siblings.
	 *
	 *	@returns	void
	 */
	void			Prepare();
	/**
	 *	@brief		Checks for contact between this object and any others.
	 *	@author		Josh Williams
	 *	@date		04-Sep-2003
	 *
	 *	@remarks	Default implementation checks the bounding spheres of the
	 *				two objects.  If they intersect, a collision is signaled.
	 *
	 *	@param		pObj		Object ot be checked for collisions with.
	 *
	 *	@returns	void
	 */
	void			CheckCollisions(VMovable *pObj);		/**
	 *	@brief		Initiates animation calculations for this object.
	 *	@author		Josh Williams
	 *	@date		04-Sep-2003
	 *
	 *	@remarks	Really just a wrapper around the callback OnAnimate().
	 *
	 *	@param		deltaTime	Amount of time that has elapsed since the last
	 *							frame of animation was drawn
	 *
	 *	@returns	void
	 */
	void			Animate(scalar_t pDeltaTime);
	/**
	 *	@brief		Updates the velocity for this object.
	 *	@author		Josh Williams
	 *	@date		09-Sep-2003
	 *
	 *	@param		pNewVelocity	Updated velocity in vector form
	 *
	 *	@returns	(VVector) The original velocity.
	 */
	VVector			SetVelocity(VVector pNewVelocity)
	{
		VVector vOld = mVelocity;
		mVelocity = pNewVelocity;
		return vOld;
	}
	/**
	 *	@brief		Updates the acceleration for this object.
	 *	@author		Josh Williams
	 *	@date		09-Sep-2003
	 *
	 *	@param		pNewAccel	New value for acceleration
	 *
	 *	@returns	(VVector) The original acceleration value.
	 */
	VVector			SetAcceleration(VVector pNewAccel)
	{
		VVector vOld = mAcceleration;
		mAcceleration = pNewAccel;
		return vOld;
	}

protected:
	/*==================================*
	 *             CALLBACKS			*
	 *==================================*/
	/**
	 *	@brief		Called when this object is asked to prepare for
	 *				animation/rendering.
	 *	@author		Josh Williams
	 *	@date		12-Sep-2003
	 *
	 *	@remarks	Default implementation simply calls the collision
	 *				dection routine.
	 *
	 *	@returns	void
	 */
	virtual void	OnPrepare();
	/**
	 *	@brief		Handles processing collisions for this object with other
	 *				objects in the world.
	 *	@author		Josh Williams
	 *	@date		04-Sep-2003
	 *
	 *	@remarks	Must be overridden.  Instructions on how to handle collisions
	 *				should be added to the derived object's OnCollision().
	 *
	 *	@param		collisionObject	Object in the world we collided with
	 *
	 *	@returns	void
	 */
	virtual void	OnCollision(VMovable *pCollisionObject) {}
	/**
	 *	@brief		Performs actual animation on the object.
	 *	@author		Josh Williams
	 *	@date		04-Sep-2003
	 *
	 *	@remarks	Should be overridden to provide object specific animation
	 *				instructions.  Called by the engine every frame to handle
	 *				object manipulation.
	 *
	 *	@param		pDeltaTime	Amount of time that has elapsed since the last
	 *							frame of animation was drawn.
	 *
	 *	@returns	void
	 */
	virtual void	OnAnimate(scalar_t pDeltaTime);

private:
	/*==================================*
	 *             INTERNALS            *
	 *==================================*/

private:
	/*==================================*
	 *             VARIABLES            *
	 *==================================*/
public:
	scalar_t		mSpeed;		/**< Object's current speed. */
	VVector			mVelocity;		/**< Object's speed + direction vector. */
	VVector			mAcceleration;	/**< Rate of acceleration for this object, if applicable. */
	VQuaternion		mOrientation;	/**< Rotation of this object relative to it's parent. */
};

} // End Namespace

#endif // __VMOVABLE_H_INCLUDED__
