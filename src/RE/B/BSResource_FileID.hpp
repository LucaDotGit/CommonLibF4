#pragma once

namespace RE::BSResource
{
	class FileID
	{
	public:
		// members
		std::uint32_t file{0};		// 0x00
		std::uint32_t extension{0}; // 0x04
	};

	static_assert(sizeof(FileID) == 0x08);
}
