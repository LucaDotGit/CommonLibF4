#pragma once

#include "RE/H/HeldStateHandler.hpp"

namespace RE
{
	class __declspec(novtable) MeleeThrowHandler
		: public HeldStateHandler // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::MeleeThrowHandler };
		inline static constexpr auto VTABLE{ VTABLE::MeleeThrowHandler };

		// members
		bool buttonHoldDebounce; // 28
		bool pressRegistered;	 // 29
		bool queueThrow;		 // 2A
	};
	static_assert(sizeof(MeleeThrowHandler) == 0x30);
}
