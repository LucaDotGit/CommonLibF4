#pragma once

namespace RE
{
	enum class SCRIPT_ERROR : std::int32_t;
	enum class SCRIPT_OUTPUT : std::int32_t;

	class SCRIPT_LINE
	{
	public:
		// members
		std::uint32_t lineNumber;						   // 0x000
		REX::StaticString<0x200> line;					   // 0x004
		std::uint32_t size;								   // 0x204
		std::uint32_t offset;							   // 0x208
		REX::StaticString<0x200> output;				   // 0x20C
		std::uint32_t outputSize;						   // 0x40C
		SCRIPT_OUTPUT expression;						   // 0x410
		std::uint32_t refObjectIndex;					   // 0x414
		REX::Enum<SCRIPT_ERROR, std::int32_t> scriptError; // 0x418
	};

	static_assert(sizeof(SCRIPT_LINE) == 0x41C);
}
