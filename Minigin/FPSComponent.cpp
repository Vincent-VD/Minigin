#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "Timer.h"


burger::FPSComponent::FPSComponent()
{

}

burger::FPSComponent::~FPSComponent()
{
}

uint32_t burger::FPSComponent::GetFps() const
{
	return m_FPS;
}

void burger::FPSComponent::Update()
{
	if (!m_pText)
		m_pText = m_pGameObject->GetComponent<TextComponent>();

	m_ElapsedSec = Timer::GetInstance().GetElapsedSec();
	m_FPS = static_cast<int>(1.f / m_ElapsedSec);
	if (m_pText)
		m_pText->SetText("FPS: " + std::to_string(m_FPS));
}