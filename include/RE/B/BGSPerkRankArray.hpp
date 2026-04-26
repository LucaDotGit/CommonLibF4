#pragma once

#include "RE/B/BaseFormComponent.hpp"
#include "RE/S/SimpleArray.hpp"

namespace RE
{
	class PerkRankData;

	class __declspec(novtable) BGSPerkRankArray
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSPerkRankArray };
		inline static constexpr auto VTABLE{ VTABLE::BGSPerkRankArray };

		~BGSPerkRankArray() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		[[nodiscard]] std::span<PerkRankData* const> GetPerks() const noexcept;
		void SetPerks(std::span<std::unique_ptr<PerkRankData>> a_perks);
		void ClearPerks();

		// members
		SimpleArray<PerkRankData*> perks; // 08
		std::uint32_t perkCount;		  // 10
	};
	static_assert(sizeof(BGSPerkRankArray) == 0x18);
}
