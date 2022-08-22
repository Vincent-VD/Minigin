#pragma once
#include <BaseCollisionComponent.h>
class TileCollisionComponent : public cycle::BaseCollisionComponent
{
public:
	TileCollisionComponent(cycle::GameObject* pOwner, float left, float bottom, float width, float height, bool isDynamic);
	virtual ~TileCollisionComponent() override = default;
	TileCollisionComponent(const TileCollisionComponent& other) = delete;
	TileCollisionComponent(TileCollisionComponent&& other) noexcept = delete;
	TileCollisionComponent& operator=(const TileCollisionComponent& other) = delete;
	TileCollisionComponent& operator=(TileCollisionComponent&& other) noexcept = delete;

	virtual void OnCollision(BaseCollisionComponent* /*other*/) override {}
};

