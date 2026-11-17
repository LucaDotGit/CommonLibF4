#pragma once

#include "RE/B/BSTSingleton.hpp"

namespace RE
{
	class BSGamepadDevice;
	class BSInputDevice;
	class BSKeyboardDevice;
	class BSMouseDevice;
	class BSPCGamepadDevice;
	class BSPCKeyboardDevice;
	class BSPCMouseDevice;
	class BSPCOrbisGamepadDevice;
	class BSPCVirtualKeyboardDevice;
	class BSVirtualKeyboardDevice;

	class BSInputDeviceManager : public BSTSingletonSDM<BSInputDeviceManager> // 0x00
	{
	public:
		enum class BS_DEVICES : std::int32_t
		{
			Keyboard = 0,
			Mouse = 1,
			Gamepad = 2,
			DebugGamepad = 3,
			VirtualKeyboard = 4,

			Supported = 3,
			_Count = 5
		};

		[[nodiscard]]
		static auto GetSingleton() noexcept -> BSInputDeviceManager*;

		[[nodiscard]]
		auto IsGamepadConnected() const noexcept -> bool;

		[[nodiscard]]
		auto GetKeyboard() const noexcept -> BSKeyboardDevice*;
		[[nodiscard]]
		auto GetMouse() const noexcept -> BSMouseDevice*;
		[[nodiscard]]
		auto GetGamepad() const noexcept -> BSGamepadDevice*;
		[[nodiscard]]
		auto GetDebugGamepad() const noexcept -> BSGamepadDevice*;
		[[nodiscard]]
		auto GetVirtualKeyboard() const noexcept -> BSVirtualKeyboardDevice*;

		[[nodiscard]]
		auto GetPCKeyboard() const noexcept -> BSPCKeyboardDevice*;
		[[nodiscard]]
		auto GetPCMouse() const noexcept -> BSPCMouseDevice*;
		[[nodiscard]]
		auto GetPCXInputGamepad() const noexcept -> BSPCGamepadDevice*;
		[[nodiscard]]
		auto GetPCXInputDebugGamepad() const noexcept -> BSPCGamepadDevice*;
		[[nodiscard]]
		auto GetPCOrbisGamepad() const noexcept -> BSPCOrbisGamepadDevice*;
		[[nodiscard]]
		auto GetPCOrbisDebugGamepad() const noexcept -> BSPCOrbisGamepadDevice*;
		[[nodiscard]]
		auto GetPCVirtualKeyboard() const noexcept -> BSPCVirtualKeyboardDevice*;

		// members
		std::array<BSInputDevice*, std::to_underlying(BS_DEVICES::_Count)> devices;	   // 0x08
		std::array<bool, std::to_underlying(BS_DEVICES::Supported)> deviceLightStates; // 0x30
		bool queuedGamepadEnableValue;												   // 0x33
		bool valueQueued;															   // 0x34
		bool pollingEnabled;														   // 0x35
	};

	static_assert(sizeof(BSInputDeviceManager) == 0x38);
}
