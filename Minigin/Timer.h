#pragma once
#include <iostream>
#include <SDL.h>

namespace Engine
{
	class Timer
	{
	public:
		static Timer* GetInstance();
		~Timer() = default;
		static void CleanUp();

		void Reset();
		void Start();
		void Update();
		void Stop();

		uint32_t GetFPS() const { return m_FPS; };
		float GetElapsedSec() const { return m_ElapsedSec; };
		float GetTotal() const { return m_TotalTime; };

	private:
		Timer();
		~Timer() = default;

		static Timer* m_Instance;

		//runtime counters
		uint64_t m_BaseTime = 0;
		uint64_t m_PausedTime = 0;
		uint64_t m_StopTime = 0;
		uint64_t m_PreviousTime = 0;
		uint64_t m_CurrentTime = 0;

		//user values
		uint32_t m_FPS = 0;
		uint32_t m_FPSCount = 0;
		float m_TotalTime = 0.f;
		float m_SecondsPerCount = 0.f;
		float m_ElapsedSec = 0.f;
		float m_FPSTimer = 0.f;

		bool m_IsPaused{ true };
	};

}