#pragma once
#include "Singleton.h"

namespace cycle
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		Scene& GetCurrentScene() const { return *m_Scenes[m_CurrentScene]; }
		void NextScene();

		void Update();
		void FixedUpdate();
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		size_t m_CurrentScene {};
		std::vector<std::shared_ptr<Scene>> m_Scenes;
	};
}
