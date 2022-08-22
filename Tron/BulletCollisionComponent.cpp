#include "BulletCollisionComponent.h"

#include "BulletMoveComponent.h"

BulletCollisionComponent::BulletCollisionComponent(cycle::GameObject* owner, const std::string& spawner, float left, float bottom, float width, float height, bool isDynamic)
	: BaseCollisionComponent(owner, left, bottom, width, height, isDynamic)
	, m_Spawner(spawner)
{
}

void BulletCollisionComponent::OnCollision(BaseCollisionComponent* other)
{
	if(other->GetOwner()->GetTag() == "tile")
	{
		//Calculate reflection
		const Fvec2 bulletDir{ m_pGameObject->GetComponent<BulletMoveComponent>()->GetDir() };
		
		const Fvec2 edgeNormal{ CalculateTileNormal(bulletDir) };

		//Reflect
		const float dot{ bulletDir.x * edgeNormal.x + bulletDir.y * bulletDir.y };
		Fvec2 reflect;
		reflect.x = bulletDir.x - 2 * dot * edgeNormal.x;
		reflect.y = bulletDir.y - 2 * dot * edgeNormal.y;
		m_pGameObject->GetComponent<BulletMoveComponent>()->UpdateDir(reflect);


		//std::cout << "COLLISION with tile\n";

	}
}

Fvec2 BulletCollisionComponent::CalculateTileNormal(const Fvec2& bulletDir) const
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
