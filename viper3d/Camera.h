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
#if !defined(__CAMERA_H_INCLUDED__)
#define __CAMERA_H_INCLUDED__

/* System Headers */

/* Local Headers */
#include <viper3d/Globals.h>
#include <viper3d/Movable.h>
#include <viper3d/Math.h>

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
	bool		mUpdateFrustum;
	VMatrix		mViewMatrix;
};

} // End Namespace

#endif // __CAMERA_H_INCLUDED__
