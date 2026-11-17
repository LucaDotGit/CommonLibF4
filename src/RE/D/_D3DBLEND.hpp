#pragma once

namespace RE
{
	enum class _D3DBLEND : std::int32_t
	{
		None = 0,
		Zero = 1,
		One = 2,
		SrcColor = 3,
		InvSrcColor = 4,
		SrcAlpha = 5,
		InvSrcAlpha = 6,
		DestAlpha = 7,
		InvDestAlpha = 8,
		DestColor = 9,
		InvDestColor = 10,
		SrcAlphaSat = 11,
		BothSrcAlpha = 12,
		BothInvSrcAlpha = 13,
		BlendFactor = 14,
		InvBlendFactor = 15,
		SrcColor2 = 16,
		InvSrcColor2 = 17,
		Force_DWORD = std::numeric_limits<std::int32_t>::max()
	};
}
