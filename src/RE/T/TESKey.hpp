#pragma once

#include "RE/T/TESObjectMISC.hpp"

namespace RE
{
	class __declspec(novtable) TESKey : public TESObjectMISC // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESKey;
		inline static constexpr const auto& VTABLE = VTABLE::TESKey;
		inline static constexpr auto FORM_TYPE = FormType::Key;

		~TESKey() override; // 0x00
	};

	static_assert(sizeof(TESKey) == 0x168);
}
