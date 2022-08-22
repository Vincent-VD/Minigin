#pragma once
#include <Singleton.h>
#include <vector>

namespace cycle
{
	class GameObject;
}

class PlayerManager :  public cycle::Singleton<PlayerManager>
{
public:

	void Init() {}
	void AddPlayer(cycle::GameObject* player);
	std::vector<cycle::GameObject*> GetPlayers() { return m_pPlayers; }

	virtual ~PlayerManager() override= default;
	PlayerManager(const PlayerManager& other) = delete;
	PlayerManager(PlayerManager&& other) noexcept = delete;
	PlayerManager& operator=(const PlayerManager& other) = delete;
	PlayerManager& operator=(PlayerManager&& other) noexcept = delete;


private:
	friend class Singleton<PlayerManager>;
	PlayerManager() = default;

	std::vector<cycle::GameObject*> m_pPlayers{};
};

