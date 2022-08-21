#include "GameLoopObserver.h"

#include <iostream>

#include "GameObject.h"
#include "Observer.h"

cycle::GameLoopObserver::GameLoopObserver()
	: m_PlayerScore{ 0 }
{
	m_Type = ObserverType::GameLoopObserver;
}


void cycle::GameLoopObserver::OnNotify(const Event& message)
{
	switch (message.m_Event)
	{
	case GameEvent::ENEMY_KILLED:
		++m_PlayerScore;
		std::cout << "Kills: " << m_PlayerScore << std::endl;
		break;

	}
}