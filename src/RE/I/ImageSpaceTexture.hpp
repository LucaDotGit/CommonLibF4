#pragma once

namespace RE::BSGraphics
{
	enum class TextureAddressMode : std::int32_t;
	enum class TextureFilterMode : std::int32_t;
}

namespace RE
{
	class NiTexture;

	class ImageSpaceTexture
	{
	public:
		// members
		bool forceAniso;						  // 0x00
		NiTexture* texture;						  // 0x08
		std::int32_t renderTarget;				  // 0x10
		std::int32_t depthBuffer;				  // 0x14
		std::int32_t stencilBuffer;				  // 0x18
		BSGraphics::TextureFilterMode filterMode; // 0x1C
		BSGraphics::TextureAddressMode clampMode; // 0x20
		bool acquiredTarget;					  // 0x24
	};

	static_assert(sizeof(ImageSpaceTexture) == 0x28);
}
