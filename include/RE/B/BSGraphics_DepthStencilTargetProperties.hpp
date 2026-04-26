#pragma once

namespace RE::BSGraphics
{
	class DepthStencilTargetProperties
	{
	public:
		// members
		std::uint32_t width;	   // 00
		std::uint32_t height;	   // 04
		std::uint32_t arraySize;   // 08
		std::uint32_t multiSample; // 0C
		std::int32_t alias;		   // 10
		bool sampleable;		   // 14
		bool htile;				   // 15
		bool stencil;			   // 16
		bool use16BitsDepth;	   // 17
	};
	static_assert(sizeof(DepthStencilTargetProperties) == 0x18);
}
