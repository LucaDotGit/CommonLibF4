#pragma once

#include "RE/N/NiPoint.hpp"

namespace RE
{
	class MoveData
	{
	public:
		// members
		NiPoint3A angle;					   // 00
		NiPoint3A displacement;				   // 10
		REX::Float32 time{ 0.0_f32 };		   // 20
		REX::Float32 currMoveSpeed{ 0.0_f32 }; // 24
		bool visible{ false };				   // 28
		bool deferMove{ false };			   // 29
		bool forceAllowZTranslation{ false };  // 2A
	};
	static_assert(sizeof(MoveData) == 0x30);
}
