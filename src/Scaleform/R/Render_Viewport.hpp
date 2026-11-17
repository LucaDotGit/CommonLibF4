#pragma once

namespace Scaleform::Render
{
	class Viewport
	{
	public:
		enum class Flags : std::uint32_t
		{
			None = 0,

			IsRenderTexture = 1 << 0,

			AlphaComposite = 1 << 1,
			UseScissorRect = 1 << 2,

			NoSetState = 1 << 3,

			Orientation_Normal = 0,
			Orientation_R90 = 1 << 4,
			Orientation_180 = 1 << 5,
			Orientation_L90 = Orientation_R90 | Orientation_180,
			Orientation_Mask = Orientation_Normal | Orientation_R90 | Orientation_180 | Orientation_L90,

			Stereo_SplitV = 1 << 6,
			Stereo_SplitH = 1 << 7,
			Stereo_AnySplit = Stereo_SplitV | Stereo_SplitH,

			RenderTextureAlpha = IsRenderTexture | AlphaComposite,

			FirstHalFlag = 1 << 8
		};

		// members
		std::int32_t bufferWidth;				  // 0x00
		std::int32_t bufferHeight;				  // 0x04
		std::int32_t left;						  // 0x08
		std::int32_t top;						  // 0x0C
		std::int32_t width;						  // 0x10
		std::int32_t height;					  // 0x14
		std::int32_t scissorLeft;				  // 0x18
		std::int32_t scissorTop;				  // 0x1C
		std::int32_t scissorWidth;				  // 0x20
		std::int32_t scissorHeight;				  // 0x24
		REX::EnumSet<Flags, std::uint32_t> flags; // 0x28
	};

	static_assert(sizeof(Viewport) == 0x2C);
}
