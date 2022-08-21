#include "MovementComponent.h"

#include <SDL_rect.h>
#include <SDL_render.h>

#include "BaseCollisionComponent.h"
#include "Minigin.h"
#include "Renderer.h"

Fvec2::Fvec2()
	: x{0.f}
	, y{0.f}
{
}


Fvec2::Fvec2(float x, float y)
	: x{x}
	, y{y}
{
}

MovementComponent::MovementComponent(cycle::GameObject* owner, float moveSpeed)
	: RootComponent(owner)
	, m_Dir(Fvec2{})
	, m_MoveSpeed(moveSpeed)
{
	
}

void MovementComponent::Update()
{
	//std::cout << "can move\n";
	glm::vec3 pos{ m_pGameObject->GetTransform()->GetPosition() };
	pos.x += m_Dir.x;
	pos.y += m_Dir.y;
	pos.x = std::max(0.f, pos.x);
	pos.y = std::max(0.f, pos.y);

	if(!m_pGameObject->GetComponent<cycle::BaseCollisionComponent>()->CheckForCollision(Rectf{ pos.x, pos.y, 28, 28 }, m_pGameObject->GetTag()))
	{
		m_pGameObject->GetTransform()->SetPosition(pos.x, pos.y, 0.f);
		m_Dir = Fvec2{};
	}

}

void MovementComponent::Render() const
{
	/*glm::vec3 pos{ m_pGameObject->GetTransform()->GetPosition() };
	const SDL_Rect rect{ (int)pos.x, (int)pos.y, 28, 28 };
	SDL_SetRenderDrawColor(cycle::Renderer::GetInstance().GetSDLRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawRect(cycle::Renderer::GetInstance().GetSDLRenderer(), &rect);
	SDL_SetRenderDrawColor(cycle::Renderer::GetInstance().GetSDLRenderer(), 0, 0, 0, 255);*/
}


void MovementComponent::UpdateDir(const Fvec2& dir)
{
	m_Dir.x = dir.x * m_MoveSpeed;
	m_Dir.y = dir.y * m_MoveSpeed;
}

