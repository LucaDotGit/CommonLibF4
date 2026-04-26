#pragma once

namespace RE
{
	enum class REGION_DATA_ID : std::int32_t
	{
		kNone = 0,
		kGeneralID = 1,
		kObjectsID = 2,
		kWeatherID = 3,
		kMapID = 4,
		kLandscapeID = 5,
		kGrassID = 6,
		kSoundID = 7,

		kTotal = 8
	};
}
