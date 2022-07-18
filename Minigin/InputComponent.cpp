#include "InputComponent.h"

using namespace cycle;

void InputComponent::ProcessInput()
{
	m_pController->Update();

	for (auto iter = m_CommandsMap.begin(); iter != m_CommandsMap.end(); ++iter)
	{
		switch (iter->second->m_InputType)
		{
		case Command::InputType::held:
			if (m_pController->IsHeld(iter->first))
			{
				iter->second->Execute();
			}
			break;
		case Command::InputType::pressed:
			if (m_pController->IsPressed(iter->first))
			{
				iter->second->Execute();
			}
			break;
		case Command::InputType::released:
			if (m_pController->IsReleased(iter->first))
			{
				iter->second->Execute();
			}
			break;
		}
	}
}

bool InputComponent::IsPressed(XBoxController::ControllerButton button) const
{
	return m_pController->IsPressed(button);
}

bool InputComponent::IsHeld(XBoxController::ControllerButton button) const
{
	return m_pController->IsHeld(button);
}

bool InputComponent::IsReleased(XBoxController::ControllerButton button) const
{
	return m_pController->IsReleased(button);
}

void InputComponent::AddCommand(XBoxController::ControllerButton button, std::unique_ptr<cycle::Command> command)
{
	m_CommandsMap[button] = std::move(command);
}

void InputComponent::Update()
{
	ProcessInput();
}

void InputComponent::FixedUpdate()
{
	
}

