#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"

namespace RE
{
	class __declspec(novtable) IMessageBoxCallback
		: public BSIntrusiveRefCounted // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::IMessageBoxCallback };
		inline static constexpr auto VTABLE{ VTABLE::IMessageBoxCallback };

		virtual ~IMessageBoxCallback() = default; // 00

		// add
		virtual void operator()(std::uint8_t a_buttonIndex) = 0; // 01
	};
	static_assert(sizeof(IMessageBoxCallback) == 0x10);
}
