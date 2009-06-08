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
#if !defined(__MOVABLE_H_INCLUDED__)
#define __MOVABLE_H_INCLUDED__

#include <viper3d/Globals.h>
#include <viper3d/Math.h>
#include <viper3d/Node.h>

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
	VMovable();
public:
	virtual ~VMovable() {};
	/**
	 *	@brief		Returns the direction the camera is currently looking in.
	 *	@author		Josh Williams
	 *	@date		11-Sep-2003
	 *
	 *	@returns	(Vector) Current viewing direction.
	 */
	const VVector&	GetPosition() const;
	VVector			GetDirection() const;
	const VQuaternion&	GetOrientation() const { return mOrientation; }

	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	VVector			SetPosition(const VVector& pNewPosition);
	/**
	 *	@brief		Directs the camera's point of focus to an object.
	 *	@author		Josh Williams
	 *	@date		07-Sep-2003
	 *
	 *	@remarks	Directs the camera at the supplied object.
	 *
	 *	@param		object	Object to be focused on
	 *
	 *	@returns	void
	 */
	void			LookAt(VMovable *pObject);
	/**
	 *	@brief		Directs the camera's point of focus by vector.
	 *	@author		Josh Williams
	 *	@date		07-Sep-2003
	 *
	 *	@param		pVector	Point the camera should focus on.
	 *
	 *	@returns	void
	 */
	void			LookAt(const VVector& pVector);
	/**
	 *	@brief		Directs the camera at the point specified.
	 *	@author		Josh Williams
	 *	@date		10-Sep-2003
	 *
	 *	@param		pX
	 *	@param		pY
	 *	@param		pZ	Coordinates to focus on
	 *
	 *	@returns	void
	 */
	void			LookAt(scalar_t pX, scalar_t pY, scalar_t pZ);
	/**
	 *	@brief		Updates the direction this camera is looking in.
	 *	@author		Josh Williams
	 *	@date		10-Sep-2003
	 *
	 *	@param		pVector	New direction for this vector to view.
	 *
	 *	@returns	void
	 */
	void			SetDirection(const VVector& pVector);
	/**
	 *	@brief		Moves the camera by the specified vector in world
	 *				coordinates.
	 *	@author		Josh Williams
	 *	@date		07-Sep-2003
	 *
	 *	@remarks	Movement is made globally, relative to the origin.
	 *				Current	rotation, orientation is not taken into account.
	 *
	 *	@param		pVector	Direction/magnitude to move
	 *
	 *	@returns	void
	 */
	void			Move(const VVector& pVector);
	/**
	 *	@brief		Moves the object relative to it's curent position/orientation.
	 *	@author		Josh Williams
	 *	@date		07-Sep-2003
	 *
	 *	@remarks	Uses the current orientation to determine the exact movement
	 *				vector in world coordinates.
	 *
	 *	@param		pVector	Direction/magnitude to move in local coordinates
	 *
	 *	@returns	void
	 */
	void			MoveRelative(const VVector& pVector);
	/**
	 *	@brief		Moves the camera to the location of object specified.
	 *	@author		Josh Williams
	 *	@date		10-Sep-2003
	 *
	 *	@param		pObject	Object whose position we should move to
	 *
	 *	@returns	void
	 */
	void			MoveTo(VMovable *pObject);
	/**
	 *	@brief		Moves the camera to the location specified by vector.
	 *	@author		Josh Williams
	 *	@date		07-Sep-2003
	 *
	 *	@param		pVector	Position in space camera should occupy
	 *
	 *	@returns	void
	 */
	void			MoveTo(const VVector& pVector);
	/**
	 *	@brief		Moves the camera to the coordinates specified.
	 *	@author		Josh Williams
	 *	@date		10-Sep-2003
	 *
	 *	@param		pX
	 *	@param		pY
	 *	@param		pZ	Coordinates to move to
	 *
	 *	@returns	void
	 */
	void			MoveTo(scalar_t pX, scalar_t pY, scalar_t pZ);
	/**
	 *	@brief		Rotates the camera about the y axis.
	 *	@author		Josh Williams
	 *	@date		07-Sep-2003
	 *
	 *	@param		pDegrees	Amount of yaw to perform
	 *
	 *	@returns	void
	 */
	void			RotateYaw(scalar_t pDegrees);
	/**
	 *	@brief		Rotates the camera about the x axis.
	 *	@author		Josh Williams
	 *	@date		07-Sep-2003
	 *
	 *	@param		pDegrees	Amount of pitch to perform.
	 *
	 *	@returns	void
	 */
	void			RotatePitch(scalar_t pDegrees);
	/**
	 *	@brief		Rotates the camera about the z axis.
	 *	@author		Josh Williams
	 *	@date		07-Sep-2003
	 *
	 *	@param		pDegrees	Amount of roll to perform.
	 *
	 *	@returns	void
	 */
	void			RotateRoll(scalar_t pDegrees);
	/**
	 *	@brief		Rotate the camera about a given axis.
	 *	@author		Josh Williams
	 *	@date		11-Sep-2003
	 *
	 *	@param		pAxis		Axis to rotate around
	 *	@param		pDegrees	Amount of rotation to perform
	 *
	 *	@returns	void
	 */
	void			Rotate(const VVector& pAxis, scalar_t pDegrees);
	/**
	 *	@brief		Rotate the camera based on a given quaternion.
	 *	@author		Josh Williams
	 *	@date		11-Sep-2003
	 *
	 *	@param		pQ	Quaternion to base rotation on
	 *
	 *	@returns	void
	 */
	void			Rotate(const VQuaternion& pQ);
	/**
	 *	@brief		Increases/decreases the speed of the camera.
	 *	@author		Josh Williams
	 *	@date		11-Sep-2003
	 *
	 *	@param		pDelta	Amount to increase/decrease velocity
	 *
	 *	@returns	void
	 */
	void			UpdateSpeed(scalar_t pDelta);
	/**
	 *	@brief		Updates the view matrix/position, if necessary.
	 *	@author		Josh Williams
	 *	@date		11-Sep-2003
	 *
	 *	@returns	void
	 */

protected:
	/*==================================*
	 *             CALLBACKS			*
	 *==================================*/
	virtual void	OnMove(){};
	virtual void	OnRotate(){};
	virtual void	OnRender(){};

private:
	/*==================================*
	 *             INTERNALS            *
	 *==================================*/

private:
	/*==================================*
	 *             VARIABLES            *
	 *==================================*/
public:
	VQuaternion		mOrientation;	/**< Rotation of this object relative to it's parent. */
	VVector			mPosition;		/**< This object's position within the world */
};

} // End Namespace

#endif // __MOVABLE_H_INCLUDED__
