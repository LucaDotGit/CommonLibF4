#pragma once

#include "RE/B/BGSMessageIcon.hpp"
#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/B/BaseFormComponent.hpp"
#include "RE/T/TESIcon.hpp"
#include "RE/T/TESModelRDT.hpp"

namespace RE
{
	class __declspec(novtable) TESBipedModelForm
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESBipedModelForm };
		inline static constexpr auto VTABLE{ VTABLE::TESBipedModelForm };

		~TESBipedModelForm() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		// members
		std::array<BGSModelMaterialSwap, 2> worldModel; // 008
		std::array<TESIcon, 2> inventoryIcon;			// 088
		std::array<BGSMessageIcon, 2> messageIcon;		// 0A8
		TESModelRDT constraintTemplate;					// 0D8
	};
	static_assert(sizeof(TESBipedModelForm) == 0x108);
}
