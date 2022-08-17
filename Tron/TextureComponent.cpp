#include "TextureComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "Texture2D.h"

namespace cycle
{
	TextureComponent::TextureComponent(cycle::GameObject* owner, cycle::Texture2D* texture, float left, float bottom, float width, float height, bool isDynamic)
		: RootComponent(owner)
		, m_pTexture(texture)
		, m_Rect(left, bottom, width, height)
		, m_IsDynamic(isDynamic)
	{
	}

	TextureComponent::~TextureComponent()
	{
		delete m_pTexture;
	}

	void TextureComponent::Update()
	{
		if (m_IsDynamic)
		{
			const glm::vec3 pos{ m_pGameObject->GetTransform()->GetPosition() };

			m_Rect.left = pos.x;
			m_Rect.bottom = pos.y;
		}
	}

	void TextureComponent::Render() const
	{
		cycle::Renderer::GetInstance().RenderTexture(*m_pTexture, m_Rect.left, m_Rect.bottom, m_Rect.width, m_Rect.height);
	}


}

