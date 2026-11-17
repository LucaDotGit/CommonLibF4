#pragma once

namespace RE
{
	enum class SCRIPT_OUTPUT : std::int32_t;

	class FUNCTION_DATA
	{
	public:
		// members
		REX::Enum<SCRIPT_OUTPUT, std::uint16_t> function; // 0x00
		std::array<void*, 2> param;						  // 0x08
	};

	static_assert(sizeof(FUNCTION_DATA) == 0x18);
}
