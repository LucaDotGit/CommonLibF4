#pragma once

namespace RE
{
	class BGSObjectInstance;
}

namespace RE::ActorEquipManagerEvent
{
	class Event
	{
	public:
		enum class EventType : std::int16_t
		{
			Equip = 0,
			Unequip = 1
		};

		// members
		REX::Enum<EventType, std::int16_t> eventType; // 0x00
		BGSObjectInstance* affectedItem;			  // 0x08
		Actor* affectedActor;						  // 0x10
		std::uint32_t stackID;						  // 0x18
	};

	static_assert(sizeof(Event) == 0x20);
}
