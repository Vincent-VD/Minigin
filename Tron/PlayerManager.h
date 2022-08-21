#pragma once
#include <Singleton.h>

namespace cycle
{
	class GameObject;
}

class PlayerManager :  public cycle::Singleton<PlayerManager>
{
public:

	void Init();
	void AddPlayer(cycle::GameObject* player);


	PlayerManager() = default;
	~PlayerManager() = default;
	PlayerManager(const PlayerManager& other) = delete;
	PlayerManager(PlayerManager&& other) noexcept = delete;
	PlayerManager& operator=(const PlayerManager& other) = delete;
	PlayerManager& operator=(PlayerManager&& other) noexcept = delete;


};

