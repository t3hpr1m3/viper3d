/*============================================================================*
 *                                                                            *
 * 	This source file is part of the Viper3D Game Engine.                      *
 *                                                                            *
 *	Copyright (C) 2004 UDP Games   All Rights Reserved.                       *
 *                                                                            *
 *============================================================================*/
#include "VCPU.h"

/* System Headers */
#include <cstring>

/* Local Headers */
#include "VGlobals.h"
#include "VLog.h"

namespace UDP
{
bool	VCPU::mSSE = false;
bool	VCPU::mOSSSE = false;
bool	VCPU::mSSE2 = false;
bool	VCPU::m3DNOW = false;
bool	VCPU::mMMX = false;
bool	VCPU::mEXT = false;
bool	VCPU::mMMXEX = false;
bool	VCPU::m3DNOWEX = false;
char	VCPU::mVendor[13];
char	VCPU::mName[48];

static char __CLASS__[] = "[     VCPU     ]";

#if VIPER_PLATFORM == PLATFORM_LINUX
#include <signal.h>
static void sigill_handler(int signal, struct sigcontext sc)
{
	sc.eip += 3;
	UDP::VCPU::mOSSSE = false;
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
	return (mSSE && mOSSSE);
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
	struct	sigaction vSavedSigill;
	int		vN = 0;

	memset(mName, '\0', sizeof(mName));

	/* Get the vendor name */
	GetCPUVendor();

	/* Get the base feature list */
	GetBaseFeatures();

	/* Get the extended feature list */
	GetExtFeatures();

	/* vendor specific stuff */
	if ((strncmp(mVendor, "GenuineIntel", 12) == 0) && mEXT)
	{
		/* Intel family */
		GetIntelInfo(&vN);
	}
	else if ((strncmp(mVendor, "AuthenticAMD", 12) == 0) && mEXT)
	{
		/* AMD family */
		GetAMDInfo(&vN);
	}

	/* Test for OS SSE support */
	mOSSSE = true;
	sigaction(SIGILL, NULL, &vSavedSigill);
	signal(SIGILL, (void (*)(int))sigill_handler);
	__asm__ __volatile__ ("xorps %xmm0, %xmm0");

	/* Output CPU information to trace file */
	VTRACE(_CL("============ CPU Info =============\n"));
	VTRACE(_CL("Vendor:         %s\n"), mVendor);
	VTRACE(_CL("\n"));
	VTRACE(_CL("Base features: "));
	if (mSSE)	VTRACE(" SSE");
	if (mSSE2)	VTRACE(" SSE2");
	if (mMMX)	VTRACE(" MMX");
	VTRACE("\n");

	if (mEXT)
	{
		VTRACE(_CL("Ext features:  "));
		if (m3DNOW)		VTRACE(" 3DNOW");
		if (m3DNOWEX)	VTRACE(" 3DNOWEX");
		if (mMMXEX)		VTRACE(" MMXEX");
		VTRACE("\n");
	}

	VTRACE(_CL("OS SSE Support: %s\n"), (mOSSSE ? "Yes" : "No"));
	
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
	char *vVendor = mVendor;

	memset(mVendor, '\0', sizeof(mVendor));
	/* Get the vendor name */
#if VIPER_PLATFORM == PLATFORM_WINDOWS
	_asm {
		mov		eax, 0
		CPUID

		mov		esi,		vVendor
		mov		[esi],		ebx
		mov		[esi+4],	edx
		mov		[exi+8],	ecx
	}
#elif VIPER_PLATFORM == PLATFORM_APPLE
#elif VIPER_PLATFORM == PLATFORM_LINUX
	__asm__ __volatile__("\n\t"
			"movl $0, %%eax\n\t"
			"cpuid\n\t"
			: "=b" (*(int*)&vVendor[0]),
			  "=d" (*(int*)&vVendor[4]),
			  "=c" (*(int*)&vVendor[8])
			: 
			: "eax"
	);
#endif
	vVendor[12] = '\0';
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
		mov		[mSSE2],	1
NOSSE2:	test	edx,		02000000h
		jz		NOSSE
		mov		[mSSE],	1
NOSSE:	test	edx,		00800000h
		jz		EXIT
		mov		[mMMX],	1
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
		: "=m" (mSSE2),
		  "=m" (mSSE),
		  "=m" (mMMX)
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
			: "=m" (mEXT),
			  "=m" (m3DNOW)
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
void VCPU::GetIntelInfo(int *pN)
{
#if VIPER_PLATFORM == PLATFORM_WINDOWS
#elif VIPER_PLATFORM == PLATFORM_APPLE
#elif VIPER_PLATFORM == PLATFORM_LINUX
	__asm__ __volatile__ ("\n\t"
			"mov	$1, %%eax\n\t"
			"cpuid\n\t"
			: "=b" (*pN)
			:
			: "eax", "cx", "dx", "memory"
	);
	int vM=0;
	memcpy(&vM, pN, sizeof(char));
	*pN = vM;
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
void VCPU::GetAMDInfo(int *pN)
{
#if VIPER_PLATFORM == PLATFORM_WINDOWS
#elif VIPER_PLATFORM == PLATFORM_APPLE
#elif VIPER_PLATFORM == PLATFORM_LINUX
	__asm__ __volatile__ (
			"movl	$1, %%eax\n"
			"cpuid\n"
			: "=a" (*pN)
			:
			: "bx", "cx", "dx"
	);
	int vM = 0;
	memcpy(&vM, pN, sizeof(char));
	*pN = vM;

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
			: "=m" (m3DNOWEX),
			  "=m" (mMMXEX)
			:
			: "ax", "bx", "cx", "dx", "memory"
	);
#endif
}

} // End Namespace

