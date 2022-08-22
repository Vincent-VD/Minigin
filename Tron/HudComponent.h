#pragma once
#include <RootComponent.h>
class ScoreComponent;

class HudComponent :  public cycle::RootComponent
{
public:
	HudComponent(cycle::GameObject* owner, ScoreComponent* score1, ScoreComponent* score2, ScoreComponent* score3, ScoreComponent* score4);
	virtual ~HudComponent() override = default;
	HudComponent(const HudComponent& other) = delete;
	HudComponent(HudComponent&& other) noexcept = delete;
	HudComponent& operator=(const HudComponent& other) = delete;
	HudComponent& operator=(HudComponent&& other) noexcept = delete;

	virtual void Update() override {}
	virtual void FixedUpdate() override {}

	void UpdateScore(const int playerId, const int score) const;
	void ResetScore(const int playerId) const;

	int GetLiveScore(int playerId) const;
	int GetScore(int playerId) const;

private:
	ScoreComponent* m_ScoreComponent1;
	ScoreComponent* m_ScoreComponent2;
	ScoreComponent* m_ScoreComponent3;
	ScoreComponent* m_ScoreComponent4;
};

