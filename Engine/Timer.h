#pragma once
class Timer
{
	DECLARE_SINGLE(Timer)

public:
	void Init();
	void Update();

	UINT32 GetFps() { return _fps; }
	float GetDeltaTime() { return _deltaTime; }
	float GetTotalTime() { return _TotalTime; }


private:
	UINT64	_frequency = 0;
	UINT64	_prevCount = 0;
	float	_deltaTime = 0.f;
	float	_TotalTime = 0.f;


private:
	UINT32	_frameCount = 0;
	float	_frameTime = 0.f;
	UINT32	_fps = 0;
};

