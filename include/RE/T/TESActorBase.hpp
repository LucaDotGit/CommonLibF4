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
	class __declspec(novtable) TESActorBase
		: public TESBoundAnimObject,		// 000
		  public TESActorBaseData,			// 068
		  public TESContainer,				// 0D0
		  public TESSpellList,				// 0E8
		  public TESAIForm,					// 0F8
		  public TESFullName,				// 120
		  public ActorValueOwner,			// 130
		  public BGSDestructibleObjectForm, // 138
		  public BGSSkinForm,				// 148
		  public BGSKeywordForm,			// 158
		  public BGSAttackDataForm,			// 178
		  public BGSPerkRankArray,			// 188
		  public BGSPropertySheet			// 1A0
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESActorBase };
		inline static constexpr auto VTABLE{ VTABLE::TESActorBase };
		inline static constexpr auto FORM_TYPE{ FormType::kNone };

		// add
		virtual bool GetHasPLSpecTex() const;		  // 67 - { return false; }
		virtual TESCombatStyle* GetCombatStyle();	  // 68 - { return nullptr; }
		virtual void SetCombatStyle(TESCombatStyle*); // 69 - { return; }
		virtual TESForm* GetAsForm();				  // 6A - { return nullptr; }
	};
	static_assert(sizeof(TESActorBase) == 0x1B0);
}
