#pragma once

namespace RE
{
	class BSStreamHeader
	{
	public:
		// members
		std::uint32_t version;							  // 000
		std::array<char, 64> author;					  // 004
		std::array<char, 64> processScript;				  // 044
		std::array<char, 64> exportScript;				  // 084
		std::array<char, REX::W32::MAX_PATH> maxFilePath; // 0C4
	};
	static_assert(sizeof(BSStreamHeader) == 0x1C8);
}
