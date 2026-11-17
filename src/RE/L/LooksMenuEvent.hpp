#pragma once

namespace RE
{
	class LooksMenuEvent
	{
	public:
		enum class EventType : std::int32_t
		{
			Misc = 0,
			Eyes = 1,
			Nose = 2,
			Mouth = 3,
			Head = 4,
			Beard = 5,
			BodyEditStart = 6,
			BodyEditEnd = 7,
			HeadTrackingResume = 8,

			_Count = 9
		};
	};
}
