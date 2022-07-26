#include "Keyboard.h"

#include <iostream>
#include <SDL_events.h>

using namespace cycle;

class Keyboard::KeyboardImpl
{
public:
	KeyboardImpl() = default;
	~KeyboardImpl() = default;
	KeyboardImpl(const KeyboardImpl& other) = delete;
	KeyboardImpl(KeyboardImpl&& other) noexcept = delete;
	KeyboardImpl& operator=(const KeyboardImpl& other) = delete;
	KeyboardImpl& operator=(KeyboardImpl&& other) noexcept = delete;

	void Update()
	{
		m_PreviousState = m_CurrentState;
		SDL_PollEvent(&m_CurrentState);
	}

	bool IsHeldThisFrame(int button) const
	{
		if(m_CurrentState.key.type == SDL_KEYDOWN)
		{
			if(static_cast<int>(m_CurrentState.key.keysym.sym) == button && static_cast<int>(m_PreviousState.key.keysym.sym) == button)
			{
				return true;
			}
		}
		return false;
	}
	bool IsPressedThisFrame(int button) const
	{
		if (m_CurrentState.key.type == SDL_KEYDOWN)
		{
			if (static_cast<int>(m_CurrentState.key.keysym.sym) == button)
			{
				return true;
			}
		}
		return false;
	}
	bool IsReleasedThisFrame(int button) const
	{
		if (m_CurrentState.key.type == SDL_KEYUP)
		{
			if (static_cast<int>(m_CurrentState.key.keysym.sym) == button)
			{
				return true;
			}
		}
		return false;
	}

private:
	SDL_Event m_CurrentState{};
	SDL_Event m_PreviousState{};
};

Keyboard::Keyboard()
	: m_pImpl(new KeyboardImpl())
{
}

Keyboard::~Keyboard()
{
	delete m_pImpl;
}


void Keyboard::Update() const
{
	m_pImpl->Update();
}

bool Keyboard::IsHeld(int key) const
{
	return m_pImpl->IsHeldThisFrame(key);
}

bool Keyboard::IsPressed(int key) const
{
	return m_pImpl->IsPressedThisFrame(key);
}

bool Keyboard::IsReleased(int key) const
{
	return m_pImpl->IsReleasedThisFrame(key);
}
