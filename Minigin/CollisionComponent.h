#pragma once
#include "RootComponent.h"

struct Point2f
{
	Point2f();
	explicit Point2f(float x, float y);

	float x;
	float y;
};



struct Rectf
{
	Rectf();
	explicit Rectf(const Point2f& point, float width, float height);
	explicit Rectf(float left, float bottom, float width, float height);

	float left;
	float bottom;
	float width;
	float height;

};

namespace cycle
{
	class CollisionComponent : public cycle::RootComponent
	{
	public:
		CollisionComponent(GameObject* owner, float left, float bottom, float width, float height, bool isDynamic);
		~CollisionComponent() override = default;
		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent(CollisionComponent&& other) noexcept = delete;
		CollisionComponent& operator=(const CollisionComponent& other) = delete;
		CollisionComponent& operator=(CollisionComponent&& other) noexcept = delete;

		virtual void Update() override;
		virtual void FixedUpdate() override {}

		bool HandleCollision(const Rectf& actorShape) const;

	private:
		Rectf m_Rect;
		const bool m_IsDynamic;
	};

}

