#pragma once

#include "RE/B/BIPED_MODEL.hpp"
#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class __declspec(novtable) BGSBipedObjectForm : public BaseFormComponent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSBipedObjectForm;
		inline static constexpr const auto& VTABLE = VTABLE::BGSBipedObjectForm;

		~BGSBipedObjectForm() override; // 0x00

		// override (BaseFormComponent)
		auto GetFormComponentType() const -> std::uint32_t override;			  // 0x01
		void InitializeDataComponent() override;								  // 0x02
		void ClearDataComponent() override;										  // 0x03
		void InitComponent() override;											  // 0x04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 0x05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 0x06

		// add
		virtual auto FillsBipedSlot(std::int32_t a_bipedSlot) const -> bool; // 0x06

		// members
		BIPED_MODEL bipedModelData; // 0x08
	};

	static_assert(sizeof(BGSBipedObjectForm) == 0x10);
}
