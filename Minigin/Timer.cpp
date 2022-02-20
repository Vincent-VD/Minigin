#include "MiniginPCH.h"
#include "Timer.h"
#include <chrono>


namespace Engine
{

	/*Timer* Timer::GetInstance()
	{
		if (m_Instance == nullptr)
		{
			m_Instance = new Timer{};
		}
		return m_Instance;
	}

	void Timer::CleanUp()
	{
		delete m_Instance;
	}*/

	void Timer::Init()
	{
		m_CountsPerSecond = (float)SDL_GetPerformanceFrequency();
		m_FrameTimeLimit = MSTOS / m_FrameRateTarget;
	}

	void Timer::Reset()
	{
		uint64_t currentTime{ SDL_GetPerformanceCounter() };
		m_BaseTime = currentTime;
		m_PreviousTime = currentTime;
		m_StopTime = 0;
		m_FPSTimer = 0.f;
		m_FPSCount = 0;
		m_IsPaused = true;
	}

	void Timer::Start()
	{

	}

	void Timer::Update()
	{
		Uint32 currentTime;
		currentTime = SDL_GetTicks();

		m_ElapsedSec = (float)currentTime - m_PreviousTime; // in ms
		m_PreviousTime = currentTime;

		if (m_IsVSyncEnabled && m_ElapsedSec > m_FrameTimeLimit)
		{
			m_ElapsedSec = m_FrameTimeLimit;
		}

		m_FPSTimer += m_ElapsedSec;
		++m_FPSCount;
		if (m_FPSTimer >= MSTOS)
		{
			m_FPS = m_FPSCount;
			m_FPSCount = 0;
			m_FPSTimer -= MSTOS;
		}

		//if (m_IsPaused)
		//{
		//	m_FPS = 0;
		//	m_ElapsedSec = 0.0f;
		//	m_TotalTime = (float)(((m_StopTime - m_PausedTime) - m_BaseTime) * m_BaseTime);
		//	return;
		//}

		//uint64_t currentTime = SDL_GetPerformanceCounter();
		//m_CurrentTime = currentTime;

		//m_ElapsedSec = (float)((m_CurrentTime - m_PreviousTime) * m_SecondsPerCount);
		//m_PreviousTime = m_CurrentTime;

		//if (m_ElapsedSec < 0.0f)
		//{
		//	m_ElapsedSec = 0.0f;
		//}

		//m_TotalTime = (float)(((m_CurrentTime - m_PausedTime) - m_BaseTime) * m_SecondsPerCount);

		////FPS LOGIC
		//m_FPSTimer += m_ElapsedSec;
		//++m_FPSCount;
		//if (m_FPSTimer >= 1.0f)
		//{
		//	m_FPS = m_FPSCount;
		//	m_FPSCount = 0;
		//	m_FPSTimer -= 1.0f;
		//}
	}

	void Timer::Stop()
	{
		
	}
}