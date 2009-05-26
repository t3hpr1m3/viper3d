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
#if !defined(__NODE_H_INCLUDED__)
#define __NODE_H_INCLUDED__

#include <stdlib.h>
#include <viper3d/Globals.h>
#include <viper3d/Renderable.h>

namespace UDP
{
/**
 *	@class		VNode
 *
 *	@brief		Smallest engine element.
 *	@author		Josh Williams <volzman19@yahoo.com>
 *	@version	0.1.0
 *	@date		03-Sep-2003
 *	@remarks	This is the building block for our game engine.  It represents
 *				an element in a linked list of other elements, allowing us to
 *				define an object heirarchy within the system.
 */
class VNode : public VRenderable
{
public:
	/*==================================*
	 *	   CONSTRUCTION/DESTRUCTION		*
	 *==================================*/
	VNode();
	VNode(VNode* node);
	virtual ~VNode();

public:
	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/
	/**
	 *	@brief		Determines the topmost element of this node's
	 *				heirarchy.
	 *	@author		Josh Williams
	 *	@date		04-Sep-2003
	 *
	 *	@returns	Root node in the tree, or this node, if we're at
	 *				the top.
	 */
	VNode  			*FindRoot();
	/**
	 *	@brief		Determine whether or not we have a parent, or are a 
	 *				top-level node.
	 *	@author		Josh Williams
	 *	@date		05-Sep-2003
	 *
	 *	@returns	True/false
	 */
	inline bool		HasParent() { return (mParentNode != NULL); }
	/**
	 *	@brief		Determine whether this node has any children
	 *	@author		Josh Williams
	 *	@date		05-Sep-2003
	 *
	 *	@returns	True/false
	 */
	inline bool		HasChild() { return (mChildNode != NULL); }
	/**
	 *	@brief		Determine whether this node is directly connected to
	 *				a top level parent.
	 *	@author		Josh Williams
	 *	@date		05-Sep-2003
	 *
	 *	@returns	True/false
	 */
	bool			IsFirstChild();
	/**
	 *	@brief		Determine whether this node is the last in the linked
	 *				list.
	 *	@author		Josh Williams
	 *	@date		05-Sep-2003
	 *
	 *	@returns	True/false
	 */
	bool			IsLastChild();
	/**
	 *	@brief		Returns the parent node of this node, or NULL if this node is a
	 *				top-level node.
	 *	@author		Josh Williams
	 *	@date		07-Sep-2003
	 *
	 *	@returns	(VNode*) Parent of this node, or NULL.
	 */
	inline VNode*	GetParent() { return mParentNode; }
	/**
	 *	@brief		Returns the first child node of this node, or NULL if this node
	 *				has no children.
	 *	@author		Josh Williams
	 *	@date		07-Sep-2003
	 *
	 *	@returns	(VNode*) First child of this node, or NULL.
	 */
	inline VNode*	GetChild() { return mChildNode; }
	/**
	 *	@brief		Returns the next sibling of this node, or NULL if we are an
	 *				only child.
	 *	@author		Josh Williams
	 *	@date		07-Sep-2003
	 *
	 *	@returns	(Node*) Our next sibling, or NULL.
	 */
	inline VNode*	GetNext() { return mNextNode; }
	/**
	 *	@brief		Returns the previous sibling of this node, or NULL if we are an
	 *				only child.
	 *	@author		Josh Williams
	 *	@date		07-Sep-2003
	 *
	 *	@returns	(VNode*) Our previous sibling, or NULL.
	 */
	inline VNode*	GetPrev() { return mPrevNode; }	

public:
	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	/**
	 *	@brief		Overridden from Renderable.
	 *	@author		Josh Williams
	 *	@date		12-Sep-2003
	 *
	 *	@remarks	This version allows the entire Node tree to be rendered.
	 *
	 *	@returns	void
	 */
	void			Render();
	/**
	 *	@brief		Attaches this node to another.
	 *	@author		Josh Williams
	 *	@date		05-Sep-2003
	 *
	 *	@remarks	Makes this node a child of the supplied node.  This allows 
	 *				a heirarchy to be constructed, so that groups of objects
	 *				can be drawn together.
	 *
	 *	@param		newParent	Node we should attach to
	 *
	 *	@returns	void
	 */
	void			AttachTo(VNode *pNewParent);
	/**
	 *	@brief		Makes the supplied node our child.
	 *	@author		Josh Williams
	 *	@date		05-Sep-2003
	 *
	 *	@remarks	If the node is already attached somewhere, it is detached.
	 *				Then the node is placed at the end of the list for this
	 *				node.
	 *
	 *	@param		newChild	Node to be added to our linked list
	 *
	 *	@returns	void
	 */
	void			Attach(VNode *pNewChild);
	/**
	 *	@brief		Removes this node from the tree, usually before it is
	 *				deleted.
	 *	@author		Josh Williams
	 *	@date		05-Sep-2003
	 *
	 *	@returns	void
	 */
	void			Detach();
	/**
	 *	@brief		Determines the total number of nodes owned by this node.
	 *	@author		Josh Williams
	 *	@date		05-Sep-2003
	 *
	 *	@returns	(int) Total number of nodes counted.
	 */
	int				CountNodes();
	/**
	 *	@brief		Sets the parent of this node.
	 *	@author		Josh Williams
	 *	@date		07-Sep-2003
	 *
	 *	@param		pNewParent	Node to set as our new parent node
	 *
	 *	@returns	(VNode*) Our previous parent node, or NULL.
	 */
	inline VNode*	SetParent(VNode *pNewParent)
	{
		VNode *vOldParent = mParentNode;
		mParentNode = pNewParent;
		return vOldParent;
	}
	/**
	 *	@brief		Sets the first child for this node.
	 *	@author		Josh Williams
	 *	@date		07-Sep-2003
	 *
	 *	@param		pNewChild	Node to set as our first child
	 *
	 *	@returns	(VNode*) Our previous child node, or NULL.
	 */
	inline VNode*	SetChild(VNode *pNewChild)
	{
	 	VNode *vOldChild = mChildNode;
		mChildNode = pNewChild;
		return vOldChild;
	}
	/**
	 *	@brief		Sets the previous sibling of this node.
	 *	@author		Josh Williams
	 *	@date		07-Sep-2003
	 *
	 *	@param		pNewPrev	Node to set as our previous sibling
	 *
	 *	@returns	(VNode*) Our old previous node, or NULL.
	 */
	inline VNode*	SetPrev(VNode *pNewPrev)
	{
		VNode *vOldPrev = mPrevNode;
		mPrevNode = pNewPrev;
		return vOldPrev;
	}
	/**
	 *	@brief		Sets the next sibling of this node.
	 *	@author		Josh Williams
	 *	@date		07-Sep-2003
	 *
	 *	@param		pNewNext Node to set as our next sibling
	 *
	 *	@returns	(VNode*) Our old next node, or NULL.
	 */
	inline VNode*	SetNext(VNode *pNewNext)
	{
		VNode* vOldNext = mNextNode;
		mNextNode = pNewNext;
		return vOldNext;
	}

protected:
	/*==================================*
	 *			  CALLBACKS				*
	 *==================================*/

private:
	/*==================================*
	 *			  INTERNALS				*
	 *==================================*/

private:
	/*==================================*
	 *			  VARIABLES				*
	 *==================================*/
	VNode	*mParentNode;	/**< Owner of this node, or null if we are a top-level */
	VNode	*mChildNode;	/**< Pointer to our first child node, or null */
	VNode	*mPrevNode;		/**< Pointer to our previous sibling, or ourselves if we're 
								 an only child.
							*/
	VNode	*mNextNode;		/**< Pointer to our next sibling, or ourselves if we're an
								 only child.
							*/
};
} // End Namespace

#endif // __NODE_H_INCLUDED__
