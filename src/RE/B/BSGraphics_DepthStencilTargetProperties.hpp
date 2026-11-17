#pragma once

namespace RE::BSGraphics
{
	class DepthStencilTargetProperties
	{
	public:
		// members
		std::uint32_t width;	   // 0x00
		std::uint32_t height;	   // 0x04
		std::uint32_t arraySize;   // 0x08
		std::uint32_t multiSample; // 0x0C
		std::int32_t alias;		   // 0x10
		bool sampleable;		   // 0x14
		bool htile;				   // 0x15
		bool stencil;			   // 0x16
		bool use16BitsDepth;	   // 0x17
	};

	static_assert(sizeof(DepthStencilTargetProperties) == 0x18);
}
