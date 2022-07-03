#pragma once
#include "GameObject.h"
#include "TransformComponent.h"
#include "RootComponent.h"

namespace cycle
{
	class Font;
	class Texture2D;
	class TextComponent final : public RootComponent
	{
	public:
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);

		explicit TextComponent(const std::string& text, const std::shared_ptr<Font>& font);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		TransformComponent m_Transform;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_TextTexture;
	};
}
