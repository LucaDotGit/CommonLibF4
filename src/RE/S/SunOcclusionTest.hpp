#pragma once

namespace RE::BSGraphics
{
	class OcclusionQuery;
}

namespace RE
{
	class SunOcclusionTest
	{
	public:
		// members
		BSGraphics::OcclusionQuery* occlusionQuery; // 0x00
		REX::Float32 percentOccluded;				// 0x08
		std::uint32_t pixelCount;					// 0x0C
		std::uint32_t frameCount;					// 0x10
		bool waiting;								// 0x14
	};
}
