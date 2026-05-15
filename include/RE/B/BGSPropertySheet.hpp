#pragma once

#include "RE/B/BGSTypedFormValuePair.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class __declspec(novtable) BGSPropertySheet
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSPropertySheet };
		inline static constexpr auto VTABLE{ VTABLE::BGSPropertySheet };

		~BGSPropertySheet() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		[[nodiscard]] auto GetProperties() const noexcept
			-> std::optional<std::span<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>>;
		void SetProperties(std::span<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>> a_properties);

		// members
		BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>* properties; // 08
	};
	static_assert(sizeof(BGSPropertySheet) == 0x10);
}
