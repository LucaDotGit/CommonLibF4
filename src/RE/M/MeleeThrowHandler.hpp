#pragma once

#include "RE/H/HeldStateHandler.hpp"

namespace RE
{
	class __declspec(novtable) MeleeThrowHandler : public HeldStateHandler // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::MeleeThrowHandler;
		inline static constexpr const auto& VTABLE = VTABLE::MeleeThrowHandler;

		// members
		bool buttonHoldDebounce; // 0x28
		bool pressRegistered;	 // 0x29
		bool queueThrow;		 // 0x2A
	};

	static_assert(sizeof(MeleeThrowHandler) == 0x30);
}
