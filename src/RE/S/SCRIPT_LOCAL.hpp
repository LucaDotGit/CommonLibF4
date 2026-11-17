#pragma once

namespace RE
{
	class SCRIPT_LOCAL
	{
	public:
		// members
		std::uint32_t id;	// 0x00
		REX::Float32 value; // 0x04
		bool isInteger;		// 0x08
	};

	static_assert(sizeof(SCRIPT_LOCAL) == 0x0C);
}
