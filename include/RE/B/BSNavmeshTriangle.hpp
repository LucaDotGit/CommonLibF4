#pragma once

namespace RE
{
	class BSNavmeshTriangle
	{
	public:
		// members
		std::array<std::uint16_t, 3> vertices;	// 00
		std::array<std::uint16_t, 3> triangles; // 06
		REX::Float32 height;					// 0C
		std::uint32_t triangleFlags;			// 10
		std::int8_t traversalFlags;				// 14
	};
	static_assert(sizeof(BSNavmeshTriangle) == 0x18);
}
