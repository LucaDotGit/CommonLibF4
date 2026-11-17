#pragma once

#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class MoveData
	{
	public:
		// members
		NiPoint3A angle;											// 0x00
		NiPoint3A displacement;										// 0x10
		REX::Float32 time{static_cast<REX::Float32>(0.0)};			// 0x20
		REX::Float32 currMoveSpeed{static_cast<REX::Float32>(0.0)}; // 0x24
		bool visible{false};										// 0x28
		bool deferMove{false};										// 0x29
		bool forceAllowZTranslation{false};							// 0x2A
	};

	static_assert(sizeof(MoveData) == 0x30);
}
