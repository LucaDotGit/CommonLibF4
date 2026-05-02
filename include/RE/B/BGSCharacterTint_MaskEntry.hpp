#pragma once

#include "RE/B/BGSCharacterTint_Entry.hpp"

namespace RE::BGSCharacterTint
{
	class __declspec(novtable) MaskEntry
		: public Entry // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSCharacterTint__MaskEntry };
		inline static constexpr auto VTABLE{ VTABLE::BGSCharacterTint__MaskEntry };

		~MaskEntry() override; // 00
	};
	static_assert(sizeof(MaskEntry) == 0x18);
}
