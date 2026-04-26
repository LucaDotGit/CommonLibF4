#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/I/INPUT_DEVICE.hpp"

#include "REX/ErrorCode.hpp"

namespace F4SE::Inputs
{
	struct Macro
	{
		enum : std::int32_t
		{
			kKeyboardOffset = 0,
			kKeyboardKeyCount = 0x100,

			kMouseButtonOffset = kKeyboardKeyCount,
			kMouseButtonCount = 8,

			kMouseWheelOffset = kMouseButtonOffset + kMouseButtonCount,
			kMouseWheelDirectionCount = 2,

			kGamepadButtonOffset = kMouseWheelOffset + kMouseWheelDirectionCount,
			kGamepadButtonCount = 16,

			kTotalButtonCount = kGamepadButtonOffset + kGamepadButtonCount
		};
	};

	struct XInput
	{
		enum : std::int32_t
		{
			kGameButton_LeftTrigger = 0x09,
			kGameButton_RightTrigger = 0x0A
		};
	};

	struct ScanCode
	{
		enum : std::int32_t
		{
			kDirectInputOffset = 0x80,
			kBreakKey = 69,

			kMinBit = 16,
			kMaxBit = 23,
			kExtendedBit = 24
		};
	};

	struct MouseButton
	{
		enum : std::int32_t
		{
			kLeftButton = Macro::kMouseButtonOffset,
			kRightButton,
			kMiddleButton,
			kButton3,
			kButton4,
			kButton5,
			kButton6,
			kButton7,
			kWheelUp,
			kWheelDown
		};
	};

	struct GamepadButton
	{
		enum : std::int32_t
		{
			kDPadUp = Macro::kGamepadButtonOffset,
			kDPadDown,
			kDPadLeft,
			kDPadRight,
			kStart,
			kBack,
			kLeftThumb,
			kRightThumb,
			kLeftShoulder,
			kRightShoulder,
			kA,
			kB,
			kX,
			kY,
			kLeftTrigger,
			kRightTrigger
		};
	};

	// This API should only be used after the game data is ready;
	// it is not thread-safe, except for the functions marked as `noexcept`.

	[[nodiscard]] bool IsGamepadConnected();

	[[nodiscard]] bool IsKeyCodeInRange(std::uint32_t a_keyCode) noexcept;
	[[nodiscard]] bool IsKeyboardKeyCodeInRange(std::uint32_t a_keyCode) noexcept;
	[[nodiscard]] bool IsMouseButtonCodeInRange(std::uint32_t a_keyCode) noexcept;
	[[nodiscard]] bool IsGamepadButtonCodeInRange(std::uint32_t a_keyCode) noexcept;

	[[nodiscard]] bool IsKeyCodeValid(std::uint32_t a_keyCode);
	[[nodiscard]] bool IsKeyboardKeyCodeValid(std::uint32_t a_keyCode);
	[[nodiscard]] bool IsMouseButtonCodeValid(std::uint32_t a_keyCode);
	[[nodiscard]] bool IsGamepadButtonCodeValid(std::uint32_t a_keyCode);

	[[nodiscard]] bool IsXInputGamepadButtonCodeValid(std::uint32_t a_keyCode);
	[[nodiscard]] bool IsOrbisGamepadButtonCodeValid(std::uint32_t a_keyCode);

	[[nodiscard]] bool IsKeyPressed(std::uint32_t a_keyCode);
	[[nodiscard]] bool IsKeyboardKeyPressed(std::uint32_t a_keyCode);
	[[nodiscard]] bool IsMouseButtonPressed(std::uint32_t a_keyCode);
	[[nodiscard]] bool IsGamepadButtonPressed(std::uint32_t a_keyCode);

	[[nodiscard]] bool IsXInputGamepadButtonPressed(std::uint32_t a_keyCode);
	[[nodiscard]] bool IsOrbisGamepadButtonPressed(std::uint32_t a_keyCode);

	[[nodiscard]] auto GetPressedKeyCodes() -> std::expected<std::vector<std::uint32_t>, REX::SystemError>;
	[[nodiscard]] auto GetPressedKeyboardKeyCodes() -> std::expected<std::vector<std::uint32_t>, REX::SystemError>;
	[[nodiscard]] auto GetPressedMouseButtonCodes() -> std::expected<std::vector<std::uint32_t>, REX::SystemError>;
	[[nodiscard]] auto GetPressedGamepadButtonCodes() -> std::expected<std::vector<std::uint32_t>, REX::SystemError>;

	[[nodiscard]] auto GetPressedXInputButtonCodes() -> std::expected<std::vector<std::uint32_t>, REX::SystemError>;
	[[nodiscard]] auto GetPressedOrbisGamepadButtonCodes() -> std::expected<std::vector<std::uint32_t>, REX::SystemError>;

	[[nodiscard]] auto GetPressedControlNames(RE::INPUT_DEVICE a_deviceType = RE::INPUT_DEVICE::kNone) -> std::expected<std::vector<RE::BSFixedString>, REX::SystemError>;
	[[nodiscard]] auto GetPressedKeyboardControlNames() -> std::expected<std::vector<RE::BSFixedString>, REX::SystemError>;
	[[nodiscard]] auto GetPressedMouseButtonControlNames() -> std::expected<std::vector<RE::BSFixedString>, REX::SystemError>;
	[[nodiscard]] auto GetPressedGamepadButtonControlNames() -> std::expected<std::vector<RE::BSFixedString>, REX::SystemError>;

	[[nodiscard]] auto GetPressedXInputGamepadButtonControlNames() -> std::expected<std::vector<RE::BSFixedString>, REX::SystemError>;
	[[nodiscard]] auto GetPressedOrbisGamepadButtonControlNames() -> std::expected<std::vector<RE::BSFixedString>, REX::SystemError>;

	[[nodiscard]] auto GetKeyName(std::uint32_t a_keyCode) -> std::expected<RE::BSFixedStringCS, REX::SystemError>;
	[[nodiscard]] auto GetKeyboardKeyName(std::uint32_t a_keyCode) -> std::expected<RE::BSFixedStringCS, REX::SystemError>;
	[[nodiscard]] auto GetMouseButtonName(std::uint32_t a_keyCode) -> std::expected<RE::BSFixedStringCS, REX::SystemError>;
	[[nodiscard]] auto GetGamepadButtonName(std::uint32_t a_keyCode) -> std::expected<RE::BSFixedStringCS, REX::SystemError>;

	[[nodiscard]] auto GetXInputGamepadButtonName(std::uint32_t a_keyCode) -> std::expected<RE::BSFixedStringCS, REX::SystemError>;
	[[nodiscard]] auto GetOrbisGamepadButtonName(std::uint32_t a_keyCode) -> std::expected<RE::BSFixedStringCS, REX::SystemError>;

	[[nodiscard]] auto GetControlNameByKeyCode(std::uint32_t a_keyCode) -> std::expected<RE::BSFixedString, REX::SystemError>;
	[[nodiscard]] auto GetControlNameByKeyboardKeyCode(std::uint32_t a_keyCode) -> std::expected<RE::BSFixedString, REX::SystemError>;
	[[nodiscard]] auto GetControlNameByMouseKeyCode(std::uint32_t a_keyCode) -> std::expected<RE::BSFixedString, REX::SystemError>;
	[[nodiscard]] auto GetControlNameByGamepadKeyCode(std::uint32_t a_keyCode) -> std::expected<RE::BSFixedString, REX::SystemError>;

	[[nodiscard]] auto GetKeyCodeByControlName(const RE::BSFixedString& a_controlName, RE::INPUT_DEVICE a_deviceType = RE::INPUT_DEVICE::kNone) -> std::expected<std::uint32_t, REX::SystemError>;
	[[nodiscard]] auto GetKeyCodeByKeyboardControlName(const RE::BSFixedString& a_controlName) -> std::expected<std::uint32_t, REX::SystemError>;
	[[nodiscard]] auto GetKeyCodeByMouseControlName(const RE::BSFixedString& a_controlName) -> std::expected<std::uint32_t, REX::SystemError>;
	[[nodiscard]] auto GetKeyCodeByGamepadControlName(const RE::BSFixedString& a_controlName) -> std::expected<std::uint32_t, REX::SystemError>;

	bool HoldKey(std::uint32_t a_keyCode);
	bool HoldKeyboardKey(std::uint32_t a_keyCode);
	bool HoldMouseButton(std::uint32_t a_keyCode);
	bool HoldGamepadButton(std::uint32_t a_keyCode);

	bool HoldXInputGamepadButton(std::uint32_t a_keyCode);
	bool HoldOrbisGamepadButton(std::uint32_t a_keyCode);

	bool ReleaseKey(std::uint32_t a_keyCode, REX::Float32 a_deltaTime = 0.0_f32);
	bool ReleaseKeyboardKey(std::uint32_t a_keyCode, REX::Float32 a_deltaTime = 0.0_f32);
	bool ReleaseMouseButton(std::uint32_t a_keyCode, REX::Float32 a_deltaTime = 0.0_f32);
	bool ReleaseGamepadButton(std::uint32_t a_keyCode, REX::Float32 a_deltaTime = 0.0_f32);

	bool ReleaseXInputGamepadButton(std::uint32_t a_keyCode, REX::Float32 a_deltaTime = 0.0_f32);
	bool ReleaseOrbisGamepadButton(std::uint32_t a_keyCode, REX::Float32 a_deltaTime = 0.0_f32);

	bool TapKey(std::uint32_t a_keyCode, REX::Float32 a_durationSeconds = 0.0_f32);
	bool TapKeyboardKey(std::uint32_t a_keyCode, REX::Float32 a_durationSeconds = 0.0_f32);
	bool TapMouseButton(std::uint32_t a_keyCode, REX::Float32 a_durationSeconds = 0.0_f32);
	bool TapGamepadButton(std::uint32_t a_keyCode, REX::Float32 a_durationSeconds = 0.0_f32);

	bool TapXInputGamepadButton(std::uint32_t a_keyCode, REX::Float32 a_durationSeconds = 0.0_f32);
	bool TapOrbisGamepadButton(std::uint32_t a_keyCode, REX::Float32 a_durationSeconds = 0.0_f32);

	[[nodiscard]] auto GamepadFlagToKeyCode(std::uint32_t a_keyFlag) -> std::expected<std::uint32_t, REX::SystemError>;
	[[nodiscard]] auto GamepadKeyCodeToFlag(std::uint32_t a_keyCode) -> std::expected<std::uint32_t, REX::SystemError>;

	[[nodiscard]] auto XInputGamepadFlagToScePadFlag(std::uint32_t a_keyFlag) noexcept -> std::expected<std::uint32_t, REX::SystemError>;
	[[nodiscard]] auto ScePadFlagToXInputGamepadFlag(std::uint32_t a_keyFlag) noexcept -> std::expected<std::uint32_t, REX::SystemError>;

	[[nodiscard]] auto XInputGamepadFlagToKeyCode(std::uint32_t a_keyFlag) noexcept -> std::expected<std::uint32_t, REX::SystemError>;
	[[nodiscard]] auto XInputGamepadKeyCodeToFlag(std::uint32_t a_keyCode) noexcept -> std::expected<std::uint32_t, REX::SystemError>;

	[[nodiscard]] auto OrbisGamepadFlagToKeyCode(std::uint32_t a_keyFlag) noexcept -> std::expected<std::uint32_t, REX::SystemError>;
	[[nodiscard]] auto OrbisGamepadKeyCodeToFlag(std::uint32_t a_keyCode) noexcept -> std::expected<std::uint32_t, REX::SystemError>;
}
