#pragma once

namespace RE
{
	class SceFVector3
	{
	public:
		// members
		REX::Float32 x; // 0x00
		REX::Float32 y; // 0x04
		REX::Float32 z; // 0x08
	};

	static_assert(sizeof(SceFVector3) == 0x0C);
}
