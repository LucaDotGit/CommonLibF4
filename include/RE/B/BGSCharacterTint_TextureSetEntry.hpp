#pragma once

#include "RE/B/BGSCharacterTint_Entry.hpp"

namespace RE::BGSCharacterTint
{
	class __declspec(novtable) TextureSetEntry
		: public Entry // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSCharacterTint__TextureSetEntry };
		inline static constexpr auto VTABLE{ VTABLE::BGSCharacterTint__TextureSetEntry };

		~TextureSetEntry() override; // 00
	};
	static_assert(sizeof(TextureSetEntry) == 0x18);
}
