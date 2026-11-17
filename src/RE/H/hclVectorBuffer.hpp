#pragma once

namespace RE
{
	class hclVectorBuffer
	{
	public:
		// members
		std::byte* bufferStart;	   // 0x00
		std::uint32_t numElements; // 0x08
		std::uint8_t stride;	   // 0x0C
		std::uint32_t flags;	   // 0x10 - To-Do
	};

	static_assert(sizeof(hclVectorBuffer) == 0x18);
}
