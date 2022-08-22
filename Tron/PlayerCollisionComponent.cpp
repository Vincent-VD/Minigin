#include "PlayerCollisionComponent.h"

#include "BulletCollisionComponent.h"
#include "GameObject.h"
#include "LifeComponent.h"
#include "MovementComponent.h"
#include "SpawnPointManager.h"
#include "Subject.h"

PlayerCollisionComponent::PlayerCollisionComponent(cycle::GameObject* owner, float left, float bottom, float width, float height, bool isDynamic)
	: BaseCollisionComponent(owner, left, bottom, width, height, isDynamic)
{
	
}

void PlayerCollisionComponent::OnCollision(BaseCollisionComponent* other)
{
	if(other->GetOwner()->GetTag() == "bullet")
	{
		const auto otherColl = dynamic_cast<BulletCollisionComponent*>(other);
		if (otherColl)
		{
			std::string bulletSpawner{ otherColl->GetSpawner() };
			const std::string tag{ m_pGameObject->GetTag() };
			if(bulletSpawner != tag)
			{
				const cycle::Event ev{ cycle::GameEvent::ENEMY_KILLED, nullptr, bulletSpawner };
				const auto subject{ m_pGameObject->GetComponent<cycle::Subject>() };
				if (subject)
				{
					subject->Notify(ev);
				}
				otherColl->HasCollided();
				const auto life{ m_pGameObject->GetComponent<LifeComponent>() };
				if (life)
				{
					life->Hit();
				}

				auto currPosVec3{ m_pGameObject->GetTransform()->GetPosition() };
				Fvec2 currPos{ currPosVec3.x, currPosVec3.y };
				const Fvec2 newPos{ SpawnPointManager::GetInstance().GetSpawnPoint(currPos) };
				m_pGameObject->GetTransform()->SetPosition(newPos.x, newPos.y, 0.f);
			}
		}
	}
}
