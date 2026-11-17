#pragma once

#include "RE/B/BaseFormComponent.hpp"
#include "RE/S/SimpleArray.hpp"

namespace RE
{
	class PerkRankData;

	class __declspec(novtable) BGSPerkRankArray : public BaseFormComponent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSPerkRankArray;
		inline static constexpr const auto& VTABLE = VTABLE::BGSPerkRankArray;

		~BGSPerkRankArray() override; // 0x00

		// override (BaseFormComponent)
		auto GetFormComponentType() const -> std::uint32_t override;			  // 0x01
		void InitializeDataComponent() override;								  // 0x02
		void ClearDataComponent() override;										  // 0x03
		void InitComponent() override;											  // 0x04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 0x05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 0x06

		[[nodiscard]]
		auto GetPerks() const noexcept -> std::span<PerkRankData* const>;
		void SetPerks(std::span<std::unique_ptr<PerkRankData>> a_perks);
		void ClearPerks();

		// members
		SimpleArray<PerkRankData*> perks; // 0x08
		std::uint32_t perkCount;		  // 0x10
	};

	static_assert(sizeof(BGSPerkRankArray) == 0x18);
}
