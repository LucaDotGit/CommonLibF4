#include "RE/B/BSInputDeviceManager.hpp"

#include "RE/B/BSGamepadDevice.hpp"
#include "RE/B/BSKeyboardDevice.hpp"
#include "RE/B/BSMouseDevice.hpp"
#include "RE/B/BSPCGamepadDevice.hpp"
#include "RE/B/BSPCKeyboardDevice.hpp"
#include "RE/B/BSPCMouseDevice.hpp"
#include "RE/B/BSPCOrbisGamepadDevice.hpp"
#include "RE/B/BSPCVirtualKeyboardDevice.hpp"
#include "RE/B/BSVirtualKeyboardDevice.hpp"

namespace RE
{
	auto BSInputDeviceManager::GetSingleton() noexcept -> BSInputDeviceManager*
	{
		static const auto SINGLETON = REL::Relocation<BSInputDeviceManager**>(ID::BSInputDeviceManager::Singleton);
		return *SINGLETON;
	}

	auto BSInputDeviceManager::IsGamepadConnected() const noexcept -> bool
	{
		const auto* gamepadDevice = GetGamepad();
		return gamepadDevice && gamepadDevice->IsConnected();
	}

	auto BSInputDeviceManager::GetKeyboard() const noexcept -> BSKeyboardDevice*
	{
		return DynamicCast<BSKeyboardDevice*>(devices[REX::ToUnsigned(std::to_underlying(BS_DEVICES::Keyboard))]);
	}

	auto BSInputDeviceManager::GetMouse() const noexcept -> BSMouseDevice*
	{
		return DynamicCast<BSMouseDevice*>(devices[REX::ToUnsigned(std::to_underlying(BS_DEVICES::Mouse))]);
	}

	auto BSInputDeviceManager::GetGamepad() const noexcept -> BSGamepadDevice*
	{
		return DynamicCast<BSGamepadDevice*>(devices[REX::ToUnsigned(std::to_underlying(BS_DEVICES::Gamepad))]);
	}

	auto BSInputDeviceManager::GetDebugGamepad() const noexcept -> BSGamepadDevice*
	{
		return DynamicCast<BSGamepadDevice*>(devices[REX::ToUnsigned(std::to_underlying(BS_DEVICES::DebugGamepad))]);
	}

	auto BSInputDeviceManager::GetVirtualKeyboard() const noexcept -> BSVirtualKeyboardDevice*
	{
		return DynamicCast<BSVirtualKeyboardDevice*>(
			devices[REX::ToUnsigned(std::to_underlying(BS_DEVICES::VirtualKeyboard))]);
	}

	auto BSInputDeviceManager::GetPCKeyboard() const noexcept -> BSPCKeyboardDevice*
	{
		return DynamicCast<BSPCKeyboardDevice*>(devices[REX::ToUnsigned(std::to_underlying(BS_DEVICES::Keyboard))]);
	}

	auto BSInputDeviceManager::GetPCMouse() const noexcept -> BSPCMouseDevice*
	{
		return DynamicCast<BSPCMouseDevice*>(devices[REX::ToUnsigned(std::to_underlying(BS_DEVICES::Mouse))]);
	}

	auto BSInputDeviceManager::GetPCXInputGamepad() const noexcept -> BSPCGamepadDevice*
	{
		return DynamicCast<BSPCGamepadDevice*>(devices[REX::ToUnsigned(std::to_underlying(BS_DEVICES::Gamepad))]);
	}

	auto BSInputDeviceManager::GetPCXInputDebugGamepad() const noexcept -> BSPCGamepadDevice*
	{
		return DynamicCast<BSPCGamepadDevice*>(devices[REX::ToUnsigned(std::to_underlying(BS_DEVICES::DebugGamepad))]);
	}

	auto BSInputDeviceManager::GetPCOrbisGamepad() const noexcept -> BSPCOrbisGamepadDevice*
	{
		return DynamicCast<BSPCOrbisGamepadDevice*>(devices[REX::ToUnsigned(std::to_underlying(BS_DEVICES::Gamepad))]);
	}

	auto BSInputDeviceManager::GetPCOrbisDebugGamepad() const noexcept -> BSPCOrbisGamepadDevice*
	{
		return DynamicCast<BSPCOrbisGamepadDevice*>(
			devices[REX::ToUnsigned(std::to_underlying(BS_DEVICES::DebugGamepad))]);
	}

	auto BSInputDeviceManager::GetPCVirtualKeyboard() const noexcept -> BSPCVirtualKeyboardDevice*
	{
		return DynamicCast<BSPCVirtualKeyboardDevice*>(
			devices[REX::ToUnsigned(std::to_underlying(BS_DEVICES::VirtualKeyboard))]);
	}
}
