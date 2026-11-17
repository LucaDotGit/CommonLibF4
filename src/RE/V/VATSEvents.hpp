#pragma once

#include "RE/V/VATS.hpp"

namespace RE::VATSEvents
{
	class ModeChange
	{
	public:
		// members
		VATS::VATS_MODE_ENUM oldMode; // 0x00
		VATS::VATS_MODE_ENUM newMode; // 0x04
	};

	static_assert(sizeof(ModeChange) == 0x08);
}
