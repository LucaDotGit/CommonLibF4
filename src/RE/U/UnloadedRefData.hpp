#pragma once

#include "RE/B/BSTTuple.hpp"

namespace RE
{
	class UnloadedRefData
	{
	public:
		// members
		TESFormID refID{0};			// 0x00
		TESFormID parentSpaceID{0}; // 0x04

		union
		{
		public:
			BSTPair<std::int16_t, std::int16_t> xy;
			std::int32_t raw{0};
		} cellKey; // 0x08
	};

	static_assert(sizeof(UnloadedRefData) == 0x0C);
}
