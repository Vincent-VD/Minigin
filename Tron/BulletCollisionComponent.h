#pragma once
#include <BaseCollisionComponent.h>
class BulletCollisionComponent : public cycle::BaseCollisionComponent
{
public:
	BulletCollisionComponent(cycle::GameObject* owner, const std::string& tag, float left, float bottom, float width, float height, bool isDynamic = true);
	virtual ~BulletCollisionComponent() override= default;
	BulletCollisionComponent(const BulletCollisionComponent& other) = delete;
	BulletCollisionComponent(BulletCollisionComponent&& other) noexcept = delete;
	BulletCollisionComponent& operator=(const BulletCollisionComponent& other) = delete;
	BulletCollisionComponent& operator=(BulletCollisionComponent&& other) noexcept = delete;

	virtual void OnCollision() override;
};

