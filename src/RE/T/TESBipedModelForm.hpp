#pragma once

#include "RE/B/BGSMessageIcon.hpp"
#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/B/BaseFormComponent.hpp"
#include "RE/T/TESIcon.hpp"
#include "RE/T/TESModelRDT.hpp"

namespace RE
{
	class __declspec(novtable) TESBipedModelForm : public BaseFormComponent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESBipedModelForm;
		inline static constexpr const auto& VTABLE = VTABLE::TESBipedModelForm;

		~TESBipedModelForm() override; // 0x00

		// override (BaseFormComponent)
		auto GetFormComponentType() const -> std::uint32_t override;			  // 0x01
		void InitializeDataComponent() override;								  // 0x02
		void ClearDataComponent() override;										  // 0x03
		void InitComponent() override;											  // 0x04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 0x05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 0x06

		// members
		std::array<BGSModelMaterialSwap, 2> worldModel; // 0x008
		std::array<TESIcon, 2> inventoryIcon;			// 0x088
		std::array<BGSMessageIcon, 2> messageIcon;		// 0x0A8
		TESModelRDT constraintTemplate;					// 0x0D8
	};

	static_assert(sizeof(TESBipedModelForm) == 0x108);
}
