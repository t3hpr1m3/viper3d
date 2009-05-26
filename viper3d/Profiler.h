/*============================================================================*
 *                                                                            *
 * 	This file is part of the Viper3D Game Engine.							  *
 *                                                                            *
 *	Copyright (C) 2004 UDP Games   All Rights Reserved.						  *
 *                                                                            *
 *============================================================================*
 *                                  CHANGELOG                                 *
 *    Date      Description                                     Author        *
 * -----------  ----------------------------------------------	------------- *
 *                                                                            *
 *============================================================================*/
#if !defined(__VPROFILER_H_INCLUDED__)
#define __VPROFILER_H_INCLUDED__

#ifdef PROFILER
#include <string>
#include <sys/time.h>
#define MAX_PROFILER_SAMPLES 50
#include <iostream>


class VProfileSample;

class VProfileSample
{
public:
	VProfileSample(std::string pSampleName);
	~VProfileSample();

	static void Output();

	static void ResetSample(std::string pName);
	static void ResetAll();

	static bool mProfilerIsRunning;

protected:
	//index into the array of samples
	int			mSampleIndex;
	int			mParentIndex;

	double		GetTime();

	static struct VSample
	{
		VSample()
		{
			mIsValid=false; 
			mDataCount=0;
			mAveragePc = mMinPc = mMaxPc = -1;
		}

		bool		mIsValid;		//whether or not this sample is valid (for use with fixed-size arrays)
		bool		mIsOpen;		//is this sample currently being profiled?
		unsigned int mCallCount;	//number of times this sample has been profiled this frame
		std::string	mName;	//name of the sample
		
		double mStartTime;	//starting time on the clock, in seconds
		double mTotalTime;	//total time recorded across all profiles of this sample
		double mChildTime;	//total time taken by children of this sample

		int mParentCount;	//number of parents this sample has (useful for indenting)

		float mAveragePc;	//average percentage of game loop time taken up
		float mMinPc;		//minimum percentage of game loop time taken up
		float mMaxPc;		//maximum percentage of game loop time taken up
		unsigned long mDataCount;//number of percentage values that have been stored
	} mSamples[MAX_PROFILER_SAMPLES];

	static int mLastOpenedSample;
	static int mOpenSampleCount;
	static double mRootBegin, mRootEnd;
	static struct timeval mStartTime;
	static bool mTimeSet;
};

#define PROFILE(name) VProfileSample _profile_sample(name);
#define PROFILE_OUTPUT() VProfileSample::Output()
#else
#define PROFILE(name)
#define PROFILE_OUTPUT()
#endif

#endif // __VPROFILER_H_INCLUDED__
