#pragma once

namespace RE
{
	enum class SCRIPT_ERROR : std::int32_t;
	enum class SCRIPT_OUTPUT : std::int32_t;

	class SCRIPT_LINE
	{
	public:
		// members
		std::uint32_t lineNumber;						   // 000
		std::array<char, 0x200> line;					   // 004
		std::uint32_t size;								   // 204
		std::uint32_t offset;							   // 208
		std::array<char, 0x200> output;					   // 20C
		std::uint32_t outputSize;						   // 40C
		SCRIPT_OUTPUT expression;						   // 410
		std::uint32_t refObjectIndex;					   // 414
		REX::Enum<SCRIPT_ERROR, std::int32_t> scriptError; // 418
	};
	static_assert(sizeof(SCRIPT_LINE) == 0x41C);
}
