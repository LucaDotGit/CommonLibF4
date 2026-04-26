#pragma once

#include "RE/B/BSTTuple.hpp"

namespace RE
{
	class UnloadedRefData
	{
	public:
		// members
		TESFormID refID{ 0 };		  // 00
		TESFormID parentSpaceID{ 0 }; // 04
		union
		{
			BSTPair<std::int16_t, std::int16_t> xy;
			std::int32_t raw{ 0 };
		} cellKey; // 08
	};
	static_assert(sizeof(UnloadedRefData) == 0x0C);
}
