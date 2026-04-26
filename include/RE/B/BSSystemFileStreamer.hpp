#pragma once

namespace RE::BSSystemFileStreamer
{
	class ID
	{
	public:
		// members
		std::uint32_t id; // 00
	};
	static_assert(sizeof(ID) == 0x04);

	void UncacheAll(bool a_block);
}
