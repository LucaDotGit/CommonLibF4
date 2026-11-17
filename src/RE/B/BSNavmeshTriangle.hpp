#pragma once

namespace RE
{
	class BSNavmeshTriangle
	{
	public:
		// members
		std::array<std::uint16_t, 3> vertices;	// 0x00
		std::array<std::uint16_t, 3> triangles; // 0x06
		REX::Float32 height;					// 0x0C
		std::uint32_t triangleFlags;			// 0x10
		std::int8_t traversalFlags;				// 0x14
	};

	static_assert(sizeof(BSNavmeshTriangle) == 0x18);
}
