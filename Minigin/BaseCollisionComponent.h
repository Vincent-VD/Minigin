#pragma once
#include <string>
#include <vector>

#include "RootComponent.h"
#include "Singleton.h"

struct Rectf
{
public:
	Rectf();
	explicit Rectf(float left, float bottom, float width, float height);

	float left;
	float bottom;
	float width;
	float height;

};

namespace cycle
{
	class BaseCollisionComponent;

	class CollisionManager final : public Singleton<CollisionManager>
	{
	public:

		void Init();
		void AddCollision(BaseCollisionComponent* collision);
		std::vector<BaseCollisionComponent*> GetCollisions();

		virtual ~CollisionManager() override = default;
		CollisionManager(const CollisionManager& other) = delete;
		CollisionManager(CollisionManager&& other) noexcept = delete;
		CollisionManager& operator=(const CollisionManager& other) = delete;
		CollisionManager& operator=(CollisionManager&& other) noexcept = delete;

	private:
		friend class Singleton<CollisionManager>;
		CollisionManager() = default;
		std::vector<BaseCollisionComponent*> m_pCollisionComponents;
	};

	class BaseCollisionComponent : public cycle::RootComponent
	{
	public:
		BaseCollisionComponent(GameObject* owner, const std::string& tag, float left, float bottom, float width, float height, bool isDynamic);
		virtual ~BaseCollisionComponent() override = default;
		BaseCollisionComponent(const BaseCollisionComponent& other) = delete;
		BaseCollisionComponent(BaseCollisionComponent&& other) noexcept = delete;
		BaseCollisionComponent& operator=(const BaseCollisionComponent& other) = delete;
		BaseCollisionComponent& operator=(BaseCollisionComponent&& other) noexcept = delete;

		virtual void Update() override;
		virtual void FixedUpdate() override {}
		void Render() const override;
		virtual void OnCollision() = 0;

		std::pair<float, float> GetCollisionBoxWidthAndHeight() { return {m_Rect.width, m_Rect.height}; }

		static bool CheckForCollision(const Rectf& actorShape, const std::string& tag);

		bool HasCollided() const { return m_CollisionDetail.m_CollisionThisFrame; }

	protected:

		struct CollisionDetail
		{
			CollisionDetail() = default;
			CollisionDetail(const std::string& tag, const Rectf& otherRect) : m_Tag(tag), m_OtherRect(otherRect) {}

			std::string m_Tag{};
			Rectf m_OtherRect{};
			bool m_CollisionThisFrame{ false };

		};

		Rectf m_Rect;
		const bool m_IsDynamic;

		std::string m_Tag;

		CollisionDetail m_CollisionDetail; //tag of object component collided with this frame

		//std::string GetTag() { return m_Tag; }
		 
		bool HandleCollision(const Rectf& rect1, const Rectf& rect2, const std::string& tag) const;

	};

}

