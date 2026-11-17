#include "RE/B/ButtonEvent.hpp"

#include "RE/B/BS_BUTTON_CODE.hpp"

namespace RE
{
	auto ButtonEvent::QAnalogValue() const noexcept -> REX::Float32
	{
		return value;
	}

	auto ButtonEvent::QHeldDown(REX::Float32 a_heldDownSecs) const noexcept -> bool
	{
		return value != static_cast<REX::Float32>(0.0) && a_heldDownSecs <= heldDownSecs;
	}

	auto ButtonEvent::QHeldDown() const noexcept -> bool
	{
		return value != static_cast<REX::Float32>(0.0) && heldDownSecs > static_cast<REX::Float32>(0.0);
	}

	auto ButtonEvent::QHeldDownSecs() const noexcept -> REX::Float32
	{
		return heldDownSecs;
	}

	auto ButtonEvent::QJustPressed() const noexcept -> bool
	{
		return value != static_cast<REX::Float32>(0.0) && heldDownSecs == static_cast<REX::Float32>(0.0);
	}

	auto ButtonEvent::QPressed() const noexcept -> bool
	{
		return value != static_cast<REX::Float32>(0.0);
	}

	auto ButtonEvent::QReleased(REX::Float32 a_heldDownSecs) const noexcept -> bool
	{
		return value == static_cast<REX::Float32>(0.0) && a_heldDownSecs <= heldDownSecs;
	}

	auto ButtonEvent::QReleased() const noexcept -> bool
	{
		return value == static_cast<REX::Float32>(0.0) && heldDownSecs > static_cast<REX::Float32>(0.0);
	}

	auto ButtonEvent::GetBSButtonCode() const noexcept -> BS_BUTTON_CODE
	{
		auto result = REX::EnumSet(static_cast<BS_BUTTON_CODE>(idCode));
		if (device.get() == INPUT_DEVICE::Gamepad) {
			result.set(BS_BUTTON_CODE::Gamepad);
		}

		return result.get();
	}
}
