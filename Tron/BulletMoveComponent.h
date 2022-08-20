#pragma once
#include <RootComponent.h>

#include "InputComponent.h"
#include "MovementComponent.h"
#include "TurretComponent.h"

void CreateBullet(float posX, float posY, float dirX, float dirY);

class BulletMoveComponent : public cycle::RootComponent
{
public:
	BulletMoveComponent(cycle::GameObject* owner, float dirX, float dirY);
	virtual ~BulletMoveComponent() override = default;
	BulletMoveComponent(const BulletMoveComponent& other) = delete;
	BulletMoveComponent(BulletMoveComponent&& other) noexcept = delete;
	BulletMoveComponent& operator=(const BulletMoveComponent& other) = delete;
	BulletMoveComponent& operator=(BulletMoveComponent&& other) noexcept = delete;

	virtual void Update() override;
	virtual void FixedUpdate() override {}

	vec2 GetDir() const { return m_Dir; }

	void UpdateDir(const vec2& dir);

private:
	vec2 m_Dir;

	const float m_MoveSpeed;

	int m_Lives{ 5 };
};

class FireBullet : public cycle::Command
{
public:
	FireBullet(InputType type, const cycle::InputComponent* input)
		: Command(type, input)
	{
	}
	virtual void Execute() override;
	
};