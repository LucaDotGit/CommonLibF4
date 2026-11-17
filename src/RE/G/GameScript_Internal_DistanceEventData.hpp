#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class Object;
}

namespace RE::GameScript::Internal
{
	class DistanceEventData : public BSIntrusiveRefCounted // 0x00
	{
	public:
		enum class EventType : std::int32_t
		{
			DerivedAttribute = 0,
			Attribute = 1,
			Skill = 2,
			AIAttribute = 3,
			Resistance = 4,
			Condition = 5,
			Charge = 6,
			Integer = 7,
			Variable = 8,
			Resource = 9
		};

		// members
		BSTSmartPointer<BSScript::Object> object;	  // 0x08
		BSScript::ObjectHandle handle01;			  // 0x10
		BSScript::ObjectHandle handle02;			  // 0x18
		REX::Float32 distance;						  // 0x20
		REX::Enum<EventType, std::int32_t> eventType; // 0x24
	};

	static_assert(sizeof(DistanceEventData) == 0x28);
}
