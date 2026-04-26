#include "RE/B/ButtonEvent.hpp"

#include "RE/B/BS_BUTTON_CODE.hpp"

namespace RE
{
	REX::Float32 ButtonEvent::QAnalogValue() const noexcept
	{
		return value;
	}

	bool ButtonEvent::QHeldDown(REX::Float32 a_heldDownSecs) const noexcept
	{
		return value != 0.0_f32 && a_heldDownSecs <= heldDownSecs;
	}

	bool ButtonEvent::QHeldDown() const noexcept
	{
		return value != 0.0_f32 && heldDownSecs > 0.0_f32;
	}

	REX::Float32 ButtonEvent::QHeldDownSecs() const noexcept
	{
		return heldDownSecs;
	}

	bool ButtonEvent::QJustPressed() const noexcept
	{
		return value != 0.0_f32 && heldDownSecs == 0.0_f32;
	}

	bool ButtonEvent::QPressed() const noexcept
	{
		return value != 0.0_f32;
	}

	bool ButtonEvent::QReleased(REX::Float32 a_heldDownSecs) const noexcept
	{
		return value == 0.0_f32 && a_heldDownSecs <= heldDownSecs;
	}

	bool ButtonEvent::QReleased() const noexcept
	{
		return value == 0.0_f32 && heldDownSecs > 0.0_f32;
	}

	BS_BUTTON_CODE ButtonEvent::GetBSButtonCode() const noexcept
	{
		auto result = REX::EnumSet(static_cast<BS_BUTTON_CODE>(idCode));
		if (device.get() == INPUT_DEVICE::kGamepad) {
			result.set(BS_BUTTON_CODE::kGamepad);
		}

		return result.get();
	}

	template bool InputEvent::Is<ButtonEvent>() const noexcept;
	template bool InputEvent::IsNot<ButtonEvent>() const noexcept;

	template ButtonEvent* InputEvent::As() noexcept;
	template const ButtonEvent* InputEvent::As() const noexcept;
}
