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



BaseCollisionComponent::BaseCollisionComponent(GameObject* owner, const std::string& tag, float left, float bottom, float width, float height, bool isDynamic)
	: RootComponent(owner)
	, m_Rect{ Rectf{left, bottom, width, height} }
	, m_IsDynamic(isDynamic)
	, m_Tag(tag)
	, m_CollisionDetail("")
{
	CollisionManager::GetInstance().AddCollision(this);
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
	const std::vector<BaseCollisionComponent*> components{ CollisionManager::GetInstance().GetCollisions() };

	for (const BaseCollisionComponent* component : components)
	{
		if (component->HandleCollision(m_Rect, component->m_Rect, m_Tag))
		{
			//std::cout << "FHJSDLF\n";
			detail.m_Tag = component->m_Tag;
			detail.m_CollisionThisFrame = true;
			m_CollisionDetail = detail;
			OnCollision();
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
	if(m_Tag != tag)
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
	//// If one rectangle is on left side of the other
	//if ((m_Rect.left + m_Rect.width) < actorShape.left || (actorShape.left + actorShape.width) < m_Rect.left)
	//{
	//	return false;
	//}

	//// If one rectangle is under the other
	//if (m_Rect.bottom > (actorShape.bottom + actorShape.height) || actorShape.bottom > (m_Rect.bottom + m_Rect.height))
	//{
	//	return false;
	//}

	//return true;
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
