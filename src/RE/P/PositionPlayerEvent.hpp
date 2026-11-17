#pragma once

namespace RE
{
	class PositionPlayerEvent
	{
	public:
		enum class EventType : std::int32_t
		{
			PrePositionPlayer = 0,
			PositionPlayerPreUpdatePackages = 1,
			PositionPlayerPostUpdatePackages = 2,
			PostPositionPlayer = 3,
			FinishPositionPlayer = 4
		};

		// members
		REX::Enum<EventType, std::int32_t> eventType; // 0x00
		bool noLoadScreen;							  // 0x04
	};

	static_assert(sizeof(PositionPlayerEvent) == 0x08);
}
