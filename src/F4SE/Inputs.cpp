#include "F4SE/Inputs.hpp"

#include "RE/B/BSGamepadDevice.hpp"
#include "RE/B/BSInputDeviceManager.hpp"
#include "RE/B/BSPCGamepadDevice.hpp"
#include "RE/B/BSPCKeyboardDevice.hpp"
#include "RE/B/BSPCMouseDevice.hpp"
#include "RE/B/BSPCOrbisGamepadDevice.hpp"
#include "RE/C/ControlMap.hpp"
#include "RE/P/PC_GAMEPAD_TYPE.hpp"

#include "REX/Contract.hpp"
#include "REX/PS4/SCEPAD.hpp"
#include "REX/W32/XINPUT.hpp"

namespace F4SE::Inputs::Impl
{
	static_assert(Macro::kKeyboardOffset < Macro::kMouseButtonOffset);
	static_assert(Macro::kMouseButtonOffset < Macro::kGamepadButtonOffset);
	static_assert(Macro::kGamepadButtonOffset < Macro::kTotalButtonCount);

	static constexpr auto ABSOLUTE_LEFT_TRIGGER_BUTTON_CODE =
		std::to_underlying(Macro::kGamepadButtonOffset) +
		std::to_underlying(XInput::kGameButton_LeftTrigger);
	static constexpr auto ABSOLUTE_RIGHT_TRIGGER_BUTTON_CODE =
		std::to_underlying(Macro::kGamepadButtonOffset) +
		std::to_underlying(XInput::kGameButton_RightTrigger);

	[[nodiscard]] static bool IsKeyboardKeyPressed(const RE::BSPCKeyboardDevice* a_keyboardDevice, std::uint32_t a_keyCode) noexcept
	{
		if (!a_keyboardDevice) {
			return false;
		}

		constexpr auto MAX_KEYBOARD_KEY_INDEX = Macro::kMouseButtonOffset - Macro::kKeyboardOffset;

		const auto keyIndex = a_keyCode - Macro::kKeyboardOffset;
		if (keyIndex >= MAX_KEYBOARD_KEY_INDEX) {
			return false;
		}

		return a_keyboardDevice->currKeyStates[keyIndex];
	}

	[[nodiscard]] static bool IsMouseButtonPressed(const RE::BSPCMouseDevice* a_mouseDevice, std::uint32_t a_keyCode) noexcept
	{
		if (!a_mouseDevice) {
			return false;
		}

		constexpr auto MAX_MOUSE_BUTTON_INDEX = Macro::kGamepadButtonOffset - Macro::kMouseButtonOffset;

		const auto buttonIndex = a_keyCode - Macro::kMouseButtonOffset;
		if (buttonIndex >= MAX_MOUSE_BUTTON_INDEX) {
			return false;
		}

		const auto buttonFlag = static_cast<RE::BSPCMouseDevice::ButtonFlags>(1 << buttonIndex);
		return a_mouseDevice->currButtonFlags.any(buttonFlag);
	}

	[[nodiscard]] static bool IsXInputGamepadButtonPressed(const RE::BSPCGamepadDevice* a_gamepadDevice, std::uint32_t a_keyCode) noexcept
	{
		if (!a_gamepadDevice) {
			return false;
		}

		const auto& gamepadState = a_gamepadDevice->currState.hardwareState.gamepad;
		if ((gamepadState.leftTrigger != 0 && a_keyCode == ABSOLUTE_LEFT_TRIGGER_BUTTON_CODE) ||
			(gamepadState.rightTrigger != 0 && a_keyCode == ABSOLUTE_RIGHT_TRIGGER_BUTTON_CODE)) {
			return true;
		}

		const auto buttonFlag = XInputGamepadKeyCodeToFlag(a_keyCode);
		if (!buttonFlag) {
			return false;
		}

		return (gamepadState.buttons & *buttonFlag) != 0;
	}

	[[nodiscard]] static bool IsOrbisGamepadButtonPressed(const RE::BSPCOrbisGamepadDevice* a_gamepadDevice, std::uint32_t a_keyCode) noexcept
	{
		if (!a_gamepadDevice) {
			return false;
		}

		const auto& gamepadState = a_gamepadDevice->currState.hardwareState;
		if ((gamepadState.analogButtons.l2 != 0 && a_keyCode == ABSOLUTE_LEFT_TRIGGER_BUTTON_CODE) ||
			(gamepadState.analogButtons.r2 != 0 && a_keyCode == ABSOLUTE_RIGHT_TRIGGER_BUTTON_CODE)) {
			return true;
		}

		const auto buttonFlag = OrbisGamepadKeyCodeToFlag(a_keyCode);
		if (!buttonFlag) {
			return false;
		}

		return (gamepadState.buttons & *buttonFlag) != 0;
	}

	[[nodiscard]] static bool PressKeyboardKey(std::uint32_t a_keyCode, bool a_isPressed, REX::Float32 a_deltaTime = 0.0_f32)
	{
		if (!IsKeyboardKeyCodeInRange(a_keyCode)) {
			return false;
		}

		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		auto* keyboardDevice = inputDeviceManager->GetPCKeyboard();
		if (!keyboardDevice || !keyboardDevice->IsConnected()) {
			return false;
		}

		const auto buttonInfo = keyboardDevice->GetButtonInfoByID(a_keyCode);
		if (!buttonInfo) {
			return false;
		}

		const auto buttonID = buttonInfo->first;
		keyboardDevice->CreateButtonEvent(
			buttonID,
			a_deltaTime,
			!a_isPressed,
			a_isPressed);

		return true;
	}

	[[nodiscard]] static bool PressMouseButton(std::uint32_t a_keyCode, bool a_isPressed, REX::Float32 a_deltaTime = 0.0_f32)
	{
		if (!IsMouseButtonCodeInRange(a_keyCode)) {
			return false;
		}

		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		auto* mouseDevice = inputDeviceManager->GetPCMouse();
		if (!mouseDevice || !mouseDevice->IsConnected()) {
			return false;
		}

		const auto buttonInfo = mouseDevice->GetButtonInfoByID(a_keyCode - Macro::kMouseButtonOffset);
		if (!buttonInfo) {
			return false;
		}

		const auto buttonID = buttonInfo->first;
		mouseDevice->CreateButtonEvent(
			buttonID,
			a_deltaTime,
			!a_isPressed,
			a_isPressed);

		return true;
	}

	[[nodiscard]] static bool PressXInputGamepadButton(std::uint32_t a_keyCode, bool a_isPressed, REX::Float32 a_deltaTime = 0.0_f32)
	{
		if (!IsGamepadButtonCodeInRange(a_keyCode)) {
			return false;
		}

		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		auto* gamepadDevice = inputDeviceManager->GetPCXInputGamepad();
		if (!gamepadDevice || !gamepadDevice->IsConnected()) {
			return false;
		}

		const auto buttonInfo = gamepadDevice->GetButtonInfoByID(a_keyCode - Macro::kGamepadButtonOffset);
		if (!buttonInfo) {
			return false;
		}

		const auto buttonID = buttonInfo->first;
		gamepadDevice->CreateButtonEvent(
			buttonID,
			a_deltaTime,
			!a_isPressed,
			a_isPressed);

		return true;
	}

	[[nodiscard]] static bool PressOrbisGamepadButton(std::uint32_t a_keyCode, bool a_isPressed, REX::Float32 a_deltaTime = 0.0_f32)
	{
		if (!IsGamepadButtonCodeInRange(a_keyCode)) {
			return false;
		}

		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		auto* gamepadDevice = inputDeviceManager->GetPCOrbisGamepad();
		if (!gamepadDevice || !gamepadDevice->IsConnected()) {
			return false;
		}

		const auto buttonInfo = gamepadDevice->GetButtonInfoByID(a_keyCode - Macro::kGamepadButtonOffset);
		if (!buttonInfo) {
			return false;
		}

		const auto buttonID = buttonInfo->first;
		gamepadDevice->CreateButtonEvent(
			buttonID,
			a_deltaTime,
			!a_isPressed,
			a_isPressed);

		return true;
	}
}

namespace F4SE::Inputs
{
	bool IsGamepadConnected()
	{
		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		return inputDeviceManager->IsGamepadConnected();
	}

	bool IsKeyCodeInRange(std::uint32_t a_keyCode) noexcept
	{
		return IsKeyboardKeyCodeInRange(a_keyCode) ||
			   IsMouseButtonCodeInRange(a_keyCode) ||
			   IsGamepadButtonCodeInRange(a_keyCode);
	}

	bool IsKeyboardKeyCodeInRange(std::uint32_t a_keyCode) noexcept
	{
		return a_keyCode >= Macro::kKeyboardOffset &&
			   a_keyCode < Macro::kMouseButtonOffset;
	}

	bool IsMouseButtonCodeInRange(std::uint32_t a_keyCode) noexcept
	{
		return a_keyCode >= Macro::kMouseButtonOffset &&
			   a_keyCode < Macro::kGamepadButtonOffset;
	}

	bool IsGamepadButtonCodeInRange(std::uint32_t a_keyCode) noexcept
	{
		return a_keyCode >= Macro::kGamepadButtonOffset &&
			   a_keyCode < Macro::kTotalButtonCount;
	}

	bool IsKeyCodeValid(std::uint32_t a_keyCode)
	{
		return IsKeyboardKeyCodeValid(a_keyCode) ||
			   IsMouseButtonCodeValid(a_keyCode) ||
			   IsGamepadButtonCodeValid(a_keyCode);
	}

	bool IsKeyboardKeyCodeValid(std::uint32_t a_keyCode)
	{
		if (!IsKeyboardKeyCodeInRange(a_keyCode)) {
			return false;
		}

		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		const auto* keyboardDevice = inputDeviceManager->GetPCKeyboard();
		if (!keyboardDevice || !keyboardDevice->IsConnected()) {
			return false;
		}

		return keyboardDevice->ContainsButtonID(a_keyCode);
	}

	bool IsMouseButtonCodeValid(std::uint32_t a_keyCode)
	{
		if (!IsMouseButtonCodeInRange(a_keyCode)) {
			return false;
		}

		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		const auto* mouseDevice = inputDeviceManager->GetPCMouse();
		if (!mouseDevice || !mouseDevice->IsConnected()) {
			return false;
		}

		return mouseDevice->ContainsButtonID(a_keyCode - Macro::kMouseButtonOffset);
	}

	bool IsGamepadButtonCodeValid(std::uint32_t a_keyCode)
	{
		if (!IsGamepadButtonCodeInRange(a_keyCode)) {
			return false;
		}

		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		switch (controlMap->pcGamepadMapType.get()) {
			case RE::PC_GAMEPAD_TYPE::kDirectX: {
				return IsXInputGamepadButtonCodeValid(a_keyCode);
			}
			case RE::PC_GAMEPAD_TYPE::kOrbis: {
				return IsOrbisGamepadButtonCodeValid(a_keyCode);
			}
			[[unlikely]] default: {
				REX::Assert(false);
				return false;
			}
		}
	}

	bool IsXInputGamepadButtonCodeValid(std::uint32_t a_keyCode)
	{
		if (!IsGamepadButtonCodeInRange(a_keyCode)) {
			return false;
		}

		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		const auto* gamepadDevice = inputDeviceManager->GetPCXInputGamepad();
		if (!gamepadDevice || !gamepadDevice->IsConnected()) {
			return false;
		}

		return gamepadDevice->ContainsButtonID(a_keyCode - Macro::kGamepadButtonOffset);
	}

	bool IsOrbisGamepadButtonCodeValid(std::uint32_t a_keyCode)
	{
		if (!IsGamepadButtonCodeInRange(a_keyCode)) {
			return false;
		}

		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		const auto* gamepadDevice = inputDeviceManager->GetPCOrbisGamepad();
		if (!gamepadDevice || !gamepadDevice->IsConnected()) {
			return false;
		}

		return gamepadDevice->ContainsButtonID(a_keyCode - Macro::kGamepadButtonOffset);
	}

	bool IsKeyPressed(std::uint32_t a_keyCode)
	{
		return IsKeyboardKeyPressed(a_keyCode) ||
			   IsMouseButtonPressed(a_keyCode) ||
			   IsGamepadButtonPressed(a_keyCode);
	}

	bool IsKeyboardKeyPressed(std::uint32_t a_keyCode)
	{
		if (!IsKeyboardKeyCodeInRange(a_keyCode)) {
			return false;
		}

		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		const auto* keyboardDevice = inputDeviceManager->GetPCKeyboard();
		if (!keyboardDevice || !keyboardDevice->IsConnected()) {
			return false;
		}

		return Impl::IsKeyboardKeyPressed(keyboardDevice, a_keyCode);
	}

	bool IsMouseButtonPressed(std::uint32_t a_keyCode)
	{
		if (!IsMouseButtonCodeInRange(a_keyCode)) {
			return false;
		}

		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		const auto* mouseDevice = inputDeviceManager->GetPCMouse();
		if (!mouseDevice || !mouseDevice->IsConnected()) {
			return false;
		}

		return Impl::IsMouseButtonPressed(mouseDevice, a_keyCode);
	}

	bool IsGamepadButtonPressed(std::uint32_t a_keyCode)
	{
		if (!IsGamepadButtonCodeInRange(a_keyCode)) {
			return false;
		}

		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		switch (controlMap->pcGamepadMapType.get()) {
			case RE::PC_GAMEPAD_TYPE::kDirectX: {
				return IsXInputGamepadButtonPressed(a_keyCode);
			}
			case RE::PC_GAMEPAD_TYPE::kOrbis: {
				return IsOrbisGamepadButtonPressed(a_keyCode);
			}
			[[unlikely]] default: {
				REX::Assert(false);
				return false;
			}
		}
	}

	bool IsXInputGamepadButtonPressed(std::uint32_t a_keyCode)
	{
		if (!IsGamepadButtonCodeInRange(a_keyCode)) {
			return false;
		}

		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		const auto* gamepadDevice = inputDeviceManager->GetPCXInputGamepad();
		if (!gamepadDevice || !gamepadDevice->IsConnected()) {
			return false;
		}

		return Impl::IsXInputGamepadButtonPressed(gamepadDevice, a_keyCode);
	}

	bool IsOrbisGamepadButtonPressed(std::uint32_t a_keyCode)
	{
		if (!IsGamepadButtonCodeInRange(a_keyCode)) {
			return false;
		}

		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		const auto* gamepadDevice = inputDeviceManager->GetPCOrbisGamepad();
		if (!gamepadDevice || !gamepadDevice->IsConnected()) {
			return false;
		}

		return Impl::IsOrbisGamepadButtonPressed(gamepadDevice, a_keyCode);
	}

	auto GetPressedKeyCodes()
		-> std::expected<std::vector<std::uint32_t>, REX::SystemError>
	{
		auto result = std::vector<std::uint32_t>();

		{
			const auto keyCodes = GetPressedKeyboardKeyCodes();
			if (keyCodes) {
				result.insert(result.end(), keyCodes->begin(), keyCodes->end());
			}
		}

		{
			const auto keyCodes = GetPressedMouseButtonCodes();
			if (keyCodes) {
				result.insert(result.end(), keyCodes->begin(), keyCodes->end());
			}
		}

		{
			const auto keyCodes = GetPressedGamepadButtonCodes();
			if (keyCodes) {
				result.insert(result.end(), keyCodes->begin(), keyCodes->end());
			}
		}

		return result;
	}

	auto GetPressedKeyboardKeyCodes()
		-> std::expected<std::vector<std::uint32_t>, REX::SystemError>
	{
		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			REX::Assert(false);
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto* keyboardDevice = inputDeviceManager->GetPCKeyboard();
		if (!keyboardDevice || !keyboardDevice->IsConnected()) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::no_such_device_or_address));
		}

		auto result = std::vector<std::uint32_t>();

		for (auto keyCode = std::to_underlying(Macro::kKeyboardOffset); keyCode < std::to_underlying(Macro::kMouseButtonOffset); keyCode++) {
			if (Impl::IsKeyboardKeyPressed(keyboardDevice, keyCode)) {
				result.push_back(keyCode);
			}
		}

		return result;
	}

	auto GetPressedMouseButtonCodes()
		-> std::expected<std::vector<std::uint32_t>, REX::SystemError>
	{
		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			REX::Assert(false);
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto* mouseDevice = inputDeviceManager->GetPCMouse();
		if (!mouseDevice || !mouseDevice->IsConnected()) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::no_such_device_or_address));
		}

		auto result = std::vector<std::uint32_t>();

		for (auto keyCode = std::to_underlying(Macro::kMouseButtonOffset); keyCode < std::to_underlying(Macro::kGamepadButtonOffset); keyCode++) {
			if (Impl::IsMouseButtonPressed(mouseDevice, keyCode)) {
				result.push_back(keyCode);
			}
		}

		return result;
	}

	auto GetPressedGamepadButtonCodes()
		-> std::expected<std::vector<std::uint32_t>, REX::SystemError>
	{
		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			REX::Assert(false);
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		switch (controlMap->pcGamepadMapType.get()) {
			case RE::PC_GAMEPAD_TYPE::kDirectX: {
				return GetPressedXInputButtonCodes();
			}
			case RE::PC_GAMEPAD_TYPE::kOrbis: {
				return GetPressedOrbisGamepadButtonCodes();
			}
			[[unlikely]] default: {
				REX::Assert(false);
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::value_too_large));
			}
		}
	}

	auto GetPressedXInputButtonCodes()
		-> std::expected<std::vector<std::uint32_t>, REX::SystemError>
	{
		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			REX::Assert(false);
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto* gamepadDevice = inputDeviceManager->GetPCXInputGamepad();
		if (!gamepadDevice || !gamepadDevice->IsConnected()) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::no_such_device_or_address));
		}

		auto result = std::vector<std::uint32_t>();

		for (auto keyCode = std::to_underlying(Macro::kGamepadButtonOffset); keyCode < std::to_underlying(Macro::kTotalButtonCount); keyCode++) {
			if (Impl::IsXInputGamepadButtonPressed(gamepadDevice, keyCode)) {
				result.push_back(keyCode);
			}
		}

		return result;
	}

	auto GetPressedOrbisGamepadButtonCodes()
		-> std::expected<std::vector<std::uint32_t>, REX::SystemError>
	{
		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			REX::Assert(false);
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto* gamepadDevice = inputDeviceManager->GetPCOrbisGamepad();
		if (!gamepadDevice || !gamepadDevice->IsConnected()) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::no_such_device_or_address));
		}

		auto result = std::vector<std::uint32_t>();

		for (auto keyCode = std::to_underlying(Macro::kGamepadButtonOffset); keyCode < std::to_underlying(Macro::kTotalButtonCount); keyCode++) {
			if (Impl::IsOrbisGamepadButtonPressed(gamepadDevice, keyCode)) {
				result.push_back(keyCode);
			}
		}

		return result;
	}

	auto GetPressedControlNames(RE::INPUT_DEVICE a_deviceType)
		-> std::expected<std::vector<RE::BSFixedString>, REX::SystemError>
	{
		auto result = std::vector<RE::BSFixedString>();

		if (a_deviceType == RE::INPUT_DEVICE::kNone || a_deviceType == RE::INPUT_DEVICE::kKeyboard) {
			const auto controlNames = GetPressedKeyboardControlNames();
			if (controlNames) {
				result.insert(result.end(), controlNames->begin(), controlNames->end());
			}
		}

		if (a_deviceType == RE::INPUT_DEVICE::kNone || a_deviceType == RE::INPUT_DEVICE::kMouse) {
			const auto controlNames = GetPressedMouseButtonControlNames();
			if (controlNames) {
				result.insert(result.end(), controlNames->begin(), controlNames->end());
			}
		}

		if (a_deviceType == RE::INPUT_DEVICE::kNone || a_deviceType == RE::INPUT_DEVICE::kGamepad) {
			const auto controlNames = GetPressedGamepadButtonControlNames();
			if (controlNames) {
				result.insert(result.end(), controlNames->begin(), controlNames->end());
			}
		}

		return result;
	}

	auto GetPressedKeyboardControlNames()
		-> std::expected<std::vector<RE::BSFixedString>, REX::SystemError>
	{
		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			REX::Assert(false);
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto* keyboardDevice = inputDeviceManager->GetPCKeyboard();
		if (!keyboardDevice || !keyboardDevice->IsConnected()) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::no_such_device_or_address));
		}

		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			REX::Assert(false);
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		auto result = std::vector<RE::BSFixedString>();

		for (auto keyCode = std::to_underlying(Macro::kKeyboardOffset); keyCode < std::to_underlying(Macro::kMouseButtonOffset); keyCode++) {
			if (!Impl::IsKeyboardKeyPressed(keyboardDevice, keyCode)) {
				continue;
			}

			auto controlName = controlMap->GetControlNameByKeyCode(keyCode, keyboardDevice->deviceType.get());
			if (!controlName) {
				continue;
			}

			result.push_back(std::move(controlName).value());
		}

		return result;
	}

	auto GetPressedMouseButtonControlNames()
		-> std::expected<std::vector<RE::BSFixedString>, REX::SystemError>
	{
		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			REX::Assert(false);
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto* mouseDevice = inputDeviceManager->GetPCMouse();
		if (!mouseDevice || !mouseDevice->IsConnected()) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::no_such_device_or_address));
		}

		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			REX::Assert(false);
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		auto result = std::vector<RE::BSFixedString>();

		for (auto keyCode = std::to_underlying(Macro::kMouseButtonOffset); keyCode < std::to_underlying(Macro::kGamepadButtonOffset); keyCode++) {
			if (!Impl::IsMouseButtonPressed(mouseDevice, keyCode)) {
				continue;
			}

			auto controlName = controlMap->GetControlNameByKeyCode(keyCode, mouseDevice->deviceType.get());
			if (!controlName) {
				continue;
			}

			result.push_back(std::move(controlName).value());
		}

		return result;
	}

	auto GetPressedGamepadButtonControlNames()
		-> std::expected<std::vector<RE::BSFixedString>, REX::SystemError>
	{
		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			REX::Assert(false);
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			REX::Assert(false);
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		switch (controlMap->pcGamepadMapType.get()) {
			case RE::PC_GAMEPAD_TYPE::kDirectX: {
				return GetPressedXInputGamepadButtonControlNames();
			}
			case RE::PC_GAMEPAD_TYPE::kOrbis: {
				return GetPressedOrbisGamepadButtonControlNames();
			}
			[[unlikely]] default: {
				REX::Assert(false);
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::value_too_large));
			}
		}
	}

	auto GetPressedXInputGamepadButtonControlNames()
		-> std::expected<std::vector<RE::BSFixedString>, REX::SystemError>
	{
		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			REX::Assert(false);
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto* gamepadDevice = inputDeviceManager->GetPCXInputGamepad();
		if (!gamepadDevice || !gamepadDevice->IsConnected()) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::no_such_device_or_address));
		}

		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			REX::Assert(false);
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		auto result = std::vector<RE::BSFixedString>();

		for (auto keyCode = std::to_underlying(Macro::kGamepadButtonOffset); keyCode < std::to_underlying(Macro::kTotalButtonCount); keyCode++) {
			if (!Impl::IsXInputGamepadButtonPressed(gamepadDevice, keyCode)) {
				continue;
			}

			auto controlName = controlMap->GetControlNameByKeyCode(keyCode, gamepadDevice->deviceType.get());
			if (!controlName) {
				continue;
			}

			result.push_back(std::move(controlName).value());
		}

		return result;
	}

	auto GetPressedOrbisGamepadButtonControlNames()
		-> std::expected<std::vector<RE::BSFixedString>, REX::SystemError>
	{
		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			REX::Assert(false);
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto* gamepadDevice = inputDeviceManager->GetPCOrbisGamepad();
		if (!gamepadDevice || !gamepadDevice->IsConnected()) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::no_such_device_or_address));
		}

		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			REX::Assert(false);
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		auto result = std::vector<RE::BSFixedString>();

		for (auto keyCode = std::to_underlying(Macro::kGamepadButtonOffset); keyCode < std::to_underlying(Macro::kTotalButtonCount); keyCode++) {
			if (!Impl::IsOrbisGamepadButtonPressed(gamepadDevice, keyCode)) {
				continue;
			}

			auto controlName = controlMap->GetControlNameByKeyCode(keyCode, gamepadDevice->deviceType.get());
			if (!controlName) {
				continue;
			}

			result.push_back(std::move(controlName).value());
		}

		return result;
	}

	auto GetKeyName(std::uint32_t a_keyCode)
		-> std::expected<RE::BSFixedStringCS, REX::SystemError>
	{
		if (!IsKeyCodeInRange(a_keyCode)) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		if (IsKeyboardKeyCodeInRange(a_keyCode)) {
			return GetKeyboardKeyName(a_keyCode);
		}

		if (IsMouseButtonCodeInRange(a_keyCode)) {
			return GetMouseButtonName(a_keyCode);
		}

		if (IsGamepadButtonCodeInRange(a_keyCode)) {
			return GetGamepadButtonName(a_keyCode);
		}

		return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
	}

	auto GetKeyboardKeyName(std::uint32_t a_keyCode)
		-> std::expected<RE::BSFixedStringCS, REX::SystemError>
	{
		if (!IsKeyboardKeyCodeInRange(a_keyCode)) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			REX::Assert(false);
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto* keyboardDevice = inputDeviceManager->GetPCKeyboard();
		if (!keyboardDevice || !keyboardDevice->IsConnected()) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::no_such_device_or_address));
		}

		const auto buttonInfo = keyboardDevice->GetButtonInfoByID(a_keyCode);
		if (!buttonInfo) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto* buttonInfoData = buttonInfo->second;
		if (!buttonInfoData) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		return buttonInfoData->name;
	}

	auto GetMouseButtonName(std::uint32_t a_keyCode)
		-> std::expected<RE::BSFixedStringCS, REX::SystemError>
	{
		if (!IsMouseButtonCodeInRange(a_keyCode)) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			REX::Assert(false);
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto* mouseDevice = inputDeviceManager->GetPCMouse();
		if (!mouseDevice || !mouseDevice->IsConnected()) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::no_such_device_or_address));
		}

		const auto buttonInfo = mouseDevice->GetButtonInfoByID(a_keyCode - Macro::kMouseButtonOffset);
		if (!buttonInfo) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto* buttonInfoData = buttonInfo->second;
		if (!buttonInfoData) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		return buttonInfoData->name;
	}

	auto GetGamepadButtonName(std::uint32_t a_keyCode)
		-> std::expected<RE::BSFixedStringCS, REX::SystemError>
	{
		if (!IsGamepadButtonCodeInRange(a_keyCode)) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			REX::Assert(false);
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		switch (controlMap->pcGamepadMapType.get()) {
			case RE::PC_GAMEPAD_TYPE::kDirectX: {
				return GetXInputGamepadButtonName(a_keyCode);
			}
			case RE::PC_GAMEPAD_TYPE::kOrbis: {
				return GetOrbisGamepadButtonName(a_keyCode);
			}
			[[unlikely]] default: {
				REX::Assert(false);
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::value_too_large));
			}
		}
	}

	auto GetXInputGamepadButtonName(std::uint32_t a_keyCode)
		-> std::expected<RE::BSFixedStringCS, REX::SystemError>
	{
		if (!IsGamepadButtonCodeInRange(a_keyCode)) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			REX::Assert(false);
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto* gamepadDevice = inputDeviceManager->GetPCXInputGamepad();
		if (!gamepadDevice || !gamepadDevice->IsConnected()) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::no_such_device_or_address));
		}

		const auto buttonInfo = gamepadDevice->GetButtonInfoByID(a_keyCode - Macro::kGamepadButtonOffset);
		if (!buttonInfo) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto* buttonInfoData = buttonInfo->second;
		if (!buttonInfoData) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		return buttonInfoData->name;
	}

	auto GetOrbisGamepadButtonName(std::uint32_t a_keyCode)
		-> std::expected<RE::BSFixedStringCS, REX::SystemError>
	{
		if (!IsGamepadButtonCodeInRange(a_keyCode)) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			REX::Assert(false);
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto* gamepadDevice = inputDeviceManager->GetPCOrbisGamepad();
		if (!gamepadDevice || !gamepadDevice->IsConnected()) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::no_such_device_or_address));
		}

		const auto buttonInfo = gamepadDevice->GetButtonInfoByID(a_keyCode - Macro::kGamepadButtonOffset);
		if (!buttonInfo) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto* buttonInfoData = buttonInfo->second;
		if (!buttonInfoData) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		return buttonInfoData->name;
	}

	auto GetControlNameByKeyCode(std::uint32_t a_keyCode)
		-> std::expected<RE::BSFixedString, REX::SystemError>
	{
		if (!IsKeyCodeInRange(a_keyCode)) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		if (IsKeyboardKeyCodeInRange(a_keyCode)) {
			auto controlName = GetControlNameByKeyboardKeyCode(a_keyCode);
			if (!controlName) {
				return std::unexpected(controlName.error());
			}

			return *std::move(controlName);
		}

		if (IsMouseButtonCodeInRange(a_keyCode)) {
			auto controlName = GetControlNameByMouseKeyCode(a_keyCode);
			if (!controlName) {
				return std::unexpected(controlName.error());
			}

			return *std::move(controlName);
		}

		if (IsGamepadButtonCodeInRange(a_keyCode)) {
			auto controlName = GetControlNameByGamepadKeyCode(a_keyCode);
			if (!controlName) {
				return std::unexpected(controlName.error());
			}

			return *std::move(controlName);
		}

		return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
	}

	auto GetControlNameByKeyboardKeyCode(std::uint32_t a_keyCode)
		-> std::expected<RE::BSFixedString, REX::SystemError>
	{
		if (!IsKeyboardKeyCodeInRange(a_keyCode)) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			REX::Assert(false);
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		auto controlName = controlMap->GetControlNameByKeyCode(a_keyCode, RE::INPUT_DEVICE::kKeyboard);
		if (!controlName) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		return *std::move(controlName);
	}

	auto GetControlNameByMouseKeyCode(std::uint32_t a_keyCode)
		-> std::expected<RE::BSFixedString, REX::SystemError>
	{
		if (!IsMouseButtonCodeInRange(a_keyCode)) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			REX::Assert(false);
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		auto controlName = controlMap->GetControlNameByKeyCode(a_keyCode, RE::INPUT_DEVICE::kMouse);
		if (!controlName) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		return *std::move(controlName);
	}

	auto GetControlNameByGamepadKeyCode(std::uint32_t a_keyCode)
		-> std::expected<RE::BSFixedString, REX::SystemError>
	{
		if (!IsGamepadButtonCodeInRange(a_keyCode)) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			REX::Assert(false);
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		auto controlName = controlMap->GetControlNameByKeyCode(a_keyCode, RE::INPUT_DEVICE::kGamepad);
		if (!controlName) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		return *std::move(controlName);
	}

	auto GetKeyCodeByControlName(const RE::BSFixedString& a_controlName, RE::INPUT_DEVICE a_deviceType)
		-> std::expected<std::uint32_t, REX::SystemError>
	{
		if (a_deviceType > RE::INPUT_DEVICE::kNone) {
			const auto* controlMap = RE::ControlMap::GetSingleton();
			if (!controlMap) [[unlikely]] {
				REX::Assert(false);
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
			}

			const auto keyCode = controlMap->GetKeyCodeByControlName(a_controlName, a_deviceType);
			if (!keyCode) {
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
			}

			return *keyCode;
		}

		{
			const auto keyCode = GetKeyCodeByKeyboardControlName(a_controlName);
			if (keyCode) {
				return keyCode.value();
			}
		}

		{
			const auto keyCode = GetKeyCodeByMouseControlName(a_controlName);
			if (keyCode) {
				return keyCode.value();
			}
		}

		{
			const auto keyCode = GetKeyCodeByGamepadControlName(a_controlName);
			if (keyCode) {
				return keyCode.value();
			}
		}

		return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
	}

	auto GetKeyCodeByKeyboardControlName(const RE::BSFixedString& a_controlName)
		-> std::expected<std::uint32_t, REX::SystemError>
	{
		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			REX::Assert(false);
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto keyCode = controlMap->GetKeyCodeByControlName(a_controlName, RE::INPUT_DEVICE::kKeyboard);
		if (!keyCode) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		return *keyCode;
	}

	auto GetKeyCodeByMouseControlName(const RE::BSFixedString& a_controlName)
		-> std::expected<std::uint32_t, REX::SystemError>
	{
		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			REX::Assert(false);
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto keyCode = controlMap->GetKeyCodeByControlName(a_controlName, RE::INPUT_DEVICE::kMouse);
		if (!keyCode) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		return *keyCode;
	}

	auto GetKeyCodeByGamepadControlName(const RE::BSFixedString& a_controlName)
		-> std::expected<std::uint32_t, REX::SystemError>
	{
		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			REX::Assert(false);
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto keyCode = controlMap->GetKeyCodeByControlName(a_controlName, RE::INPUT_DEVICE::kGamepad);
		if (!keyCode) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		return *keyCode;
	}

	bool HoldKey(std::uint32_t a_keyCode)
	{
		return HoldKeyboardKey(a_keyCode) ||
			   HoldMouseButton(a_keyCode) ||
			   HoldGamepadButton(a_keyCode);
	}

	bool HoldKeyboardKey(std::uint32_t a_keyCode)
	{
		return Impl::PressKeyboardKey(a_keyCode, true);
	}

	bool HoldMouseButton(std::uint32_t a_keyCode)
	{
		return Impl::PressMouseButton(a_keyCode, true);
	}

	bool HoldGamepadButton(std::uint32_t a_keyCode)
	{
		if (!IsGamepadButtonCodeInRange(a_keyCode)) {
			return false;
		}

		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		switch (controlMap->pcGamepadMapType.get()) {
			case RE::PC_GAMEPAD_TYPE::kDirectX: {
				return HoldXInputGamepadButton(a_keyCode);
			}
			case RE::PC_GAMEPAD_TYPE::kOrbis: {
				return HoldOrbisGamepadButton(a_keyCode);
			}
			[[unlikely]] default: {
				REX::Assert(false);
				return false;
			}
		}
	}

	bool HoldXInputGamepadButton(std::uint32_t a_keyCode)
	{
		return Impl::PressXInputGamepadButton(a_keyCode, true);
	}

	bool HoldOrbisGamepadButton(std::uint32_t a_keyCode)
	{
		return Impl::PressOrbisGamepadButton(a_keyCode, true);
	}

	bool ReleaseKey(std::uint32_t a_keyCode, REX::Float32 a_deltaTime)
	{
		return ReleaseKeyboardKey(a_keyCode, a_deltaTime) ||
			   ReleaseMouseButton(a_keyCode, a_deltaTime) ||
			   ReleaseGamepadButton(a_keyCode, a_deltaTime);
	}

	bool ReleaseKeyboardKey(std::uint32_t a_keyCode, REX::Float32 a_deltaTime)
	{
		return Impl::PressKeyboardKey(a_keyCode, false, a_deltaTime);
	}

	bool ReleaseMouseButton(std::uint32_t a_keyCode, REX::Float32 a_deltaTime)
	{
		return Impl::PressMouseButton(a_keyCode, false, a_deltaTime);
	}

	bool ReleaseGamepadButton(std::uint32_t a_keyCode, REX::Float32 a_deltaTime)
	{
		if (!IsGamepadButtonCodeInRange(a_keyCode)) {
			return false;
		}

		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		switch (controlMap->pcGamepadMapType.get()) {
			case RE::PC_GAMEPAD_TYPE::kDirectX: {
				return ReleaseXInputGamepadButton(a_keyCode, a_deltaTime);
			}
			case RE::PC_GAMEPAD_TYPE::kOrbis: {
				return ReleaseOrbisGamepadButton(a_keyCode, a_deltaTime);
			}
			[[unlikely]] default: {
				REX::Assert(false);
				return false;
			}
		}
	}

	bool ReleaseXInputGamepadButton(std::uint32_t a_keyCode, REX::Float32 a_deltaTime)
	{
		return Impl::PressXInputGamepadButton(a_keyCode, false, a_deltaTime);
	}

	bool ReleaseOrbisGamepadButton(std::uint32_t a_keyCode, REX::Float32 a_deltaTime)
	{
		return Impl::PressOrbisGamepadButton(a_keyCode, false, a_deltaTime);
	}

	bool TapKey(std::uint32_t a_keyCode, REX::Float32 a_durationSeconds)
	{
		return TapKeyboardKey(a_keyCode, a_durationSeconds) ||
			   TapMouseButton(a_keyCode, a_durationSeconds) ||
			   TapGamepadButton(a_keyCode, a_durationSeconds);
	}

	bool TapKeyboardKey(std::uint32_t a_keyCode, REX::Float32 a_durationSeconds)
	{
		return HoldKeyboardKey(a_keyCode) &&
			   ReleaseKeyboardKey(a_keyCode, a_durationSeconds);
	}

	bool TapMouseButton(std::uint32_t a_keyCode, REX::Float32 a_durationSeconds)
	{
		return HoldMouseButton(a_keyCode) &&
			   ReleaseMouseButton(a_keyCode, a_durationSeconds);
	}

	bool TapGamepadButton(std::uint32_t a_keyCode, REX::Float32 a_durationSeconds)
	{
		return HoldGamepadButton(a_keyCode) &&
			   ReleaseGamepadButton(a_keyCode, a_durationSeconds);
	}

	bool TapXInputGamepadButton(std::uint32_t a_keyCode, REX::Float32 a_durationSeconds)
	{
		return HoldXInputGamepadButton(a_keyCode) &&
			   ReleaseXInputGamepadButton(a_keyCode, a_durationSeconds);
	}

	bool TapOrbisGamepadButton(std::uint32_t a_keyCode, REX::Float32 a_durationSeconds)
	{
		return HoldOrbisGamepadButton(a_keyCode) &&
			   ReleaseOrbisGamepadButton(a_keyCode, a_durationSeconds);
	}

	auto GamepadFlagToKeyCode(std::uint32_t a_keyFlag)
		-> std::expected<std::uint32_t, REX::SystemError>
	{
		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			REX::Assert(false);
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		switch (controlMap->pcGamepadMapType.get()) {
			case RE::PC_GAMEPAD_TYPE::kDirectX: {
				auto result = XInputGamepadFlagToKeyCode(a_keyFlag);
				if (!result) {
					return std::unexpected(result.error());
				}

				return *result;
			}
			case RE::PC_GAMEPAD_TYPE::kOrbis: {
				auto result = OrbisGamepadFlagToKeyCode(a_keyFlag);
				if (!result) {
					return std::unexpected(result.error());
				}

				return *result;
			}
			[[unlikely]] default: {
				REX::Assert(false);
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::value_too_large));
			}
		}
	}

	auto GamepadKeyCodeToFlag(std::uint32_t a_keyCode)
		-> std::expected<std::uint32_t, REX::SystemError>
	{
		if (!IsGamepadButtonCodeInRange(a_keyCode)) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			REX::Assert(false);
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		switch (controlMap->pcGamepadMapType.get()) {
			case RE::PC_GAMEPAD_TYPE::kDirectX: {
				auto result = XInputGamepadKeyCodeToFlag(a_keyCode);
				if (!result) {
					return std::unexpected(result.error());
				}

				return *result;
			}
			case RE::PC_GAMEPAD_TYPE::kOrbis: {
				auto result = OrbisGamepadKeyCodeToFlag(a_keyCode);
				if (!result) {
					return std::unexpected(result.error());
				}

				return *result;
			}
			[[unlikely]] default: {
				REX::Assert(false);
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::value_too_large));
			}
		}
	}

	auto XInputGamepadFlagToScePadFlag(std::uint32_t a_keyFlag) noexcept
		-> std::expected<std::uint32_t, REX::SystemError>
	{
		switch (a_keyFlag) {
			case REX::W32::XINPUT_GAMEPAD_DPAD_UP: {
				return REX::PS4::SCE_PAD_BUTTON_UP;
			}
			case REX::W32::XINPUT_GAMEPAD_DPAD_DOWN: {
				return REX::PS4::SCE_PAD_BUTTON_DOWN;
			}
			case REX::W32::XINPUT_GAMEPAD_DPAD_LEFT: {
				return REX::PS4::SCE_PAD_BUTTON_LEFT;
			}
			case REX::W32::XINPUT_GAMEPAD_DPAD_RIGHT: {
				return REX::PS4::SCE_PAD_BUTTON_RIGHT;
			}
			case REX::W32::XINPUT_GAMEPAD_START: {
				return REX::PS4::SCE_PAD_BUTTON_OPTIONS;
			}
			case REX::W32::XINPUT_GAMEPAD_BACK: {
				return REX::PS4::SCE_PAD_BUTTON_TOUCH_PAD;
			}
			case REX::W32::XINPUT_GAMEPAD_LEFT_THUMB: {
				return REX::PS4::SCE_PAD_BUTTON_L3;
			}
			case REX::W32::XINPUT_GAMEPAD_RIGHT_THUMB: {
				return REX::PS4::SCE_PAD_BUTTON_R3;
			}
			case REX::W32::XINPUT_GAMEPAD_LEFT_SHOULDER: {
				return REX::PS4::SCE_PAD_BUTTON_L1;
			}
			case REX::W32::XINPUT_GAMEPAD_RIGHT_SHOULDER: {
				return REX::PS4::SCE_PAD_BUTTON_R1;
			}
			case REX::W32::XINPUT_GAMEPAD_A: {
				return REX::PS4::SCE_PAD_BUTTON_CROSS;
			}
			case REX::W32::XINPUT_GAMEPAD_B: {
				return REX::PS4::SCE_PAD_BUTTON_CIRCLE;
			}
			case REX::W32::XINPUT_GAMEPAD_X: {
				return REX::PS4::SCE_PAD_BUTTON_SQUARE;
			}
			case REX::W32::XINPUT_GAMEPAD_Y: {
				return REX::PS4::SCE_PAD_BUTTON_TRIANGLE;
			}
			[[unlikely]] default: {
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
			}
		}
	}

	auto ScePadFlagToXInputGamepadFlag(std::uint32_t a_keyFlag) noexcept
		-> std::expected<std::uint32_t, REX::SystemError>
	{
		switch (a_keyFlag) {
			case REX::PS4::SCE_PAD_BUTTON_UP: {
				return REX::W32::XINPUT_GAMEPAD_DPAD_UP;
			}
			case REX::PS4::SCE_PAD_BUTTON_DOWN: {
				return REX::W32::XINPUT_GAMEPAD_DPAD_DOWN;
			}
			case REX::PS4::SCE_PAD_BUTTON_LEFT: {
				return REX::W32::XINPUT_GAMEPAD_DPAD_LEFT;
			}
			case REX::PS4::SCE_PAD_BUTTON_RIGHT: {
				return REX::W32::XINPUT_GAMEPAD_DPAD_RIGHT;
			}
			case REX::PS4::SCE_PAD_BUTTON_OPTIONS: {
				return REX::W32::XINPUT_GAMEPAD_START;
			}
			case REX::PS4::SCE_PAD_BUTTON_TOUCH_PAD: {
				return REX::W32::XINPUT_GAMEPAD_BACK;
			}
			case REX::PS4::SCE_PAD_BUTTON_L3: {
				return REX::W32::XINPUT_GAMEPAD_LEFT_THUMB;
			}
			case REX::PS4::SCE_PAD_BUTTON_R3: {
				return REX::W32::XINPUT_GAMEPAD_RIGHT_THUMB;
			}
			case REX::PS4::SCE_PAD_BUTTON_L1: {
				return REX::W32::XINPUT_GAMEPAD_LEFT_SHOULDER;
			}
			case REX::PS4::SCE_PAD_BUTTON_R1: {
				return REX::W32::XINPUT_GAMEPAD_RIGHT_SHOULDER;
			}
			case REX::PS4::SCE_PAD_BUTTON_CROSS: {
				return REX::W32::XINPUT_GAMEPAD_A;
			}
			case REX::PS4::SCE_PAD_BUTTON_CIRCLE: {
				return REX::W32::XINPUT_GAMEPAD_B;
			}
			case REX::PS4::SCE_PAD_BUTTON_SQUARE: {
				return REX::W32::XINPUT_GAMEPAD_X;
			}
			case REX::PS4::SCE_PAD_BUTTON_TRIANGLE: {
				return REX::W32::XINPUT_GAMEPAD_Y;
			}
			[[unlikely]] default: {
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
			}
		}
	}

	auto XInputGamepadFlagToKeyCode(std::uint32_t a_keyFlag) noexcept
		-> std::expected<std::uint32_t, REX::SystemError>
	{
		switch (a_keyFlag) {
			case REX::W32::XINPUT_GAMEPAD_DPAD_UP: {
				return GamepadButton::kDPadUp;
			}
			case REX::W32::XINPUT_GAMEPAD_DPAD_DOWN: {
				return GamepadButton::kDPadDown;
			}
			case REX::W32::XINPUT_GAMEPAD_DPAD_LEFT: {
				return GamepadButton::kDPadLeft;
			}
			case REX::W32::XINPUT_GAMEPAD_DPAD_RIGHT: {
				return GamepadButton::kDPadRight;
			}
			case REX::W32::XINPUT_GAMEPAD_START: {
				return GamepadButton::kStart;
			}
			case REX::W32::XINPUT_GAMEPAD_BACK: {
				return GamepadButton::kBack;
			}
			case REX::W32::XINPUT_GAMEPAD_LEFT_THUMB: {
				return GamepadButton::kLeftThumb;
			}
			case REX::W32::XINPUT_GAMEPAD_RIGHT_THUMB: {
				return GamepadButton::kRightThumb;
			}
			case REX::W32::XINPUT_GAMEPAD_LEFT_SHOULDER: {
				return GamepadButton::kLeftShoulder;
			}
			case REX::W32::XINPUT_GAMEPAD_RIGHT_SHOULDER: {
				return GamepadButton::kRightShoulder;
			}
			case REX::W32::XINPUT_GAMEPAD_A: {
				return GamepadButton::kA;
			}
			case REX::W32::XINPUT_GAMEPAD_B: {
				return GamepadButton::kB;
			}
			case REX::W32::XINPUT_GAMEPAD_X: {
				return GamepadButton::kX;
			}
			case REX::W32::XINPUT_GAMEPAD_Y: {
				return GamepadButton::kY;
			}
			[[unlikely]] default: {
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
			}
		}
	}

	auto XInputGamepadKeyCodeToFlag(std::uint32_t a_keyCode) noexcept
		-> std::expected<std::uint32_t, REX::SystemError>
	{
		switch (a_keyCode) {
			case GamepadButton::kDPadUp: {
				return REX::W32::XINPUT_GAMEPAD_DPAD_UP;
			}
			case GamepadButton::kDPadDown: {
				return REX::W32::XINPUT_GAMEPAD_DPAD_DOWN;
			}
			case GamepadButton::kDPadLeft: {
				return REX::W32::XINPUT_GAMEPAD_DPAD_LEFT;
			}
			case GamepadButton::kDPadRight: {
				return REX::W32::XINPUT_GAMEPAD_DPAD_RIGHT;
			}
			case GamepadButton::kStart: {
				return REX::W32::XINPUT_GAMEPAD_START;
			}
			case GamepadButton::kBack: {
				return REX::W32::XINPUT_GAMEPAD_BACK;
			}
			case GamepadButton::kLeftThumb: {
				return REX::W32::XINPUT_GAMEPAD_LEFT_THUMB;
			}
			case GamepadButton::kRightThumb: {
				return REX::W32::XINPUT_GAMEPAD_RIGHT_THUMB;
			}
			case GamepadButton::kLeftShoulder: {
				return REX::W32::XINPUT_GAMEPAD_LEFT_SHOULDER;
			}
			case GamepadButton::kRightShoulder: {
				return REX::W32::XINPUT_GAMEPAD_RIGHT_SHOULDER;
			}
			case GamepadButton::kA: {
				return REX::W32::XINPUT_GAMEPAD_A;
			}
			case GamepadButton::kB: {
				return REX::W32::XINPUT_GAMEPAD_B;
			}
			case GamepadButton::kX: {
				return REX::W32::XINPUT_GAMEPAD_X;
			}
			case GamepadButton::kY: {
				return REX::W32::XINPUT_GAMEPAD_Y;
			}
			[[unlikely]] default: {
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
			}
		}
	}

	auto OrbisGamepadFlagToKeyCode(std::uint32_t a_keyFlag) noexcept
		-> std::expected<std::uint32_t, REX::SystemError>
	{
		auto newKeyFlag = ScePadFlagToXInputGamepadFlag(a_keyFlag);
		if (!newKeyFlag) {
			return std::unexpected(newKeyFlag.error());
		}

		return XInputGamepadFlagToKeyCode(*newKeyFlag);
	}

	auto OrbisGamepadKeyCodeToFlag(std::uint32_t a_keyCode) noexcept
		-> std::expected<std::uint32_t, REX::SystemError>
	{
		auto newKeyCode = XInputGamepadKeyCodeToFlag(a_keyCode);
		if (!newKeyCode) {
			return std::unexpected(newKeyCode.error());
		}

		return XInputGamepadFlagToScePadFlag(*newKeyCode);
	}
}
