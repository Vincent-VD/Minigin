#pragma once

namespace burger
{
	class GameObject;

	class RootComponent
	{
	public:
		RootComponent();
		virtual ~RootComponent();

		RootComponent(const RootComponent& other) = delete;
		RootComponent(RootComponent&& other) = delete;
		RootComponent& operator=(const RootComponent& other) = delete;
		RootComponent& operator=(RootComponent&& other) = delete;

		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() const {};
		void SetOwner(GameObject* pOwner) { m_pGameObject = pOwner; }

	protected:
		GameObject* m_pGameObject;

	private:
	};
}

