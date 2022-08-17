#pragma once
#include ""

#include "Root"

namespace cycle
{
	class GameObject;
	class Texture2D;
}

namespace Tron
{
	class TextureComponent : public cycle::RootComponent
	{
	public:
		TextureComponent(cycle::GameObject* owner, cycle::Texture2D* texture, float left, float bottom, float width, float height, bool isDynamic);
		virtual ~TextureComponent() override;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) noexcept = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) noexcept = delete;

		virtual void Update() override;
		virtual void FixedUpdate() override {}
		void Render() const override;

	private:
		cycle::Texture2D* m_pTexture;
		Rectf m_Rect;
		const bool m_IsDynamic;
	};

}

