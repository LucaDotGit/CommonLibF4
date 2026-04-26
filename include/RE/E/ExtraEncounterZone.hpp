#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraEncounterZone
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraEncounterZone };
		inline static constexpr auto VTABLE{ VTABLE::ExtraEncounterZone };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kEncounterZone };

		ExtraEncounterZone()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraEncounterZone() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		BGSEncounterZone* encounterZone{ nullptr }; // 18
	};
	static_assert(sizeof(ExtraEncounterZone) == 0x20);

}
