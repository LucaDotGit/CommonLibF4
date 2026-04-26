#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE::BSScript
{
	class __declspec(novtable) ICachedErrorMessage
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__ICachedErrorMessage };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__ICachedErrorMessage };

		virtual ~ICachedErrorMessage() = default; // 00

		// add
		virtual void GetErrorMsg(BSFixedString& a_message) const = 0; // 01
	};
	static_assert(sizeof(ICachedErrorMessage) == 0x08);
}
