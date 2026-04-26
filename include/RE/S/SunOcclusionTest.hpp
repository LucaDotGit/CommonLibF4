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
		BSGraphics::OcclusionQuery* occlusionQuery; // 00
		REX::Float32 percentOccluded;				// 08
		std::uint32_t pixelCount;					// 0C
		std::uint32_t frameCount;					// 10
		bool waiting;								// 14
	};
}
