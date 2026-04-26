#pragma once

#include "RE/B/BSInputDevice.hpp"
#include "RE/I/INPUT_DEVICE.hpp"
#include "RE/T/ThumbstickDirectionHandler.hpp"

namespace RE
{
	class __declspec(novtable) BSGamepadDevice
		: public BSInputDevice // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSGamepadDevice };
		inline static constexpr auto VTABLE{ VTABLE::BSGamepadDevice };
		inline static constexpr auto DEVICE_TYPE{ INPUT_DEVICE::kGamepad };

		template <class T>
		class GamepadState
		{
		public:
			// members
			T hardwareState;			// 00
			REX::Float32 ltTrigger;		// 00
			REX::Float32 rtTrigger;		// 04
			REX::Float32 lxAxisNormVal; // 08
			REX::Float32 lyAxisNormVal; // 0C
			REX::Float32 rxAxisNormVal; // 10
			REX::Float32 ryAxisNormVal; // 14
		};

		// override(BSInputDevice)
		bool IsConnected() const override; // 03 - { return connected; }
		~BSGamepadDevice() override;	   // 04

		// add
		virtual void RestoreDirectionRepeatRates(REX::Float32 a_shortRate, REX::Float32 a_longRate, bool a_leftTrigger); // 06
		virtual void SetDeviceLight(const std::array<std::uint8_t, 3>& a_color);										 // 07
		virtual void ResetDeviceLight();																				 // 08
		virtual bool IsRemoteController() const { return false; }														 // 09
		virtual void NormalizeThumbstickValue(REX::Float32 a_xHardware, REX::Float32 a_yHardware, REX::Float32& a_xOut); // 0A
		virtual bool DoEnableListeningMode() { return false; }															 // 0B

		// members
		ThumbstickDirectionHandler ltDirHandler; // 70
		ThumbstickDirectionHandler rtDirHandler; // 8C
		std::int32_t forceGamepadID;			 // A8
		bool connected;							 // AC
		bool listeningForInput;					 // AD
	};
	static_assert(sizeof(BSGamepadDevice) == 0xB0);
}
