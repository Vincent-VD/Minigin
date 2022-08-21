#pragma once
#include <BaseCollisionComponent.h>

class PlayerCollisionComponent : public cycle::BaseCollisionComponent
{
public:
	PlayerCollisionComponent(cycle::GameObject* owner, float left, float bottom, float width, float height, bool isDynamic = true);
	virtual ~PlayerCollisionComponent() override = default;
	PlayerCollisionComponent(const PlayerCollisionComponent& other) = delete;
	PlayerCollisionComponent(PlayerCollisionComponent&& other) noexcept = delete;
	PlayerCollisionComponent& operator=(const PlayerCollisionComponent& other) = delete;
	PlayerCollisionComponent& operator=(PlayerCollisionComponent&& other) noexcept = delete;

	virtual void OnCollision(BaseCollisionComponent* other) override;
};

