#pragma once

#include "RE/B/BSSimpleList.hpp"
#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class GROUP_REACTION;

	class __declspec(novtable) TESReactionForm : public BaseFormComponent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESReactionForm;
		inline static constexpr const auto& VTABLE = VTABLE::TESReactionForm;

		~TESReactionForm() override; // 0x00

		// override (BaseFormComponent)
		auto GetFormComponentType() const -> std::uint32_t override;			  // 0x01
		void InitializeDataComponent() override;								  // 0x02
		void ClearDataComponent() override;										  // 0x03
		void InitComponent() override;											  // 0x04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 0x05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 0x06

		void SetReactions(std::span<std::unique_ptr<GROUP_REACTION>> a_reactions);
		void ClearReactions();

		// members
		BSSimpleList<GROUP_REACTION*> reactionList; // 0x08
		std::int8_t groupFormType;					// 0x18
	};

	static_assert(sizeof(TESReactionForm) == 0x20);
}
