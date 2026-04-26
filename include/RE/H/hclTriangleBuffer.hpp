#pragma once

namespace RE
{
	class hclTriangleBuffer
	{
	public:
		// members
		std::byte* bufferStart;	   // 00
		std::uint32_t numElements; // 08
		std::uint8_t stride;	   // 0C
		bool use16BitsIndices;	   // 0D
	};
	static_assert(sizeof(hclTriangleBuffer) == 0x10);
}
