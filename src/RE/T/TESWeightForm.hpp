#pragma once

#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class __declspec(novtable) TESWeightForm : public BaseFormComponent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESWeightForm;
		inline static constexpr const auto& VTABLE = VTABLE::TESWeightForm;

		~TESWeightForm() override; // 0x00

		// override (BaseFormComponent)
		auto GetFormComponentType() const -> std::uint32_t override;			  // 0x01
		void InitializeDataComponent() override;								  // 0x02
		void ClearDataComponent() override;										  // 0x03
		void InitComponent() override;											  // 0x04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 0x05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 0x06

		[[nodiscard]]
		static auto GetFormWeight(const TESForm* a_form) -> std::optional<REX::Float32>;
		static auto SetFormWeight(TESForm* a_form, REX::Float32 a_weight) -> bool;

		// members
		REX::Float32 weight; // 0x08
	};

	static_assert(sizeof(TESWeightForm) == 0x10);
}
