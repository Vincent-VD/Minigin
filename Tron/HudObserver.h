#pragma once
#include "Observer.h"

class HudObserver : public cycle::Observer
{
public:
	HudObserver(cycle::GameObject* hud);
	virtual ~HudObserver() override = default;
	HudObserver(const HudObserver& other) = delete;
	HudObserver(HudObserver&& other) noexcept = delete;
	HudObserver& operator=(const HudObserver& other) = delete;
	HudObserver& operator=(HudObserver&& other) noexcept = delete;

	virtual void OnNotify(const cycle::Event& message) override;

private:
	cycle::GameObject* m_pGameObject;
};

