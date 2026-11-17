#pragma once

namespace RE
{
	enum class RESET_3D_FLAGS : std::int32_t
	{
		None = 0,
		Model = 1 << 0,
		Skin = 1 << 1,
		Head = 1 << 2,
		Face = 1 << 3,
		Scale = 1 << 4,
		Skeleton = 1 << 5,
		InitDefault = 1 << 6,
		SkyCellSkin = 1 << 7,
		Havok = 1 << 8,
		DoNotAddOutfit = 1 << 9,
		KeepHead = 1 << 10,
		Dismemberment = 1 << 11,

		_All = Model |
			Skin |
			Head |
			Face |
			Scale |
			Skeleton |
			InitDefault |
			SkyCellSkin |
			Havok |
			DoNotAddOutfit |
			KeepHead |
			Dismemberment
	};
}
