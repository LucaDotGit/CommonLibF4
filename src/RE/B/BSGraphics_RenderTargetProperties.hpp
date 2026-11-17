#pragma once

namespace RE::BSGraphics
{
	enum class Format : std::int32_t;

	class RenderTargetProperties
	{
	public:
		// members
		std::uint32_t width;		 // 0x00
		std::uint32_t height;		 // 0x04
		Format format;				 // 0x08
		std::uint32_t multiSample;	 // 0x0C
		bool copyable;				 // 0x10
		bool supportUnorderedAccess; // 0x11
		bool allowMipGeneration;	 // 0x12
		bool forceLinear;			 // 0x13
		std::int32_t mipLevel;		 // 0x14
		std::uint32_t textureTarget; // 0x18
		bool enableFastClear;		 // 0x1C
	};

	static_assert(sizeof(RenderTargetProperties) == 0x20);
}
