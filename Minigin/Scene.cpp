#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace cycle;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::Update()
{
	for(auto& object : m_Objects)
	{
		object->Update();
	}
	for (size_t iter{}; iter < m_Objects.size(); ++iter)
	{
		if (m_Objects[iter]->IsMarkedForDeletion())
		{
			m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), m_Objects.at(iter)), m_Objects.end());
		}
	}
}

void Scene::FixedUpdate()
{
	for (auto& object : m_Objects)
	{
		object->FixedUpdate();
	}
}


void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

