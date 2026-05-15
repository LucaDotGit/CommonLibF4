#pragma once

#include "RE/B/BSSimpleList.hpp"
#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class GROUP_REACTION;

	class __declspec(novtable) TESReactionForm
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESReactionForm };
		inline static constexpr auto VTABLE{ VTABLE::TESReactionForm };

		~TESReactionForm() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		void SetReactions(std::span<std::unique_ptr<GROUP_REACTION>> a_reactions);
		void ClearReactions();

		// members
		BSSimpleList<GROUP_REACTION*> reactionList; // 08
		std::int8_t groupFormType;					// 18
	};
	static_assert(sizeof(TESReactionForm) == 0x20);
}
