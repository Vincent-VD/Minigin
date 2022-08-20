#include "BulletMoveComponent.h"

#include "BaseCollisionComponent.h"
#include "BulletCollisionComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextureComponent2D.h"

BulletMoveComponent::BulletMoveComponent(cycle::GameObject* owner, float dirX, float dirY)
	: RootComponent(owner)
	, m_Dir(dirX, dirY)
	, m_MoveSpeed(1.7f)
{
}

void BulletMoveComponent::Update()
{
	glm::vec3 pos{ m_pGameObject->GetTransform()->GetPosition() };
	pos.x += m_Dir.x;
	pos.y += m_Dir.y;
	pos.x = std::max(0.f, pos.x);
	//pos.x = std::min(cycle::g_WindowsInfo.m_Width, pos.x);
	pos.y = std::max(0.f, pos.y);
	//pos.y = std::max(cycle::g_WindowsInfo.m_Width, pos.y);
	m_pGameObject->GetTransform()->SetPosition(pos.x, pos.y, 0.f);
	//m_Dir = vec2{};
}

void BulletMoveComponent::UpdateDir(const vec2& dir)
{
	m_Dir.x = dir.x * m_MoveSpeed;
	m_Dir.y = dir.y * m_MoveSpeed;
	--m_Lives;
}

void CreateBullet(float posX, float posY, float dirX, float dirY)
{
	std::shared_ptr<cycle::GameObject> go = std::make_shared<cycle::GameObject>();

	cycle::TextureComponent2D* textureComp{ new cycle::TextureComponent2D{go.get(), "bullet.png", posX, posY, 16.f, 16.f, true}};
	BulletMoveComponent* moveComponent{ new BulletMoveComponent{go.get(), dirX, dirY}};
	BulletCollisionComponent* collisionComponent{ new BulletCollisionComponent{go.get(), "bullet", posX, posY, 16.f, 16.f} }; 

	go->GetTransform()->SetPosition(posX, posY, 0.f);
	go->AddComponent(textureComp);
	go->AddComponent(moveComponent);
	go->AddComponent(collisionComponent);

	auto& scene = cycle::SceneManager::GetInstance().GetCurrentScene();

	scene.Add(go);
}

void FireBullet::Execute()
{
	std::cout << "PLACEHOLDER BULLET CODE\n";

	const auto barrelInfo{ m_Input->GetOwner()->GetComponent<TurretComponent>()->GetBarrelDir() };

	/*const auto& ownerPos{ m_Input->GetOwner()->GetTransform()->GetPosition() };

	const vec2 bulletSpawnPos{ ownerPos.x + barrelInfo.second * barrelInfo.first.x, ownerPos.y + barrelInfo.second * barrelInfo.first.y };*/

	CreateBullet(barrelInfo.first.x, barrelInfo.first.y, barrelInfo.second.x, barrelInfo.second.y);
}
