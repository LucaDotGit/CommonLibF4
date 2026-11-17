#pragma once

#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSReferenceGroup : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSReferenceGroup;
		inline static constexpr const auto& VTABLE = VTABLE::BGSReferenceGroup;
		inline static constexpr auto FORM_TYPE = FormType::ReferenceGroup;
	};

	static_assert(sizeof(BGSReferenceGroup) == 0x20);
}
