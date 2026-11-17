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
	class __declspec(novtable) Mod :
		public TESForm,				 // 0x00
		public TESFullName,			 // 0x20
		public TESDescription,		 // 0x30
		public BGSModelMaterialSwap, // 0x48
		public Container			 // 0x88
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSMod__Attachment__Mod;
		inline static constexpr const auto& VTABLE = VTABLE::BGSMod__Attachment__Mod;
		inline static constexpr auto FORM_TYPE = FormType::ObjectMod;

		class Data : public Container::Data // 0x00
		{
		public:
			// members
			REX::Enum<FormType, std::uint8_t> targetFormType; // 0x18
			std::int8_t maxRank;							  // 0x19
			std::int8_t lvlsPerTierScaledOffset;			  // 0x1A
			bool optional;									  // 0x1B
			bool childrenExclusive;							  // 0x1C
		};

		static_assert(sizeof(Data) == 0x20);

		GAME_HEAP_REDEFINE_NEW(Mod);

		static void FindFilesForLooseMod(TESObjectMISC* a_looseMod, BSScrapArray<BGSMod::Attachment::Mod*>& a_result)
		{
			using FuncType = decltype(&Mod::FindFilesForLooseMod);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSMod::Attachment::Mod::FindFilesForLooseMod);
			std::invoke(FUNC, a_looseMod, a_result);
		}

		void GetData(Data& a_data) const
		{
			using FuncType = decltype(&Mod::GetData);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSMod::Attachment::Mod::GetData);
			std::invoke(FUNC, this, a_data);
		}

		[[nodiscard]]
		auto GetLooseMod() const -> TESObjectMISC*
		{
			using FuncType = decltype(&Mod::GetLooseMod);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSMod::Attachment::Mod::GetLooseMod);
			return std::invoke(FUNC, this);
		}

		void SetLooseMod(TESObjectMISC* misc)
		{
			using FuncType = decltype(&Mod::SetLooseMod);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSMod::Attachment::Mod::SetLooseMod);
			std::invoke(FUNC, this, misc);
		}

		// members
		BGSAttachParentArray attachParents;											// 0x98
		BGSTypedKeywordValueArray<KeywordType::InstantiationFilter> filterKeywords; // 0xB0
		BGSTypedKeywordValue<KeywordType::AttachPoint> attachPoint;					// 0xC0
		REX::Enum<FormType, std::uint8_t> targetFormType;							// 0xC2
		std::uint8_t maxRank;														// 0xC3
		std::uint8_t lvlsPerTierScaledOffset;										// 0xC4
		std::int8_t priority;														// 0xC5
		bool optional		   : 1;													// 0xC6:00
		bool childrenExclusive : 1;													// 0xC6:01
	};

	static_assert(sizeof(Mod) == 0xC8);
}
