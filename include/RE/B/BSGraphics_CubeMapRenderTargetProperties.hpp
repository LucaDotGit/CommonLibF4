#pragma once

namespace RE::BSGraphics
{
	enum class Format : std::int32_t;

	class CubeMapRenderTargetProperties
	{
	public:
		// members
		std::uint32_t width;		 // 00
		std::uint32_t height;		 // 04
		Format format;				 // 08
		std::uint32_t multiSample;	 // 0C
		bool sampleable;			 // 10
		std::int32_t alias;			 // 14
		std::int32_t _360Alias;		 // 18
		std::int32_t _360Group;		 // 1C
		std::int32_t _360TileHeight; // 20
	};
	static_assert(sizeof(CubeMapRenderTargetProperties) == 0x24);
}
