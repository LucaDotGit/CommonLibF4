#pragma once

namespace RE
{
	class StolenItemValueStruct
	{
	public:
		// members
		std::uint32_t stolenItemValueNoCrime; // 0x00
		std::uint32_t istolenItemValueCrime;  // 0x04
	};

	static_assert(sizeof(StolenItemValueStruct) == 0x08);
}
