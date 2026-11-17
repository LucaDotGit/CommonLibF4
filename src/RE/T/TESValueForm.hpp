#pragma once

#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class __declspec(novtable) TESValueForm : public BaseFormComponent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESValueForm;
		inline static constexpr const auto& VTABLE = VTABLE::TESValueForm;

		~TESValueForm() override; // 0x00

		// override (BaseFormComponent)
		auto GetFormComponentType() const -> std::uint32_t override;			  // 0x01
		void InitializeDataComponent() override;								  // 0x02
		void ClearDataComponent() override;										  // 0x03
		void InitComponent() override;											  // 0x04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 0x05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 0x06

		[[nodiscard]]
		static auto GetFormValue(const TESForm* a_form) -> std::optional<std::int32_t>;
		static auto SetFormValue(TESForm* a_form, std::int32_t a_value) -> bool;

		// members
		std::int32_t value; // 0x08
	};

	static_assert(sizeof(TESValueForm) == 0x10);
}
