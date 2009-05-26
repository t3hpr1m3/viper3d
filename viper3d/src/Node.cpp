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
#include <viper3d/Node.h>

/* System Headers */
#include <stdlib.h>
#include <GL/gl.h>

/* Local Headers */

namespace UDP
{

/********************************************************************
 *          C O N S T R U C T I O N / D E S T R U C T I O N         *
 ********************************************************************/
VNode::VNode()
{
	mParentNode = mChildNode = NULL;

	mPrevNode = mNextNode = NULL;
}

VNode::VNode(VNode *pNode)
{
	mParentNode = mChildNode = NULL;
	mPrevNode = mNextNode = this;
	AttachTo(pNode);
}

VNode::~VNode()
{
	/*
	 * Take us out of our parent's linked list.
	 */
	Detach();

	/*
	 * Now, clean up all of our children.
	 */
	while(mChildNode)
	{
		delete mChildNode;
	}
}

/********************************************************************
 *                        A T T R I B U T E S                       *
 ********************************************************************/

/*------------------------------------------------------------------*
 *							  FindRoot()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VNode *VNode::FindRoot()
{
	if (GetParent())
		return (GetParent()->FindRoot());
	else
		return this;
}

/*------------------------------------------------------------------*
 *							IsFirstChild()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
bool VNode::IsFirstChild()
{
	if (mParentNode)
		return (mParentNode->GetChild() == this);
	else
		return false;
}

/*------------------------------------------------------------------*
 *							IsLastChild()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
bool VNode::IsLastChild()
{
	if (mParentNode)
		return (mParentNode->GetChild()->GetPrev() == this);
	else
		return false;
}


/********************************************************************
 *                        O P E R A T I O N S                       *
 ********************************************************************/

/*------------------------------------------------------------------*
 *								Render()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *		Render this object											*
 *		If this object has children									*
 *			render them												*
 *		If this object has siblings									*
 *			render them												*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VNode::Render()
{
	glPushMatrix();
		OnRender();
		if (HasChild())
			((VNode*)mChildNode)->Render();
	glPopMatrix();

	/*
	 * Draw siblings
	 */
	if (HasParent() && !IsLastChild())
		((VNode*)mNextNode)->Render();
}

/*------------------------------------------------------------------*
 *								AttachTo()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *		If we're currently attached somewhere						*
 *			detach us												*
 *		Set our parent to the new parent node						*
 *		If our new parent has children								*
 *			set our prev/next nodes to the last/first nodes in list	*
 *		Else														*
 *			we are an only child.  prev/next nodes need to be us	*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VNode::AttachTo(VNode *pNewParent)
{
	/*
	 * If we're currently attached somewhere, break off.
	 */
	if (mParentNode)
		Detach();

	mParentNode = pNewParent;

	/*
	 * Now, insert us at the end of the line.
	 */
	if (mParentNode->HasChild())
	{
		mPrevNode = mParentNode->GetChild()->GetPrev();
		mNextNode = mParentNode->GetChild();
		mParentNode->GetChild()->GetPrev()->SetNext(this);
		mParentNode->GetChild()->SetPrev(this);
	}
	else
	{
		mParentNode->SetChild(this);
		mPrevNode = NULL;
		mNextNode = NULL;
	}
}

/*------------------------------------------------------------------*
 *								Attach()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *		Make sure the node isn't already attached somewhere			*
 *		If we already have children									*
 *			Stick this node at the end of our list					*
 *		Else														*
 *			Make this node our first child.							*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VNode::Attach(VNode *pNewChild)
{
	/*
	 * If the node is already attached somewhere, yank it out.
	 */
	if (pNewChild->HasParent())
		pNewChild->Detach();

	pNewChild->SetParent(this);

	/*
	 * Now, stick the new node at the end of the list.
	 */
	if (mChildNode)
	{
		pNewChild->SetPrev(mChildNode->GetPrev());
		pNewChild->SetNext(mChildNode);
		mChildNode->GetPrev()->SetNext(pNewChild);
		mChildNode->SetPrev(pNewChild);
	}
	else
	{
		mChildNode = pNewChild;
		mChildNode->SetPrev(NULL);
		mChildNode->SetNext(NULL);
	}
}

/*------------------------------------------------------------------*
 *								Detach()							*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *		If we have a parent node and we're the first child			*
 *			If we're not an only child								*
 *				move our first sibling to the parent's first child	*
 *			Else													*
 *				parent's first child is null						*
 *		Set our previous sibling's next node to our next node		*
 *		Set our next sibling's prev node to our prev node			*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VNode::Detach()
{
	if (mParentNode && mParentNode->mChildNode == this)
	{
		mParentNode->SetChild(mNextNode);
	}

	if (mPrevNode == mNextNode)
	{
		if (mPrevNode != NULL)
		{
			mPrevNode->SetNext(NULL);
			mNextNode->SetPrev(NULL);
		}
	}
	else
	{
		mPrevNode->SetNext(mNextNode);
		mNextNode->SetPrev(mPrevNode);
	}

	mPrevNode = NULL;
	mNextNode = NULL;
}


/*------------------------------------------------------------------*
 *								CountNodes()						*
 *------------------------------------------------------------------*
 *	ALGORITHM:														*
 *																	*
 *------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
int VNode::CountNodes()
{
	if (mChildNode)
		return mChildNode->CountNodes() + 1;
	else
		return 1;
}

/********************************************************************
 *                         C A L L B A C K S                        *
 ********************************************************************/

/********************************************************************
 *                         I N T E R N A L S                        *
 ********************************************************************/

} // End Namespace
