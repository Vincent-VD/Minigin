#pragma once
#include <iostream>

#include "Observer.h"

namespace cycle
{
	class GameLoopObserver final : public Observer
	{
	public:
		GameLoopObserver();
		virtual ~GameLoopObserver() override = default;
		GameLoopObserver(const GameLoopObserver& other) = delete;
		GameLoopObserver(GameLoopObserver&& other) noexcept = delete;
		GameLoopObserver& operator=(const GameLoopObserver& other) = delete;
		GameLoopObserver& operator=(GameLoopObserver&& other) noexcept = delete;

		virtual void OnNotify(const Event& message) override;

	private:
		int m_PlayerScore;
	};
}



