#pragma once

#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class __declspec(novtable) BGSBlockBashData
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSBlockBashData };
		inline static constexpr auto VTABLE{ VTABLE::BGSBlockBashData };

		~BGSBlockBashData() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		// members
		BGSImpactDataSet* blockBashImpactDataSet; // 08
		BGSMaterialType* altBlockMaterialType;	  // 10
	};
	static_assert(sizeof(BGSBlockBashData) == 0x18);
}
