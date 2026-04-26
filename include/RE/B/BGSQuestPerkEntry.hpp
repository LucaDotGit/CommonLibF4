#pragma once

#include "RE/B/BGSPerkEntry.hpp"

namespace RE
{
	class __declspec(novtable) BGSQuestPerkEntry
		: public BGSPerkEntry // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSQuestPerkEntry };
		inline static constexpr auto VTABLE{ VTABLE::BGSQuestPerkEntry };
		inline static constexpr auto ENTRY_TYPE{ PERK_ENTRY_TYPE::kQuest };

		class EntryData
		{
		public:
			// members
			TESQuest* quest{ nullptr }; // 00
			std::uint16_t stage{ 0 };	// 08
		};
		static_assert(sizeof(EntryData) == 0x10);

		BGSQuestPerkEntry();

		BGSEntryPoint::ENTRY_POINT GetFunction() override;			 // 00
		BGSEntryPointFunctionData* GetFunctionData() const override; // 01

		~BGSQuestPerkEntry() override; // 02

		PERK_ENTRY_TYPE GetType() const override;	   // 03
		void ClearData() override;					   // 04
		void InitItem(TESFile* a_owner) override;	   // 05
		bool Load(TESFile* a_file) override;		   // 06
		void SetParent(BGSPerk* a_parent) override;	   // 07
		std::uint16_t GetID() const override;		   // 08
		void ApplyPerkEntry(Actor* a_actor) override;  // 09
		void RemovePerkEntry(Actor* a_actor) override; // 0A

		// members
		EntryData data; // 10
	};
	static_assert(sizeof(BGSQuestPerkEntry) == 0x20);

	extern template bool BGSPerkEntry::Is<BGSQuestPerkEntry>() const noexcept;
	extern template bool BGSPerkEntry::IsNot<BGSQuestPerkEntry>() const noexcept;

	extern template BGSQuestPerkEntry* BGSPerkEntry::As<BGSQuestPerkEntry>() noexcept;
	extern template const BGSQuestPerkEntry* BGSPerkEntry::As<BGSQuestPerkEntry>() const noexcept;
}
