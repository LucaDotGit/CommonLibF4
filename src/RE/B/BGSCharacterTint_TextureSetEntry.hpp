#pragma once

#include "RE/B/BGSCharacterTint_Entry.hpp"

namespace RE::BGSCharacterTint
{
	class __declspec(novtable) TextureSetEntry : public Entry // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSCharacterTint__TextureSetEntry;
		inline static constexpr const auto& VTABLE = VTABLE::BGSCharacterTint__TextureSetEntry;

		~TextureSetEntry() override; // 0x00
	};

	static_assert(sizeof(TextureSetEntry) == 0x18);
}
