#pragma once

namespace RE::BSGraphics
{
	enum class Format : std::int32_t;

	class RenderTargetProperties
	{
	public:
		// members
		std::uint32_t width;		 // 00
		std::uint32_t height;		 // 04
		Format format;				 // 08
		std::uint32_t multiSample;	 // 0C
		bool copyable;				 // 10
		bool supportUnorderedAccess; // 11
		bool allowMipGeneration;	 // 12
		bool forceLinear;			 // 13
		std::int32_t mipLevel;		 // 14
		std::uint32_t textureTarget; // 18
		bool enableFastClear;		 // 1C
	};
	static_assert(sizeof(RenderTargetProperties) == 0x20);
}
