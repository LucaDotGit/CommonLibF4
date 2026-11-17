#pragma once

#include "RE/B/BGSTypedFormValuePair.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class __declspec(novtable) BGSPropertySheet : public BaseFormComponent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSPropertySheet;
		inline static constexpr const auto& VTABLE = VTABLE::BGSPropertySheet;

		~BGSPropertySheet() override; // 0x00

		// override (BaseFormComponent)
		auto GetFormComponentType() const -> std::uint32_t override;			  // 0x01
		void InitializeDataComponent() override;								  // 0x02
		void ClearDataComponent() override;										  // 0x03
		void InitComponent() override;											  // 0x04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 0x05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 0x06

		[[nodiscard]]
		auto GetProperties() const noexcept
			-> std::optional<std::span<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>>;
		void SetProperties(std::span<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>> a_properties);

		// members
		BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>* properties; // 0x08
	};

	static_assert(sizeof(BGSPropertySheet) == 0x10);
}
