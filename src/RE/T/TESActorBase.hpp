#pragma once

#include "RE/A/ActorValueOwner.hpp"
#include "RE/B/BGSAttackDataForm.hpp"
#include "RE/B/BGSDestructibleObjectForm.hpp"
#include "RE/B/BGSKeywordForm.hpp"
#include "RE/B/BGSPerkRankArray.hpp"
#include "RE/B/BGSPropertySheet.hpp"
#include "RE/B/BGSSkinForm.hpp"
#include "RE/T/TESAIForm.hpp"
#include "RE/T/TESActorBaseData.hpp"
#include "RE/T/TESBoundAnimObject.hpp"
#include "RE/T/TESContainer.hpp"
#include "RE/T/TESFullName.hpp"
#include "RE/T/TESSpellList.hpp"

namespace RE
{
	class __declspec(novtable) TESActorBase :
		public TESBoundAnimObject,		  // 0x000
		public TESActorBaseData,		  // 0x068
		public TESContainer,			  // 0x0D0
		public TESSpellList,			  // 0x0E8
		public TESAIForm,				  // 0x0F8
		public TESFullName,				  // 0x120
		public ActorValueOwner,			  // 0x130
		public BGSDestructibleObjectForm, // 0x138
		public BGSSkinForm,				  // 0x148
		public BGSKeywordForm,			  // 0x158
		public BGSAttackDataForm,		  // 0x178
		public BGSPerkRankArray,		  // 0x188
		public BGSPropertySheet			  // 0x1A0
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESActorBase;
		inline static constexpr const auto& VTABLE = VTABLE::TESActorBase;
		inline static constexpr auto FORM_TYPE = FormType::None;

		~TESActorBase() override; // 0x00

		// add
		virtual auto GetHasPLSpecTex() const -> bool;	  // 0x67 - { return false; }
		virtual auto GetCombatStyle() -> TESCombatStyle*; // 0x68 - { return nullptr; }
		virtual void SetCombatStyle(TESCombatStyle*);	  // 0x69 - { return; }
		virtual auto GetAsForm() -> TESForm*;			  // 0x6A - { return nullptr; }
	};

	static_assert(sizeof(TESActorBase) == 0x1B0);
}
