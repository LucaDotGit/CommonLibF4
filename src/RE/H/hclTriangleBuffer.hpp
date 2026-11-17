#pragma once

namespace RE
{
	class hclTriangleBuffer
	{
	public:
		// members
		std::byte* bufferStart;	   // 0x00
		std::uint32_t numElements; // 0x08
		std::uint8_t stride;	   // 0x0C
		bool use16BitsIndices;	   // 0x0D
	};

	static_assert(sizeof(hclTriangleBuffer) == 0x10);
}
