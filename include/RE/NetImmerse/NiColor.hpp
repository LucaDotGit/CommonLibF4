#pragma once

namespace RE
{
	class NiColor
	{
	public:
		// members
		float r; // 00
		float g; // 04
		float b; // 08
	};
	static_assert(sizeof(NiColor) == 0xC);

	class NiColorA
	{
	public:
		// members
		float r; // 00
		float g; // 04
		float b; // 08
		float a; // 0C
	};
	static_assert(sizeof(NiColorA) == 0x10);
}
