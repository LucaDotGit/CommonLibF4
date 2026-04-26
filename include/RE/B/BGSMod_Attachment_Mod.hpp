#pragma once

#include "RE/B/BGSAttachParentArray.hpp"
#include "RE/B/BGSMod_Container.hpp"
#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/B/BGSTypedKeywordValue.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/T/TESDescription.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESFullName.hpp"

namespace RE::BGSMod::Attachment
{
	class __declspec(novtable) Mod
		: public TESForm,			   // 00
		  public TESFullName,		   // 20
		  public TESDescription,	   // 30
		  public BGSModelMaterialSwap, // 48
		  public Container			   // 88
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSMod__Attachment__Mod };
		inline static constexpr auto VTABLE{ VTABLE::BGSMod__Attachment__Mod };
		inline static constexpr auto FORM_TYPE{ FormType::kObjectMod };

		class Data
			: public Container::Data // 00
		{
		public:
			// members
			REX::Enum<FormType, std::uint8_t> targetFormType; // 18
			std::int8_t maxRank;							  // 19
			std::int8_t lvlsPerTierScaledOffset;			  // 1A
			bool optional;									  // 1B
			bool childrenExclusive;							  // 1C
		};
		static_assert(sizeof(Data) == 0x20);

		GAME_HEAP_REDEFINE_NEW(Mod);

		static void FindFilesForLooseMod(TESObjectMISC* a_looseMod, BSScrapArray<BGSMod::Attachment::Mod*>& a_result)
		{
			using FuncType = decltype(&Mod::FindFilesForLooseMod);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSMod::Attachment::Mod::FindFilesForLooseMod };
			FUNC(a_looseMod, a_result);
		}

		void GetData(Data& a_data) const
		{
			using FuncType = decltype(&Mod::GetData);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSMod::Attachment::Mod::GetData };
			FUNC(this, a_data);
		}

		[[nodiscard]] TESObjectMISC* GetLooseMod() const
		{
			using FuncType = decltype(&Mod::GetLooseMod);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSMod::Attachment::Mod::GetLooseMod };
			return std::invoke(FUNC, this);
		}

		void SetLooseMod(TESObjectMISC* misc)
		{
			using FuncType = decltype(&Mod::SetLooseMod);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSMod::Attachment::Mod::SetLooseMod };
			FUNC(this, misc);
		}

		// members
		BGSAttachParentArray attachParents;											 // 98
		BGSTypedKeywordValueArray<KeywordType::kInstantiationFilter> filterKeywords; // B0
		BGSTypedKeywordValue<KeywordType::kAttachPoint> attachPoint;				 // C0
		REX::Enum<FormType, std::uint8_t> targetFormType;							 // C2
		std::uint8_t maxRank;														 // C3
		std::uint8_t lvlsPerTierScaledOffset;										 // C4
		std::int8_t priority;														 // C5
		bool optional		   : 1;													 // C6:00
		bool childrenExclusive : 1;													 // C6:01
	};
	static_assert(sizeof(Mod) == 0xC8);
}
