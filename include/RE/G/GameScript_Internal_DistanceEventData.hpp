#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class Object;
}

namespace RE::GameScript::Internal
{
	class DistanceEventData
		: public BSIntrusiveRefCounted // 00
	{
	public:
		enum class EventType : std::int32_t
		{
			kDerivedAttribute = 0,
			kAttribute = 1,
			kSkill = 2,
			kAIAttribute = 3,
			kResistance = 4,
			kCondition = 5,
			kCharge = 6,
			kInteger = 7,
			kVariable = 8,
			kResource = 9
		};

		// members
		BSTSmartPointer<BSScript::Object> object;	  // 08
		BSScript::ObjectHandle handle01;			  // 10
		BSScript::ObjectHandle handle02;			  // 18
		REX::Float32 distance;						  // 20
		REX::Enum<EventType, std::int32_t> eventType; // 24
	};
	static_assert(sizeof(DistanceEventData) == 0x28);
}
