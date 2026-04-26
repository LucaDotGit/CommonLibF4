#pragma once

namespace REX::W32
{
	inline constexpr std::uint16_t XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE{ 7849 };
	inline constexpr std::uint16_t XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE{ 8689 };
	inline constexpr std::uint8_t XINPUT_GAMEPAD_TRIGGER_THRESHOLD{ 30 };
}

namespace REX::W32
{
	enum XINPUT_GAMEPAD_BUTTON : std::uint16_t
	{
		XINPUT_GAMEPAD_DPAD_UP = 0x1,
		XINPUT_GAMEPAD_DPAD_DOWN = 0x2,
		XINPUT_GAMEPAD_DPAD_LEFT = 0x4,
		XINPUT_GAMEPAD_DPAD_RIGHT = 0x8,
		XINPUT_GAMEPAD_START = 0x10,
		XINPUT_GAMEPAD_BACK = 0x20,
		XINPUT_GAMEPAD_LEFT_THUMB = 0x40,
		XINPUT_GAMEPAD_RIGHT_THUMB = 0x80,
		XINPUT_GAMEPAD_LEFT_SHOULDER = 0x100,
		XINPUT_GAMEPAD_RIGHT_SHOULDER = 0x200,
		XINPUT_GAMEPAD_A = 0x1000,
		XINPUT_GAMEPAD_B = 0x2000,
		XINPUT_GAMEPAD_X = 0x4000,
		XINPUT_GAMEPAD_Y = 0x8000,

		XINPUT_GAMEPAD_BUTTON_MASK = XINPUT_GAMEPAD_DPAD_UP |
									 XINPUT_GAMEPAD_DPAD_DOWN |
									 XINPUT_GAMEPAD_DPAD_LEFT |
									 XINPUT_GAMEPAD_DPAD_RIGHT |
									 XINPUT_GAMEPAD_START |
									 XINPUT_GAMEPAD_BACK |
									 XINPUT_GAMEPAD_LEFT_THUMB |
									 XINPUT_GAMEPAD_RIGHT_THUMB |
									 XINPUT_GAMEPAD_LEFT_SHOULDER |
									 XINPUT_GAMEPAD_RIGHT_SHOULDER |
									 XINPUT_GAMEPAD_A |
									 XINPUT_GAMEPAD_B |
									 XINPUT_GAMEPAD_X |
									 XINPUT_GAMEPAD_Y
	};
}

namespace REX::W32
{
	struct XINPUT_BATTERY_INFORMATION
	{
		std::uint8_t batteryType;
		std::uint8_t batteryLevel;
	};

	struct XINPUT_GAMEPAD
	{
		std::uint16_t buttons;
		std::uint8_t leftTrigger;
		std::uint8_t rightTrigger;
		std::int16_t thumbLX;
		std::int16_t thumbLY;
		std::int16_t thumbRX;
		std::int16_t thumbRY;
	};

	struct XINPUT_KEYSTROKE
	{
		std::uint16_t virtualKey;
		std::uint16_t unicode;
		std::uint16_t flags;
		std::uint8_t userIndex;
		std::uint8_t hidCode;
	};

	struct XINPUT_STATE
	{
		std::uint32_t packetNumber;
		XINPUT_GAMEPAD gamepad;
	};

	struct XINPUT_VIBRATION
	{
		std::uint16_t leftMotorSpeed;
		std::uint16_t rightMotorSpeed;
	};

	struct XINPUT_CAPABILITIES
	{
		std::uint8_t type;
		std::uint8_t subType;
		std::uint16_t flags;
		XINPUT_GAMEPAD gamepad;
		XINPUT_VIBRATION vibration;
	};
}
