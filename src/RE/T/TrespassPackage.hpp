#pragma once

#include "RE/T/TESPackage.hpp"

namespace RE
{
	class __declspec(novtable) TrespassPackage : public TESPackage // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TrespassPackage;
		inline static constexpr const auto& VTABLE = VTABLE::TrespassPackage;
		inline static constexpr auto FORM_TYPE = FormType::Package;

		~TrespassPackage() override; // 0x00

		// members
		REX::Float32 warningtimer; // 0xC8
		std::int32_t warning;	   // 0xCC
		TESForm* owner;			   // 0xD0
		std::int32_t crimeNumber;  // 0xD9
		std::int32_t warninglevel; // 0xDC
		std::int32_t numberActors; // 0xE0
	};

	static_assert(sizeof(TrespassPackage) == 0xE8);
}
