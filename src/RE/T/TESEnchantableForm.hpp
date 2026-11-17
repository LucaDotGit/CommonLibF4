#pragma once

#include "RE/B/BaseFormComponent.hpp"

namespace RE::MagicSystem
{
	enum class CastingType : std::int32_t;
}

namespace RE
{
	class __declspec(novtable) TESEnchantableForm : public BaseFormComponent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESEnchantableForm;
		inline static constexpr const auto& VTABLE = VTABLE::TESEnchantableForm;

		~TESEnchantableForm() override; // 0x00

		// override (BaseFormComponent)
		auto GetFormComponentType() const -> std::uint32_t override;			  // 0x01
		void InitializeDataComponent() override;								  // 0x02
		void ClearDataComponent() override;										  // 0x03
		void InitComponent() override;											  // 0x04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 0x05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 0x06

		// add
		virtual auto GetCastingType() const -> MagicSystem::CastingType; // 0x07 - { return *castingType; }

		[[nodiscard]]
		auto GetBaseCharge() const noexcept -> std::uint16_t
		{
			return amountOfEnchantment;
		}

		[[nodiscard]]
		auto GetBaseEnchanting() const noexcept -> EnchantmentItem*
		{
			return formEnchanting;
		}

		void SetBaseCharge(std::uint16_t a_amount) noexcept
		{
			amountOfEnchantment = a_amount;
		}

		void SetBaseEnchanting(EnchantmentItem* a_ench) noexcept
		{
			formEnchanting = a_ench;
		}

		// members
		EnchantmentItem* formEnchanting;							   // 0x08
		REX::Enum<MagicSystem::CastingType, std::int16_t> castingType; // 0x10
		std::uint16_t amountOfEnchantment;							   // 0x12
	};

	static_assert(sizeof(TESEnchantableForm) == 0x18);
}
