/*============================================================================*
 *                                                                            *
 * 	This source file is part of the Viper3D Game Engine.                      *
 *                                                                            *
 *	Copyright (C) 2004 UDP Games   All Rights Reserved.                       *
 *                                                                            *
 *============================================================================*/

/* System Headers */
#include <cstring>

/* Local Headers */
#include "VGlobals.h"
#include "VCPU.h"
#include "VLog.h"

namespace UDP
{
bool	VCPU::m_bSSE = false;
bool	VCPU::m_bOSSSE = false;
bool	VCPU::m_bSSE2 = false;
bool	VCPU::m_b3DNOW = false;
bool	VCPU::m_bMMX = false;
bool	VCPU::m_bEXT = false;
bool	VCPU::m_bMMXEX = false;
bool	VCPU::m_b3DNOWEX = false;
char	VCPU::m_Vendor[13];
char	VCPU::m_Name[48];

static char __CLASS__[] = "[     VCPU     ]";

#if VIPER_PLATFORM == PLATFORM_LINUX
#include <signal.h>
static void sigill_handler(int signal, struct sigcontext sc)
{
	sc.eip += 3;
	UDP::VCPU::m_bOSSSE = false;
}
#endif

/********************************************************************
 *          C O N S T R U C T I O N / D E S T R U C T I O N         *
 ********************************************************************/
VCPU::VCPU(void)
{

}

VCPU::~VCPU(void)
{

}

/********************************************************************
 *                        A T T R I B U T E S                       *
 ********************************************************************/

/*------------------------------------------------------------------*
 *								HaveSSE()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Returns whether or not the CPU/OS can support SSE.
 *	@author		Josh Williams
 *	@date		09-Sep-2004
 *
 *	@returns	True/false
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
bool VCPU::HaveSSE(void)
{
	return (m_bSSE && m_bOSSSE);
}

/********************************************************************
 *                        O P E R A T I O N S                       *
 ********************************************************************/

/*------------------------------------------------------------------*
 *								 Init()								*
 *------------------------------------------------------------------*/
/**
 *	@brief		Extracts the CPU information from the processor.
 *	@author		Josh Williams
 *	@date		09-Sep-2004
 *
 *	@returns	void
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VCPU::Init(void)
{
	struct sigaction saved_sigill;
	int		n = 0;

	memset(m_Name, '\0', sizeof(m_Name));

	/* Get the vendor name */
	GetCPUVendor();

	/* Get the base feature list */
	GetBaseFeatures();

	/* Get the extended feature list */
	GetExtFeatures();

	/* vendor specific stuff */
	if ((strncmp(m_Vendor, "GenuineIntel", 12) == 0) && m_bEXT)
	{
		/* Intel family */
		GetIntelInfo(&n);
	}
	else if ((strncmp(m_Vendor, "AuthenticAMD", 12) == 0) && m_bEXT)
	{
		/* AMD family */
		GetAMDInfo(&n);
	}

	/* Test for OS SSE support */
	m_bOSSSE = true;
	sigaction(SIGILL, NULL, &saved_sigill);
	signal(SIGILL, (void (*)(int))sigill_handler);
	__asm__ __volatile__ ("xorps %xmm0, %xmm0");

	/* Output CPU information to trace file */
	VTRACE(_CL("============ CPU Info =============\n"));
	VTRACE(_CL("Vendor:         %s\n"), m_Vendor);
	VTRACE(_CL("\n"));
	VTRACE(_CL("Base features: "));
	if (m_bSSE)		VTRACE(" SSE");
	if (m_bSSE2)	VTRACE(" SSE2");
	if (m_bMMX)		VTRACE(" MMX");
	VTRACE("\n");

	if (m_bEXT)
	{
		VTRACE(_CL("Ext features:  "));
		if (m_b3DNOW)	VTRACE(" 3DNOW");
		if (m_b3DNOWEX)	VTRACE(" 3DNOWEX");
		if (m_bMMXEX)	VTRACE(" MMXEX");
		VTRACE("\n");
	}

	VTRACE(_CL("OS SSE Support: %s\n"), (m_bOSSSE ? "Yes" : "No"));
	
	VTRACE(_CL("===================================\n"));

}

/********************************************************************
 *                         C A L L B A C K S                        *
 ********************************************************************/

/********************************************************************
 *                         I N T E R N A L S                        *
 ********************************************************************/

/*------------------------------------------------------------------*
 *							  GetCPUVendor()						*
 *------------------------------------------------------------------*/
/**
 *	@brief		Determines the manufacturer of the CPU.
 *	@author		Josh Williams
 *	@date		10-Sep-2004
 *
 *	@returns	void
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VCPU::GetCPUVendor()
{
	char *pVendor = m_Vendor;

	memset(m_Vendor, '\0', sizeof(m_Vendor));
	/* Get the vendor name */
#if VIPER_PLATFORM == PLATFORM_WINDOWS
	_asm {
		mov		eax, 0
		CPUID

		mov		esi,		pVendor
		mov		[esi],		ebx
		mov		[esi+4],	edx
		mov		[exi+8],	ecx
	}
#elif VIPER_PLATFORM == PLATFORM_APPLE
#elif VIPER_PLATFORM == PLATFORM_LINUX
	__asm__ __volatile__("\n\t"
			"movl $0, %%eax\n\t"
			"cpuid\n\t"
			: "=b" (*(int*)&pVendor[0]),
			  "=d" (*(int*)&pVendor[4]),
			  "=c" (*(int*)&pVendor[8])
			: 
			: "eax"
	);
#endif
	pVendor[12] = '\0';
}

/*------------------------------------------------------------------*
 *							  GetBaseFeatures()						*
 *------------------------------------------------------------------*/
/**
 *	@brief		Determines the base set of features available.
 *	@author		Josh Williams
 *	@date		10-Sep-2004
 *
 *	@returns	void
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VCPU::GetBaseFeatures()
{
#if VIPER_PLATFORM == PLATFORM_WINDOWS
	_asm {
		mov		eax,		1
		CPUID

		test	edx,		04000000h
		jz		NOSSE2
		mov		[m_bSSE2],	1
NOSSE2:	test	edx,		02000000h
		jz		NOSSE
		mov		[m_bSSE],	1
NOSSE:	test	edx,		00800000h
		jz		EXIT
		mov		[m_bMMX],	1
EXIT:
	}		
#elif VIPER_PLATFORM == PLATFORM_APPLE
#elif VIPER_PLATFORM == PLATFORM_LINUX

	__asm__ __volatile__ ("\n\t"
		"movl	$1, %%eax\n\t"
		"cpuid\n\t"
		"movb	$0,	%0\n\t"
		"movb	$0,	%1\n\t"
		"movb	$0,	%2\n\t"
		"test	$0x04000000, %%edx\n\t"
		"jz		NOSSE2\n\t"
		"movb	$1, %0\n\t"
		"NOSSE2:\n\t"
		"test	$0x02000000, %%edx\n\t"
		"jz		NOSSE\n\t"
		"movb	$1, %1\n\t"
		"NOSSE:\n\t"
		"test	$0x00800000, %%edx\n\t"
		"jz		EXIT\n\t"
		"movb	$1, %2\n\t"
		"EXIT:\n\t"
		: "=m" (m_bSSE2),
		  "=m" (m_bSSE),
		  "=m" (m_bMMX)
		:
		: "ax", "bx", "cx", "dx", "memory"
	);
#endif
}

/*------------------------------------------------------------------*
 *							  GetExtFeatures()						*
 *------------------------------------------------------------------*/
/**
 *	@brief		Determines the extended set of features available.
 *	@author		Josh Williams
 *	@date		10-Sep-2004
 *
 *	@returns	void
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VCPU::GetExtFeatures()
{
#if VIPER_PLATFORM == PLATFORM_WINDOWS
#elif VIPER_PLATFORM == PLATFORM_APPLE
#elif VIPER_PLATFORM == PLATFORM_LINUX

	/* extended info */
	__asm__ __volatile__ ("\n\t"
			"movl	$0x80000000, %%eax\n\t"
			"cpuid\n\t"
			"cmp	$0x80000000, %%eax\n\t"
			"jbe	EXIT2\n\t"
			"movb	$1, %0\n\t"
			"movl	$0x80000001, %%eax\n\t"
			"cpuid\n\t"
			"test	$0x80000000, %%edx\n\t"
			"jz		EXIT2\n\t"
			"movb	$1, %1\n\t"
			"EXIT2:\n"
			: "=m" (m_bEXT),
			  "=m" (m_b3DNOW)
			:
			: "ax", "bx", "cx", "dx", "memory"
	);
#endif
}

/*------------------------------------------------------------------*
 *							  GetIntelInfo()						*
 *------------------------------------------------------------------*/
/**
 *	@brief		Gets the model number of an Intel processor.
 *	@author		Josh Williams
 *	@date		10-Sep-2004
 *
 *	@returns	void
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VCPU::GetIntelInfo(int *n)
{
#if VIPER_PLATFORM == PLATFORM_WINDOWS
#elif VIPER_PLATFORM == PLATFORM_APPLE
#elif VIPER_PLATFORM == PLATFORM_LINUX
	__asm__ __volatile__ ("\n\t"
			"mov	$1, %%eax\n\t"
			"cpuid\n\t"
			: "=b" (*n)
			:
			: "eax", "cx", "dx", "memory"
	);
	int m=0;
	memcpy(&m, n, sizeof(char));
	*n = m;
#endif
}

/*------------------------------------------------------------------*
 *							   GetAMDInfo()							*
 *------------------------------------------------------------------*/
/**
 *	@brief		Gets the model number of an AMD processor.  Also
 *				determines if the processor supports 3DNow! extended
 *				or MMX Extended.
 *	@author		Josh Williams
 *	@date		10-Sep-2004
 *
 *	@returns	void
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
void VCPU::GetAMDInfo(int *n)
{
#if VIPER_PLATFORM == PLATFORM_WINDOWS
#elif VIPER_PLATFORM == PLATFORM_APPLE
#elif VIPER_PLATFORM == PLATFORM_LINUX
	__asm__ __volatile__ (
			"movl	$1, %%eax\n"
			"cpuid\n"
			: "=a" (*n)
			:
			: "bx", "cx", "dx"
	);
	int m = 0;
	memcpy(&m, n, sizeof(char));
	*n = m;

	__asm__ __volatile__ ("\n\t"
			"movl	$0x80000001, %%eax\n"
			"cpuid\n"
			"test	$0x40000000, %%edx\n"
			"jz		AMD1\n"
			"movb	$1, %0\n"
			"AMD1:\n"
			"test	$0x00400000, %%edx\n"
			"jz		AMD2\n"
			"movb	$1, %1\n"
			"AMD2:\n"
			: "=m" (m_b3DNOWEX),
			  "=m" (m_bMMXEX)
			:
			: "ax", "bx", "cx", "dx", "memory"
	);
#endif
}

} // End Namespace

