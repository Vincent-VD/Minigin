#pragma once

namespace cycle
{

	class Game
	{
	public:
		Game() = default;
		virtual ~Game() = default;
		Game(const Game& other) = delete;
		Game(Game&& other) noexcept = delete;
		Game& operator=(const Game& other) = delete;
		Game& operator=(Game&& other) noexcept = delete;

		virtual void LoadGame() const = 0;

	};

}