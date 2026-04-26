#pragma once

#include "RE/B/BSSimpleList.hpp"
#include "RE/T/TESPackage.hpp"

namespace RE
{
	class Crime;

	class __declspec(novtable) AlarmPackage
		: public TESPackage // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::AlarmPackage };
		inline static constexpr auto VTABLE{ VTABLE::AlarmPackage };
		inline static constexpr auto FORM_TYPE{ FormType::kPackage };

		~AlarmPackage() override; // 00

		// members
		BSSimpleList<Crime*> crimes; // C8
		bool forceGreet;			 // D8
	};
	static_assert(sizeof(AlarmPackage) == 0xE0);
}
