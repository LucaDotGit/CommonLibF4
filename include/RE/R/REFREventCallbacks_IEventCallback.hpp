#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"

namespace RE
{
	class BSStorage;
}

namespace RE::REFREventCallbacks
{
	class __declspec(novtable) IEventCallback
		: public BSIntrusiveRefCounted // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::REFREventCallbacks__IEventCallback };
		inline static constexpr auto VTABLE{ VTABLE::REFREventCallbacks__IEventCallback };

		virtual ~IEventCallback() = default; // 00

		// add
		virtual void operator()() = 0;				   // 01
		virtual bool Save(BSStorage& a_storage);	   // 02
		virtual const BSFixedString* GetType() = 0;	   // 03
		virtual bool Load(const BSStorage& a_storage); // 04
	};
	static_assert(sizeof(IEventCallback) == 0x10);
}
