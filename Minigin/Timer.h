#pragma once
#include <iostream>
#include <SDL.h>
#include "Singleton.h"

namespace Engine
{
	class Timer final : public dae::Singleton<Timer>
	{
	public:
		void Init();
		//tatic Timer* GetInstance();
		//~Timer() = default;
		//static void CleanUp();

		void Reset();
		void Start();
		void Update();
		void Stop();

		uint32_t GetFPS() const { return m_FPS; };
		float GetElapsedSec() const { return m_ElapsedSec; };
		float GetTotal() const { return m_TotalTime; };

	private:
		//static Timer* m_Instance;

		//runtime counters
		uint64_t m_BaseTime{};
		uint64_t m_PausedTime{};
		uint64_t m_StopTime{};
		uint64_t m_PreviousTime{};
		uint64_t m_CurrentTime{};

		//user values
		uint32_t m_FPS{};
		uint32_t m_FPSCount{};
		float m_TotalTime{};
		float m_CountsPerSecond{};
		float m_FrameTimeLimit;
		float m_ElapsedSec{};
		float m_FPSTimer{};
		const float m_FrameRateTarget{ 60.f };

		bool m_IsPaused{ true };
		bool m_IsVSyncEnabled{ true };
	};

}