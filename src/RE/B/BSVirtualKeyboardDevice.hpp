#pragma once

#include "RE/B/BSKeyboardDevice.hpp"

namespace RE
{
	class __declspec(novtable) BSVirtualKeyboardDevice : public BSKeyboardDevice // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSVirtualKeyboardDevice;
		inline static constexpr const auto& VTABLE = VTABLE::BSVirtualKeyboardDevice;

		class kbInfo
		{
		public:
			// members
			const char* defaultText;								  // 0x00
			void (*callbackDone)(void* a_data, const char* a_text);	  // 0x08
			void (*callbackCancel)(void* a_data, const char* a_text); // 0x10
			void* callbackData;										  // 0x18
			std::uint32_t maxLength;								  // 0x20
			std::uint32_t offset;									  // 0x24
			bool lengthIndicatorVisibility;							  // 0x28
			bool isPasswordField;									  // 0x29
		};

		static_assert(sizeof(kbInfo) == 0x30);

		// override (BSKeyboardDevice)
		~BSVirtualKeyboardDevice() override; // 0x04

		// add
		virtual void Start(const BSVirtualKeyboardDevice::kbInfo& a_info); // 0x06
		virtual void Stop();											   // 0x07
		virtual void UserCancelled();									   // 0x08
	};

	static_assert(sizeof(BSVirtualKeyboardDevice) == 0x70);
}
