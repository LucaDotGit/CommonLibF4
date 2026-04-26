#pragma once

namespace RE::BSResource
{
	class FileID
	{
	public:
		// members
		std::uint32_t file{ 0 };	  // 00
		std::uint32_t extension{ 0 }; // 04
	};
	static_assert(sizeof(FileID) == 0x08);
}
