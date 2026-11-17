#pragma once

namespace RE
{
	enum class REGION_DATA_ID : std::int32_t
	{
		None = 0,
		GeneralID = 1,
		ObjectsID = 2,
		WeatherID = 3,
		MapID = 4,
		LandscapeID = 5,
		GrassID = 6,
		SoundID = 7,

		_Count = 8
	};
}
