#pragma once

#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class TBO_InstanceData;

	class __declspec(novtable) BGSEquipType
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSEquipType };
		inline static constexpr auto VTABLE{ VTABLE::BGSEquipType };

		~BGSEquipType() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		// add
		[[nodiscard]] virtual BGSEquipSlot* GetEquipSlot(const TBO_InstanceData* a_data); // 06 - { return equipSlot; }
		virtual void SetEquipSlot(BGSEquipSlot* a_slot);								  // 07 - { equipSlot = a_slot; }

		// members
		BGSEquipSlot* equipSlot; // 08
	};
	static_assert(sizeof(BGSEquipType) == 0x10);
}
