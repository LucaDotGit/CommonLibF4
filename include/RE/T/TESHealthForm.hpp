#pragma once

#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class __declspec(novtable) TESHealthForm
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESHealthForm };
		inline static constexpr auto VTABLE{ VTABLE::TESHealthForm };

		~TESHealthForm() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		[[nodiscard]] static auto GetFormHealth(const TESForm* a_form) -> std::optional<std::uint32_t>;
		static bool SetFormHealth(TESForm* a_form, std::uint32_t a_health);

		// members
		std::uint32_t health; // 08
	};
	static_assert(sizeof(TESHealthForm) == 0x10);
}
