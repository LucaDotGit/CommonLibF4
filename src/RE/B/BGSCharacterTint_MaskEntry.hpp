#pragma once

#include "RE/B/BGSCharacterTint_Entry.hpp"

namespace RE::BGSCharacterTint
{
	class __declspec(novtable) MaskEntry : public Entry // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSCharacterTint__MaskEntry;
		inline static constexpr const auto& VTABLE = VTABLE::BGSCharacterTint__MaskEntry;

		~MaskEntry() override; // 0x00
	};

	static_assert(sizeof(MaskEntry) == 0x18);
}
