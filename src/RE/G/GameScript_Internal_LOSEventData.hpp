#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class Object;
}

namespace RE::GameScript::Internal
{
	class __declspec(novtable) LOSEventData : public BSIntrusiveRefCounted // 0x00
	{
	public:
		enum class EventType : std::int32_t
		{
		};

		virtual ~LOSEventData(); // 0x00

		// members
		BSTSmartPointer<BSScript::Object> object;	  // 0x10
		BSScript::ObjectHandle viewerHandle;		  // 0x18
		BSScript::ObjectHandle targetHandle;		  // 0x20
		REX::Enum<EventType, std::int32_t> eventType; // 0x28
	};

	static_assert(sizeof(LOSEventData) == 0x30);
}
