#pragma once

namespace RE
{
	class CrimeGoldStruct
	{
	public:
		// members
		std::uint32_t violent;					  // 0x00
		std::uint32_t nonViolent;				  // 0x04
		std::uint32_t totalNonViolentAccumulated; // 0x08
		std::uint32_t totalViolentAccumulated;	  // 0x0C
	};

	static_assert(sizeof(CrimeGoldStruct) == 0x10);
}
