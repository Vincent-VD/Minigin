#pragma once
#include <memory>
#include <utility>

namespace cycle
{
	class XBoxController
	{
		class XBoxControllerImpl;
		XBoxControllerImpl* m_pImpl;
	public:
		enum class ControllerButton
		{
			DPadUp = 0x0001,
			DPadDown = 0x0002,
			DPadLeft = 0x0004,
			DPadRight = 0x0008,
			Start = 0x0010,
			Back = 0x0020,
			LeftStick = 0x0040,
			RightStick = 0x0080,
			LeftShoulder = 0x0100,
			RightShoulder = 0x0200,
			ButtonA = 0x1000,
			ButtonB = 0x2000,
			ButtonX = 0x4000,
			ButtonY = 0x8000,
		};
		void Update() const;
		bool IsHeld(ControllerButton button) const;
		bool IsPressed(ControllerButton button) const;
		bool IsReleased(ControllerButton button) const;

		float GetLeftTriggerPressure() const;
		float GetRightTriggerPressure() const;
		std::pair<float, float> GetLeftStickValues() const;
		std::pair<float, float> GetRightStickValues() const;

		explicit XBoxController(int controllerIdx);
		~XBoxController();
		XBoxController(const XBoxController& other) = delete;
		XBoxController(XBoxController&& other) noexcept = delete;
		XBoxController& operator=(const XBoxController& other) = delete;
		XBoxController& operator=(XBoxController&& other) noexcept = delete;
	};
}
