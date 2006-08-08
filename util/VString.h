/**
 *	@class		UDP::VString
 *
 *	@brief		Generic string handling class.
 *	@author		Josh Williams
 *	@version	0.1.0
 *	@date		19-Sep-2003
 *	@remarks	Provides a set of simple functions for handling dynamic strings
 *				within our applications.
 */
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
#if !defined(__VSTRING_H_INCLUDED__)
#define __VSTRING_H_INCLUDED__

#include <cstring>
#include <iostream>

using std::ostream;

namespace UDP
{

class VString
{
public:
	/*==================================*
	 *	   CONSTRUCTION/DESTRUCTION		*
	 *==================================*/
	VString();
	VString(char *pc);
	VString(const char *pc);
	VString(int n);
	VString(const VString &str);
	virtual ~VString();

	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/
	const char*		C_Str() const;
	int				Length() const;
	int				Size() const;
	VString			SubStr(int nOffset, int nCount) const;

	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	void			Resize(int nSize);
	void			Copy(const char *pc, ...);
	void			Cat(const char *pc, ...);
	void			Cat(const char c);
	int				Compare(const char *pc) const;
	int				Replace(const char *pcSearch, const char *pcStr);
	void			Trim();

	/*==================================*
	 *			   OPERATORS			*
	 *==================================*/
	char&			operator[](int offset);
	char			operator[](int offset) const;
	VString&		operator=(const VString &strSource);
	VString&		operator=(const char *pcSource);
	const VString&	operator+=(const VString& strCat);
	const VString&	operator+=(const char *pcCat);
	const VString	operator+(const VString& strCat) const;
	const VString	operator+(const char *pcCat) const;
	friend const VString	operator+(const char *pcFront,
									const VString& strBack);
					operator const char*() const;
	friend ostream& operator<<(ostream& os, const VString& strOut);

protected:
	/*==================================*
	 *             CALLBACKS			*
	 *==================================*/

private:
	/*==================================*
	 *             INTERNALS            *
	 *==================================*/
	void			Init();
	
private:
	/*==================================*
	 *             VARIABLES            *
	 *==================================*/
	char*			m_pData;
	char*			m_pDataLeft;
	char*			m_pDataRight;
	char*			m_pDataMid;
	int				m_nLength;
	int				m_nSize;
};


/*------------------------------------------------------------------*
 *								C_Str()								*
 *------------------------------------------------------------------*/
/**
 *	@brief		Returns the array of chars for this VString.
 *	@author		Josh Williams
 *	@date		19-Sep-2003
 *
 *	@remarks	Useful when this VString is used in printf variants
 *				where % formatting is used.
 *
 *	@returns	(char*) Array of chars.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
inline const char* VString::C_Str() const
{
	return m_pData;
}

/*------------------------------------------------------------------*
 *								Length()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Returns the length of this VString object.
 *	@author		Josh Williams
 *	@date		19-Sep-2003
 *
 *	@returns	(int) Length of string.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
inline int VString::Length() const
{
	return m_nLength;
}

/*------------------------------------------------------------------*
 *								 Size()								*
 *------------------------------------------------------------------*/
/**
 *	@brief		Returns the total size of the array currently
 *				allocated by this VString.
 *	@author		Josh Williams
 *	@date		19-Sep-2003
 *
 *	@remarks	Length returns the length of the string held by this
 *				object.  This function returns the total available
 *				space in the curently allocated char array.
 *
 *	@returns	(int) Total space allocated.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
inline int VString::Size() const
{
	return m_nSize;
}

/*------------------------------------------------------------------*
 *								Compare()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Compares the supplied character array against this
 *				VString object using strcmp().
 *	@author		Josh Williams
 *	@date		30-Aug-2004
 *
 *	@param		pc	Char array to be compared against
 *
 *	@returns	0 if the string matches, <>0 otherwise
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
inline int VString::Compare(const char *pc) const
{
	return strcmp(m_pData, pc);
}

/*------------------------------------------------------------------*
 *							operator=()								*
 *------------------------------------------------------------------*/
/**
 *	@brief		VString assignment.
 *	@author		Josh Williams
 *	@date		19-Sep-2003
 *
 *	@param		strSource	VString whose value we should inherit.
 *
 *	@returns	(CStr&) This object after manipulation.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
inline VString& VString::operator=(const VString& strSource)
{
	Copy(strSource.C_Str());
	return *this;
}

/**
 *	@overload
 */
inline VString& VString::operator=(const char *pcSource)
{
	Copy(pcSource);
	return *this;
}

/*------------------------------------------------------------------*
 *						  operator const char*()					*
 *------------------------------------------------------------------*/
/**
 *	@brief		Allows this object to be treated as a normal
 *				character array.
 *	@author		Josh Williams
 *	@date		19-Sep-2003
 *
 *	@remarks	Useful when this object is used in standard library
 *				calls such as strcpy.
 *
 *	@returns	(char*) Pointer to the actual string held by this object
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
inline VString::operator const char*() const
{
	return C_Str();
}

/*------------------------------------------------------------------*
 *								Init() 								*
 *------------------------------------------------------------------*/
/**
 *	@brief		Initializes the member variables for this instance.
 *	@author		Josh Williams
 *	@date		22-Sep-2003
 *
 *	@returns	void
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
inline
void VString::Init(void)
{
	m_pDataLeft		= new char[1];
	*m_pDataLeft	= '\0';
	m_pDataRight	= new char[1];
	*m_pDataRight	= '\0';
	m_pDataMid		= new char[1];
	*m_pDataMid		= '\0';
}

} // End Namespace

#endif // __VSTRING_H_INCLUDED__
