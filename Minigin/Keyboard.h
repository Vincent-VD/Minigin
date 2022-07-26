#pragma once
#include <string>
#include "InputSystem.h"

namespace cycle
{

	class Keyboard final : public InputSystem
	{
	public:
		class KeyboardImpl;
		KeyboardImpl* m_pImpl;

		Keyboard();
		virtual ~Keyboard() override;
		Keyboard(const Keyboard& other) = delete;
		Keyboard(Keyboard&& other) noexcept = delete;
		Keyboard& operator=(const Keyboard& other) = delete;
		Keyboard& operator=(Keyboard&& other) noexcept = delete;

		void Update() const override;
		bool IsHeld(int key) const override;
		bool IsPressed(int key) const override;
		bool IsReleased(int key) const override;


	};

}