#pragma once
#include "glm/vec3.hpp"
namespace cycle
{
	class TransformComponent final
	{
	public:
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(glm::vec3 newPos);
		void SetPosition(float x, float y, float z);

		const glm::vec3& GetRotation() const { return m_Rotation; }
		void SetRotation(glm::vec3 newRot);
		void SetRotation(float x, float y, float z);

		const glm::vec3& GetScale() const { return m_Scale; }
		void SetScale(glm::vec3 newScale);
		void SetScale(float x, float y, float z);

	private:
		glm::vec3 m_Position{};
		glm::vec3 m_Rotation{};
		glm::vec3 m_Scale{};
	};
}
