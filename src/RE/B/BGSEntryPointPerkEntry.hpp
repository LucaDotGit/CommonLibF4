#pragma once

#include "RE/B/BGSPerkEntry.hpp"
#include "RE/S/SimpleArray.hpp"

namespace RE
{
	class BGSEntryPointFunctionData;
	class TESCondition;

	class __declspec(novtable) BGSEntryPointPerkEntry : public BGSPerkEntry // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSEntryPointPerkEntry;
		inline static constexpr const auto& VTABLE = VTABLE::BGSEntryPointPerkEntry;
		inline static constexpr auto ENTRY_TYPE = PERK_ENTRY_TYPE::EntryPoint;

		class EntryData
		{
		public:
			enum class EntryPointFunctionType : std::int8_t
			{
				SetValue = 0,
				AddValue = 1,
				MultiplyValue = 2,
				AddRangeToValue = 3,
				AddActorValueMult = 4,
				AbsoluteValue = 5,
				NegativeAbsoluteValue = 6,
				AddLeveledList = 7,
				AddActivateChoice = 8,
				SelectSpell = 9,
				SelectText = 10,
				SetToActorValueMult = 11,
				MultiplyActorValueMult = 12,
				Multiply1PlusActorValueMult = 13,
				SetText = 14
			};

			// members
			REX::Enum<BGSEntryPoint::ENTRY_POINT, std::int8_t> entryPoint; // 0x00
			REX::Enum<EntryPointFunctionType, std::int8_t> functionType;   // 0x01
			std::uint8_t numConditions;									   // 0x02
		};

		static_assert(sizeof(EntryData) == 0x03);

		BGSEntryPointPerkEntry();

		auto GetFunction() -> BGSEntryPoint::ENTRY_POINT override;			 // 0x00
		auto GetFunctionData() const -> BGSEntryPointFunctionData* override; // 0x01

		~BGSEntryPointPerkEntry() override; // 0x02

		auto GetType() const -> PERK_ENTRY_TYPE override; // 0x03
		void ClearData() override;						  // 0x04
		void InitItem(TESFile* a_owner) override;		  // 0x05
		auto Load(TESFile* a_file) -> bool override;	  // 0x06
		void SetParent(BGSPerk* a_parent) override;		  // 0x07
		auto GetID() const -> std::uint16_t override;	  // 0x08
		void ApplyPerkEntry(Actor* a_actor) override;	  // 0x09
		void RemovePerkEntry(Actor* a_actor) override;	  // 0x0A

		// members
		EntryData entryData;							  // 0x10
		BGSEntryPointFunctionData* functionData{nullptr}; // 0x18
		SimpleArray<TESCondition> conditions;			  // 0x20
		BGSPerk* perk{nullptr};							  // 0x28
	};

	static_assert(sizeof(BGSEntryPointPerkEntry) == 0x30);
}
