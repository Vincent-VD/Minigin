#include "XBoxController.h"
#include <Windows.h>
#include <Xinput.h>

#pragma comment(lib, "xinput.lib")

using namespace cycle;

class XBoxController::XBoxControllerImpl
{
public:
	XBoxControllerImpl(int controllerIdx)
		: m_ControllerIdx{ controllerIdx }
	{
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
	}

	~XBoxControllerImpl() = default;

	XBoxControllerImpl(const XBoxControllerImpl& other) = delete;
	XBoxControllerImpl(XBoxControllerImpl&& other) noexcept = delete;
	XBoxControllerImpl& operator=(const XBoxControllerImpl& other) = delete;
	XBoxControllerImpl& operator=(XBoxControllerImpl&& other) noexcept = delete;

	void Update()
	{
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(m_ControllerIdx, &m_CurrentState);

		auto buttons = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		m_ButtonsPressedThisFrame = buttons & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttons & (~m_CurrentState.Gamepad.wButtons);
	}

	bool IsHeldThisFrame(unsigned int button) const
	{
		return m_CurrentState.Gamepad.wButtons & button;
	}
	bool IsPressedThisFrame(unsigned int button) const
	{
		return m_ButtonsPressedThisFrame & button;
	}
	bool IsReleasedThisFrame(unsigned int button) const
	{
		return m_ButtonsReleasedThisFrame & button;
	}

	float GetLeftTriggerPressureThisFrame() const
	{
		float res{};
		const float leftTrigger = static_cast<float>(m_CurrentState.Gamepad.bLeftTrigger) / 255;
		if (leftTrigger > m_TriggerDZ)
		{
			res = m_CurrentState.Gamepad.bLeftTrigger;
		}
		return static_cast<float>(m_CurrentState.Gamepad.bLeftTrigger);
	}
	float GetRightTriggerPressureThisFrame() const
	{
		float res{};
		const float rightTrigger = static_cast<float>(m_CurrentState.Gamepad.bRightTrigger) / 255;
		if (rightTrigger > m_TriggerDZ)
		{
			res = m_CurrentState.Gamepad.bRightTrigger;
		}
		return res;
	}

	std::pair<float, float> GetLeftStickValuesThisFrame() const
	{
		float normLX = fmaxf(-1, static_cast<float>(m_CurrentState.Gamepad.sThumbLX) / 32767);
		float normLY = fmaxf(-1, static_cast<float>(m_CurrentState.Gamepad.sThumbLY) / 32767);
		float leftStickX = (abs(normLX) < m_TriggerDZ ? 0 : normLX);
		float leftStickY = (abs(normLY) < m_TriggerDZ ? 0 : normLY);
		return std::pair<float, float>{ leftStickX, leftStickY };
	}
	std::pair<float, float> GetRightStickValuesThisFrame() const
	{
		float normRX = fmaxf(-1, static_cast<float>(m_CurrentState.Gamepad.sThumbRX) / 32767);
		float normRY = fmaxf(-1, static_cast<float>(m_CurrentState.Gamepad.sThumbRY) / 32767);
		float rightStickX = (abs(normRX) < m_TriggerDZ ? 0 : normRX);
		float rightStickY = (abs(normRY) < m_TriggerDZ ? 0 : normRY);
		return std::pair<float, float>{ rightStickX, rightStickY };
	}

private:
	XINPUT_STATE m_CurrentState{};
	XINPUT_STATE m_PreviousState{};

	WORD m_ButtonsPressedThisFrame{};
	WORD m_ButtonsReleasedThisFrame{};

	int m_ControllerIdx;
	float m_TriggerDZ{ .05f }; //Trigger dead zone
	float m_AnalogueDZ{ .02f }; //Analogue stick dead zone
};

XBoxController::XBoxController(int controllerIdx)
	: m_pImpl(new XBoxControllerImpl(controllerIdx))
{

}

XBoxController::~XBoxController()
{
	delete m_pImpl;
}


void XBoxController::Update() const
{
	m_pImpl->Update();
}

bool XBoxController::IsHeld(ControllerButton button) const
{
	return m_pImpl->IsHeldThisFrame(static_cast<unsigned int>(button));
}

bool XBoxController::IsPressed(ControllerButton button) const
{
	return m_pImpl->IsPressedThisFrame(static_cast<unsigned int>(button));
}

bool XBoxController::IsReleased(ControllerButton button) const
{
	return m_pImpl->IsReleasedThisFrame(static_cast<unsigned int>(button));
}

float XBoxController::GetLeftTriggerPressure() const
{
	return m_pImpl->GetLeftTriggerPressureThisFrame();
}

float XBoxController::GetRightTriggerPressure() const
{
	return m_pImpl->GetRightTriggerPressureThisFrame();
}

std::pair<float, float> XBoxController::GetLeftStickValues() const
{
	return m_pImpl->GetLeftStickValuesThisFrame();
}

std::pair<float, float> XBoxController::GetRightStickValues() const
{
	return m_pImpl->GetRightStickValuesThisFrame();
}

