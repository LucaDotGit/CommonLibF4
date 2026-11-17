#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE::BSScript
{
	class __declspec(novtable) ICachedErrorMessage
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__ICachedErrorMessage;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__ICachedErrorMessage;

		virtual ~ICachedErrorMessage() = default; // 0x00

		// add
		virtual void GetErrorMsg(BSFixedString& a_message) const = 0; // 0x01

		GAME_HEAP_REDEFINE_NEW(ICachedErrorMessage);
	};

	static_assert(sizeof(ICachedErrorMessage) == 0x08);
}
