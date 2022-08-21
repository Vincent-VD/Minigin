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
		break;
	case 2:
		m_ScoreComponent4->UpdateScore(score);
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
