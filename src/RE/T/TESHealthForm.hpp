#pragma once

#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class __declspec(novtable) TESHealthForm : public BaseFormComponent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESHealthForm;
		inline static constexpr const auto& VTABLE = VTABLE::TESHealthForm;

		~TESHealthForm() override; // 0x00

		// override (BaseFormComponent)
		auto GetFormComponentType() const -> std::uint32_t override;			  // 0x01
		void InitializeDataComponent() override;								  // 0x02
		void ClearDataComponent() override;										  // 0x03
		void InitComponent() override;											  // 0x04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 0x05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 0x06

		[[nodiscard]]
		static auto GetFormHealth(const TESForm* a_form) -> std::optional<std::uint32_t>;
		static auto SetFormHealth(TESForm* a_form, std::uint32_t a_health) -> bool;

		// members
		std::uint32_t health; // 0x08
	};

	static_assert(sizeof(TESHealthForm) == 0x10);
}
