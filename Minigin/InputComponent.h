#pragma once
#include <iostream>
#include <map>
#include "RootComponent.h"
#include "XBoxController.h"

namespace cycle
{
	class Command
	{
	public:
		enum class InputType
		{
			pressed = 0,
			held = 1,
			released = 2
		};
		Command(InputType type) : m_InputType{ type } {}
		virtual ~Command() = default;
		Command(const Command& other) = delete;
		Command(Command&& other) noexcept = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) noexcept = delete;

		InputType m_InputType;
		virtual void Execute() = 0;
	};

	class Test final : public Command
	{
	public:
		Test(InputType type) : Command(type) {}
		void Execute() override { std::cout << "Fire\n"; }
	};

	class InputComponent final : public RootComponent
	{
	public:
		InputComponent(GameObject* pOwner)
			: RootComponent(pOwner)
			, m_pController{ new XBoxController{0} }
		{
		}
		virtual ~InputComponent() override
		{
			delete m_pController;
			m_CommandsMap.clear();
		}

		InputComponent(const InputComponent& other) = delete;
		InputComponent(InputComponent&& other) noexcept = delete;
		InputComponent& operator=(const InputComponent& other) = delete;
		InputComponent& operator=(InputComponent&& other) noexcept = delete;

		void ProcessInput();
		bool IsPressed(XBoxController::ControllerButton button) const;
		bool IsHeld(XBoxController::ControllerButton button) const;
		bool IsReleased(XBoxController::ControllerButton button) const;

		void AddCommand(XBoxController::ControllerButton button, std::unique_ptr<Command> command);
		void Update() override;
		void FixedUpdate() override;


	private:
		XBoxController* m_pController;
		std::map<cycle::XBoxController::ControllerButton, std::unique_ptr<Command>> m_CommandsMap{};
	};

}
