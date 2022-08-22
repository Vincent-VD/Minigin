#include "LifeComponent.h"

#include <iostream>

#include "AudioManager.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "TextComponent.h"
#include "TronGame.h"

LifeComponent::LifeComponent(cycle::GameObject* pOwner)
	: RootComponent(pOwner)
{
}

void LifeComponent::Hit()
{
	--m_Lives;

	if(m_Lives == 0)
	{
		std::cout << "DEAD\n";
		cycle::AudioManager::GetInstance().PlayAudio(cycle::SoundDesc{ cycle::SoundId::death, 0.7f });
		TronGame::LoadEnd();
	}
}


