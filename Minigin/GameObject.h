#pragma once
#include "TransformComponent.h"
#include "SceneObject.h"
#include "RootComponent.h"

namespace burger
{
	class Texture2D;

	// todo: this should become final.
	class GameObject final : public SceneObject
	{
	public:
		GameObject(const std::vector<RootComponent*>& pComponents = {});
		virtual ~GameObject();
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
		void RemoveChild(int index);
		void AddChild(GameObject* obj);

	private:
		TransformComponent* m_pTransform;
		std::vector<RootComponent*> m_pComponents;
		std::vector<GameObject*> m_pChildren;
		GameObject* m_pParent;
		// todo: mmm, every gameobject has a texture? Is that correct?
		//std::shared_ptr<Texture2D> m_Texture; //Scheduled for deletion
		bool m_MarkedForDeletion{ false };
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
