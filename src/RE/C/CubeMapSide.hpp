#pragma once

namespace RE
{
	class CubeMapSide
	{
	public:
		// members
		std::uint32_t side;		 // 0x00
		REX::Float32 renderTime; // 0x04
	};

	static_assert(sizeof(CubeMapSide) == 0x08);
}
