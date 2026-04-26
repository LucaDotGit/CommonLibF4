#pragma once

namespace RE
{
	class SCRIPT_LOCAL
	{
	public:
		// members
		std::uint32_t id;	// 00
		REX::Float32 value; // 04
		bool isInteger;		// 08
	};
	static_assert(sizeof(SCRIPT_LOCAL) == 0x0C);
}
