#pragma once
#include <utility>

#include "RootComponent.h"
#include "Singleton.h"


namespace cycle
{
	class TextComponent;
}

class ScoreTally : public cycle::Singleton<ScoreTally>
{
public:

	void Init(cycle::GameObject* hud);
	std::pair<int, int> DecideWinner();

	virtual ~ScoreTally() override = default;
	ScoreTally(const ScoreTally& other) = delete;
	ScoreTally(ScoreTally&& other) noexcept = delete;
	ScoreTally& operator=(const ScoreTally& other) = delete;
	ScoreTally& operator=(ScoreTally&& other) noexcept = delete;

private:
	friend class Singleton<ScoreTally>;
	ScoreTally() = default;

	cycle::GameObject* m_Hud{};

	int m_WinningScore{};
	int m_WinningPlayerId{};

};

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
	int GetScore() const { return m_CurrScore; }

private:
	bool m_IsLiveScore;

	int m_CurrScore;
	int m_InitScore;
	const int m_ScoreChangeFactor;

	float m_CurrTimer{};
	const float m_TimerLimit{ 2.f };

	cycle::TextComponent* m_pTextComponent;


};

