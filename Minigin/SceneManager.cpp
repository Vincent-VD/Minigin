#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

using namespace cycle;

void SceneManager::Update()
{
	m_Scenes[m_CurrentScene]->Update();
}

void SceneManager::FixedUpdate()
{
	m_Scenes[m_CurrentScene]->FixedUpdate();
}


void SceneManager::Render()
{
	m_Scenes[m_CurrentScene]->Render();
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	/*if(m_Scenes.size() == 1)
	{
		m_CurrentScene = scene;
	}*/
	return *scene;
}

void SceneManager::NextScene()
{
	++m_CurrentScene;
}
