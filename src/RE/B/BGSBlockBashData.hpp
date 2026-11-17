#pragma once

#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class __declspec(novtable) BGSBlockBashData : public BaseFormComponent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSBlockBashData;
		inline static constexpr const auto& VTABLE = VTABLE::BGSBlockBashData;

		~BGSBlockBashData() override; // 0x00

		// override (BaseFormComponent)
		auto GetFormComponentType() const -> std::uint32_t override;			  // 0x01
		void InitializeDataComponent() override;								  // 0x02
		void ClearDataComponent() override;										  // 0x03
		void InitComponent() override;											  // 0x04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 0x05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 0x06

		// members
		BGSImpactDataSet* blockBashImpactDataSet; // 0x08
		BGSMaterialType* altBlockMaterialType;	  // 0x10
	};

	static_assert(sizeof(BGSBlockBashData) == 0x18);
}
