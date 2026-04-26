#pragma once

#include "RE/B/BGSPerkEntry.hpp"
#include "RE/S/SimpleArray.hpp"

namespace RE
{
	class BGSEntryPointFunctionData;
	class TESCondition;

	class __declspec(novtable) BGSEntryPointPerkEntry
		: public BGSPerkEntry // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSEntryPointPerkEntry };
		inline static constexpr auto VTABLE{ VTABLE::BGSEntryPointPerkEntry };
		inline static constexpr auto ENTRY_TYPE{ PERK_ENTRY_TYPE::kEntryPoint };

		class EntryData
		{
		public:
			enum class EntryPointFunctionType : std::int8_t
			{
				kSetValue = 0,
				kAddValue = 1,
				kMultiplyValue = 2,
				kAddRangeToValue = 3,
				kAddActorValueMult = 4,
				kAbsoluteValue = 5,
				kNegativeAbsoluteValue = 6,
				kAddLeveledList = 7,
				kAddActivateChoice = 8,
				kSelectSpell = 9,
				kSelectText = 10,
				kSetToActorValueMult = 11,
				kMultiplyActorValueMult = 12,
				kMultiply1PlusActorValueMult = 13,
				kSetText = 14
			};

			// members
			REX::Enum<BGSEntryPoint::ENTRY_POINT, std::int8_t> entryPoint; // 00
			REX::Enum<EntryPointFunctionType, std::int8_t> functionType;   // 01
			std::uint8_t numConditions;									   // 02
		};
		static_assert(sizeof(EntryData) == 0x03);

		BGSEntryPointPerkEntry();

		BGSEntryPoint::ENTRY_POINT GetFunction() override;			 // 00
		BGSEntryPointFunctionData* GetFunctionData() const override; // 01

		~BGSEntryPointPerkEntry() override; // 02

		PERK_ENTRY_TYPE GetType() const override;	   // 03
		void ClearData() override;					   // 04
		void InitItem(TESFile* a_owner) override;	   // 05
		bool Load(TESFile* a_file) override;		   // 06
		void SetParent(BGSPerk* a_parent) override;	   // 07
		std::uint16_t GetID() const override;		   // 08
		void ApplyPerkEntry(Actor* a_actor) override;  // 09
		void RemovePerkEntry(Actor* a_actor) override; // 0A

		// members
		EntryData entryData;								// 10
		BGSEntryPointFunctionData* functionData{ nullptr }; // 18
		SimpleArray<TESCondition> conditions;				// 20
		BGSPerk* perk{ nullptr };							// 28
	};
	static_assert(sizeof(BGSEntryPointPerkEntry) == 0x30);

	extern template bool BGSPerkEntry::Is<BGSEntryPointPerkEntry>() const noexcept;
	extern template bool BGSPerkEntry::IsNot<BGSEntryPointPerkEntry>() const noexcept;

	extern template BGSEntryPointPerkEntry* BGSPerkEntry::As<BGSEntryPointPerkEntry>() noexcept;
	extern template const BGSEntryPointPerkEntry* BGSPerkEntry::As<BGSEntryPointPerkEntry>() const noexcept;
}
