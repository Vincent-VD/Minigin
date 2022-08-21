#pragma once
#include <vector>

#include "Singleton.h"

struct Fvec2;

class SpawnPointManager : public cycle::Singleton<SpawnPointManager>
{
public:

	void Init(std::vector<Fvec2> spawnPoints);

	Fvec2 GetSpawnPoint(const Fvec2& pos) const;

	virtual ~SpawnPointManager() override = default;
	SpawnPointManager(const SpawnPointManager& other) = delete;
	SpawnPointManager(SpawnPointManager&& other) noexcept = delete;
	SpawnPointManager& operator=(const SpawnPointManager& other) = delete;
	SpawnPointManager& operator=(SpawnPointManager&& other) noexcept = delete;

private:
	friend class Singleton<SpawnPointManager>;
	SpawnPointManager() = default;

	std::vector<Fvec2> m_SpawnPoints{};

	const float m_MinDistance{ 1000.f };

};

