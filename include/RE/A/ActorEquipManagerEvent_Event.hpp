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
			kEquip = 0,
			kUnequip = 1
		};

		// members
		REX::Enum<EventType, std::int16_t> eventType; // 00
		BGSObjectInstance* affectedItem;			  // 08
		Actor* affectedActor;						  // 10
		std::uint32_t stackID;						  // 18
	};
	static_assert(sizeof(Event) == 0x20);
}
