#pragma once
namespace cycle
{
	class SceneObject
	{
	public:
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() const = 0;
		void MarkForDeletion() { m_MarkedForDeletion = true; }
		bool IsMarkedForDeletion() { return m_MarkedForDeletion; }

		SceneObject() = default;
		virtual ~SceneObject() = default;
		SceneObject(const SceneObject& other) = delete;
		SceneObject(SceneObject&& other) = delete;
		SceneObject& operator=(const SceneObject& other) = delete;
		SceneObject& operator=(SceneObject&& other) = delete;

	private:
		bool m_MarkedForDeletion{ false };
	};
}
