#pragma once

namespace RE
{
	class BGSSaveLoadBuffer
	{
	public:
		// members
		std::byte* buffer; // 08
	};
	static_assert(sizeof(BGSSaveLoadBuffer) == 0x08);
}
