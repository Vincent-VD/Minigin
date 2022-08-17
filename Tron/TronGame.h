#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Game.h"

namespace cycle
{
	class GameObject;
}

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

	std::vector<std::shared_ptr<cycle::GameObject>> ReadLevelFile(const std::string& filename) const;

};

