#include "MiniginPCH.h"
#include <SDL_ttf.h>
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

using namespace cycle;

TextComponent::TextComponent(GameObject* pOwner, const std::string& text, const std::shared_ptr<Font>& font)
	: RootComponent(pOwner)
	, m_NeedsUpdate(true), m_Text(text), m_Font(font), m_TextTexture(nullptr)
{
	
}

void TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_TextTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void TextComponent::FixedUpdate()
{
	
}


void TextComponent::Render() const
{
	if (m_TextTexture != nullptr)
	{
		const auto& pos = m_pGameObject->GetTransform()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_TextTexture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

//void TextComponent::SetPosition(const float x, const float y)
//{
//	//m_Transform.SetPosition(x, y, 0.0f);
//}


