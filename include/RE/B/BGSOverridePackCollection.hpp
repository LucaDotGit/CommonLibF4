#pragma once

#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class __declspec(novtable) BGSOverridePackCollection
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSOverridePackCollection };
		inline static constexpr auto VTABLE{ VTABLE::BGSOverridePackCollection };

		~BGSOverridePackCollection() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		// members
		BGSListForm* spectatorOverridePackList;		  // 08
		BGSListForm* observeCorpseOverridePackList;	  // 10
		BGSListForm* guardWarnOverridePackList;		  // 18
		BGSListForm* enterCombatOverridePackList;	  // 20
		BGSListForm* followerCommandOverridePackList; // 28
		BGSListForm* elevatorOverridePackList;		  // 30
	};
	static_assert(sizeof(BGSOverridePackCollection) == 0x38);
}
