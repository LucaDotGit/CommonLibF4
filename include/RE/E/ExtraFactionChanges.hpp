#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE
{
	class FACTION_RANK;

	class __declspec(novtable) ExtraFactionChanges
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraFactionChanges };
		inline static constexpr auto VTABLE{ VTABLE::ExtraFactionChanges };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kFactionChanges };

		ExtraFactionChanges()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraFactionChanges() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		bool removeCrimeFaction{ false };	   // 18
		BSTArray<FACTION_RANK> factionChanges; // 20
		TESFaction* crimeFaction{ nullptr };   // 38
	};
	static_assert(sizeof(ExtraFactionChanges) == 0x40);
}
