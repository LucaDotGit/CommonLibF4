#pragma once

#include "RE/B/BaseFormComponent.hpp"

namespace RE
{
	class TBO_InstanceData;

	class __declspec(novtable) BGSEquipType : public BaseFormComponent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSEquipType;
		inline static constexpr const auto& VTABLE = VTABLE::BGSEquipType;

		~BGSEquipType() override; // 0x00

		// override (BaseFormComponent)
		auto GetFormComponentType() const -> std::uint32_t override;			  // 0x01
		void InitializeDataComponent() override;								  // 0x02
		void ClearDataComponent() override;										  // 0x03
		void InitComponent() override;											  // 0x04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 0x05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 0x06

		// add
		[[nodiscard]]
		virtual auto GetEquipSlot(const TBO_InstanceData* a_data) -> BGSEquipSlot*; // 0x06 - { return equipSlot; }
		virtual void SetEquipSlot(BGSEquipSlot* a_slot);							// 0x07 - { equipSlot = a_slot; }

		// members
		BGSEquipSlot* equipSlot; // 0x08
	};

	static_assert(sizeof(BGSEquipType) == 0x10);
}
