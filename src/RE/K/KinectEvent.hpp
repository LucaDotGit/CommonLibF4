#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/I/IDEvent.hpp"

namespace RE
{
	class __declspec(novtable) KinectEvent : public IDEvent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::KinectEvent;
		inline static constexpr const auto& VTABLE = VTABLE::KinectEvent;
		inline static constexpr auto INPUT_TYPE = INPUT_EVENT_TYPE::Kinect;

		~KinectEvent() override = default; // 0x00

		// members
		BSFixedString strHeard; // 0x38
	};

	static_assert(sizeof(KinectEvent) == 0x40);
}
