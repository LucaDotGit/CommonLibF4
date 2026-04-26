#pragma once

#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class __declspec(novtable) TESWeightForm
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESWeightForm };
		inline static constexpr auto VTABLE{ VTABLE::TESWeightForm };

		~TESWeightForm() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		[[nodiscard]] static auto GetFormWeight(const TESForm* a_form) -> std::optional<REX::Float32>;
		static bool SetFormWeight(TESForm* a_form, REX::Float32 a_weight);

		// members
		REX::Float32 weight; // 08
	};
	static_assert(sizeof(TESWeightForm) == 0x10);
}
