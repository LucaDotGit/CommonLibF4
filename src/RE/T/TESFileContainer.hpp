#pragma once

namespace RE
{
	class TESFileArray;

	class TESFileContainer
	{
	public:
		// members
		TESFileArray* array; // 0x00
	};

	static_assert(sizeof(TESFileContainer) == 0x08);
}
