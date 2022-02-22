#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

burger::GameObject::GameObject(const std::vector<RootComponent*>& pComponents)
	: m_pTransform{ new TransformComponent{} }
	, m_pComponents{ pComponents }
{

}

burger::GameObject::~GameObject()
{
	//Remove all components when object is destroyed
	for (auto* pComponent : m_pComponents)
	{
		delete pComponent;
		pComponent = nullptr;
	}
	delete m_pTransform;
}

void burger::GameObject::m_MarkForDeletion()
{
	m_MarkedForDeletion = true;
}

void burger::GameObject::Update()
{
	for (auto* pComponent : m_pComponents)
	{
		pComponent->Update();
	}
}

void burger::GameObject::Render() const
{
	for (auto* pComponent : m_pComponents)
	{
		pComponent->Render();
	}
	//const auto& pos = m_pTransform->GetPosition();
	//Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

burger::TransformComponent* burger::GameObject::GetTransform() const
{
	return m_pTransform;
}

void burger::GameObject::SetParent(GameObject* parent)
{
	m_pParent = parent;
}

burger::GameObject* burger::GameObject::GetParent() const
{
	return m_pParent;
}

size_t burger::GameObject::GetChildCount() const
{
	return m_pChildren.size();
}

burger::GameObject* burger::GameObject::GetChildAt(int index) const
{
	return m_pChildren[index];
}

void burger::GameObject::RemoveChild(int index)
{
	m_pChildren.erase(m_pChildren.begin() + index);
}

void burger::GameObject::AddChild(GameObject* obj)
{
	m_pChildren.push_back(obj);
}


//void burger::GameObject::SetTexture(const std::string& filename)
//{
//	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
//}
//
//void burger::GameObject::SetPosition(float x, float y)
//{
//	m_Transform.SetPosition(x, y, 0.0f);
//}
