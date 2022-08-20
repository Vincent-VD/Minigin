#include "MovementComponent.h"

#include <SDL_rect.h>
#include <SDL_render.h>

#include "BaseCollisionComponent.h"
#include "Minigin.h"
#include "Renderer.h"

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
	//std::cout << "can move\n";
	glm::vec3 pos{ m_pGameObject->GetTransform()->GetPosition() };
	pos.x += m_Dir.x;
	pos.y += m_Dir.y;
	pos.x = std::max(0.f, pos.x);
	//pos.x = std::min(cycle::g_WindowsInfo.m_Width, pos.x);
	pos.y = std::max(0.f, pos.y);
	//pos.y = std::max(cycle::g_WindowsInfo.m_Width, pos.y);

	if(!cycle::BaseCollisionComponent::CheckForCollision(Rectf{ pos.x, pos.y, 28, 28 }, "tile"))
	{
		m_pGameObject->GetTransform()->SetPosition(pos.x, pos.y, 0.f);
		m_Dir = vec2{};
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


void MovementComponent::UpdateDir(const vec2& dir)
{
	m_Dir.x = dir.x * m_MoveSpeed;
	m_Dir.y = dir.y * m_MoveSpeed;
}

