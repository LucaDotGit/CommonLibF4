#pragma once

namespace RE::BSGraphics
{
	enum class Format : std::int32_t;

	class CubeMapRenderTargetProperties
	{
	public:
		// members
		std::uint32_t width;		 // 0x00
		std::uint32_t height;		 // 0x04
		Format format;				 // 0x08
		std::uint32_t multiSample;	 // 0x0C
		bool sampleable;			 // 0x10
		std::int32_t alias;			 // 0x14
		std::int32_t _360Alias;		 // 0x18
		std::int32_t _360Group;		 // 0x1C
		std::int32_t _360TileHeight; // 0x20
	};

	static_assert(sizeof(CubeMapRenderTargetProperties) == 0x24);
}
