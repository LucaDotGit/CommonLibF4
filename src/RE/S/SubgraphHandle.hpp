#pragma once

namespace RE
{
	class SubgraphHandle
	{
	public:
		// members
		std::uint64_t handle; // 0x00
	};

	static_assert(sizeof(SubgraphHandle) == 0x08);
}
