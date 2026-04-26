#pragma once

namespace RE
{
	enum class _D3DBLEND : std::int32_t
	{
		kNone = 0,
		kZero = 1,
		kOne = 2,
		kSrcColor = 3,
		kInvSrcColor = 4,
		kSrcAlpha = 5,
		kInvSrcAlpha = 6,
		kDestAlpha = 7,
		kInvDestAlpha = 8,
		kDestColor = 9,
		kInvDestColor = 10,
		kSrcAlphaSat = 11,
		kBothSrcAlpha = 12,
		kBothInvSrcAlpha = 13,
		kBlendFactor = 14,
		kInvBlendFactor = 15,
		kSrcColor2 = 16,
		kInvSrcColor2 = 17,
		kForce_DWORD = std::numeric_limits<std::int32_t>::max()
	};
}
