#pragma once

namespace RE
{
	enum class ENUM_LOD_MULT : std::int32_t
	{
		None = 0,
		Objects = 1,
		Items = 2,
		Actors = 3,
		Trees = 4,
		Landscape = 5,
		DistantLOD = 6,
		ActorBodyPart = 7,
		RenderedMenu = 8,
		Invisible = 9,
		SkyCell = 10
	};
}
