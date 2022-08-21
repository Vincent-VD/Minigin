#pragma once
#include <RootComponent.h>
class LifeComponent : public cycle::RootComponent
{
public:
	LifeComponent(cycle::GameObject* pOwner);
	virtual ~LifeComponent() override= default;
	LifeComponent(const LifeComponent& other) = delete;
	LifeComponent(LifeComponent&& other) noexcept = delete;
	LifeComponent& operator=(const LifeComponent& other) = delete;
	LifeComponent& operator=(LifeComponent&& other) noexcept = delete;

	virtual void Update() override {}
	virtual void FixedUpdate() override {}

	void Hit();

private:
	int m_Lives{ 3 };


};

