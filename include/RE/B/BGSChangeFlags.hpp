#pragma once

namespace RE
{
	class BGSChangeFlags
	{
	public:
		// members
		std::uint32_t flags; // 00
	};
	static_assert(sizeof(BGSChangeFlags) == 0x04);
}
