#pragma once

namespace RE
{
	class SceFVector3
	{
	public:
		// members
		REX::Float32 x; // 00
		REX::Float32 y; // 04
		REX::Float32 z; // 08
	};
	static_assert(sizeof(SceFVector3) == 0x0C);
}
