#pragma once

namespace RE
{
	class SubgraphHandle
	{
	public:
		// members
		std::uint64_t handle; // 00
	};
	static_assert(sizeof(SubgraphHandle) == 0x08);
}
