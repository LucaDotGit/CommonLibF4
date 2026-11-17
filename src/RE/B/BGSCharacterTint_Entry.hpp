#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE::BGSCharacterTint::Template
{
	class Entry;
}

namespace RE::BGSCharacterTint
{
	enum class EntryType : std::int32_t;

	class __declspec(novtable) Entry
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSCharacterTint__Entry;
		inline static constexpr const auto& VTABLE = VTABLE::BGSCharacterTint__Entry;

		virtual ~Entry(); // 0x00

		// add
		virtual auto GetIsIdentical(const Entry* entry) -> bool;					  // 0x08
		virtual auto CopyData(Entry entry) -> bool;									  // 0x10
		virtual auto SetFromTemplateDefault(const Template::Entry* entry) -> bool;	  // 0x18
		virtual auto GetMatchesTemplateDefault(const Template::Entry* entry) -> bool; // 0x20
		virtual auto GetType() -> EntryType;										  // 0x28

		GAME_HEAP_REDEFINE_NEW(Entry);

		// members
		Template::Entry* templateEntry{nullptr}; // 0x08
		std::uint16_t idLink{0};				 // 0x10
		std::uint8_t tintingValue{0};			 // 0x12
	};

	static_assert(sizeof(Entry) == 0x18);
}
