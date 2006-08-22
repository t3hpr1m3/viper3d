#include "engtest2.h"
#include <cstdio>

static unsigned int nIters = 1000000;

void TestLength(VVector& vec, unsigned int nIters);
void TestNormalize(VVector& vec, unsigned int nIters);
void TestCross(VVector& vec1, VVector& vec2, unsigned int nIters);

void TestVectors()
{
	cout << "===========================================" << endl;
	cout << "= Vector testing							" << endl;
	cout << "= Iterations: " << nIters << endl;
	VVector v1(1.1f, 2.2f, 3.3f);
	VVector v2(4.4f, 5.5f, 6.6f);

	TestLength(v1, nIters);
	TestNormalize(v1, nIters);
	TestCross(v1, v2, nIters);
}

void TestLength(VVector& vec, unsigned int nIters)
{
	struct timeb	tp_start;
	struct timeb	tp_end;
	time_t			tm_diff_sec;
	unsigned short	tm_diff_ms;
	float length = 0;

	cout << "===========================================" << endl;
	cout << "                  Length()" << endl;
	cout << "===========================================" << endl;
	/* first, test without SSE */
	VCPU::mOSSSE = false;
	ftime(&tp_start);
	for (unsigned int i = 0; i < nIters; i++)
	{
		length = vec.Length();
	}
	ftime(&tp_end);
	tm_diff_sec = tp_end.time - tp_start.time;
	tm_diff_ms  = tp_end.millitm - tp_start.millitm;
	cout << " WITHOUT SSE: " << tm_diff_sec << "secs " << tm_diff_ms << "ms" << endl;
	cout << "      length: " << length << endl;

	/* now, try with SSE */
	VCPU::mOSSSE = true;
	ftime(&tp_start);
	for (unsigned int i = 0; i < nIters; i++)
	{
		length = vec.Length();
	}
	ftime(&tp_end);
	tm_diff_sec = tp_end.time - tp_start.time;
	tm_diff_ms  = tp_end.millitm - tp_start.millitm;
	cout << "    WITH SSE: " << tm_diff_sec << "secs " << tm_diff_ms << "ms" << endl;
	cout << "      length: " << length << endl << endl;
}

void TestNormalize(VVector& vec, unsigned int nIters)
{
	struct timeb	tp_start;
	struct timeb	tp_end;
	time_t			tm_diff_sec;
	unsigned short	tm_diff_ms;
	VVector vTmp;

	cout << "===========================================" << endl;
	cout << "                Normalize()" << endl;
	cout << "===========================================" << endl;
	/* first, test without SSE */
	VCPU::mOSSSE = false;
	ftime(&tp_start);
	for (unsigned int i = 0; i < nIters; i++)
	{
		vTmp = vec;
		vTmp.Normalize();
	}
	ftime(&tp_end);
	tm_diff_sec = tp_end.time - tp_start.time;
	tm_diff_ms  = tp_end.millitm - tp_start.millitm;
	cout << " WITHOUT SSE: " << tm_diff_sec << "secs " << tm_diff_ms << "ms" << endl;
	cout << "        vTmp: " << vTmp << endl;

	/* now, try with SSE */
	VCPU::mOSSSE = true;
	ftime(&tp_start);
	for (unsigned int i = 0; i < nIters; i++)
	{
		vTmp = vec;
		vTmp.Normalize();
	}
	ftime(&tp_end);
	tm_diff_sec = tp_end.time - tp_start.time;
	tm_diff_ms  = tp_end.millitm - tp_start.millitm;
	cout << "    WITH SSE: " << tm_diff_sec << "secs " << tm_diff_ms << "ms" << endl;
	cout << "        vTmp: " << vTmp << endl << endl;
}

void TestCross(VVector& vec1, VVector& vec2, unsigned int nIters)
{
	struct timeb	tp_start;
	struct timeb	tp_end;
	time_t			tm_diff_sec;
	unsigned short	tm_diff_ms;
	VVector vTmp;

	cout << "===========================================" << endl;
	cout << "                  Cross()" << endl;
	cout << "===========================================" << endl;
	/* first, test without SSE */
	VCPU::mOSSSE = false;
	ftime(&tp_start);
	for (unsigned int i = 0; i < nIters; i++)
	{
		vTmp.Cross(vec1, vec2);
	}
	ftime(&tp_end);
	tm_diff_sec = tp_end.time - tp_start.time;
	tm_diff_ms  = tp_end.millitm - tp_start.millitm;
	cout << " WITHOUT SSE: " << tm_diff_sec << "secs " << tm_diff_ms << "ms" << endl;
	cout << "        vTmp: " << vTmp << endl;

	/* now, try with SSE */
	VCPU::mOSSSE = true;
	ftime(&tp_start);
	for (unsigned int i = 0; i < nIters; i++)
	{
		vTmp.Cross(vec1, vec2);
	}
	ftime(&tp_end);
	tm_diff_sec = tp_end.time - tp_start.time;
	tm_diff_ms  = tp_end.millitm - tp_start.millitm;
	cout << "    WITH SSE: " << tm_diff_sec << "secs " << tm_diff_ms << "ms" << endl;
	cout << "        vTmp: " << vTmp << endl << endl;
}
