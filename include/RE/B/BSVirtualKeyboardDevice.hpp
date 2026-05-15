#pragma once

#include "RE/B/BSKeyboardDevice.hpp"

namespace RE
{
	class __declspec(novtable) BSVirtualKeyboardDevice
		: public BSKeyboardDevice // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSVirtualKeyboardDevice };
		inline static constexpr auto VTABLE{ VTABLE::BSVirtualKeyboardDevice };

		class kbInfo
		{
		public:
			// members
			const char* defaultText;								  // 00
			void (*callbackDone)(void* a_data, const char* a_text);	  // 08
			void (*callbackCancel)(void* a_data, const char* a_text); // 10
			void* callbackData;										  // 18
			std::uint32_t maxLength;								  // 20
			std::uint32_t offset;									  // 24
			bool lengthIndicatorVisibility;							  // 28
			bool isPasswordField;									  // 29
		};
		static_assert(sizeof(kbInfo) == 0x30);

		// override (BSKeyboardDevice)
		~BSVirtualKeyboardDevice() override; // 04

		// add
		virtual void Start(const BSVirtualKeyboardDevice::kbInfo& a_info); // 06
		virtual void Stop();											   // 07
		virtual void UserCancelled();									   // 08
	};
	static_assert(sizeof(BSVirtualKeyboardDevice) == 0x70);
}
