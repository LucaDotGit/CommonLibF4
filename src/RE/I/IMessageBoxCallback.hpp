#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"

namespace RE
{
	class __declspec(novtable) IMessageBoxCallback : public BSIntrusiveRefCounted // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::IMessageBoxCallback;
		inline static constexpr const auto& VTABLE = VTABLE::IMessageBoxCallback;

		virtual ~IMessageBoxCallback() = default; // 0x00

		// add
		virtual void operator()(std::uint8_t a_buttonIndex) = 0; // 0x01
	};

	static_assert(sizeof(IMessageBoxCallback) == 0x10);
}
