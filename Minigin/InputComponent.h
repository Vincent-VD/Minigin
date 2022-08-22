#pragma once
#include <iostream>
#include <map>
#include <thread>
#include <utility>

#include "AudioManager.h"
#include "Keyboard.h"
#include "RootComponent.h"
#include "XBoxController.h"

namespace cycle
{
	class InputComponent;

	class Command
	{
	public:
		enum class InputType
		{
			pressed = 0,
			held = 1,
			released = 2
		};
		Command(InputType type, const InputComponent* input = nullptr) : m_InputType{ type }, m_Input(input) {}
		virtual ~Command() = default;
		Command(const Command& other) = delete;
		Command(Command&& other) noexcept = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) noexcept = delete;

		InputType m_InputType;
		
		virtual void Execute() = 0;
	protected:
		const InputComponent* m_Input;
	};

	/*class Test final : public Command
	{
	public:
		Test(InputType type, const InputComponent* input = nullptr) : Command(type, input) {}
		void Execute() override
		{
			AudioManager& audioManager{ AudioManager::GetInstance() };
			audioManager.PlayAudio(SoundDesc{ SoundId::ram, 1.f });
		}
	};*/

	class InputComponent final : public RootComponent
	{
	public:
		InputComponent(GameObject* pOwner, int playerId)
			: RootComponent(pOwner)
			, m_pController{ new XBoxController(playerId) }
			, m_pKeyboard( new Keyboard() )
		{
		}

		virtual ~InputComponent() override
		{
			m_CommandsMap.clear();
			delete m_pController;
			delete m_pKeyboard;
		}

		InputComponent(const InputComponent& other) = delete;
		InputComponent(InputComponent&& other) noexcept = delete;
		InputComponent& operator=(const InputComponent& other) = delete;
		InputComponent& operator=(InputComponent&& other) noexcept = delete;

		void ProcessInput();
		bool IsPressed(XBoxController::ControllerButton button) const;
		bool IsHeld(XBoxController::ControllerButton button) const;
		bool IsReleased(XBoxController::ControllerButton button) const;

		float GetLeftTriggerPressure() const;
		float GetRightTriggerPressure() const;
		std::pair<float, float> GetLeftStickValues() const;
		std::pair<float, float> GetRightStickValues() const;

		void AddCommand(int key, XBoxController::ControllerButton button, std::unique_ptr<Command> command);
		void Update() override;
		void FixedUpdate() override;

	private:
		XBoxController* m_pController;
		Keyboard* m_pKeyboard;
		std::map<XBoxController::ControllerButton, std::unique_ptr<Command>> m_CommandsMap{};
	};

}
