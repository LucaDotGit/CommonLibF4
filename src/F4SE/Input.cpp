#include "F4SE/Input.hpp"

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSInputDeviceManager.hpp"
#include "RE/B/BSPCGamepadDevice.hpp"
#include "RE/B/BSPCKeyboardDevice.hpp"
#include "RE/B/BSPCMouseDevice.hpp"
#include "RE/B/BSPCOrbisGamepadDevice.hpp"
#include "RE/C/ControlMap.hpp"
#include "RE/I/INPUT_DEVICE.hpp"
#include "RE/P/PC_GAMEPAD_TYPE.hpp"
#include "REX/Contract.hpp"
#include "REX/Error.hpp"
#include "REX/PS4/SCEPAD.hpp"
#include "REX/W32/XINPUT.hpp"

namespace F4SE::Input::Impl
{
	namespace
	{
		static_assert(Macro::KeyboardOffset < Macro::MouseButtonOffset);
		static_assert(Macro::MouseButtonOffset < Macro::GamepadButtonOffset);
		static_assert(Macro::GamepadButtonOffset < Macro::TotalButtonCount);

		constexpr auto ABSOLUTE_LEFT_TRIGGER_BUTTON_CODE =
			std::to_underlying(Macro::GamepadButtonOffset) + std::to_underlying(XInput::GameButton_LeftTrigger);
		constexpr auto ABSOLUTE_RIGHT_TRIGGER_BUTTON_CODE =
			std::to_underlying(Macro::GamepadButtonOffset) + std::to_underlying(XInput::GameButton_RightTrigger);

		[[nodiscard]]
		auto IsKeyboardKeyPressed(const RE::BSPCKeyboardDevice* a_keyboardDevice, KeyCode a_keyCode) noexcept -> bool
		{
			if (!a_keyboardDevice) {
				return false;
			}

			constexpr auto MAX_KEYBOARD_KEY_INDEX =
				std::to_underlying(Macro::MouseButtonOffset) - std::to_underlying(Macro::KeyboardOffset);

			const auto keyIndex = a_keyCode - std::to_underlying(Macro::KeyboardOffset);
			if (keyIndex >= MAX_KEYBOARD_KEY_INDEX) {
				return false;
			}

			return a_keyboardDevice->currKeyStates[keyIndex];
		}

		[[nodiscard]]
		auto IsMouseButtonPressed(const RE::BSPCMouseDevice* a_mouseDevice, KeyCode a_keyCode) noexcept -> bool
		{
			if (!a_mouseDevice) {
				return false;
			}

			constexpr auto MAX_MOUSE_BUTTON_INDEX =
				std::to_underlying(Macro::GamepadButtonOffset) - std::to_underlying(Macro::MouseButtonOffset);

			const auto buttonIndex = a_keyCode - std::to_underlying(Macro::MouseButtonOffset);
			if (buttonIndex >= MAX_MOUSE_BUTTON_INDEX) {
				return false;
			}

			const auto buttonFlag = static_cast<RE::BSPCMouseDevice::ButtonFlags>(1 << buttonIndex);
			return a_mouseDevice->currButtonFlags.any(buttonFlag);
		}

		[[nodiscard]]
		auto IsXInputGamepadButtonPressed(const RE::BSPCGamepadDevice* a_gamepadDevice, KeyCode a_keyCode) noexcept
			-> bool
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
			if (!buttonFlag.has_value()) {
				return false;
			}

			return (gamepadState.buttons & buttonFlag.value()) != 0;
		}

		[[nodiscard]]
		auto IsOrbisGamepadButtonPressed(const RE::BSPCOrbisGamepadDevice* a_gamepadDevice, KeyCode a_keyCode) noexcept
			-> bool
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
			if (!buttonFlag.has_value()) {
				return false;
			}

			return (gamepadState.buttons & buttonFlag.value()) != 0;
		}

		[[nodiscard]]
		auto PressKeyboardKey(KeyCode a_keyCode, bool a_isPressed, DeltaTime a_deltaTime = DeltaTime::zero()) -> bool
		{
			if (!IsKeyboardKeyCodeInRange(a_keyCode)) {
				return false;
			}

			const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
			if (!inputDeviceManager) {
				return false;
			}

			auto* keyboardDevice = inputDeviceManager->GetPCKeyboard();
			if (!keyboardDevice || !keyboardDevice->IsConnected()) {
				return false;
			}

			const auto buttonInfo = keyboardDevice->GetButtonInfoByID(a_keyCode);
			if (!buttonInfo.has_value()) {
				return false;
			}

			const auto buttonID = buttonInfo->first;
			keyboardDevice->CreateButtonEvent(buttonID, a_deltaTime.count(), !a_isPressed, a_isPressed);

			return true;
		}

		[[nodiscard]]
		auto PressMouseButton(KeyCode a_keyCode, bool a_isPressed, DeltaTime a_deltaTime = DeltaTime::zero()) -> bool
		{
			if (!IsMouseButtonCodeInRange(a_keyCode)) {
				return false;
			}

			const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
			if (!inputDeviceManager) {
				return false;
			}

			auto* mouseDevice = inputDeviceManager->GetPCMouse();
			if (!mouseDevice || !mouseDevice->IsConnected()) {
				return false;
			}

			const auto buttonInfo =
				mouseDevice->GetButtonInfoByID(a_keyCode - std::to_underlying(Macro::MouseButtonOffset));
			if (!buttonInfo.has_value()) {
				return false;
			}

			const auto buttonID = buttonInfo->first;
			mouseDevice->CreateButtonEvent(buttonID, a_deltaTime.count(), !a_isPressed, a_isPressed);

			return true;
		}

		[[nodiscard]]
		auto PressXInputGamepadButton(KeyCode a_keyCode, bool a_isPressed, DeltaTime a_deltaTime = DeltaTime::zero())
			-> bool
		{
			if (!IsGamepadButtonCodeInRange(a_keyCode)) {
				return false;
			}

			const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
			if (!inputDeviceManager) {
				return false;
			}

			auto* gamepadDevice = inputDeviceManager->GetPCXInputGamepad();
			if (!gamepadDevice || !gamepadDevice->IsConnected()) {
				return false;
			}

			const auto buttonInfo =
				gamepadDevice->GetButtonInfoByID(a_keyCode - std::to_underlying(Macro::GamepadButtonOffset));
			if (!buttonInfo.has_value()) {
				return false;
			}

			const auto buttonID = buttonInfo->first;
			gamepadDevice->CreateButtonEvent(buttonID, a_deltaTime.count(), !a_isPressed, a_isPressed);

			return true;
		}

		[[nodiscard]]
		auto PressOrbisGamepadButton(KeyCode a_keyCode, bool a_isPressed, DeltaTime a_deltaTime = DeltaTime::zero())
			-> bool
		{
			if (!IsGamepadButtonCodeInRange(a_keyCode)) {
				return false;
			}

			const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
			if (!inputDeviceManager) {
				return false;
			}

			auto* gamepadDevice = inputDeviceManager->GetPCOrbisGamepad();
			if (!gamepadDevice || !gamepadDevice->IsConnected()) {
				return false;
			}

			const auto buttonInfo =
				gamepadDevice->GetButtonInfoByID(a_keyCode - std::to_underlying(Macro::GamepadButtonOffset));
			if (!buttonInfo.has_value()) {
				return false;
			}

			const auto buttonID = buttonInfo->first;
			gamepadDevice->CreateButtonEvent(buttonID, a_deltaTime.count(), !a_isPressed, a_isPressed);

			return true;
		}
	}
}

namespace F4SE::Input
{
	auto IsGamepadConnected() -> bool
	{
		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) {
			return false;
		}

		return inputDeviceManager->IsGamepadConnected();
	}

	auto IsKeyCodeInRange(KeyCode a_keyCode) noexcept -> bool
	{
		return IsKeyboardKeyCodeInRange(a_keyCode) ||
			   IsMouseButtonCodeInRange(a_keyCode) ||
			   IsGamepadButtonCodeInRange(a_keyCode);
	}

	auto IsKeyboardKeyCodeInRange(KeyCode a_keyCode) noexcept -> bool
	{
		return std::cmp_greater_equal(a_keyCode, std::to_underlying(Macro::KeyboardOffset)) &&
			   std::cmp_less(a_keyCode, std::to_underlying(Macro::MouseButtonOffset));
	}

	auto IsMouseButtonCodeInRange(KeyCode a_keyCode) noexcept -> bool
	{
		return std::cmp_greater_equal(a_keyCode, std::to_underlying(Macro::MouseButtonOffset)) &&
			   std::cmp_less(a_keyCode, std::to_underlying(Macro::GamepadButtonOffset));
	}

	auto IsGamepadButtonCodeInRange(KeyCode a_keyCode) noexcept -> bool
	{
		return std::cmp_greater_equal(a_keyCode, std::to_underlying(Macro::GamepadButtonOffset)) &&
			   std::cmp_less(a_keyCode, std::to_underlying(Macro::TotalButtonCount));
	}

	auto IsKeyCodeValid(KeyCode a_keyCode) -> bool
	{
		return IsKeyboardKeyCodeValid(a_keyCode) ||
			   IsMouseButtonCodeValid(a_keyCode) ||
			   IsGamepadButtonCodeValid(a_keyCode);
	}

	auto IsKeyboardKeyCodeValid(KeyCode a_keyCode) -> bool
	{
		if (!IsKeyboardKeyCodeInRange(a_keyCode)) {
			return false;
		}

		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) {
			return false;
		}

		const auto* keyboardDevice = inputDeviceManager->GetPCKeyboard();
		if (!keyboardDevice || !keyboardDevice->IsConnected()) {
			return false;
		}

		return keyboardDevice->ContainsButtonID(a_keyCode);
	}

	auto IsMouseButtonCodeValid(KeyCode a_keyCode) -> bool
	{
		if (!IsMouseButtonCodeInRange(a_keyCode)) {
			return false;
		}

		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) {
			return false;
		}

		const auto* mouseDevice = inputDeviceManager->GetPCMouse();
		if (!mouseDevice || !mouseDevice->IsConnected()) {
			return false;
		}

		return mouseDevice->ContainsButtonID(a_keyCode - std::to_underlying(Macro::MouseButtonOffset));
	}

	auto IsGamepadButtonCodeValid(KeyCode a_keyCode) -> bool
	{
		if (!IsGamepadButtonCodeInRange(a_keyCode)) {
			return false;
		}

		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) {
			return false;
		}

		switch (controlMap->pcGamepadMapType.get()) {
			case RE::PC_GAMEPAD_TYPE::DirectX: {
				return IsXInputGamepadButtonCodeValid(a_keyCode);
			}
			case RE::PC_GAMEPAD_TYPE::Orbis: {
				return IsOrbisGamepadButtonCodeValid(a_keyCode);
			}
			[[unlikely]]
			default: {
				REX::Assert(false);
				return false;
			}
		}
	}

	auto IsXInputGamepadButtonCodeValid(KeyCode a_keyCode) -> bool
	{
		if (!IsGamepadButtonCodeInRange(a_keyCode)) {
			return false;
		}

		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) {
			return false;
		}

		const auto* gamepadDevice = inputDeviceManager->GetPCXInputGamepad();
		if (!gamepadDevice || !gamepadDevice->IsConnected()) {
			return false;
		}

		return gamepadDevice->ContainsButtonID(a_keyCode - std::to_underlying(Macro::GamepadButtonOffset));
	}

	auto IsOrbisGamepadButtonCodeValid(KeyCode a_keyCode) -> bool
	{
		if (!IsGamepadButtonCodeInRange(a_keyCode)) {
			return false;
		}

		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) {
			return false;
		}

		const auto* gamepadDevice = inputDeviceManager->GetPCOrbisGamepad();
		if (!gamepadDevice || !gamepadDevice->IsConnected()) {
			return false;
		}

		return gamepadDevice->ContainsButtonID(a_keyCode - std::to_underlying(Macro::GamepadButtonOffset));
	}

	auto IsKeyPressed(KeyCode a_keyCode) -> bool
	{
		return IsKeyboardKeyPressed(a_keyCode) || IsMouseButtonPressed(a_keyCode) || IsGamepadButtonPressed(a_keyCode);
	}

	auto IsKeyboardKeyPressed(KeyCode a_keyCode) -> bool
	{
		if (!IsKeyboardKeyCodeInRange(a_keyCode)) {
			return false;
		}

		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) {
			return false;
		}

		const auto* keyboardDevice = inputDeviceManager->GetPCKeyboard();
		if (!keyboardDevice || !keyboardDevice->IsConnected()) {
			return false;
		}

		return Impl::IsKeyboardKeyPressed(keyboardDevice, a_keyCode);
	}

	auto IsMouseButtonPressed(KeyCode a_keyCode) -> bool
	{
		if (!IsMouseButtonCodeInRange(a_keyCode)) {
			return false;
		}

		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) {
			return false;
		}

		const auto* mouseDevice = inputDeviceManager->GetPCMouse();
		if (!mouseDevice || !mouseDevice->IsConnected()) {
			return false;
		}

		return Impl::IsMouseButtonPressed(mouseDevice, a_keyCode);
	}

	auto IsGamepadButtonPressed(KeyCode a_keyCode) -> bool
	{
		if (!IsGamepadButtonCodeInRange(a_keyCode)) {
			return false;
		}

		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) {
			return false;
		}

		switch (controlMap->pcGamepadMapType.get()) {
			case RE::PC_GAMEPAD_TYPE::DirectX: {
				return IsXInputGamepadButtonPressed(a_keyCode);
			}
			case RE::PC_GAMEPAD_TYPE::Orbis: {
				return IsOrbisGamepadButtonPressed(a_keyCode);
			}
			[[unlikely]]
			default: {
				REX::Assert(false);
				return false;
			}
		}
	}

	auto IsXInputGamepadButtonPressed(KeyCode a_keyCode) -> bool
	{
		if (!IsGamepadButtonCodeInRange(a_keyCode)) {
			return false;
		}

		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) {
			return false;
		}

		const auto* gamepadDevice = inputDeviceManager->GetPCXInputGamepad();
		if (!gamepadDevice || !gamepadDevice->IsConnected()) {
			return false;
		}

		return Impl::IsXInputGamepadButtonPressed(gamepadDevice, a_keyCode);
	}

	auto IsOrbisGamepadButtonPressed(KeyCode a_keyCode) -> bool
	{
		if (!IsGamepadButtonCodeInRange(a_keyCode)) {
			return false;
		}

		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) {
			return false;
		}

		const auto* gamepadDevice = inputDeviceManager->GetPCOrbisGamepad();
		if (!gamepadDevice || !gamepadDevice->IsConnected()) {
			return false;
		}

		return Impl::IsOrbisGamepadButtonPressed(gamepadDevice, a_keyCode);
	}

	auto GetPressedKeyCodes() -> std::expected<std::vector<KeyCode>, REX::SystemError>
	{
		auto result = std::vector<KeyCode>();

		{
			const auto keyCodes = GetPressedKeyboardKeyCodes();
			if (keyCodes.has_value()) {
				result.insert(result.end(), keyCodes->begin(), keyCodes->end());
			}
		}

		{
			const auto keyCodes = GetPressedMouseButtonCodes();
			if (keyCodes.has_value()) {
				result.insert(result.end(), keyCodes->begin(), keyCodes->end());
			}
		}

		{
			const auto keyCodes = GetPressedGamepadButtonCodes();
			if (keyCodes.has_value()) {
				result.insert(result.end(), keyCodes->begin(), keyCodes->end());
			}
		}

		return result;
	}

	auto GetPressedKeyboardKeyCodes() -> std::expected<std::vector<KeyCode>, REX::SystemError>
	{
		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto* keyboardDevice = inputDeviceManager->GetPCKeyboard();
		if (!keyboardDevice || !keyboardDevice->IsConnected()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::no_such_device_or_address));
		}

		auto result = std::vector<KeyCode>();

		for (auto keyCode = std::to_underlying(Macro::KeyboardOffset);
			 keyCode < std::to_underlying(Macro::MouseButtonOffset);
			 keyCode++) {
			if (Impl::IsKeyboardKeyPressed(keyboardDevice, keyCode)) {
				result.push_back(keyCode);
			}
		}

		return result;
	}

	auto GetPressedMouseButtonCodes() -> std::expected<std::vector<KeyCode>, REX::SystemError>
	{
		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto* mouseDevice = inputDeviceManager->GetPCMouse();
		if (!mouseDevice || !mouseDevice->IsConnected()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::no_such_device_or_address));
		}

		auto result = std::vector<KeyCode>();

		for (auto keyCode = std::to_underlying(Macro::MouseButtonOffset);
			 keyCode < std::to_underlying(Macro::GamepadButtonOffset);
			 keyCode++) {
			if (Impl::IsMouseButtonPressed(mouseDevice, keyCode)) {
				result.push_back(keyCode);
			}
		}

		return result;
	}

	auto GetPressedGamepadButtonCodes() -> std::expected<std::vector<KeyCode>, REX::SystemError>
	{
		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		switch (controlMap->pcGamepadMapType.get()) {
			case RE::PC_GAMEPAD_TYPE::DirectX: {
				return GetPressedXInputButtonCodes();
			}
			case RE::PC_GAMEPAD_TYPE::Orbis: {
				return GetPressedOrbisGamepadButtonCodes();
			}
			[[unlikely]]
			default: {
				REX::Assert(false);
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::value_too_large));
			}
		}
	}

	auto GetPressedXInputButtonCodes() -> std::expected<std::vector<KeyCode>, REX::SystemError>
	{
		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto* gamepadDevice = inputDeviceManager->GetPCXInputGamepad();
		if (!gamepadDevice || !gamepadDevice->IsConnected()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::no_such_device_or_address));
		}

		auto result = std::vector<KeyCode>();

		for (auto keyCode = std::to_underlying(Macro::GamepadButtonOffset);
			 keyCode < std::to_underlying(Macro::TotalButtonCount);
			 keyCode++) {
			if (Impl::IsXInputGamepadButtonPressed(gamepadDevice, keyCode)) {
				result.push_back(keyCode);
			}
		}

		return result;
	}

	auto GetPressedOrbisGamepadButtonCodes() -> std::expected<std::vector<KeyCode>, REX::SystemError>
	{
		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto* gamepadDevice = inputDeviceManager->GetPCOrbisGamepad();
		if (!gamepadDevice || !gamepadDevice->IsConnected()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::no_such_device_or_address));
		}

		auto result = std::vector<KeyCode>();

		for (auto keyCode = std::to_underlying(Macro::GamepadButtonOffset);
			 keyCode < std::to_underlying(Macro::TotalButtonCount);
			 keyCode++) {
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

		if (a_deviceType == RE::INPUT_DEVICE::None || a_deviceType == RE::INPUT_DEVICE::Keyboard) {
			const auto controlNames = GetPressedKeyboardControlNames();
			if (controlNames.has_value()) {
				result.insert(result.end(), controlNames->begin(), controlNames->end());
			}
		}

		if (a_deviceType == RE::INPUT_DEVICE::None || a_deviceType == RE::INPUT_DEVICE::Mouse) {
			const auto controlNames = GetPressedMouseButtonControlNames();
			if (controlNames.has_value()) {
				result.insert(result.end(), controlNames->begin(), controlNames->end());
			}
		}

		if (a_deviceType == RE::INPUT_DEVICE::None || a_deviceType == RE::INPUT_DEVICE::Gamepad) {
			const auto controlNames = GetPressedGamepadButtonControlNames();
			if (controlNames.has_value()) {
				result.insert(result.end(), controlNames->begin(), controlNames->end());
			}
		}

		return result;
	}

	auto GetPressedKeyboardControlNames() -> std::expected<std::vector<RE::BSFixedString>, REX::SystemError>
	{
		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto* keyboardDevice = inputDeviceManager->GetPCKeyboard();
		if (!keyboardDevice || !keyboardDevice->IsConnected()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::no_such_device_or_address));
		}

		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		auto result = std::vector<RE::BSFixedString>();

		for (auto keyCode = std::to_underlying(Macro::KeyboardOffset);
			 keyCode < std::to_underlying(Macro::MouseButtonOffset);
			 keyCode++) {
			if (!Impl::IsKeyboardKeyPressed(keyboardDevice, keyCode)) {
				continue;
			}

			auto controlName = controlMap->GetControlNameByKeyCode(keyCode, keyboardDevice->deviceType.get());
			if (!controlName.has_value()) {
				continue;
			}

			result.push_back(std::move(controlName).value());
		}

		return result;
	}

	auto GetPressedMouseButtonControlNames() -> std::expected<std::vector<RE::BSFixedString>, REX::SystemError>
	{
		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto* mouseDevice = inputDeviceManager->GetPCMouse();
		if (!mouseDevice || !mouseDevice->IsConnected()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::no_such_device_or_address));
		}

		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		auto result = std::vector<RE::BSFixedString>();

		for (auto keyCode = std::to_underlying(Macro::MouseButtonOffset);
			 keyCode < std::to_underlying(Macro::GamepadButtonOffset);
			 keyCode++) {
			if (!Impl::IsMouseButtonPressed(mouseDevice, keyCode)) {
				continue;
			}

			auto controlName = controlMap->GetControlNameByKeyCode(keyCode, mouseDevice->deviceType.get());
			if (!controlName.has_value()) {
				continue;
			}

			result.push_back(std::move(controlName).value());
		}

		return result;
	}

	auto GetPressedGamepadButtonControlNames() -> std::expected<std::vector<RE::BSFixedString>, REX::SystemError>
	{
		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		switch (controlMap->pcGamepadMapType.get()) {
			case RE::PC_GAMEPAD_TYPE::DirectX: {
				return GetPressedXInputGamepadButtonControlNames();
			}
			case RE::PC_GAMEPAD_TYPE::Orbis: {
				return GetPressedOrbisGamepadButtonControlNames();
			}
			[[unlikely]]
			default: {
				REX::Assert(false);
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::value_too_large));
			}
		}
	}

	auto GetPressedXInputGamepadButtonControlNames() -> std::expected<std::vector<RE::BSFixedString>, REX::SystemError>
	{
		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto* gamepadDevice = inputDeviceManager->GetPCXInputGamepad();
		if (!gamepadDevice || !gamepadDevice->IsConnected()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::no_such_device_or_address));
		}

		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		auto result = std::vector<RE::BSFixedString>();

		for (auto keyCode = std::to_underlying(Macro::GamepadButtonOffset);
			 keyCode < std::to_underlying(Macro::TotalButtonCount);
			 keyCode++) {
			if (!Impl::IsXInputGamepadButtonPressed(gamepadDevice, keyCode)) {
				continue;
			}

			auto controlName = controlMap->GetControlNameByKeyCode(keyCode, gamepadDevice->deviceType.get());
			if (!controlName.has_value()) {
				continue;
			}

			result.push_back(std::move(controlName).value());
		}

		return result;
	}

	auto GetPressedOrbisGamepadButtonControlNames() -> std::expected<std::vector<RE::BSFixedString>, REX::SystemError>
	{
		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto* gamepadDevice = inputDeviceManager->GetPCOrbisGamepad();
		if (!gamepadDevice || !gamepadDevice->IsConnected()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::no_such_device_or_address));
		}

		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		auto result = std::vector<RE::BSFixedString>();

		for (auto keyCode = std::to_underlying(Macro::GamepadButtonOffset);
			 keyCode < std::to_underlying(Macro::TotalButtonCount);
			 keyCode++) {
			if (!Impl::IsOrbisGamepadButtonPressed(gamepadDevice, keyCode)) {
				continue;
			}

			auto controlName = controlMap->GetControlNameByKeyCode(keyCode, gamepadDevice->deviceType.get());
			if (!controlName.has_value()) {
				continue;
			}

			result.push_back(std::move(controlName).value());
		}

		return result;
	}

	auto GetKeyName(KeyCode a_keyCode) -> std::expected<RE::BSFixedStringCS, REX::SystemError>
	{
		if (!IsKeyCodeInRange(a_keyCode)) [[unlikely]] {
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

	auto GetKeyboardKeyName(KeyCode a_keyCode) -> std::expected<RE::BSFixedStringCS, REX::SystemError>
	{
		if (!IsKeyboardKeyCodeInRange(a_keyCode)) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto* keyboardDevice = inputDeviceManager->GetPCKeyboard();
		if (!keyboardDevice || !keyboardDevice->IsConnected()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::no_such_device_or_address));
		}

		const auto buttonInfo = keyboardDevice->GetButtonInfoByID(a_keyCode);
		if (!buttonInfo.has_value()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto* buttonInfoData = buttonInfo->second;
		if (!buttonInfoData) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		return buttonInfoData->name;
	}

	auto GetMouseButtonName(KeyCode a_keyCode) -> std::expected<RE::BSFixedStringCS, REX::SystemError>
	{
		if (!IsMouseButtonCodeInRange(a_keyCode)) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto* mouseDevice = inputDeviceManager->GetPCMouse();
		if (!mouseDevice || !mouseDevice->IsConnected()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::no_such_device_or_address));
		}

		const auto buttonInfo =
			mouseDevice->GetButtonInfoByID(a_keyCode - std::to_underlying(Macro::MouseButtonOffset));
		if (!buttonInfo.has_value()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto* buttonInfoData = buttonInfo->second;
		if (!buttonInfoData) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		return buttonInfoData->name;
	}

	auto GetGamepadButtonName(KeyCode a_keyCode) -> std::expected<RE::BSFixedStringCS, REX::SystemError>
	{
		if (!IsGamepadButtonCodeInRange(a_keyCode)) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		switch (controlMap->pcGamepadMapType.get()) {
			case RE::PC_GAMEPAD_TYPE::DirectX: {
				return GetXInputGamepadButtonName(a_keyCode);
			}
			case RE::PC_GAMEPAD_TYPE::Orbis: {
				return GetOrbisGamepadButtonName(a_keyCode);
			}
			[[unlikely]]
			default: {
				REX::Assert(false);
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::value_too_large));
			}
		}
	}

	auto GetXInputGamepadButtonName(KeyCode a_keyCode) -> std::expected<RE::BSFixedStringCS, REX::SystemError>
	{
		if (!IsGamepadButtonCodeInRange(a_keyCode)) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto* gamepadDevice = inputDeviceManager->GetPCXInputGamepad();
		if (!gamepadDevice || !gamepadDevice->IsConnected()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::no_such_device_or_address));
		}

		const auto buttonInfo =
			gamepadDevice->GetButtonInfoByID(a_keyCode - std::to_underlying(Macro::GamepadButtonOffset));
		if (!buttonInfo.has_value()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto* buttonInfoData = buttonInfo->second;
		if (!buttonInfoData) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		return buttonInfoData->name;
	}

	auto GetOrbisGamepadButtonName(KeyCode a_keyCode) -> std::expected<RE::BSFixedStringCS, REX::SystemError>
	{
		if (!IsGamepadButtonCodeInRange(a_keyCode)) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto* inputDeviceManager = RE::BSInputDeviceManager::GetSingleton();
		if (!inputDeviceManager) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto* gamepadDevice = inputDeviceManager->GetPCOrbisGamepad();
		if (!gamepadDevice || !gamepadDevice->IsConnected()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::no_such_device_or_address));
		}

		const auto buttonInfo =
			gamepadDevice->GetButtonInfoByID(a_keyCode - std::to_underlying(Macro::GamepadButtonOffset));
		if (!buttonInfo.has_value()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto* buttonInfoData = buttonInfo->second;
		if (!buttonInfoData) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		return buttonInfoData->name;
	}

	auto GetControlNameByKeyCode(KeyCode a_keyCode) -> std::expected<RE::BSFixedString, REX::SystemError>
	{
		if (!IsKeyCodeInRange(a_keyCode)) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		if (IsKeyboardKeyCodeInRange(a_keyCode)) {
			auto controlName = GetControlNameByKeyboardKeyCode(a_keyCode);
			if (!controlName.has_value()) [[unlikely]] {
				return std::unexpected(controlName.error());
			}

			return std::move(controlName).value();
		}

		if (IsMouseButtonCodeInRange(a_keyCode)) {
			auto controlName = GetControlNameByMouseKeyCode(a_keyCode);
			if (!controlName.has_value()) [[unlikely]] {
				return std::unexpected(controlName.error());
			}

			return std::move(controlName).value();
		}

		if (IsGamepadButtonCodeInRange(a_keyCode)) {
			auto controlName = GetControlNameByGamepadKeyCode(a_keyCode);
			if (!controlName.has_value()) [[unlikely]] {
				return std::unexpected(controlName.error());
			}

			return std::move(controlName).value();
		}

		return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
	}

	auto GetControlNameByKeyboardKeyCode(KeyCode a_keyCode) -> std::expected<RE::BSFixedString, REX::SystemError>
	{
		if (!IsKeyboardKeyCodeInRange(a_keyCode)) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		auto controlName = controlMap->GetControlNameByKeyCode(a_keyCode, RE::INPUT_DEVICE::Keyboard);
		if (!controlName.has_value()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		return std::move(controlName).value();
	}

	auto GetControlNameByMouseKeyCode(KeyCode a_keyCode) -> std::expected<RE::BSFixedString, REX::SystemError>
	{
		if (!IsMouseButtonCodeInRange(a_keyCode)) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		auto controlName = controlMap->GetControlNameByKeyCode(a_keyCode, RE::INPUT_DEVICE::Mouse);
		if (!controlName.has_value()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		return std::move(controlName).value();
	}

	auto GetControlNameByGamepadKeyCode(KeyCode a_keyCode) -> std::expected<RE::BSFixedString, REX::SystemError>
	{
		if (!IsGamepadButtonCodeInRange(a_keyCode)) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		auto controlName = controlMap->GetControlNameByKeyCode(a_keyCode, RE::INPUT_DEVICE::Gamepad);
		if (!controlName.has_value()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		return std::move(controlName).value();
	}

	auto GetKeyCodeByControlName(const RE::BSFixedString& a_controlName, RE::INPUT_DEVICE a_deviceType)
		-> std::expected<KeyCode, REX::SystemError>
	{
		if (a_deviceType > RE::INPUT_DEVICE::None) {
			const auto* controlMap = RE::ControlMap::GetSingleton();
			if (!controlMap) [[unlikely]] {
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
			}

			const auto keyCode = controlMap->GetKeyCodeByControlName(a_controlName, a_deviceType);
			if (!keyCode.has_value()) [[unlikely]] {
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
			}

			return keyCode.value();
		}

		{
			const auto keyCode = GetKeyCodeByKeyboardControlName(a_controlName);
			if (keyCode.has_value()) {
				return keyCode.value();
			}
		}

		{
			const auto keyCode = GetKeyCodeByMouseControlName(a_controlName);
			if (keyCode.has_value()) {
				return keyCode.value();
			}
		}

		{
			const auto keyCode = GetKeyCodeByGamepadControlName(a_controlName);
			if (keyCode.has_value()) {
				return keyCode.value();
			}
		}

		return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
	}

	auto GetKeyCodeByKeyboardControlName(const RE::BSFixedString& a_controlName)
		-> std::expected<KeyCode, REX::SystemError>
	{
		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto keyCode = controlMap->GetKeyCodeByControlName(a_controlName, RE::INPUT_DEVICE::Keyboard);
		if (!keyCode.has_value()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		return keyCode.value();
	}

	auto GetKeyCodeByMouseControlName(const RE::BSFixedString& a_controlName)
		-> std::expected<KeyCode, REX::SystemError>
	{
		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto keyCode = controlMap->GetKeyCodeByControlName(a_controlName, RE::INPUT_DEVICE::Mouse);
		if (!keyCode.has_value()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		return keyCode.value();
	}

	auto GetKeyCodeByGamepadControlName(const RE::BSFixedString& a_controlName)
		-> std::expected<KeyCode, REX::SystemError>
	{
		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		const auto keyCode = controlMap->GetKeyCodeByControlName(a_controlName, RE::INPUT_DEVICE::Gamepad);
		if (!keyCode.has_value()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		return keyCode.value();
	}

	auto HoldKey(KeyCode a_keyCode) -> bool
	{
		return HoldKeyboardKey(a_keyCode) || HoldMouseButton(a_keyCode) || HoldGamepadButton(a_keyCode);
	}

	auto HoldKeyboardKey(KeyCode a_keyCode) -> bool
	{
		return Impl::PressKeyboardKey(a_keyCode, true);
	}

	auto HoldMouseButton(KeyCode a_keyCode) -> bool
	{
		return Impl::PressMouseButton(a_keyCode, true);
	}

	auto HoldGamepadButton(KeyCode a_keyCode) -> bool
	{
		if (!IsGamepadButtonCodeInRange(a_keyCode)) {
			return false;
		}

		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) {
			return false;
		}

		switch (controlMap->pcGamepadMapType.get()) {
			case RE::PC_GAMEPAD_TYPE::DirectX: {
				return HoldXInputGamepadButton(a_keyCode);
			}
			case RE::PC_GAMEPAD_TYPE::Orbis: {
				return HoldOrbisGamepadButton(a_keyCode);
			}
			[[unlikely]]
			default: {
				REX::Assert(false);
				return false;
			}
		}
	}

	auto HoldXInputGamepadButton(KeyCode a_keyCode) -> bool
	{
		return Impl::PressXInputGamepadButton(a_keyCode, true);
	}

	auto HoldOrbisGamepadButton(KeyCode a_keyCode) -> bool
	{
		return Impl::PressOrbisGamepadButton(a_keyCode, true);
	}

	auto ReleaseKey(KeyCode a_keyCode, DeltaTime a_deltaTime) -> bool
	{
		return ReleaseKeyboardKey(a_keyCode, a_deltaTime) ||
			   ReleaseMouseButton(a_keyCode, a_deltaTime) ||
			   ReleaseGamepadButton(a_keyCode, a_deltaTime);
	}

	auto ReleaseKeyboardKey(KeyCode a_keyCode, DeltaTime a_deltaTime) -> bool
	{
		return Impl::PressKeyboardKey(a_keyCode, false, a_deltaTime);
	}

	auto ReleaseMouseButton(KeyCode a_keyCode, DeltaTime a_deltaTime) -> bool
	{
		return Impl::PressMouseButton(a_keyCode, false, a_deltaTime);
	}

	auto ReleaseGamepadButton(KeyCode a_keyCode, DeltaTime a_deltaTime) -> bool
	{
		if (!IsGamepadButtonCodeInRange(a_keyCode)) {
			return false;
		}

		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) {
			return false;
		}

		switch (controlMap->pcGamepadMapType.get()) {
			case RE::PC_GAMEPAD_TYPE::DirectX: {
				return ReleaseXInputGamepadButton(a_keyCode, a_deltaTime);
			}
			case RE::PC_GAMEPAD_TYPE::Orbis: {
				return ReleaseOrbisGamepadButton(a_keyCode, a_deltaTime);
			}
			[[unlikely]]
			default: {
				REX::Assert(false);
				return false;
			}
		}
	}

	auto ReleaseXInputGamepadButton(KeyCode a_keyCode, DeltaTime a_deltaTime) -> bool
	{
		return Impl::PressXInputGamepadButton(a_keyCode, false, a_deltaTime);
	}

	auto ReleaseOrbisGamepadButton(KeyCode a_keyCode, DeltaTime a_deltaTime) -> bool
	{
		return Impl::PressOrbisGamepadButton(a_keyCode, false, a_deltaTime);
	}

	auto TapKey(KeyCode a_keyCode, DeltaTime a_durationSeconds) -> bool
	{
		return TapKeyboardKey(a_keyCode, a_durationSeconds) ||
			   TapMouseButton(a_keyCode, a_durationSeconds) ||
			   TapGamepadButton(a_keyCode, a_durationSeconds);
	}

	auto TapKeyboardKey(KeyCode a_keyCode, DeltaTime a_durationSeconds) -> bool
	{
		return HoldKeyboardKey(a_keyCode) && ReleaseKeyboardKey(a_keyCode, a_durationSeconds);
	}

	auto TapMouseButton(KeyCode a_keyCode, DeltaTime a_durationSeconds) -> bool
	{
		return HoldMouseButton(a_keyCode) && ReleaseMouseButton(a_keyCode, a_durationSeconds);
	}

	auto TapGamepadButton(KeyCode a_keyCode, DeltaTime a_durationSeconds) -> bool
	{
		return HoldGamepadButton(a_keyCode) && ReleaseGamepadButton(a_keyCode, a_durationSeconds);
	}

	auto TapXInputGamepadButton(KeyCode a_keyCode, DeltaTime a_durationSeconds) -> bool
	{
		return HoldXInputGamepadButton(a_keyCode) && ReleaseXInputGamepadButton(a_keyCode, a_durationSeconds);
	}

	auto TapOrbisGamepadButton(KeyCode a_keyCode, DeltaTime a_durationSeconds) -> bool
	{
		return HoldOrbisGamepadButton(a_keyCode) && ReleaseOrbisGamepadButton(a_keyCode, a_durationSeconds);
	}

	auto GamepadFlagToKeyCode(KeyFlag a_keyFlag) -> std::expected<GamepadButton, REX::SystemError>
	{
		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		switch (controlMap->pcGamepadMapType.get()) {
			case RE::PC_GAMEPAD_TYPE::DirectX: {
				auto result = XInputGamepadFlagToKeyCode(a_keyFlag);
				if (!result.has_value()) [[unlikely]] {
					return std::unexpected(result.error());
				}

				return result.value();
			}
			case RE::PC_GAMEPAD_TYPE::Orbis: {
				auto result = OrbisGamepadFlagToKeyCode(a_keyFlag);
				if (!result.has_value()) [[unlikely]] {
					return std::unexpected(result.error());
				}

				return result.value();
			}
			[[unlikely]]
			default: {
				REX::Assert(false);
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::value_too_large));
			}
		}
	}

	auto GamepadKeyCodeToFlag(KeyCode a_keyCode) -> std::expected<KeyCode, REX::SystemError>
	{
		if (!IsGamepadButtonCodeInRange(a_keyCode)) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto* controlMap = RE::ControlMap::GetSingleton();
		if (!controlMap) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_address));
		}

		switch (controlMap->pcGamepadMapType.get()) {
			case RE::PC_GAMEPAD_TYPE::DirectX: {
				auto result = XInputGamepadKeyCodeToFlag(a_keyCode);
				if (!result.has_value()) [[unlikely]] {
					return std::unexpected(result.error());
				}

				return result.value();
			}
			case RE::PC_GAMEPAD_TYPE::Orbis: {
				auto result = OrbisGamepadKeyCodeToFlag(a_keyCode);
				if (!result.has_value()) [[unlikely]] {
					return std::unexpected(result.error());
				}

				return result.value();
			}
			[[unlikely]]
			default: {
				REX::Assert(false);
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::value_too_large));
			}
		}
	}

	auto XInputGamepadFlagToScePadFlag(KeyFlag a_keyFlag) noexcept
		-> std::expected<REX::PS4::SCE_PAD_BUTTON, REX::SystemError>
	{
		switch (static_cast<REX::W32::XINPUT_GAMEPAD_BUTTON>(a_keyFlag)) {
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
			[[unlikely]]
			default: {
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
			}
		}
	}

	auto ScePadFlagToXInputGamepadFlag(KeyFlag a_keyFlag) noexcept
		-> std::expected<REX::W32::XINPUT_GAMEPAD_BUTTON, REX::SystemError>
	{
		switch (static_cast<REX::PS4::SCE_PAD_BUTTON>(a_keyFlag)) {
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
			[[unlikely]]
			default: {
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
			}
		}
	}

	auto XInputGamepadFlagToKeyCode(KeyFlag a_keyFlag) noexcept -> std::expected<GamepadButton, REX::SystemError>
	{
		switch (static_cast<REX::W32::XINPUT_GAMEPAD_BUTTON>(a_keyFlag)) {
			case REX::W32::XINPUT_GAMEPAD_DPAD_UP: {
				return GamepadButton::DPadUp;
			}
			case REX::W32::XINPUT_GAMEPAD_DPAD_DOWN: {
				return GamepadButton::DPadDown;
			}
			case REX::W32::XINPUT_GAMEPAD_DPAD_LEFT: {
				return GamepadButton::DPadLeft;
			}
			case REX::W32::XINPUT_GAMEPAD_DPAD_RIGHT: {
				return GamepadButton::DPadRight;
			}
			case REX::W32::XINPUT_GAMEPAD_START: {
				return GamepadButton::Start;
			}
			case REX::W32::XINPUT_GAMEPAD_BACK: {
				return GamepadButton::Back;
			}
			case REX::W32::XINPUT_GAMEPAD_LEFT_THUMB: {
				return GamepadButton::LeftThumb;
			}
			case REX::W32::XINPUT_GAMEPAD_RIGHT_THUMB: {
				return GamepadButton::RightThumb;
			}
			case REX::W32::XINPUT_GAMEPAD_LEFT_SHOULDER: {
				return GamepadButton::LeftShoulder;
			}
			case REX::W32::XINPUT_GAMEPAD_RIGHT_SHOULDER: {
				return GamepadButton::RightShoulder;
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
			[[unlikely]]
			default: {
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
			}
		}
	}

	auto XInputGamepadKeyCodeToFlag(KeyCode a_keyCode) noexcept
		-> std::expected<REX::W32::XINPUT_GAMEPAD_BUTTON, REX::SystemError>
	{
		switch (static_cast<GamepadButton>(a_keyCode)) {
			case GamepadButton::DPadUp: {
				return REX::W32::XINPUT_GAMEPAD_DPAD_UP;
			}
			case GamepadButton::DPadDown: {
				return REX::W32::XINPUT_GAMEPAD_DPAD_DOWN;
			}
			case GamepadButton::DPadLeft: {
				return REX::W32::XINPUT_GAMEPAD_DPAD_LEFT;
			}
			case GamepadButton::DPadRight: {
				return REX::W32::XINPUT_GAMEPAD_DPAD_RIGHT;
			}
			case GamepadButton::Start: {
				return REX::W32::XINPUT_GAMEPAD_START;
			}
			case GamepadButton::Back: {
				return REX::W32::XINPUT_GAMEPAD_BACK;
			}
			case GamepadButton::LeftThumb: {
				return REX::W32::XINPUT_GAMEPAD_LEFT_THUMB;
			}
			case GamepadButton::RightThumb: {
				return REX::W32::XINPUT_GAMEPAD_RIGHT_THUMB;
			}
			case GamepadButton::LeftShoulder: {
				return REX::W32::XINPUT_GAMEPAD_LEFT_SHOULDER;
			}
			case GamepadButton::RightShoulder: {
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
			[[unlikely]]
			default: {
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
			}
		}
	}

	auto OrbisGamepadFlagToKeyCode(KeyFlag a_keyFlag) noexcept -> std::expected<GamepadButton, REX::SystemError>
	{
		auto newKeyFlag = ScePadFlagToXInputGamepadFlag(a_keyFlag);
		if (!newKeyFlag.has_value()) [[unlikely]] {
			return std::unexpected(newKeyFlag.error());
		}

		return XInputGamepadFlagToKeyCode(newKeyFlag.value());
	}

	auto OrbisGamepadKeyCodeToFlag(KeyCode a_keyCode) noexcept
		-> std::expected<REX::PS4::SCE_PAD_BUTTON, REX::SystemError>
	{
		auto newKeyCode = XInputGamepadKeyCodeToFlag(a_keyCode);
		if (!newKeyCode.has_value()) [[unlikely]] {
			return std::unexpected(newKeyCode.error());
		}

		return XInputGamepadFlagToScePadFlag(newKeyCode.value());
	}
}
