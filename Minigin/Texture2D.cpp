#include "MiniginPCH.h"
#include "Texture2D.h"

cycle::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

SDL_Texture* cycle::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

cycle::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
}
