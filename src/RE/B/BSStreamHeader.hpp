#pragma once

namespace RE
{
	class BSStreamHeader
	{
	public:
		// members
		std::uint32_t version;							   // 0x000
		REX::StaticString<0x40> author;					   // 0x004
		REX::StaticString<0x40> processScript;			   // 0x044
		REX::StaticString<0x40> exportScript;			   // 0x084
		REX::StaticString<REX::W32::MAX_PATH> maxFilePath; // 0x0C4
	};

	static_assert(sizeof(BSStreamHeader) == 0x1C8);
}
