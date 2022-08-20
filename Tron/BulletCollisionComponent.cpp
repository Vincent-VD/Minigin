#include "BulletCollisionComponent.h"

#include "BulletMoveComponent.h"
#include "MovementComponent.h"

BulletCollisionComponent::BulletCollisionComponent(cycle::GameObject* owner, const std::string& tag, float left, float bottom, float width, float height, bool isDynamic)
	: BaseCollisionComponent(owner, tag, left, bottom, width, height, isDynamic)
{
}

void BulletCollisionComponent::OnCollision()
{
	if(m_CollisionDetail.m_Tag == "tile")
	{
		//Calculate reflection
		vec2 edgeNormal{};
		const vec2 bulletDir{ m_pGameObject->GetComponent<BulletMoveComponent>()->GetDir() };
		
		if (bulletDir.x < m_CollisionDetail.m_OtherRect.left) //Left
		{
			edgeNormal = vec2{ -1.f, 0.f };
		}

		if ((m_CollisionDetail.m_OtherRect.left + m_CollisionDetail.m_OtherRect.width) < bulletDir.x) //Right
		{
			edgeNormal = vec2{ 1.f, 0.f };
		}
		
		if (bulletDir.y > (m_CollisionDetail.m_OtherRect.bottom + m_CollisionDetail.m_OtherRect.height)) //Above
		{
			edgeNormal = vec2{ 0.f, 1.f };
		}

		if (m_CollisionDetail.m_OtherRect.bottom > (m_Rect.bottom + m_Rect.height)) //Below
		{
			edgeNormal = vec2{ 0.f, -1.f };
		}

		//Reflect

		std::cout << "COLLISION with tile\n";

	}

	if(m_CollisionDetail.m_Tag == "Player")
	{
		std::cout << "COLLISION with player\n";
	}
}

