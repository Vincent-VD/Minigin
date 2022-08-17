#pragma once
#include "Game.h"

class TronGame : public cycle::Game
{
public:
	TronGame() = default;
	~TronGame() override = default;
	TronGame(const TronGame& other) = delete;
	TronGame(TronGame&& other) noexcept = delete;
	TronGame& operator=(const TronGame& other) = delete;
	TronGame& operator=(TronGame&& other) noexcept = delete;

	virtual void LoadGame() const override;

	

};

