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
#if !defined(__VCAMERA_H_INCLUDED__)
#define __VCAMERA_H_INCLUDED__

/* System Headers */

/* Local Headers */
#include "VGlobals.h"
#include "VMovable.h"
#include "VMath.h"

namespace UDP
{

/**
 *	@class		VCamera
 *
 *	@brief		Represents the camera system used to view our scene.
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		03-Sep-2003
 *	@remarks	Encapsulates an OpenGL camera (viewport).
 */
class VCamera : public VMovable
{
public:
	/*==================================*
	 *	   CONSTRUCTION/DESTRUCTION		*
	 *==================================*/
	/**
	 *	@brief		Creates a camera at the origin looking down the neg z axis
	 *	@author		Josh Williams
	 *	@date		04-Sep-2003
	 */
	VCamera();
	/**
	 *	@brief		Creates a camera at the origin looking in the desired
	 *				direction.
	 *	@author		Josh Williams
	 *	@date		07-Sep-2003
	 *
	 *	@param		pLook	Direction the camera should be looking in
	 */
	VCamera(const VVector& pLook);
	/**
	 *	@brief		Create a camera at the specified position looking in
	 *				the direction specified.
	 *	@author		Josh Williams
	 *	@date		07-Sep-2003
	 *
	 *	@param		pPos		Location to place the camera
	 *	@param		pLook	Direction the camera should be looking in
	 */
	VCamera(const VVector& pPos, const VVector& pLook);
	virtual ~VCamera();

	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/
	/**
	 *	@brief		Returns the direction the camera is currently looking in.
	 *	@author		Josh Williams
	 *	@date		11-Sep-2003
	 *
	 *	@returns	(Vector) Current viewing direction.
	 */
	VVector			GetDirection();

	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	/**
	 *	@brief		Sets the field of view angle used for rendering.
	 *	@author		Josh Williams
	 *	@date		24-Sep-2003
	 *
	 *	@param		fov	Degrees to use as the field of view
	 *
	 *	@returns	void
	 */
	void			SetFOV(scalar_t pFov)
	{
		mFOV = pFov;
	}
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
	void			LookAt(VNode *pObject);
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
	void			MoveTo(VNode *pObject);
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
	void			UpdateView();
	/**
	 *	@brief		Updates the frustum coordinates for this camera.
	 *	@author		Josh Williams
	 *	@date		25-Jan-1981
	 *
	 *	@returns	void
	 */
	void			UpdateFrustum();
	/**
	 *	@brief		Overridden to pacify Renderable.
	 *	@author		Josh Williams
	 *	@date		09-Sep-2003
	 *
	 *	@returns	void
	 */
	void			Render();

protected:
	/*==================================*
	 *             CALLBACKS			*
	 *==================================*/
	/**
	 *	@brief		Fired when the engine requests a render operation on
	 *				this camera.
	 *	@author		Josh Williams
	 *	@date		13-Sep-2003
	 *
	 *	@returns	void
	 */
	void			OnRender();
	/**
	 *	@brief		Dumps the Camera's current axis/rotation/position
	 *	@author		Josh Williams
	 *	@date		03-Sep-2003
	 *
	 *	@param		o	stream to dump to
	 *	@param		q	reference to a Camera object
	 *
	 *	@returns	(ostream&) stream object.
	 */
	/*inline friend	std::ostream& operator<<(std::ostream& o, const Camera& c)
	{
		Vector pos = c.GetPosition();
		Vector axis;
		o << "Camera(pos: " << pos.x << ", " << pos.y << ", " << pos.z << ")";
		return o;
	}*/

private:
	/*==================================*
	 *             INTERNALS            *
	 *==================================*/

public:
	/*==================================*
	 *             VARIABLES            *
	 *==================================*/
	scalar_t	mMaxVelocity;
	scalar_t	mMaxHeadingRate;
	scalar_t	mFOV;
	scalar_t	mNear;
	scalar_t	mFar;
	scalar_t	mAspect;
	scalar_t	mFrustrumW;
	scalar_t	mFrustrumH;
	bool		mUpdateView;
	bool		mUpdateFrustum;
	VMatrix		mViewMatrix;
};

} // End Namespace

#endif // __VCAMERA_H_INCLUDED__
