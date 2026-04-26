#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class DoorTeleportData;

	class __declspec(novtable) ExtraTeleport
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraTeleport };
		inline static constexpr auto VTABLE{ VTABLE::ExtraTeleport };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kTeleport };

		ExtraTeleport()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraTeleport() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		DoorTeleportData* teleportData{ nullptr }; // 18
	};
	static_assert(sizeof(ExtraTeleport) == 0x20);
}
