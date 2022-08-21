#include "SpawnPointManager.h"
#include "MovementComponent.h"

void SpawnPointManager::Init(std::vector<Fvec2> spawnPoints)
{
	m_SpawnPoints = spawnPoints;
}

Fvec2 SpawnPointManager::GetSpawnPoint(const Fvec2& pos) const
{
	Fvec2 res{};
	float tempDist{ m_MinDistance };
	for (auto& spawnPoint : m_SpawnPoints)
	{
		const float dist{ std::powf(pos.x - spawnPoint.x, 2) + std::powf(pos.y - spawnPoint.y, 2) };
		if(dist <= tempDist)
		{
			res = spawnPoint;
			tempDist = dist;
		}

	}

	return res;
}
