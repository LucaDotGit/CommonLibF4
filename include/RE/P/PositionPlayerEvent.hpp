#pragma once

namespace RE
{
	class PositionPlayerEvent
	{
	public:
		enum class EventType : std::int32_t
		{
			kPrePositionPlayer = 0,
			kPositionPlayerPreUpdatePackages = 1,
			kPositionPlayerPostUpdatePackages = 2,
			kPostPositionPlayer = 3,
			kFinishPositionPlayer = 4
		};

		// members
		REX::Enum<EventType, std::int32_t> eventType; // 00
		bool noLoadScreen;							  // 04
	};
	static_assert(sizeof(PositionPlayerEvent) == 0x08);
}
