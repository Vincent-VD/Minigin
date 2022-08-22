#include "HudComponent.h"

#include "ScoreComponent.h"

HudComponent::HudComponent(cycle::GameObject* owner, ScoreComponent* score1, ScoreComponent* score2, ScoreComponent* score3, ScoreComponent* score4)
	: RootComponent(owner)
	, m_ScoreComponent1(score1)
	, m_ScoreComponent2(score2)
	, m_ScoreComponent3(score3)
	, m_ScoreComponent4(score4)
{
	
}

void HudComponent::UpdateScore(const int playerId, const int score) const
{
	switch(playerId)
	{
	case 1:
		m_ScoreComponent2->UpdateScore(score);
		m_ScoreComponent1->ResetScore();
		break;
	case 2:
		m_ScoreComponent4->UpdateScore(score);
		m_ScoreComponent3->ResetScore();
		break;
	default:
		break;
	}
}

void HudComponent::ResetScore(const int playerId) const
{
	switch (playerId)
	{
	case 1:
		m_ScoreComponent1->ResetScore();
		break;
	case 2:
		m_ScoreComponent3->ResetScore();
		break;
	default:
		break;
	}
}

int HudComponent::GetLiveScore(int playerId) const
{

	switch (playerId)
	{
	case 1:
		return m_ScoreComponent1->GetLiveScore();
	case 2:
		return m_ScoreComponent3->GetLiveScore();
	default:
		return -1;
	}
}

int HudComponent::GetScore(int playerId) const
{
	switch (playerId)
	{
	case 1:
		return m_ScoreComponent1->GetScore();
	case 2:
		return m_ScoreComponent3->GetScore();
	default:
		return -1;
	}
}
