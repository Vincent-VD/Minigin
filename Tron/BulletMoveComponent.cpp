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
	//pos.x = std::max(0.f, pos.x);
	//pos.x = std::min(cycle::g_WindowsInfo.m_Width, pos.x);
	//pos.y = std::max(0.f, pos.y);
	//pos.y = std::max(cycle::g_WindowsInfo.m_Width, pos.y);
	m_pGameObject->GetTransform()->SetPosition(pos.x, pos.y, 0.f);
	//m_Dir = Fvec2{};
}

void BulletMoveComponent::UpdateDir(const Fvec2& dir)
{
	std::cout << "Updating bullet Dir: " << dir.x << " " << dir.y << std::endl;
	m_Dir.x = std::min(m_MoveSpeed, dir.x);
	m_Dir.y = std::min(m_MoveSpeed, dir.y);
	--m_Lives;
	if(m_Lives < 0)
	{
		m_pGameObject->m_MarkForDeletion();
	}
}

void CreateBullet(float posX, float posY, float dirX, float dirY, const std::string& spawner)
{
	std::shared_ptr<cycle::GameObject> go = std::make_shared<cycle::GameObject>("bullet");

	cycle::TextureComponent2D* textureComp{ new cycle::TextureComponent2D{go.get(), "bullet.png", posX, posY, 16.f, 16.f, true}};
	BulletMoveComponent* moveComponent{ new BulletMoveComponent{go.get(), dirX, dirY}};
	BulletCollisionComponent* collisionComponent{ new BulletCollisionComponent{go.get(), spawner, posX, posY, 16.f, 16.f} };

	go->GetTransform()->SetPosition(posX, posY, 0.f);
	go->AddComponent(textureComp);

	go->AddComponent(moveComponent);
	go->AddComponent(collisionComponent);
	auto& scene = cycle::SceneManager::GetInstance().GetCurrentScene();

	scene.Add(go);
}

void FireBullet::Execute()
{
	const auto barrelInfo{ m_Input->GetOwner()->GetComponent<TurretComponent>()->GetBarrelDir() };

	PlaySound();

	CreateBullet(barrelInfo.first.x, barrelInfo.first.y, barrelInfo.second.x, barrelInfo.second.y, m_Input->GetOwner()->GetTag());
}
