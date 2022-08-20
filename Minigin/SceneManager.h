#pragma once
#include "Singleton.h"

namespace cycle
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		Scene& GetCurrentScene() { return *m_CurrentScene; }

		void Update();
		void FixedUpdate();
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::shared_ptr<Scene> m_CurrentScene;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
	};
}
