#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class Object;
}

namespace RE::GameScript::Internal
{
	class __declspec(novtable) LOSEventData
		: public BSIntrusiveRefCounted // 00
	{
	public:
		enum class EventType : std::int32_t
		{
		};

		virtual ~LOSEventData(); // 00

		// members
		BSTSmartPointer<BSScript::Object> object;	  // 10
		BSScript::ObjectHandle viewerHandle;		  // 18
		BSScript::ObjectHandle targetHandle;		  // 20
		REX::Enum<EventType, std::int32_t> eventType; // 28
	};
	static_assert(sizeof(LOSEventData) == 0x30);
}
