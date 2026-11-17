#pragma once

#include "RE/B/BSInputEventReceiver.hpp"
#include "RE/B/BSInputEventUser.hpp"

namespace RE
{
	class __declspec(novtable) BSInputEventSingleUser :
		public BSInputEventReceiver, // 0x00
		public BSInputEventUser		 // 0x10
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSInputEventSingleUser;
		inline static constexpr const auto& VTABLE = VTABLE::BSInputEventSingleUser;

		~BSInputEventSingleUser() override = default; // 0x00
	};

	static_assert(sizeof(BSInputEventSingleUser) == 0x20);
}
