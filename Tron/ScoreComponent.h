#pragma once
#include "RootComponent.h"


namespace cycle
{
	class TextComponent;
}

class ScoreComponent : public cycle::RootComponent
{
public:
	ScoreComponent(cycle::GameObject* owner, bool isLiveScore, int initScore, int scoreChangeFactor, cycle::TextComponent* textComponent);
	virtual ~ScoreComponent() override = default;
	ScoreComponent(const ScoreComponent& other) = delete;
	ScoreComponent(ScoreComponent&& other) noexcept = delete;
	ScoreComponent& operator=(const ScoreComponent& other) = delete;
	ScoreComponent& operator=(ScoreComponent&& other) noexcept = delete;

	virtual void Update() override;
	virtual void FixedUpdate() override {}

	void UpdateScore(const int score);

	void ResetScore() { m_CurrScore = m_InitScore; }

	int GetLiveScore() const;

private:
	bool m_IsLiveScore;

	int m_CurrScore;
	int m_InitScore;
	const int m_ScoreChangeFactor;

	float m_CurrTimer{};
	const float m_TimerLimit{ 2.f };

	cycle::TextComponent* m_pTextComponent;


};

