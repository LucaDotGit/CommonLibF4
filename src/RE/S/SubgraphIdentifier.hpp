#pragma once

namespace RE
{
	class SubgraphIdentifier
	{
	public:
		// members
		std::uint64_t identifier; // 0x00
	};

	static_assert(sizeof(SubgraphIdentifier) == 0x08);
}
