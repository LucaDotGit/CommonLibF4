#pragma once

#include "RE/B/BSInputEventReceiver.hpp"
#include "RE/B/BSInputEventUser.hpp"

namespace RE
{
	class __declspec(novtable) BSInputEventSingleUser
		: public BSInputEventReceiver, // 00
		  public BSInputEventUser	   // 10
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSInputEventSingleUser };
		inline static constexpr auto VTABLE{ VTABLE::BSInputEventSingleUser };

		~BSInputEventSingleUser() override = default; // 00
	};
	static_assert(sizeof(BSInputEventSingleUser) == 0x20);
}
