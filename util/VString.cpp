/*============================================================================*
 *                                                                            *
 *  This source file is part of the UDP Game Engine.                 	  	  *
 *                                                                            *
 *  Copyright (C) 2003 UDP Games   All Rights Reserved.                       *
 *                                                                            *
 *============================================================================*/

/* System Headers */
#include <cstdio>
#include <cstdarg>

/* Local Headers */
#include "VString.h"

namespace UDP
{

/********************************************************************
 *          C O N S T R U C T I O N / D E S T R U C T I O N         *
 ********************************************************************/
VString::VString()
{
	m_pData		= new char[1];
	*m_pData	= '\0';
	m_nLength	= 0;
	m_nSize		= 1;
	Init();
}
VString::VString(char *pc)
{
	int n = strlen(pc);
	m_pData = new char[n+1];
	strcpy(m_pData, pc);
	m_nLength	= n;
	m_nSize		= n+1;
	Init();
}
VString::VString(const VString& str)
{
	const char *pc = str.C_Str();
	int n = str.Length();
	m_pData = new char[n+1];
	strcpy(m_pData, pc);
	m_nLength	= n;
	m_nSize		= n+1;
	Init();
}
VString::VString(const char *pc)
{
	int n = strlen(pc);
	m_pData = new char[n+1];
	strcpy(m_pData, pc);
	m_nLength	= n;
	m_nSize		= n+1;
	Init();
}
VString::VString(int n)
{
	m_pData		= new char[n+1];
	*m_pData	= '\0';
	m_nLength	= 0;
	m_nSize		= n+1;
	Init();
}

VString::~VString()
{
	delete[] m_pData;
	delete[] m_pDataLeft;
	delete[] m_pDataRight;
	delete[] m_pDataMid;
	m_pData			= NULL;
	m_pDataLeft		= NULL;
	m_pDataRight	= NULL;
	m_pDataMid		= NULL;
}	
	
/********************************************************************
 *                        A T T R I B U T E S                       *
 ********************************************************************/

/*------------------------------------------------------------------*
 *								SubStr()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Returns nCount number of characters from the beginning
 *				of this VString, up to the length of the VString.
 *	@author		Josh Williams
 *	@date		19-Sep-2003
 *
 *	@param		nOffset	Index at which to begin returning substring.
 *	@param		nCount	Number of characters to return
 *
 *	@returns	(const char*) Requested characters.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
VString VString::SubStr(int nOffset, int nCount) const
{
	int nLastIndex;
	VString temp(*this);

	if (nOffset < 0)
		nOffset = 0;

	if (nOffset >= Length())
	{
		temp = "";
		return temp;
	}

	nLastIndex = nOffset + nCount - 1;
	if (nLastIndex >= Length())
		nLastIndex = Length() - 1;

	int j, k;
	for (j = 0, k = nOffset; k <= nLastIndex; j++, k++)
	{
		temp[j] = m_pData[k];
	}
	temp[j] = '\0';
	return temp;
}

/********************************************************************
 *                        O P E R A T I O N S                       *
 ********************************************************************/

/*------------------------------------------------------------------*
 *								Resize()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Increases/decreases the total number of characters
 *				this VString object is capable of holding.
 *	@author		Josh Williams
 *	@date		19-Sep-2003
 *
 *	@param		nSize	New size for this VString object
 *
 *	@returns	void
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VString::Resize(int nSize)
{
	char *pTemp;

	if (m_pData)
	{
		pTemp = new char[m_nLength];
		memset(pTemp, '\0', sizeof(pTemp));
		memcpy(pTemp, m_pData, m_nLength);
		delete[] m_pData;
		m_pData = new char[nSize+1];
		memset(m_pData, '\0', sizeof(m_pData));
		if (nSize > m_nLength)
		{
			memcpy(m_pData, pTemp, m_nLength);
			m_pData[m_nLength] = '\0';
		}
		else
		{
			memcpy(m_pData, pTemp, nSize);
			m_pData[m_nLength] = '\0';
		}
		delete[] pTemp;
	}
	else
	{
		m_pData = new char[nSize+1];
		memset(m_pData, '\0', sizeof(m_pData));
	}

	m_nLength = strlen(m_pData);
	m_nSize = nSize+1;
}

/*------------------------------------------------------------------*
 *								 Cpy() 								*
 *------------------------------------------------------------------*/
/**
 *	@brief		Performs strcpy-like manipulation of this VString.
 *	@author		Josh Williams
 *	@date		19-Sep-2003
 *
 *	@remarks	VString is resized to the length of the string supplied.
 *
 *	@param		pcNewString	Char array with optional printf-style formatting
 *
 *	@returns	void
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VString::Copy(const char *pcNewString, ...)
{

	int n;
	va_list args;
	char acBuffer[1024];
	
	va_start(args, pcNewString);
	vsprintf(acBuffer, pcNewString, args);
	
	n = strlen(acBuffer);
	if (m_pData)
	{
		delete[] m_pData;
		m_pData = NULL;
	}
	m_pData = new char[n+1];
	m_nLength = n;
	
	strcpy(m_pData, acBuffer);
	m_nSize = n+1;
}

/*------------------------------------------------------------------*
 *								  Cat()								*
 *------------------------------------------------------------------*/
/**
 *	@brief		Performs strcat-like manipulation of this VString.
 *	@author		Josh Williams
 *	@date		19-Sep-2003
 *
 *	@remarks	VString is resized accordingly.
 *
 *	@param		pc	Char array with optional printf-style formatting
 *
 *	@returns	void
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VString::Cat(const char *pc, ...)
{
	int n;
	char *pTemp;
	va_list args;
	char acBuffer[1024];

	va_start(args, pc);
	vsprintf(acBuffer, pc, args);

	n = strlen(acBuffer);
	if (n == 0)
		return;
	else
	{
		pTemp = new char[n + strlen(m_pData) + 1];
		if (m_pData)
		{
			strcpy(pTemp, m_pData);
			delete[] m_pData;
			m_pData = NULL;
		}
		strcat(pTemp, acBuffer);
		m_pData = pTemp;
		m_nLength += n;
	}
	m_nSize = n+1;
}

/*------------------------------------------------------------------*
 *								Replace()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Replaces one substring of this String with another
 *				string.
 *	@author		Josh Williams
 *	@date		19-Sep-2003
 *
 *	@param		pcSearch	String to be replaced
 *	@param		pcStr		String to be inserted
 *
 *	@returns	(int) Final length of the string.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
int VString::Replace(const char *pcSearch, const char *pcStr)
{
	char acBuffer[8192];
	char acHold[8192];
	char *pcPos;
	int nPos;
	int nLength = (int)strlen(pcSearch);
	memset(acBuffer, 0, sizeof(acBuffer));
	memset(acHold, 0, sizeof(acHold));

	strcpy(acHold, m_pData);

	pcPos = strstr(acHold, pcSearch);
	while (pcPos != NULL)
	{
		nPos = (int)(pcPos - acHold);
		strncat(acBuffer, acHold, nPos);
		strcat(acBuffer, pcStr);
		strcpy(acHold, &acHold[nPos+nLength]);
		pcPos = strstr(acHold, pcSearch);
	}

	strcat(acBuffer, acHold);

	if (m_pData)
		delete[] m_pData;
	m_nLength = (int)strlen(acBuffer);
	m_pData = new char[m_nLength+1];
	strcpy(m_pData, acBuffer);
	return m_nLength;
}

/*------------------------------------------------------------------*
 *								 Trim()								*
 *------------------------------------------------------------------*/
/**
 *	@brief		Trims spaces from the front and back of the VString.
 *	@author		Josh Williams
 *	@date		19-Sep-2003
 *
 *	@returns	void
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VString::Trim()
{
	char *pcBuffer = new char[m_nLength+1];
	char *pc;
	memset(pcBuffer, 0, m_nLength+1);

	if (m_nLength == 0)
		return;

	if (m_pData[0] == ' ')
	{
		int i = 0;
		pc = m_pData;

		while (*pc == ' ')
		{
			i++;
			pc++;
		}
		strcpy(pcBuffer, pc);
	}
	else
		strcpy(pcBuffer, m_pData);

	pc = &pcBuffer[strlen(pcBuffer)-1];

	while (*pc == ' ')
	{
		*pc = '\0';
		pc--;
	}

	delete[] m_pData;
	m_pData = new char[strlen(pcBuffer)+1];
	strcpy(m_pData, pcBuffer);
	m_nLength = strlen(m_pData);
	m_nSize = m_nLength + 1;
	delete[] pcBuffer;
}

/********************************************************************
 *                          O P E R A T O R S                       *
 ********************************************************************/

/*------------------------------------------------------------------*
 *								operator[]							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Allows access to a specific character in the
 *				VString for modification.
 *	@author		Josh Williams
 *	@date		19-Sep-2003
 *
 *	@remarks	Returns a reference so the character can be
 *				replaced with another char.
 *
 *	@param		offset	Index of the element to be returned
 *
 *	@returns	(char&) Character requested.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
char& VString::operator[](int offset)
{
	if (offset > m_nLength)
		return m_pData[m_nLength-1];
	else
		return m_pData[offset];
}

/*------------------------------------------------------------------*
 *							    operator[]							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Returns the character in the VString represented
 *				by the given index.
 *	@author		Josh Williams
 *	@date		19-Sep-2003
 *
 *	@param		offset	Index of the element to be returned
 *
 *	@returns	(char) Character requested.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
char VString::operator[](int offset) const
{
	if (offset > m_nLength)
		return m_pData[m_nLength-1];
	else
		return m_pData[offset];
}

/*------------------------------------------------------------------*
 *							operator+=()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Performs VString concatenation.
 *	@author		Josh Williams
 *	@date		19-Sep-2003
 *
 *	@param		strCat	VString to be copied to the end of this VString
 *
 *	@returns	(String) Result of concatenation.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
const VString& VString::operator+=(const VString& strCat)
{
	Cat(strCat.C_Str());
	return *this;
}

/**
 *	@overload
 */
const VString& VString::operator+=(const char *pcCat)
{
	Cat(pcCat);
	return *this;
}

/*------------------------------------------------------------------*
 *							operator+()								*
 *------------------------------------------------------------------*/
/**
 *	@brief		Performs VString concatenation for assignment.
 *	@author		Josh Williams
 *	@date		19-Sep-2003
 *
 *	@param		strCat	VString to be added to the end of this VString
 *
 *	@returns	(String&) Result of concatenation.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
const VString VString::operator+(const VString& strCat) const
{
	VString temp(*this);
	temp.Cat(strCat.C_Str());
	return temp;
}

/**
 *	@overload
 */
const VString VString::operator+(const char *pcCat) const
{
	VString temp(*this);
	temp.Cat(pcCat);
	return temp;
}

/*------------------------------------------------------------------*
 *							operator+()								*
 *------------------------------------------------------------------*/
/**
 *	@brief		Allows concatenation when the VString object isn't
 *				first.
 *	@author		Josh Williams
 *	@date		19-Sep-2003
 *
 *	@param		pcFront	Char pointer to be the beginning of the
 *				resulting VString
 *	@param		strBack	VString object to be the end of the resulting
 *				VString.
 *
 *	@returns	(CStr) Result of concatenation.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
const VString operator+(const char *pcFront, const VString& strBack)
{
	VString temp(pcFront);
	temp.Cat(strBack.C_Str());
	return temp;
}

/*------------------------------------------------------------------*
 *							  operator<<()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Allows this VString object to be used directly
 *				in stream operations.
 *	@author		Josh Williams
 *	@date		19-Sep-2003
 *
 *	@param		os		Stream object to output to
 *	@param		strOut	VString object to be output
 *
 *	@returns	(ostream&) Output object.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
ostream& operator<<(ostream& os, const VString& strOut)
{
	os << strOut.C_Str();
	return os;
}

/********************************************************************
 *                         C A L L B A C K S                        *
 ********************************************************************/

/********************************************************************
 *                         I N T E R N A L S                        *
 ********************************************************************/

} // End Namespace
