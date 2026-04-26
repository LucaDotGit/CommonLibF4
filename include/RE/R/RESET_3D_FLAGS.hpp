#pragma once

namespace RE
{
	enum class RESET_3D_FLAGS : std::int32_t
	{
		kNone = 0,
		kModel = 1 << 0,
		kSkin = 1 << 1,
		kHead = 1 << 2,
		kFace = 1 << 3,
		kScale = 1 << 4,
		kSkeleton = 1 << 5,
		kInitDefault = 1 << 6,
		kSkyCellSkin = 1 << 7,
		kHavok = 1 << 8,
		kDoNotAddOutfit = 1 << 9,
		kKeepHead = 1 << 10,
		kDismemberment = 1 << 11,

		kAll = kModel |
			   kSkin |
			   kHead |
			   kFace |
			   kScale |
			   kSkeleton |
			   kInitDefault |
			   kSkyCellSkin |
			   kHavok |
			   kDoNotAddOutfit |
			   kKeepHead |
			   kDismemberment
	};
}
