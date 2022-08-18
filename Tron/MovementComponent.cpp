#include "MovementComponent.h"

vec2::vec2()
	: x{0.f}
	, y{0.f}
{
}


vec2::vec2(float x, float y)
	: x{x}
	, y{y}
{
}

MovementComponent::MovementComponent(cycle::GameObject* owner, float moveSpeed)
	: RootComponent(owner)
	, m_Dir(vec2{})
	, m_MoveSpeed(moveSpeed)
{
	
}

void MovementComponent::Update()
{
	glm::vec3 pos{ m_pGameObject->GetTransform()->GetPosition() };
	pos.x += m_Dir.x;
	pos.y += m_Dir.y;
	m_pGameObject->GetTransform()->SetPosition(pos.x, pos.y, 0.f);
	m_Dir = vec2{};
}

void MovementComponent::UpdateDir(const vec2& dir)
{
	m_Dir.x = dir.x * m_MoveSpeed;
	m_Dir.y = dir.y * m_MoveSpeed;
}

