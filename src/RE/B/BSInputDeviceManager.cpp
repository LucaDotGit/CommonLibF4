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
	BSInputDeviceManager* BSInputDeviceManager::GetSingleton()
	{
		static const auto SINGLETON = REL::Relocation<BSInputDeviceManager**>{ ID::BSInputDeviceManager::Singleton };
		return *SINGLETON;
	}

	bool BSInputDeviceManager::IsGamepadConnected() const noexcept
	{
		const auto* gamepadDevice = GetGamepad();
		return gamepadDevice && gamepadDevice->IsConnected();
	}

	BSKeyboardDevice* BSInputDeviceManager::GetKeyboard() const noexcept
	{
		return DynamicCast<BSKeyboardDevice*>(devices[std::to_underlying(BS_DEVICES::kKeyboard)]);
	}

	BSMouseDevice* BSInputDeviceManager::GetMouse() const noexcept
	{
		return DynamicCast<BSMouseDevice*>(devices[std::to_underlying(BS_DEVICES::kMouse)]);
	}

	BSGamepadDevice* BSInputDeviceManager::GetGamepad() const noexcept
	{
		return DynamicCast<BSGamepadDevice*>(devices[std::to_underlying(BS_DEVICES::kGamepad)]);
	}

	BSGamepadDevice* BSInputDeviceManager::GetDebugGamepad() const noexcept
	{
		return DynamicCast<BSGamepadDevice*>(devices[std::to_underlying(BS_DEVICES::kDebugGamepad)]);
	}

	BSVirtualKeyboardDevice* BSInputDeviceManager::GetVirtualKeyboard() const noexcept
	{
		return DynamicCast<BSVirtualKeyboardDevice*>(devices[std::to_underlying(BS_DEVICES::kVirtualKeyboard)]);
	}

	BSPCKeyboardDevice* BSInputDeviceManager::GetPCKeyboard() const noexcept
	{
		return DynamicCast<BSPCKeyboardDevice*>(devices[std::to_underlying(BS_DEVICES::kKeyboard)]);
	}

	BSPCMouseDevice* BSInputDeviceManager::GetPCMouse() const noexcept
	{
		return DynamicCast<BSPCMouseDevice*>(devices[std::to_underlying(BS_DEVICES::kMouse)]);
	}

	BSPCGamepadDevice* BSInputDeviceManager::GetPCXInputGamepad() const noexcept
	{
		return DynamicCast<BSPCGamepadDevice*>(devices[std::to_underlying(BS_DEVICES::kGamepad)]);
	}

	BSPCGamepadDevice* BSInputDeviceManager::GetPCXInputDebugGamepad() const noexcept
	{
		return DynamicCast<BSPCGamepadDevice*>(devices[std::to_underlying(BS_DEVICES::kDebugGamepad)]);
	}

	BSPCOrbisGamepadDevice* BSInputDeviceManager::GetPCOrbisGamepad() const noexcept
	{
		return DynamicCast<BSPCOrbisGamepadDevice*>(devices[std::to_underlying(BS_DEVICES::kGamepad)]);
	}

	BSPCOrbisGamepadDevice* BSInputDeviceManager::GetPCOrbisDebugGamepad() const noexcept
	{
		return DynamicCast<BSPCOrbisGamepadDevice*>(devices[std::to_underlying(BS_DEVICES::kDebugGamepad)]);
	}

	BSPCVirtualKeyboardDevice* BSInputDeviceManager::GetPCVirtualKeyboard() const noexcept
	{
		return DynamicCast<BSPCVirtualKeyboardDevice*>(devices[std::to_underlying(BS_DEVICES::kVirtualKeyboard)]);
	}
}
