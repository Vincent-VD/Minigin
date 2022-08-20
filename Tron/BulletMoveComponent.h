#pragma once
#include <RootComponent.h>

#include "InputComponent.h"

std::shared_ptr<cycle::GameObject*> CreateBullet(float x, float y);

class BulletMoveComponent : public cycle::RootComponent
{
public:
	BulletMoveComponent(cycle::GameObject* owner);
	virtual ~BulletMoveComponent() override = default;
	BulletMoveComponent(const BulletMoveComponent& other) = delete;
	BulletMoveComponent(BulletMoveComponent&& other) noexcept = delete;
	BulletMoveComponent& operator=(const BulletMoveComponent& other) = delete;
	BulletMoveComponent& operator=(BulletMoveComponent&& other) noexcept = delete;

	virtual void Update() override;
	virtual void FixedUpdate() override {}
};

class FireBullet : public cycle::Command
{
public:
	FireBullet(InputType type, const cycle::InputComponent* input)
		: Command(type, input)
	{
	}
	virtual void Execute() override
	{
		std::cout << "PLACEHOLDER BULLET CODE\n";
		CreateBullet(0, 0);
	}
};