#pragma once

#include "RE/B/BaseFormComponent.hpp"

namespace RE::MagicSystem
{
	enum class CastingType : std::int32_t;
}

namespace RE
{
	class __declspec(novtable) TESEnchantableForm
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESEnchantableForm };
		inline static constexpr auto VTABLE{ VTABLE::TESEnchantableForm };

		~TESEnchantableForm() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		// add
		virtual MagicSystem::CastingType GetCastingType() const; // 07 - { return *castingType; }

		[[nodiscard]] std::uint16_t GetBaseCharge() const noexcept { return amountOfEnchantment; }
		[[nodiscard]] EnchantmentItem* GetBaseEnchanting() const noexcept { return formEnchanting; }
		void SetBaseCharge(std::uint16_t a_amount) noexcept { amountOfEnchantment = a_amount; }
		void SetBaseEnchanting(EnchantmentItem* a_ench) noexcept { formEnchanting = a_ench; }

		// members
		EnchantmentItem* formEnchanting;							   // 08
		REX::Enum<MagicSystem::CastingType, std::int16_t> castingType; // 10
		std::uint16_t amountOfEnchantment;							   // 12
	};
	static_assert(sizeof(TESEnchantableForm) == 0x18);
}
