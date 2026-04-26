#pragma once

namespace RE
{
	class CubeMapSide
	{
	public:
		// members
		std::uint32_t side;		 // 00
		REX::Float32 renderTime; // 04
	};
	static_assert(sizeof(CubeMapSide) == 0x08);
}
