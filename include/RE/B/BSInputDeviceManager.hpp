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

	class BSInputDeviceManager
		: public BSTSingletonSDM<BSInputDeviceManager> // 00
	{
	public:
		enum class BS_DEVICES : std::int32_t
		{
			kKeyboard = 0,
			kMouse = 1,
			kGamepad = 2,
			kDebugGamepad = 3,
			kVirtualKeyboard = 4,

			kSupported = 3,
			kTotal = 5
		};

		[[nodiscard]] static BSInputDeviceManager* GetSingleton();

		[[nodiscard]] bool IsGamepadConnected() const noexcept;

		[[nodiscard]] BSKeyboardDevice* GetKeyboard() const noexcept;
		[[nodiscard]] BSMouseDevice* GetMouse() const noexcept;
		[[nodiscard]] BSGamepadDevice* GetGamepad() const noexcept;
		[[nodiscard]] BSGamepadDevice* GetDebugGamepad() const noexcept;
		[[nodiscard]] BSVirtualKeyboardDevice* GetVirtualKeyboard() const noexcept;

		[[nodiscard]] BSPCKeyboardDevice* GetPCKeyboard() const noexcept;
		[[nodiscard]] BSPCMouseDevice* GetPCMouse() const noexcept;
		[[nodiscard]] BSPCGamepadDevice* GetPCXInputGamepad() const noexcept;
		[[nodiscard]] BSPCGamepadDevice* GetPCXInputDebugGamepad() const noexcept;
		[[nodiscard]] BSPCOrbisGamepadDevice* GetPCOrbisGamepad() const noexcept;
		[[nodiscard]] BSPCOrbisGamepadDevice* GetPCOrbisDebugGamepad() const noexcept;
		[[nodiscard]] BSPCVirtualKeyboardDevice* GetPCVirtualKeyboard() const noexcept;

		// members
		std::array<BSInputDevice*, std::to_underlying(BS_DEVICES::kTotal)> devices;		// 08
		std::array<bool, std::to_underlying(BS_DEVICES::kSupported)> deviceLightStates; // 30
		bool queuedGamepadEnableValue;													// 33
		bool valueQueued;																// 34
		bool pollingEnabled;															// 35
	};
	static_assert(sizeof(BSInputDeviceManager) == 0x38);
}
