#include "ScoreComponent.h"

#include <string>
#include <limits>

#include "HudComponent.h"
#include "PlayerManager.h"
#include "TextComponent.h"
#include "Timer.h"

void ScoreTally::Init(cycle::GameObject* hud)
{
	m_Hud = hud;
}


std::pair<int, int> ScoreTally::DecideWinner()
{
	auto players{ PlayerManager::GetInstance().GetPlayers() };

	for (auto* player : players)
	{
		const std::string playerTag{ player->GetTag() };
		const int playerId{ std::stoi(playerTag.substr(playerTag.size() - 1, playerTag.size())) };
		const int playerScore{ m_Hud->GetComponent<HudComponent>()->GetScore(playerId) };
		if(playerScore > m_WinningScore)
		{
			m_WinningScore = playerScore;
			m_WinningPlayerId = playerId;
		}
	}
	return {m_WinningScore, m_WinningPlayerId};
}

ScoreComponent::ScoreComponent(cycle::GameObject* owner, bool isLiveScore, int initScore, int scoreChangeFactor, cycle::TextComponent* textComponent)
	: RootComponent(owner)
	, m_IsLiveScore(isLiveScore)
	, m_CurrScore(initScore)
	, m_InitScore(initScore)
	, m_ScoreChangeFactor(scoreChangeFactor)
	, m_pTextComponent(textComponent)
{
	
}

void ScoreComponent::Update()
{
	if(m_IsLiveScore)
	{
		m_CurrTimer += cycle::Timer::GetInstance().GetDeltaTime();
		if(m_CurrTimer >= m_TimerLimit)
		{
			m_CurrScore -= m_ScoreChangeFactor;
			m_pTextComponent->SetText(std::to_string(m_CurrScore));
			m_CurrTimer = 0.f;
		}
	}
}

void ScoreComponent::UpdateScore(const int score)
{
	m_CurrScore += score;
	m_pTextComponent->SetText(std::to_string(m_CurrScore));
}

int ScoreComponent::GetLiveScore() const
{
	if(m_IsLiveScore)
	{
		return m_CurrScore;
	}
	return -1;
}
