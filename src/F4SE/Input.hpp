#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/I/INPUT_DEVICE.hpp"
#include "REX/Error.hpp"

namespace REX::PS4
{
	// NOLINTNEXTLINE(cppcoreguidelines-use-enum-class)
	enum SCE_PAD_BUTTON : std::uint32_t;
}

namespace REX::W32
{
	// NOLINTNEXTLINE(cppcoreguidelines-use-enum-class)
	enum XINPUT_GAMEPAD_BUTTON : std::uint16_t;
}

namespace F4SE::Input
{
	using KeyCode = std::uint32_t;
	using KeyFlag = std::uint32_t;

	using DeltaTime = std::chrono::duration<REX::Float32, std::chrono::seconds::period>;

	enum class Macro : KeyCode
	{
		KeyboardOffset = 0,
		KeyboardKeyCount = 0x100,

		MouseButtonOffset = KeyboardKeyCount,
		MouseButtonCount = 8,

		MouseWheelOffset = MouseButtonOffset + MouseButtonCount,
		MouseWheelDirectionCount = 2,

		GamepadButtonOffset = MouseWheelOffset + MouseWheelDirectionCount,
		GamepadButtonCount = 16,

		TotalButtonCount = GamepadButtonOffset + GamepadButtonCount
	};

	enum class XInput : KeyCode
	{
		GameButton_LeftTrigger = 0x09,
		GameButton_RightTrigger = 0x0A
	};

	enum class ScanCode : KeyCode
	{
		DirectInputOffset = 0x80,
		BreakKey = 69,

		MinBit = 16,
		MaxBit = 23,
		ExtendedBit = 24
	};

	enum class MouseButton : KeyCode
	{
		LeftButton = std::to_underlying(Macro::MouseButtonOffset),
		RightButton,
		MiddleButton,
		Button3,
		Button4,
		Button5,
		Button6,
		Button7,
		WheelUp,
		WheelDown
	};

	enum class GamepadButton : KeyCode
	{
		DPadUp = std::to_underlying(Macro::GamepadButtonOffset),
		DPadDown,
		DPadLeft,
		DPadRight,
		Start,
		Back,
		LeftThumb,
		RightThumb,
		LeftShoulder,
		RightShoulder,
		kA,
		kB,
		kX,
		kY,
		LeftTrigger,
		RightTrigger
	};

	// This API should only be used after the game data is ready;
	// it is not thread-safe, except for the functions marked as `noexcept`.

	[[nodiscard]]
	auto IsGamepadConnected() -> bool;

	[[nodiscard]]
	auto IsKeyCodeInRange(KeyCode a_keyCode) noexcept -> bool;
	[[nodiscard]]
	auto IsKeyboardKeyCodeInRange(KeyCode a_keyCode) noexcept -> bool;
	[[nodiscard]]
	auto IsMouseButtonCodeInRange(KeyCode a_keyCode) noexcept -> bool;
	[[nodiscard]]
	auto IsGamepadButtonCodeInRange(KeyCode a_keyCode) noexcept -> bool;

	[[nodiscard]]
	auto IsKeyCodeValid(KeyCode a_keyCode) -> bool;
	[[nodiscard]]
	auto IsKeyboardKeyCodeValid(KeyCode a_keyCode) -> bool;
	[[nodiscard]]
	auto IsMouseButtonCodeValid(KeyCode a_keyCode) -> bool;
	[[nodiscard]]
	auto IsGamepadButtonCodeValid(KeyCode a_keyCode) -> bool;

	[[nodiscard]]
	auto IsXInputGamepadButtonCodeValid(KeyCode a_keyCode) -> bool;
	[[nodiscard]]
	auto IsOrbisGamepadButtonCodeValid(KeyCode a_keyCode) -> bool;

	[[nodiscard]]
	auto IsKeyPressed(KeyCode a_keyCode) -> bool;
	[[nodiscard]]
	auto IsKeyboardKeyPressed(KeyCode a_keyCode) -> bool;
	[[nodiscard]]
	auto IsMouseButtonPressed(KeyCode a_keyCode) -> bool;
	[[nodiscard]]
	auto IsGamepadButtonPressed(KeyCode a_keyCode) -> bool;

	[[nodiscard]]
	auto IsXInputGamepadButtonPressed(KeyCode a_keyCode) -> bool;
	[[nodiscard]]
	auto IsOrbisGamepadButtonPressed(KeyCode a_keyCode) -> bool;

	[[nodiscard]]
	auto GetPressedKeyCodes() -> std::expected<std::vector<KeyCode>, REX::SystemError>;
	[[nodiscard]]
	auto GetPressedKeyboardKeyCodes() -> std::expected<std::vector<KeyCode>, REX::SystemError>;
	[[nodiscard]]
	auto GetPressedMouseButtonCodes() -> std::expected<std::vector<KeyCode>, REX::SystemError>;
	[[nodiscard]]
	auto GetPressedGamepadButtonCodes() -> std::expected<std::vector<KeyCode>, REX::SystemError>;

	[[nodiscard]]
	auto GetPressedXInputButtonCodes() -> std::expected<std::vector<KeyCode>, REX::SystemError>;
	[[nodiscard]]
	auto GetPressedOrbisGamepadButtonCodes() -> std::expected<std::vector<KeyCode>, REX::SystemError>;

	[[nodiscard]]
	auto GetPressedControlNames(RE::INPUT_DEVICE a_deviceType = RE::INPUT_DEVICE::None)
		-> std::expected<std::vector<RE::BSFixedString>, REX::SystemError>;
	[[nodiscard]]
	auto GetPressedKeyboardControlNames() -> std::expected<std::vector<RE::BSFixedString>, REX::SystemError>;
	[[nodiscard]]
	auto GetPressedMouseButtonControlNames() -> std::expected<std::vector<RE::BSFixedString>, REX::SystemError>;
	[[nodiscard]]
	auto GetPressedGamepadButtonControlNames() -> std::expected<std::vector<RE::BSFixedString>, REX::SystemError>;

	[[nodiscard]]
	auto GetPressedXInputGamepadButtonControlNames() -> std::expected<std::vector<RE::BSFixedString>, REX::SystemError>;
	[[nodiscard]]
	auto GetPressedOrbisGamepadButtonControlNames() -> std::expected<std::vector<RE::BSFixedString>, REX::SystemError>;

	[[nodiscard]]
	auto GetKeyName(KeyCode a_keyCode) -> std::expected<RE::BSFixedStringCS, REX::SystemError>;
	[[nodiscard]]
	auto GetKeyboardKeyName(KeyCode a_keyCode) -> std::expected<RE::BSFixedStringCS, REX::SystemError>;
	[[nodiscard]]
	auto GetMouseButtonName(KeyCode a_keyCode) -> std::expected<RE::BSFixedStringCS, REX::SystemError>;
	[[nodiscard]]
	auto GetGamepadButtonName(KeyCode a_keyCode) -> std::expected<RE::BSFixedStringCS, REX::SystemError>;

	[[nodiscard]]
	auto GetXInputGamepadButtonName(KeyCode a_keyCode) -> std::expected<RE::BSFixedStringCS, REX::SystemError>;
	[[nodiscard]]
	auto GetOrbisGamepadButtonName(KeyCode a_keyCode) -> std::expected<RE::BSFixedStringCS, REX::SystemError>;

	[[nodiscard]]
	auto GetControlNameByKeyCode(KeyCode a_keyCode) -> std::expected<RE::BSFixedString, REX::SystemError>;
	[[nodiscard]]
	auto GetControlNameByKeyboardKeyCode(KeyCode a_keyCode) -> std::expected<RE::BSFixedString, REX::SystemError>;
	[[nodiscard]]
	auto GetControlNameByMouseKeyCode(KeyCode a_keyCode) -> std::expected<RE::BSFixedString, REX::SystemError>;
	[[nodiscard]]
	auto GetControlNameByGamepadKeyCode(KeyCode a_keyCode) -> std::expected<RE::BSFixedString, REX::SystemError>;

	[[nodiscard]]
	auto GetKeyCodeByControlName(
		const RE::BSFixedString& a_controlName,
		RE::INPUT_DEVICE a_deviceType = RE::INPUT_DEVICE::None) -> std::expected<KeyCode, REX::SystemError>;
	[[nodiscard]]
	auto GetKeyCodeByKeyboardControlName(const RE::BSFixedString& a_controlName)
		-> std::expected<KeyCode, REX::SystemError>;
	[[nodiscard]]
	auto GetKeyCodeByMouseControlName(const RE::BSFixedString& a_controlName)
		-> std::expected<KeyCode, REX::SystemError>;
	[[nodiscard]]
	auto GetKeyCodeByGamepadControlName(const RE::BSFixedString& a_controlName)
		-> std::expected<KeyCode, REX::SystemError>;

	auto HoldKey(KeyCode a_keyCode) -> bool;
	auto HoldKeyboardKey(KeyCode a_keyCode) -> bool;
	auto HoldMouseButton(KeyCode a_keyCode) -> bool;
	auto HoldGamepadButton(KeyCode a_keyCode) -> bool;

	auto HoldXInputGamepadButton(KeyCode a_keyCode) -> bool;
	auto HoldOrbisGamepadButton(KeyCode a_keyCode) -> bool;

	auto ReleaseKey(KeyCode a_keyCode, DeltaTime a_deltaTime = DeltaTime::zero()) -> bool;
	auto ReleaseKeyboardKey(KeyCode a_keyCode, DeltaTime a_deltaTime = DeltaTime::zero()) -> bool;
	auto ReleaseMouseButton(KeyCode a_keyCode, DeltaTime a_deltaTime = DeltaTime::zero()) -> bool;
	auto ReleaseGamepadButton(KeyCode a_keyCode, DeltaTime a_deltaTime = DeltaTime::zero()) -> bool;

	auto ReleaseXInputGamepadButton(KeyCode a_keyCode, DeltaTime a_deltaTime = DeltaTime::zero()) -> bool;
	auto ReleaseOrbisGamepadButton(KeyCode a_keyCode, DeltaTime a_deltaTime = DeltaTime::zero()) -> bool;

	auto TapKey(KeyCode a_keyCode, DeltaTime a_durationSeconds = DeltaTime::zero()) -> bool;
	auto TapKeyboardKey(KeyCode a_keyCode, DeltaTime a_durationSeconds = DeltaTime::zero()) -> bool;
	auto TapMouseButton(KeyCode a_keyCode, DeltaTime a_durationSeconds = DeltaTime::zero()) -> bool;
	auto TapGamepadButton(KeyCode a_keyCode, DeltaTime a_durationSeconds = DeltaTime::zero()) -> bool;

	auto TapXInputGamepadButton(KeyCode a_keyCode, DeltaTime a_durationSeconds = DeltaTime::zero()) -> bool;
	auto TapOrbisGamepadButton(KeyCode a_keyCode, DeltaTime a_durationSeconds = DeltaTime::zero()) -> bool;

	[[nodiscard]]
	auto GamepadFlagToKeyCode(KeyFlag a_keyFlag) -> std::expected<GamepadButton, REX::SystemError>;
	[[nodiscard]]
	auto GamepadKeyCodeToFlag(KeyCode a_keyCode) -> std::expected<KeyCode, REX::SystemError>;

	[[nodiscard]]
	auto XInputGamepadFlagToScePadFlag(KeyFlag a_keyFlag) noexcept
		-> std::expected<REX::PS4::SCE_PAD_BUTTON, REX::SystemError>;
	[[nodiscard]]
	auto ScePadFlagToXInputGamepadFlag(KeyFlag a_keyFlag) noexcept
		-> std::expected<REX::W32::XINPUT_GAMEPAD_BUTTON, REX::SystemError>;

	[[nodiscard]]
	auto XInputGamepadFlagToKeyCode(KeyFlag a_keyFlag) noexcept -> std::expected<GamepadButton, REX::SystemError>;
	[[nodiscard]]
	auto XInputGamepadKeyCodeToFlag(KeyCode a_keyCode) noexcept
		-> std::expected<REX::W32::XINPUT_GAMEPAD_BUTTON, REX::SystemError>;

	[[nodiscard]]
	auto OrbisGamepadFlagToKeyCode(KeyFlag a_keyFlag) noexcept -> std::expected<GamepadButton, REX::SystemError>;
	[[nodiscard]]
	auto OrbisGamepadKeyCodeToFlag(KeyCode a_keyCode) noexcept
		-> std::expected<REX::PS4::SCE_PAD_BUTTON, REX::SystemError>;
}
