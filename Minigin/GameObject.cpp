#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

cycle::GameObject::GameObject(const std::vector<RootComponent*>& pComponents)
	: m_pTransform{ new TransformComponent{} }
	, m_pComponents{ pComponents }
	, m_pParent{ nullptr }
{
}

cycle::GameObject::~GameObject()
{
	//Remove all components when object is destroyed
	for (auto* pComponent : m_pComponents)
	{
		delete pComponent;
		pComponent = nullptr;
	}
	delete m_pTransform;
}

void cycle::GameObject::m_MarkForDeletion()
{
	m_MarkedForDeletion = true;
}

void cycle::GameObject::Update()
{
	//m_pTransform->SetPosition();
	for (auto* pComponent : m_pComponents)
	{
		pComponent->Update();
	}
}

void cycle::GameObject::FixedUpdate()
{
	for (auto* pComponent : m_pComponents)
	{
		pComponent->FixedUpdate();
	}
}


void cycle::GameObject::Render() const
{
	for (auto* pComponent : m_pComponents)
	{
		pComponent->Render();
	}
	//const auto& pos = m_pTransform->GetPosition();
	//Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

cycle::TransformComponent* cycle::GameObject::GetTransform() const
{
	return m_pTransform;
}

void cycle::GameObject::SetParent(GameObject* parent)
{
	m_pParent = parent;
	parent->AddChild(this);
	/*m_pTransform->SetPosition(m_pTransform->GetPosition() - parent->GetTransform()->GetPosition());
	m_pTransform->SetRotation(m_pTransform->GetRotation() - parent->GetTransform()->GetRotation());
	m_pTransform->SetScale(m_pTransform->GetScale() / parent->GetTransform()->GetScale());*/

	/*parent->AddChild(this); */
}

cycle::GameObject* cycle::GameObject::GetParent() const
{
	return m_pParent;
}

size_t cycle::GameObject::GetChildCount() const
{
	return m_pChildren.size();
}

cycle::GameObject* cycle::GameObject::GetChildAt(int index) const
{
	return m_pChildren[index];
}


void cycle::GameObject::RemoveChild(GameObject* obj)
{
	
	const int idx{ GetGOIndex(obj) };
	if(idx != -1)
	{
		m_pChildren.erase(m_pChildren.begin() + GetGOIndex(obj));
		obj->SetParent(nullptr);
	}
}

void cycle::GameObject::AddChild(GameObject* obj)
{
	if(m_pParent)
	{
		m_pParent->RemoveChild(this);
	}
	m_pChildren.push_back(obj);
}

int cycle::GameObject::GetGOIndex(const GameObject* obj) const
{
	for(int iter = 0; iter < m_pChildren.size(); ++iter)
	{
		if(m_pChildren[iter] == obj)
		{
			return iter;
		}
	}
	return -1;
}


//void cycle::GameObject::SetTexture(const std::string& filename)
//{
//	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
//}
//
//void cycle::GameObject::SetPosition(float x, float y)
//{
//	m_Transform.SetPosition(x, y, 0.0f);
//}
