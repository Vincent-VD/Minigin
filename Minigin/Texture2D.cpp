#include "MiniginPCH.h"
#include "Texture2D.h"

burger::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

SDL_Texture* burger::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

burger::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
}
