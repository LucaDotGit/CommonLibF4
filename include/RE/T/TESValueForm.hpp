#pragma once

#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class __declspec(novtable) TESValueForm
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESValueForm };
		inline static constexpr auto VTABLE{ VTABLE::TESValueForm };

		~TESValueForm() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		[[nodiscard]] static auto GetFormValue(const TESForm* a_form) -> std::optional<std::int32_t>;
		static bool SetFormValue(TESForm* a_form, std::int32_t a_value);

		// members
		std::int32_t value; // 08
	};
	static_assert(sizeof(TESValueForm) == 0x10);
}
