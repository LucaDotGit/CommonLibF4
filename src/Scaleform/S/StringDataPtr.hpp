#pragma once

namespace Scaleform
{
	class StringDataPtr
	{
	public:
		// members
		const char* str;	// 0x00
		std::uint64_t size; // 0x08
	};

	static_assert(sizeof(StringDataPtr) == 0x10);
}
