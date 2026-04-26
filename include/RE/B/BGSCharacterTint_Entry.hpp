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
		inline static constexpr auto RTTI{ RTTI::BGSCharacterTint__Entry };
		inline static constexpr auto VTABLE{ VTABLE::BGSCharacterTint__Entry };

		virtual ~Entry(); // 00

		// add
		virtual bool GetIsIdentical(const Entry* entry);					  // 08
		virtual bool CopyData(Entry entry);									  // 10
		virtual bool SetFromTemplateDefault(const Template::Entry* entry);	  // 18
		virtual bool GetMatchesTemplateDefault(const Template::Entry* entry); // 20
		virtual EntryType GetType();										  // 28

		GAME_HEAP_REDEFINE_NEW(Entry);

		// members
		Entry* templateEntry{ nullptr }; // 08
		std::uint16_t idLink{ 0 };		 // 10
		std::uint8_t tingingValue{ 0 };	 // 12
	};
	static_assert(sizeof(Entry) == 0x18);
}
