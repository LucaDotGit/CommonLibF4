#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE
{
	class FACTION_RANK;

	class __declspec(novtable) ExtraFactionChanges : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraFactionChanges;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraFactionChanges;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::FactionChanges;

		ExtraFactionChanges() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraFactionChanges() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		bool removeCrimeFaction{false};		   // 0x18
		BSTArray<FACTION_RANK> factionChanges; // 0x20
		TESFaction* crimeFaction{nullptr};	   // 0x38
	};

	static_assert(sizeof(ExtraFactionChanges) == 0x40);
}
