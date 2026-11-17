#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/H/hkVector4.hpp"
#include "RE/H/hknpMotionPropertiesId.hpp"
#include "RE/T/TESTriggerEvent.hpp"

namespace RE
{
	class TESTrapHitEvent : public TESTriggerEvent
	{
	public:
		enum class EventType : std::int32_t
		{
			Begin = 0,
			End = 1,
			Hit = 2
		};

		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESTrapHitEvent>*
		{
			using FuncType = decltype(&TESTrapHitEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESTrapHitEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		REX::Enum<EventType, std::int32_t> eventType;						// 0x00
		hkVector4 trapVelocity;												// 0x04
		hkVector4 trapLocation;												// 0x10
		std::uint32_t materialID;											// 0x1C
		REX::Enum<hknpMotionPropertiesId::Preset, std::int32_t> motionType; // 0x20
		bool initialHit;													// 0x24
	};

	static_assert(sizeof(TESTrapHitEvent) == 0x50);
}
