#pragma once

#include "RE/B/BSSimpleList.hpp"
#include "RE/T/TESPackage.hpp"

namespace RE
{
	class Crime;

	class __declspec(novtable) AlarmPackage : public TESPackage // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::AlarmPackage;
		inline static constexpr const auto& VTABLE = VTABLE::AlarmPackage;
		inline static constexpr auto FORM_TYPE = FormType::Package;

		~AlarmPackage() override; // 0x00

		// members
		BSSimpleList<Crime*> crimes; // 0xC8
		bool forceGreet;			 // 0xD8
	};

	static_assert(sizeof(AlarmPackage) == 0xE0);
}
