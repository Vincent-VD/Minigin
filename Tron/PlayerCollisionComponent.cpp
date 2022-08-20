#include "PlayerCollisionComponent.h"

#include "GameObject.h"
#include "MovementComponent.h"

PlayerCollisionComponent::PlayerCollisionComponent(cycle::GameObject* owner, const std::string& tag, float left, float bottom, float width, float height, bool isDynamic)
	: BaseCollisionComponent(owner, tag, left, bottom, width, height, isDynamic)
{
	
}

void PlayerCollisionComponent::OnCollision()
{
	/*if(m_Tag != m_CollisionDetail.m_Tag && m_Tag != "tile")
	{
		std::cout << "COLLISION:" << m_Tag << " - " << m_CollisionDetail.m_Tag << std::endl;
		auto comp{ m_pGameObject->GetComponent<MovementComponent>() };
		if(comp)
		{
			comp->UpdateDir(vec2{});
		}
	}*/
}
