#pragma once

namespace RE
{
	class BGSEquipIndex
	{
	public:
		// members
		std::uint32_t index; // 00
	};
	static_assert(sizeof(BGSEquipIndex) == 0x04);
}
