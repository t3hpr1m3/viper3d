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
#ifdef PROFILER
#include <cstdio>
#include <cassert>
#include <iostream>
#include <viper3d/VProfiler.h>

using std::cout;
using std::endl;

int VProfileSample::mLastOpenedSample = -1;
int VProfileSample::mOpenSampleCount = 0;
VProfileSample::VSample VProfileSample::mSamples[MAX_PROFILER_SAMPLES];
double VProfileSample::mRootBegin=0.0f;
double VProfileSample::mRootEnd=0.0f;
bool VProfileSample::mProfilerIsRunning=true;
struct timeval VProfileSample::mStartTime;
bool VProfileSample::mTimeSet = false;

VProfileSample::VProfileSample(std::string pSampleName)
{
	if(!mProfilerIsRunning)
		return;
	//find the sample
	int i = 0;
	int vStoreIndex = -1;
	for (i = 0; i < MAX_PROFILER_SAMPLES; ++i)
	{
		if (!mSamples[i].mIsValid)
		{
			//cout << "Invalid sample" << endl;
			if (vStoreIndex < 0)
				vStoreIndex = i;
		}
		else
		{
			if (mSamples[i].mName == pSampleName)
			{
				//cout << "Found matching sample" << endl;
				//this is the sample we want
				//check that it's not already open
				assert(!mSamples[i].mIsOpen && "Tried to profile a sample which was already being profiled");
				//first, store it's index
				mSampleIndex = i;
				//the parent sample is the last opened sample
				mParentIndex = mLastOpenedSample;
				mLastOpenedSample = i;
				mSamples[i].mParentCount = mOpenSampleCount;
				++mOpenSampleCount;
				mSamples[i].mIsOpen=true;
				++mSamples[i].mCallCount;
				mSamples[i].mStartTime = GetTime();
				//if this has no parent, it must be the 'main loop' sample, so do the global timer
				if (mParentIndex < 0)
					mRootBegin = mSamples[i].mStartTime;
				return;
			}
		}
	}
	//we've not found it, so it must be a new sample
	//use the storeIndex value to store the new sample
	assert(vStoreIndex >= 0 && "Profiler has run out of sample slots!");
	mSamples[vStoreIndex].mIsValid = true;
	mSamples[vStoreIndex].mName = pSampleName;
	mSampleIndex = vStoreIndex;
	mParentIndex = mLastOpenedSample;
	mLastOpenedSample = vStoreIndex;
	mSamples[i].mParentCount = mOpenSampleCount;
	mOpenSampleCount++;
	mSamples[vStoreIndex].mIsOpen = true;
	mSamples[vStoreIndex].mCallCount = 1;

	mSamples[vStoreIndex].mTotalTime = 0.0f;
	mSamples[vStoreIndex].mChildTime = 0.0f;
	mSamples[vStoreIndex].mStartTime = GetTime();
	if (mParentIndex < 0)
		mRootBegin = mSamples[vStoreIndex].mStartTime;
}

VProfileSample::~VProfileSample()
{
	if (!mProfilerIsRunning)
		return;

	double vEndTime = GetTime();

	//phew... ok, we're done timing
	mSamples[mSampleIndex].mIsOpen = false;

	//calculate the time taken this profile, for ease of use later on
	double vTimeTaken = vEndTime - mSamples[mSampleIndex].mStartTime;

	if (mParentIndex >= 0)
	{
		mSamples[mParentIndex].mChildTime += vTimeTaken;
	}
	else
	{
		//no parent, so this is the end of the main loop sample
		mRootEnd = vEndTime;
	}

	mSamples[mSampleIndex].mTotalTime += vTimeTaken;
	mLastOpenedSample = mParentIndex;
	--mOpenSampleCount;
}

void VProfileSample::Output()
{
	char vNamebuf[256], vIndentedName[256];
	char vAvg[16], vMin[16], vMax[16], vNum[16], vTime[16];

	if(!mProfilerIsRunning)
		return;

	cout << endl;
	cout << "          New Profile Set" << endl;
	cout << "  Min :   Avg :   Max :   # : Total : Profile Name" << endl;
	cout << "--------------------------------------------" << endl;
	/*cout << "rootBegin => [" << mRootBegin << "]" << endl;
	cout << "rootEnd   => [" << mRootEnd << "]" << endl << endl;*/

	for (int i=0; i < MAX_PROFILER_SAMPLES; ++i)
	{
		if(mSamples[i].mIsValid)
		{
			/*cout << "  ** " << mSamples[i].mName.c_str() << " **" << endl;
			cout << "parentCount: " << mSamples[i].mParentCount << endl;
			cout << "averagePc: " << mSamples[i].mAveragePc << endl;
			cout << "minPc:     " << mSamples[i].mMinPc << endl;
			cout << "maxPc:     " << mSamples[i].mMaxPc << endl;
			cout << "totalTime: " << mSamples[i].mTotalTime << endl;
			cout << "childTime: " << mSamples[i].mChildTime << endl;
			cout << "dataCount: " << mSamples[i].mDataCount << endl;
			cout << "callCount: " << mSamples[i].mCallCount << endl;*/
			float vSampleTime, vPercentage;
			//calculate the time spend on the sample itself (excluding children)
			vSampleTime = mSamples[i].mTotalTime - mSamples[i].mChildTime;
			vPercentage = ( vSampleTime / ( mRootEnd - mRootBegin ) ) * 100.0f;

			//add it to the sample's values
			float vTotalPc;
			vTotalPc = mSamples[i].mAveragePc * mSamples[i].mDataCount;
			vTotalPc += vPercentage;
			mSamples[i].mDataCount++;
			mSamples[i].mAveragePc = vTotalPc / mSamples[i].mDataCount;
			if ((mSamples[i].mMinPc == -1) || (vPercentage < mSamples[i].mMinPc))
				mSamples[i].mMinPc = vPercentage;
			if ((mSamples[i].mMaxPc == -1) || (vPercentage > mSamples[i].mMaxPc))
				mSamples[i].mMaxPc = vPercentage;

			sprintf(vAvg, "%3.1f", mSamples[i].mAveragePc);
			sprintf(vMin, "%3.1f", mSamples[i].mMinPc);
			sprintf(vMax, "%3.1f", mSamples[i].mMaxPc);
			sprintf(vTime,"%3.1f", vSampleTime);
			sprintf(vNum, "%3d",   mSamples[i].mCallCount);
			sprintf(vIndentedName, "%*.*s%s", mSamples[i].mParentCount, mSamples[i].mParentCount, " ", mSamples[i].mName.c_str());

			sprintf(vNamebuf, "%5.5s : %5.5s : %5.5s : %5.5s : %5.5f : %s", vMin, vAvg, vMax, vNum, vSampleTime, vIndentedName);
			cout << vNamebuf << endl;

			//output these values
/*			outputHandler->Sample(samples[i].minPc,
					      samples[i].averagePc,
					      samples[i].maxPc,
					      sampleTime,
					      samples[i].callCount,
					      samples[i].name,
					      samples[i].parentCount);*/

			//reset the sample for next time
			mSamples[i].mCallCount = 0;
			mSamples[i].mTotalTime = 0;
			mSamples[i].mChildTime = 0;
		}
	}

	//outputHandler->EndOutput();
}

void VProfileSample::ResetSample(std::string pName)
{
	for (int i=0; i < MAX_PROFILER_SAMPLES; ++i)
	{
		if((mSamples[i].mIsValid) && (mSamples[i].mName == pName))
		{
			//found it
			//reset avg/min/max ONLY
			//because the sample may be running
			mSamples[i].mMaxPc = mSamples[i].mMinPc = -1;
			mSamples[i].mDataCount = 0;
			return;
		}
	}
}	

void VProfileSample::ResetAll()
{
	for (int i=0; i < MAX_PROFILER_SAMPLES; ++i)
	{
		if(mSamples[i].mIsValid)
		{
			mSamples[i].mMaxPc = mSamples[i].mMinPc=-1;
			mSamples[i].mDataCount=0;
			if(!mSamples[i].mIsOpen)
				mSamples[i].mIsValid=false;
		}
	}
}

double VProfileSample::GetTime()
	{
		struct timeval tv;
		struct timezone tz;
		double oldTime = 0.0f;
		double newTime = 0.0f;
		double timeDiff = 0.0f;
		struct timespec req;
		gettimeofday(&tv, &tz);
		if (mTimeSet == false)
		{
			mTimeSet = true;
			req.tv_sec = 0;
			req.tv_nsec = 1;
			//nanosleep(&req, NULL);
			mStartTime.tv_sec = tv.tv_sec;
			mStartTime.tv_usec = tv.tv_usec;
			gettimeofday(&tv, &tz);
		}

		oldTime = (double)mStartTime.tv_sec + (double)mStartTime.tv_usec/(1000*1000);
		newTime = (double)tv.tv_sec + (double)tv.tv_usec/(1000*1000);
		//cout << "oldTime: " << oldTime << ", newTime: " << newTime << endl;
		timeDiff = newTime - oldTime;

		return timeDiff;
	}
#endif
