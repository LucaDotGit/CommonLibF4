#pragma once

namespace RE
{
	class SceFQuaternion
	{
	public:
		// members
		REX::Float32 x; // 00
		REX::Float32 y; // 04
		REX::Float32 z; // 08
		REX::Float32 w; // 0C
	};
	static_assert(sizeof(SceFQuaternion) == 0x10);
}
