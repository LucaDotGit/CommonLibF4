#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class DoorTeleportData;

	class __declspec(novtable) ExtraTeleport : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraTeleport;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraTeleport;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::Teleport;

		ExtraTeleport() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraTeleport() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		DoorTeleportData* teleportData{nullptr}; // 0x18
	};

	static_assert(sizeof(ExtraTeleport) == 0x20);
}
