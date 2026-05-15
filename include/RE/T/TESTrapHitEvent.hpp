#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/H/hkVector4.hpp"
#include "RE/H/hknpMotionPropertiesId.hpp"
#include "RE/T/TESTriggerEvent.hpp"

namespace RE
{
	class TESTrapHitEvent
		: public TESTriggerEvent
	{
	public:
		enum class EventType : std::int32_t
		{
			kBegin = 0,
			kEnd = 1,
			kHit = 2
		};

		[[nodiscard]] static BSTEventSource<TESTrapHitEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESTrapHitEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESTrapHitEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		REX::Enum<EventType, std::int32_t> eventType;						// 00
		hkVector4 trapVelocity;												// 04
		hkVector4 trapLocation;												// 10
		std::uint32_t materialID;											// 1C
		REX::Enum<hknpMotionPropertiesId::Preset, std::int32_t> motionType; // 20
		bool initialHit;													// 24
	};
	static_assert(sizeof(TESTrapHitEvent) == 0x50);
}
