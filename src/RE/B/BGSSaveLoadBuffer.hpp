#pragma once

namespace RE
{
	class BGSSaveLoadBuffer
	{
	public:
		// members
		std::byte* buffer; // 0x08
	};

	static_assert(sizeof(BGSSaveLoadBuffer) == 0x08);
}
