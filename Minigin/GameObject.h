#pragma once
#include <string>
#include <vector>
#include "TransformComponent.h"
#include "SceneObject.h"
#include "RootComponent.h"

namespace cycle
{
	class Texture2D;

	class GameObject final : public SceneObject
	{
	public:
		GameObject(const std::string& tag, const std::vector<RootComponent*>& pComponents = {});
		virtual ~GameObject() override;
		void m_MarkForDeletion();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		//Getters
		TransformComponent* GetTransform() const;
		std::string GetTag() const { return m_Tag; }

		//Setters
		//void SetTexture(const std::string& filename);
		//void SetPosition(float x, float y);

		//Template component funtions
		template<typename Component>
		Component* GetComponent() const;
		template<typename Component>
		Component* AddComponent(Component* pComponent);
		template<typename Component>
		void RemoveComponent(Component* pComponent);

		void SetParent(GameObject* parent);
		GameObject* GetParent() const;

		size_t GetChildCount() const;
		GameObject* GetChildAt(int index) const;

	private:
		TransformComponent* m_pTransform;
		std::vector<RootComponent*> m_pComponents;
		std::vector<GameObject*> m_pChildren;
		GameObject* m_pParent;
		
		const std::string m_Tag;

		void RemoveChild(GameObject* obj);
		void AddChild(GameObject* obj);

		int GetGOIndex(const GameObject* obj) const;
	};

	template<typename Component>
	inline Component* GameObject::GetComponent() const
	{
		for (auto* component : m_pComponents)
		{
			Component* curr = dynamic_cast<Component*>(component);
			if (curr)
			{
				return curr;
			}
		}
		return nullptr;
	}

	template<typename Component>
	inline Component* GameObject::AddComponent(Component* component)
	{
		m_pComponents.push_back(component);
		return component;
	}

	template <typename Component>
	inline void GameObject::RemoveComponent(Component* pComponent)
	{
		std::remove_if(m_pComponents.begin, m_pComponents.end(), []<bool>(auto * component) { dynamic_cast<Component*>(component) != nullptr; });
	}
}
