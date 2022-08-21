#include "HudObserver.h"

#include "GameObject.h"
#include "HudComponent.h"

HudObserver::HudObserver(cycle::GameObject* hud)
	: m_pGameObject(hud)
{
	m_Type = ObserverType::HUD;
}

void HudObserver::OnNotify(const cycle::Event& message)
{
	switch(message.m_Event)
	{
	case cycle::GameEvent::ENEMY_KILLED:

		const int playerId{ std::stoi(message.m_Tag.substr(message.m_Tag.size() - 1, message.m_Tag.size())) };

		const auto hud{ m_pGameObject->GetComponent<HudComponent>() };

		m_pGameObject->GetComponent<HudComponent>()->UpdateScore(playerId, hud->GetLiveScore(playerId));
		break;
	}
}