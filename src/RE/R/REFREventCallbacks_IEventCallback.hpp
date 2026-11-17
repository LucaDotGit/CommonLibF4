#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"

namespace RE
{
	class BSStorage;
}

namespace RE::REFREventCallbacks
{
	class __declspec(novtable) IEventCallback : public BSIntrusiveRefCounted // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::REFREventCallbacks__IEventCallback;
		inline static constexpr const auto& VTABLE = VTABLE::REFREventCallbacks__IEventCallback;

		virtual ~IEventCallback() = default; // 0x00

		// add
		virtual void operator()() = 0;						   // 0x01
		virtual auto Save(BSStorage& a_storage) -> bool;	   // 0x02
		virtual auto GetType() -> const BSFixedString* = 0;	   // 0x03
		virtual auto Load(const BSStorage& a_storage) -> bool; // 0x04
	};

	static_assert(sizeof(IEventCallback) == 0x10);
}
