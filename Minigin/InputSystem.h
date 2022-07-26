#pragma once
#include <memory>
#include <utility>

class InputSystem
{
public:
	InputSystem() = default;
	virtual ~InputSystem() = default;
	InputSystem(const InputSystem& other) = delete;
	InputSystem(InputSystem&& other) noexcept = delete;
	InputSystem& operator=(const InputSystem& other) = delete;
	InputSystem& operator=(InputSystem&& other) noexcept = delete;

	virtual void Update() const = 0;
	virtual bool IsHeld(int button) const = 0;
	virtual bool IsPressed(int button) const = 0;
	virtual bool IsReleased(int button) const = 0;

	virtual float GetLeftTriggerPressure() const;
	virtual float GetRightTriggerPressure() const;
	virtual std::pair<float, float> GetLeftStickValues() const;
	virtual std::pair<float, float> GetRightStickValues() const;

	virtual int GetConnectedControllers() const;

};

