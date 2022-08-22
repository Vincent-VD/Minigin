#include "BaseCollisionComponent.h"

#include <iostream>
#include <SDL_render.h>

#include "GameObject.h"
#include "Renderer.h"
#include "TransformComponent.h"

using namespace cycle;

Rectf::Rectf()
	:Rectf{ 0.0f, 0.0f, 0.0f, 0.0f }
{
}

Rectf::Rectf(float left, float bottom, float width, float height)
	: left{ left }
	, bottom{ bottom }
	, width{ width }
	, height{ height }
{
}

void CollisionManager::Init()
{
	m_pCollisionComponents = std::vector<BaseCollisionComponent*>{};
}

void CollisionManager::AddCollision(BaseCollisionComponent* collision)
{
	m_pCollisionComponents.push_back(collision);
}

std::vector<BaseCollisionComponent*> CollisionManager::GetCollisions()
{
	return m_pCollisionComponents;
}

BaseCollisionComponent::BaseCollisionComponent(GameObject* owner, float left, float bottom, float width, float height, bool isDynamic)
	: RootComponent(owner)
	, m_Tag(owner->GetTag())
	, m_Rect{ Rectf{left, bottom, width, height} }
	, m_IsDynamic(isDynamic)
	, m_CollisionDetail("", Rectf{})
{
	CollisionManager::GetInstance().AddCollision(this);
	//std::cout << m_Tag << std::endl;
}

void BaseCollisionComponent::Update()
{
	CollisionDetail detail{};
	if(m_IsDynamic)
	{
		const glm::vec3 pos{ m_pGameObject->GetTransform()->GetPosition() };

		m_Rect.left = pos.x;
		m_Rect.bottom = pos.y;
	}

	//todo: optimization through distance interpolation

	for (BaseCollisionComponent* component : CollisionManager::GetInstance().GetCollisions())
	{
		if (HandleCollision(m_Rect, component->m_Rect, component->m_Tag) && !m_IsColliding)
		{
			detail.m_Tag = component->m_Tag;
			detail.m_CollisionThisFrame = true;
			detail.m_OtherRect = component->m_Rect;
			m_CollisionDetail = detail;
			OnCollision(component);
			m_IsColliding = true;
		}
		else
		{
			m_IsColliding = false;
		}
	}
	
}

void BaseCollisionComponent::Render() const 
{
	/*const SDL_Rect rect{ (int)m_Rect.left, (int)m_Rect.bottom, (int)m_Rect.width, (int)m_Rect.height };
	SDL_SetRenderDrawColor(cycle::Renderer::GetInstance().GetSDLRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawRect(cycle::Renderer::GetInstance().GetSDLRenderer(), &rect);
	SDL_SetRenderDrawColor(cycle::Renderer::GetInstance().GetSDLRenderer(), 0, 0, 0, 255);*/
}

bool BaseCollisionComponent::HandleCollision(const Rectf& rect1, const Rectf& rect2, const std::string& tag) const
{
	if(m_Tag == tag)
	{
		return false;
	}

	if(	rect1.left < rect2.left + rect2.width &&
		rect1.left + rect1.width > rect2.left &&
		rect1.bottom < rect2.bottom + rect2.height &&
		rect1.height + rect1.bottom > rect2.bottom)
	{
		return true;
	}
	return false;
}

//Checks if argument rectangle would collide with anything
//	Used for movement
bool BaseCollisionComponent::CheckForCollision(const Rectf& actorShape, const std::string& tag)
{
	const std::vector<BaseCollisionComponent*> components{ CollisionManager::GetInstance().GetCollisions() };

	for (const BaseCollisionComponent* component : components)
	{
		if (component->HandleCollision(actorShape, component->m_Rect, tag))
		{
			//std::cout << "FHJSDLF\n";
			return true;
		}
	}
	return false;
}
