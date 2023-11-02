#pragma once
#include "EngineResources/framework.h"

// Manages the time between each frame.
// Manages also the time when the app is paused.
// Provides fonction to implement slow motion.
class GameTimer
{
private:
	double mSecondsPerCount;
	double mDeltaTime;
	__int64 mBaseTime;
	__int64 mPausedTime;
	__int64 mStopTime;
	__int64 mPrevTime;
	__int64 mCurrTime;
	bool mStopped;

	double mSlowMoIndent;

public:
	GameTimer();
	~GameTimer() = default;

	float TotalTime() const; // in seconds

	float DeltaTime() const; // in seconds

	void Reset(); // Call before message loop.

	void Start(); // Call when unpaused.

	void Stop(); // Call when paused.

	void Tick(); // Call every frame.

	void SlowMotion(double slowMoIndent);

	float SlowMoIndent() const;

	void ResetSlowMo();

	void IndentSlowMo();
};