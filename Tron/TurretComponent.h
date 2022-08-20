#pragma once
#include <RootComponent.h>

#include "MovementComponent.h"

class TurretComponent :  public cycle::RootComponent
{
public:
	TurretComponent(cycle::GameObject* owner);
	virtual ~TurretComponent() override = default;
	TurretComponent(const TurretComponent& other) = delete;
	TurretComponent(TurretComponent&& other) noexcept = delete;
	TurretComponent& operator=(const TurretComponent& other) = delete;
	TurretComponent& operator=(TurretComponent&& other) noexcept = delete;

	virtual void Update() override;
	virtual void FixedUpdate() override {}

	std::pair<vec2, vec2> GetBarrelDir() const;

private:
	vec2 m_BarrelPos{};
	vec2 m_BarrelDir{};

	const float m_BarrelLength{ 10.f };

};

