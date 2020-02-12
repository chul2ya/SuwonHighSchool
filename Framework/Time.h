#pragma once
class Time : public SingleInstance<Time>
{
private:
	int tempFPS = 0;
	DWORD prevFPS;
	DWORD prevTime;

	//�߰���
	//extra2

public:
	int FPS = 0;
	float deltaTime = 0.0f;

	void Tick()
	{
		auto curTime = timeGetTime();

		static bool isFirstUpdate = true;
		if (!isFirstUpdate)
		{
			deltaTime = (curTime - prevTime) / 1000.f;
		}
		tempFPS++;
		if (prevFPS + 1000 <= curTime) {
			FPS = tempFPS;
			tempFPS = 0;
			prevFPS = curTime;
		}
		isFirstUpdate = false;
		prevTime = timeGetTime();
	}
};

