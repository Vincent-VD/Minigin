#pragma once

namespace cycle
{
	class GameObject;

	class RootComponent
	{
	public:
		RootComponent(GameObject* pOwner);
		virtual ~RootComponent();

		RootComponent(const RootComponent& other) = delete;
		RootComponent(RootComponent&& other) = delete;
		RootComponent& operator=(const RootComponent& other) = delete;
		RootComponent& operator=(RootComponent&& other) = delete;

		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() const {}

		const GameObject* GetOwner() const { return m_pGameObject; }

	protected:
		GameObject* m_pGameObject;

	private:
	};
}

