#include "engtest2.h"
#include <cstdio>

static unsigned int nIters = 1000000;
//static unsigned int nIters = 2;

void TestMult(VMatrix& m1, VMatrix &m2, unsigned int nIters);

void TestMatrices()
{
	cout << "===========================================" << endl;
	cout << "= Matrix testing							" << endl;
	cout << "= Iterations: " << nIters << endl;
	VMatrix	m1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
	VMatrix	m2(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	TestMult(m1, m2, nIters);
}

void TestMult(VMatrix &m1, VMatrix &m2, unsigned int nIters)
{
	struct timeb	tp_start;
	struct timeb	tp_end;
	time_t			tm_diff_sec;
	unsigned short	tm_diff_ms;
	VMatrix			vResult;

	cout << "===========================================" << endl;
	cout << "                  Mult()" << endl;
	cout << "===========================================" << endl;
	/* first, test without SSE */
	VCPU::mOSSSE = false;
	ftime(&tp_start);
	for (unsigned int i = 0; i < nIters; i++)
	{
		vResult = m1 * m2;
	}
	ftime(&tp_end);
	tm_diff_sec = tp_end.time - tp_start.time;
	tm_diff_ms  = tp_end.millitm - tp_start.millitm;
	cout << " WITHOUT SSE: " << tm_diff_sec << "secs " << tm_diff_ms << "ms" << endl;
	cout << "      result: " << vResult[0][0] << endl;

	/* now, try with SSE */
	VCPU::mOSSSE = true;
	ftime(&tp_start);
	for (unsigned int i = 0; i < nIters; i++)
	{
		vResult = m1 * m2;
	}
	ftime(&tp_end);
	tm_diff_sec = tp_end.time - tp_start.time;
	tm_diff_ms  = tp_end.millitm - tp_start.millitm;
	cout << "    WITH SSE: " << tm_diff_sec << "secs " << tm_diff_ms << "ms" << endl;
	cout << "      result: " << vResult[0][0] << endl << endl;
}
