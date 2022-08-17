#include "CollisionComponent.h"

#include "GameObject.h"
#include "TransformComponent.h"

using namespace cycle;

CollisionComponent::CollisionComponent(GameObject* owner, float left, float bottom, float width, float height, bool isDynamic)
	: RootComponent(owner)
	, m_Rect{left, bottom, width, height}
	, m_IsDynamic(isDynamic)
{
	
}

void CollisionComponent::Update()
{
	if(m_IsDynamic)
	{
		const glm::vec3 pos{ m_pGameObject->GetTransform()->GetPosition() };

		m_Rect.left = pos.x;
		m_Rect.bottom = pos.y;
	}
}

bool CollisionComponent::HandleCollision(const Rectf& actorShape) const
{
	// If one rectangle is on left side of the other
	if ((m_Rect.left + m_Rect.width) < actorShape.left || (actorShape.left + actorShape.width) < m_Rect.left)
	{
		return false;
	}

	// If one rectangle is under the other
	if (m_Rect.bottom > (actorShape.bottom + actorShape.height) || actorShape.bottom > (m_Rect.bottom + m_Rect.height))
	{
		return false;
	}

	return true;
}
