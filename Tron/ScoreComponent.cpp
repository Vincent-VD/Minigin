#include "ScoreComponent.h"

#include <string>

#include "TextComponent.h"
#include "Timer.h"

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
