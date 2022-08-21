#include "BulletCollisionComponent.h"

#include "BulletMoveComponent.h"

BulletCollisionComponent::BulletCollisionComponent(cycle::GameObject* owner, const std::string& tag, float left, float bottom, float width, float height, bool isDynamic)
	: BaseCollisionComponent(owner, tag, left, bottom, width, height, isDynamic)
{
}

void BulletCollisionComponent::OnCollision()
{
	if(m_CollisionDetail.m_Tag == "tile")
	{
		//Calculate reflection
		
		const vec2 bulletDir{ m_pGameObject->GetComponent<BulletMoveComponent>()->GetDir() };
		
		const vec2 edgeNormal{ CalculateTileNormal(bulletDir) };

		//Reflect
		vec2 reflect;
		const float dot{ bulletDir.x * edgeNormal.x + bulletDir.y * bulletDir.y };
		if(dot < 0.75f)
		{
			reflect.x = bulletDir.x - 2 * dot * edgeNormal.x;
			reflect.y = bulletDir.y - 2 * dot * edgeNormal.y;
			m_pGameObject->GetComponent<BulletMoveComponent>()->UpdateDir(reflect);
		}
		else
		{
			m_pGameObject->m_MarkForDeletion();
		}


		//std::cout << "COLLISION with tile\n";

	}

	if(m_CollisionDetail.m_Tag == "Player")
	{
		//std::cout << "COLLISION with player\n";
	}
}

vec2 BulletCollisionComponent::CalculateTileNormal(const vec2& bulletDir) const
{
	if (bulletDir.x < m_CollisionDetail.m_OtherRect.left) //Left
	{
		return { 1.f, 0.f };
	}

	if ((m_CollisionDetail.m_OtherRect.left + m_CollisionDetail.m_OtherRect.width) < bulletDir.x) //Right
	{
		return { -1.f, 0.f };
	}

	if (bulletDir.y < (m_CollisionDetail.m_OtherRect.bottom + m_CollisionDetail.m_OtherRect.height)) //Above
	{
		return { 0.f, -1.f };
	}

	if (m_CollisionDetail.m_OtherRect.bottom > bulletDir.y) //Below
	{
		return { 0.f, 1.f };
	}


	return {};
}
