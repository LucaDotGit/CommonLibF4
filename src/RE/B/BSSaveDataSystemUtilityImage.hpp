#pragma once

namespace RE
{
	class BSSaveDataSystemUtilityImage
	{
	public:
		// members
		std::uint32_t size;	  // 0x00
		std::uint32_t width;  // 0x04
		std::uint32_t height; // 0x08
		std::byte* buffer;	  // 0x10
	};

	static_assert(sizeof(BSSaveDataSystemUtilityImage) == 0x18);
}
