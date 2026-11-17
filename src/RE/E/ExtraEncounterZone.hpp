#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraEncounterZone : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraEncounterZone;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraEncounterZone;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::EncounterZone;

		ExtraEncounterZone() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraEncounterZone() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		BGSEncounterZone* encounterZone{nullptr}; // 0x18
	};

	static_assert(sizeof(ExtraEncounterZone) == 0x20);

}
