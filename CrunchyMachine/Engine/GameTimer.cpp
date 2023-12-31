#include "GameTimer.h"

GameTimer::GameTimer() : mSecondsPerCount(0.0), mDeltaTime(-1.0), mBaseTime(0),
mPausedTime(0), mPrevTime(0), mCurrTime(0), mStopTime(0), mStopped(false), mSlowMoIndent(0)
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	mSecondsPerCount = 1.0 / (double)countsPerSec;
}

float GameTimer::TotalTime() const
{
	if (mStopped)
	{
		return (float)(((mStopTime - mPausedTime) -
			mBaseTime) * mSecondsPerCount);
	}
	else
	{
		return (float)(((mCurrTime - mPausedTime) -
			mBaseTime) * mSecondsPerCount);
	}
}

float GameTimer::DeltaTime() const { return (float)mDeltaTime; }

void GameTimer::Reset()
{
	__int64 currTime;

	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	mBaseTime = currTime;
	mPrevTime = currTime;
	mStopTime = 0;
	mStopped = false;
}

void GameTimer::Start()
{
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

	if (mStopped)
	{
		// then accumulate the paused time.
		mPausedTime += (startTime - mStopTime);
		// since we are starting the timer back up, the current
		// previous time is not valid, as it occurred while paused.
		// So reset it to the current time.
		mPrevTime = startTime;
		// no longer stopped...
		mStopTime = 0;
		mStopped = false;
	}
}

void GameTimer::Stop()
{
	// If we are already stopped, then don�t do anything.
	if (!mStopped)
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
		// Otherwise, save the time we stopped at, and set
		// the Boolean flag indicating the timer is stopped.
		mStopTime = currTime;
		mStopped = true;
	}
}

void GameTimer::Tick()
{
	if (mStopped)
	{
		mDeltaTime = 0.0;
		return;
	}
	// Get the time this frame.
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	mCurrTime = currTime;
	// Time difference between this frame and the previous.
	mDeltaTime = (mCurrTime - mPrevTime) * mSecondsPerCount;
	// Prepare for next frame.
	mPrevTime = mCurrTime;
	// Force nonnegative. The DXSDK�s CDXUTTimer mentions that if the
	// processor goes into a power save mode or we get shuffled to
	// another processor, then mDeltaTime can be negative.
	if (mDeltaTime < 0.0)
		mDeltaTime = 0.0;
}

void GameTimer::SlowMotion(double slowMoIndent)
{
	if (slowMoIndent < 3)
		mDeltaTime *= slowMoIndent * 0.225f + 0.1f;
}

float GameTimer::SlowMoIndent() const { return (float)mSlowMoIndent; }

void GameTimer::ResetSlowMo() { mSlowMoIndent = 0; }

void GameTimer::IndentSlowMo() { mSlowMoIndent += mDeltaTime; }