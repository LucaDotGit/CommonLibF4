#pragma once

#include "RE/B/BGSMod_Container.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/S/SimpleArray.hpp"
#include "RE/T/TESFullName.hpp"

namespace RE::BGSMod::Template
{
	class Items;

	class __declspec(novtable) Item :
		public TESFullName,		 // 0x00
		public BGSMod::Container // 0x10
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSMod__Template__Item;
		inline static constexpr const auto& VTABLE = VTABLE::BGSMod__Template__Item;

		GAME_HEAP_REDEFINE_NEW(Item);

		// members
		BGSMod::Template::Items* parentTemplate; // 0x20
		SimpleArray<BGSKeyword*> nameKeywords;	 // 0x28
		std::uint16_t parent;					 // 0x30
		std::int8_t levelMin;					 // 0x32
		std::int8_t levelMax;					 // 0x33
		std::int8_t keywords;					 // 0x34
		std::int8_t tierStartLevel;				 // 0x35
		std::int8_t altLevelsPerTier;			 // 0x36
		bool isDefault			: 1;			 // 0x37:1
		bool fullNameEditorOnly : 1;			 // 0x37:2
	};

	static_assert(sizeof(Item) == 0x38);
}
