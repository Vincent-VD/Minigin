#include "TurretComponent.h"

TurretComponent::TurretComponent(cycle::GameObject* owner)
	: RootComponent(owner)
	, m_BarrelDir(1.f, 0.f)
{
	const auto pos{ owner->GetTransform()->GetPosition() };
	m_BarrelPos = { pos.x, pos.y };

}

void TurretComponent::Update()
{
	const auto comp{ m_pGameObject->GetComponent<cycle::InputComponent>()->GetRightStickValues() };

	const auto pos{ m_pGameObject->GetTransform()->GetPosition() };
	m_BarrelPos = { pos.x , pos.y  };

	if(abs(comp.first) > 0.001f || abs(comp.second) > 0.001f)
	{
		m_BarrelDir = vec2{ comp.first, -comp.second };
	}
}


std::pair<vec2, vec2> TurretComponent::GetBarrelDir() const
{
	const vec2 barrelEndPoint{ m_BarrelPos.x + m_BarrelDir.x * m_BarrelLength, m_BarrelPos.y + m_BarrelDir.y * m_BarrelLength };
	return { barrelEndPoint, m_BarrelDir};
}
