#pragma once

#include "RE/T/TESPackage.hpp"

namespace RE
{
	class __declspec(novtable) TrespassPackage
		: public TESPackage // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TrespassPackage };
		inline static constexpr auto VTABLE{ VTABLE::TrespassPackage };
		inline static constexpr auto FORM_TYPE{ FormType::kPackage };

		~TrespassPackage() override; // 00

		// members
		REX::Float32 warningtimer; // C8
		std::int32_t warning;	   // CC
		TESForm* owner;			   // D0
		std::int32_t crimeNumber;  // D9
		std::int32_t warninglevel; // DC
		std::int32_t numberActors; // E0
	};
	static_assert(sizeof(TrespassPackage) == 0xE8);
}
