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
#include "VMovable.h"

/* System Headers */

/* Local Headers */
#include "VCamera.h"

namespace UDP
{

/********************************************************************
 *          C O N S T R U C T I O N / D E S T R U C T I O N         *
 ********************************************************************/

/********************************************************************
 *                        A T T R I B U T E S                       *
 ********************************************************************/

/********************************************************************
 *                        O P E R A T I O N S                       *
 ********************************************************************/

/*------------------------------------------------------------------*
 *								Prepare()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *		Call OnPrepare() for this object							*
 *		If this object has children									*
 *			prepare them											*
 *		If this object has siblings									*
 *			prepare them as well									*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VMovable::Prepare()
{
	OnPrepare();

	if (HasChild())
		((VMovable*)GetChild())->Prepare();

	if (HasParent() && !IsLastChild())
		((VMovable*)GetNext())->Prepare();
}

/*------------------------------------------------------------------*
 *						   CheckCollisions()						*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *		If our bounding box intersects another						*
 *			sound collision											*
 *			If we have children										*
 *				check them for collisions with this object as well	*
 *			If we have siblings										*
 *				check them for collisions							*
 *		If the supplied object has children							*
 *			check for collisions with it's children					*
 *		If the supplied object has siblings							*
 *			check for collisions with it's siblings					*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VMovable::CheckCollisions(VMovable *pObj)
{
	/*
	 * If this object's bounding sphere collides with obj's sphere
	 * and the 2 objects aren't the same object
	 */
	if (((pObj->GetPosition() - GetPosition()).Length() <= (pObj->GetSize() + GetSize())) &&
		 (pObj != ((VMovable*)this)))
	{
		OnCollision(pObj);	// Sound collision.  This object should have
							// overridden OnCollision();

		// Test children now
		if (HasChild())
			((VMovable*)GetChild())->CheckCollisions(pObj);

		// Now, siblings
		if (HasParent() && !IsLastChild())
			((VMovable*)GetNext())->CheckCollisions(pObj);
	}

	/*
	 * We've performed all checks against this object.  Now, test against
	 * it's children and siblings
	 */
	if (pObj->HasChild())
		CheckCollisions((VMovable*)(pObj->GetChild()));
	
	if (pObj->HasParent() && !pObj->IsLastChild())
		CheckCollisions((VMovable*)(pObj->GetNext()));
}

/*------------------------------------------------------------------*
 *								Animate()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *		Perform animation calculations								*
 *		If we have children											*
 *			Animate them											*
 *		If we have siblings											*
 *			animate them as well									*
 *		If we have been flagged for deletion						*
 *			clean up												*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VMovable::Animate(scalar_t pDeltaTime)
{
	OnAnimate(pDeltaTime); // This object

	// Animate children, if any
	if (HasChild())
		((VMovable*)GetChild())->Animate(pDeltaTime);

	// Now do the siblings
	if (HasParent() && !IsLastChild())
		((VMovable*)GetNext())->Animate(pDeltaTime);

	if (mDelete) // Cleanup of this object needs to be performed
		delete this;		
}

/********************************************************************
 *                         C A L L B A C K S                        *
 ********************************************************************/

/*------------------------------------------------------------------*
 *							  OnPrepare()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VMovable::OnPrepare()
{
	CheckCollisions((VMovable*)FindRoot());
}

/*------------------------------------------------------------------*
 *							 OnAnimate()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VMovable::OnAnimate(scalar_t pDeltaTime)
{
	SetPosition(GetPosition() + GetVelocity() * pDeltaTime);
	SetVelocity(GetVelocity() + GetAcceleration() * pDeltaTime);
}

/********************************************************************
 *                         I N T E R N A L S                        *
 ********************************************************************/

} // End Namespace
