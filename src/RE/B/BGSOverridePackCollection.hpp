#pragma once

#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class __declspec(novtable) BGSOverridePackCollection : public BaseFormComponent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSOverridePackCollection;
		inline static constexpr const auto& VTABLE = VTABLE::BGSOverridePackCollection;

		~BGSOverridePackCollection() override; // 0x00

		// override (BaseFormComponent)
		auto GetFormComponentType() const -> std::uint32_t override;			  // 0x01
		void InitializeDataComponent() override;								  // 0x02
		void ClearDataComponent() override;										  // 0x03
		void InitComponent() override;											  // 0x04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 0x05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 0x06

		// members
		BGSListForm* spectatorOverridePackList;		  // 0x08
		BGSListForm* observeCorpseOverridePackList;	  // 0x10
		BGSListForm* guardWarnOverridePackList;		  // 0x18
		BGSListForm* enterCombatOverridePackList;	  // 0x20
		BGSListForm* followerCommandOverridePackList; // 0x28
		BGSListForm* elevatorOverridePackList;		  // 0x30
	};

	static_assert(sizeof(BGSOverridePackCollection) == 0x38);
}
