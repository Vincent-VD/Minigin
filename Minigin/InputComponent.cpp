#include "InputComponent.h"


using namespace cycle;

void InputComponent::ProcessInput()
{
	m_pController->Update();
	m_pKeyboard->Update();

	for (auto iter = m_CommandsMap.begin(); iter != m_CommandsMap.end(); ++iter)
	{
		switch (iter->second->m_InputType)
		{
		case Command::InputType::held:
			if (m_pController->IsHeld(static_cast<int>(iter->first)))
			{
				iter->second->Execute();
			}
			break;
		case Command::InputType::pressed:
			if (m_pController->IsPressed(static_cast<int>(iter->first)))
			{
				iter->second->Execute();
			}
			break;
		case Command::InputType::released:
			if (m_pController->IsReleased(static_cast<int>(iter->first)))
			{
				iter->second->Execute();
			}
			break;
		}
	}
}

bool InputComponent::IsPressed(XBoxController::ControllerButton button) const
{
	return m_pController->IsPressed(static_cast<int>(button));
}

bool InputComponent::IsHeld(XBoxController::ControllerButton button) const
{
	return m_pController->IsHeld(static_cast<int>(button));
}

bool InputComponent::IsReleased(XBoxController::ControllerButton button) const
{
	return m_pController->IsReleased(static_cast<int>(button));
}

void InputComponent::AddCommand(int /*key*/, XBoxController::ControllerButton button, std::unique_ptr<cycle::Command> command)
{

	m_CommandsMap[button] = std::move(command);
}

float InputComponent::GetLeftTriggerPressure() const
{
	if (m_pController)
	{
		return m_pController->GetLeftTriggerPressure();
	}
	std::cerr << "No controller connected, use keyboard input instead\n";
	return -1.f;
}

float InputComponent::GetRightTriggerPressure() const
{
	if (m_pController)
	{
		return m_pController->GetRightTriggerPressure();
	}
	std::cerr << "No controller connected, use keyboard input instead\n";
	return -1.f;
}

std::pair<float, float> InputComponent::GetLeftStickValues() const
{
	if (m_pController)
	{
		return m_pController->GetLeftStickValues();
	}
	std::cerr << "No controller connected, use keyboard input instead\n";
	return {};
}

std::pair<float, float> InputComponent::GetRightStickValues() const
{
	if (m_pController)
	{
		return m_pController->GetRightStickValues();
	}
	std::cerr << "No controller connected, use keyboard input instead\n";
	return {};
}


void InputComponent::Update()
{
	ProcessInput();
}

void InputComponent::FixedUpdate()
{
	
}




