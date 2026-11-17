#pragma once

#include "RE/B/BGSPerkEntry.hpp"

namespace RE
{
	class __declspec(novtable) BGSQuestPerkEntry : public BGSPerkEntry // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSQuestPerkEntry;
		inline static constexpr const auto& VTABLE = VTABLE::BGSQuestPerkEntry;
		inline static constexpr auto ENTRY_TYPE = PERK_ENTRY_TYPE::Quest;

		class EntryData
		{
		public:
			// members
			TESQuest* quest{nullptr}; // 0x00
			std::uint16_t stage{0};	  // 0x08
		};

		static_assert(sizeof(EntryData) == 0x10);

		BGSQuestPerkEntry();

		auto GetFunction() -> BGSEntryPoint::ENTRY_POINT override;			 // 0x00
		auto GetFunctionData() const -> BGSEntryPointFunctionData* override; // 0x01

		~BGSQuestPerkEntry() override; // 0x02

		auto GetType() const -> PERK_ENTRY_TYPE override; // 0x03
		void ClearData() override;						  // 0x04
		void InitItem(TESFile* a_owner) override;		  // 0x05
		auto Load(TESFile* a_file) -> bool override;	  // 0x06
		void SetParent(BGSPerk* a_parent) override;		  // 0x07
		auto GetID() const -> std::uint16_t override;	  // 0x08
		void ApplyPerkEntry(Actor* a_actor) override;	  // 0x09
		void RemovePerkEntry(Actor* a_actor) override;	  // 0x0A

		// members
		EntryData data; // 0x10
	};

	static_assert(sizeof(BGSQuestPerkEntry) == 0x20);
}
