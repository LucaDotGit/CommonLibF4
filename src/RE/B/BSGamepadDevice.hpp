#pragma once

#include "RE/B/BSInputDevice.hpp"
#include "RE/I/INPUT_DEVICE.hpp"
#include "RE/T/ThumbstickDirectionHandler.hpp"

namespace RE
{
	class __declspec(novtable) BSGamepadDevice : public BSInputDevice // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSGamepadDevice;
		inline static constexpr const auto& VTABLE = VTABLE::BSGamepadDevice;
		inline static constexpr auto DEVICE_TYPE = INPUT_DEVICE::Gamepad;

		template <class T>
		class GamepadState
		{
		public:
			// members
			T hardwareState;			// 0x00
			REX::Float32 ltTrigger;		// 0x00
			REX::Float32 rtTrigger;		// 0x04
			REX::Float32 lxAxisNormVal; // 0x08
			REX::Float32 lyAxisNormVal; // 0x0C
			REX::Float32 rxAxisNormVal; // 0x10
			REX::Float32 ryAxisNormVal; // 0x14
		};

		// override (BSInputDevice)
		auto IsConnected() const -> bool override; // 0x03 - { return connected; }
		~BSGamepadDevice() override;			   // 0x04

		// add
		virtual void RestoreDirectionRepeatRates(
			REX::Float32 a_shortRate,
			REX::Float32 a_longRate,
			bool a_leftTrigger);												 // 0x06
		virtual void SetDeviceLight(const std::array<std::uint8_t, 3>& a_color); // 0x07
		virtual void ResetDeviceLight();										 // 0x08

		virtual auto IsRemoteController() const -> bool // 0x09
		{
			return false;
		}

		virtual void NormalizeThumbstickValue(
			REX::Float32 a_xHardware,
			REX::Float32 a_yHardware,
			REX::Float32& a_xOut); // 0x0A

		virtual auto DoEnableListeningMode() -> bool // 0x0B
		{
			return false;
		}

		// members
		ThumbstickDirectionHandler ltDirHandler; // 0x70
		ThumbstickDirectionHandler rtDirHandler; // 0x8C
		std::int32_t forceGamepadID;			 // 0xA8
		bool connected;							 // 0xAC
		bool listeningForInput;					 // 0xAD
	};

	static_assert(sizeof(BSGamepadDevice) == 0xB0);
}
