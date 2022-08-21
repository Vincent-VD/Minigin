#pragma once
#include <BaseCollisionComponent.h>

#include "MovementComponent.h"

class BulletCollisionComponent : public cycle::BaseCollisionComponent
{
public:
	BulletCollisionComponent(cycle::GameObject* owner, const std::string& spawner, float left, float bottom, float width, float height, bool isDynamic = true);
	virtual ~BulletCollisionComponent() override= default;
	BulletCollisionComponent(const BulletCollisionComponent& other) = delete;
	BulletCollisionComponent(BulletCollisionComponent&& other) noexcept = delete;
	BulletCollisionComponent& operator=(const BulletCollisionComponent& other) = delete;
	BulletCollisionComponent& operator=(BulletCollisionComponent&& other) noexcept = delete;

	virtual void OnCollision(BaseCollisionComponent* other) override;

	Fvec2 CalculateTileNormal(const Fvec2& bulletDir) const;

	std::string GetSpawner() const { return m_Spawner; }

	void HasCollided() { m_pGameObject->m_MarkForDeletion(); }

private:
	const std::string m_Spawner;

	bool m_HasCollided{ false };

};

