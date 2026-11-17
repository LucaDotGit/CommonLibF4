#pragma once

namespace RE
{
	class BSSplatterData
	{
	public:
		// members
		REX::Float32 age;	   // 0x00
		REX::Float32 duration; // 0x04
		REX::Float32 alpha;	   // 0x08
		std::uint32_t count;   // 0x0C
	};

	static_assert(sizeof(BSSplatterData) == 0x10);
}
