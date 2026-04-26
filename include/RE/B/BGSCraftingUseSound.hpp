#pragma once

#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class __declspec(novtable) BGSCraftingUseSound
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSCraftingUseSound };
		inline static constexpr auto VTABLE{ VTABLE::BGSCraftingUseSound };

		~BGSCraftingUseSound() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		// members
		BGSSoundDescriptorForm* craftingUseSound; // 08
	};
	static_assert(sizeof(BGSCraftingUseSound) == 0x10);
}
