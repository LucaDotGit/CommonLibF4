#pragma once

#include "RE/B/BGSMod_Container.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/S/SimpleArray.hpp"
#include "RE/T/TESFullName.hpp"

namespace RE::BGSMod::Template
{
	class Items;

	class __declspec(novtable) Item
		: public TESFullName,	   // 00
		  public BGSMod::Container // 10
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSMod__Template__Item };
		inline static constexpr auto VTABLE{ VTABLE::BGSMod__Template__Item };

		GAME_HEAP_REDEFINE_NEW(Item);

		// members
		BGSMod::Template::Items* parentTemplate; // 20
		SimpleArray<BGSKeyword*> nameKeywords;	 // 28
		std::uint16_t parent;					 // 30
		std::int8_t levelMin;					 // 32
		std::int8_t levelMax;					 // 33
		std::int8_t keywords;					 // 34
		std::int8_t tierStartLevel;				 // 35
		std::int8_t altLevelsPerTier;			 // 36
		bool isDefault			: 1;			 // 37:1
		bool fullNameEditorOnly : 1;			 // 37:2
	};
	static_assert(sizeof(Item) == 0x38);
}
