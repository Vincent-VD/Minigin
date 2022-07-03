#include "MiniginPCH.h"
#include "TransformComponent.h"

using namespace cycle;

void TransformComponent::SetPosition(glm::vec3 newPos)
{
	SetPosition(newPos.x, newPos.y, newPos.z);
}


void TransformComponent::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void TransformComponent::SetRotation(glm::vec3 newRot)
{
	SetRotation(newRot.x, newRot.y, newRot.z);
}


void TransformComponent::SetRotation(float x, float y, float z)
{
	m_Rotation.x = x;
	m_Rotation.y = y;
	m_Rotation.z = z;
}

void TransformComponent::SetScale(glm::vec3 newScale)
{
	SetScale(newScale.x, newScale.y, newScale.z);
}


void TransformComponent::SetScale(float x, float y, float z)
{
	m_Scale.x = x;
	m_Scale.y = y;
	m_Scale.z = z;
}