#pragma once
#include "RootComponent.h"
#include "GameObject.h"

namespace burger
{
	class TextComponent;

	class FPSComponent final : public RootComponent
	{
	public:
		FPSComponent();
		virtual ~FPSComponent();

		uint32_t GetFps() const;
		void Update() override;
	private:
		float m_ElapsedSec{};
		uint32_t m_FPS{};
		TextComponent* m_pText = nullptr;
	};

}