#include "TextureComponent2D.h"

#include <SDL_render.h>

#include "GameObject.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"

namespace cycle
{
	TextureComponent2D::TextureComponent2D(cycle::GameObject* owner, const std::string& filename, float left, float bottom, float width, float height, bool isDynamic)
		: RootComponent(owner)
		, m_Rect(left, bottom, width, height)
		, m_IsDynamic(isDynamic)
	{
		m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
	}

	void TextureComponent2D::Update()
	{
		if (m_IsDynamic)
		{
			const glm::vec3 pos{ m_pGameObject->GetTransform()->GetPosition() };

			m_Rect.left = pos.x;
			m_Rect.bottom = pos.y;
		}
	}

	void TextureComponent2D::Render() const
	{
		cycle::Renderer::GetInstance().RenderTexture(*m_pTexture, m_Rect.left, m_Rect.bottom, m_Rect.width, m_Rect.height);
	}

	std::pair<float, float> TextureComponent2D::GetTextureDimensions() const
	{
		int width{}, height{};
		SDL_QueryTexture(m_pTexture->GetSDLTexture(), nullptr, nullptr, &width, &height);
		return { width, height };
	}


}

