#pragma once

#include "RE/B/BSInputEventUser.hpp"
#include "RE/B/BSReadWriteLock.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/B/ButtonEvent.hpp"
#include "RE/C/CharacterEvent.hpp"
#include "RE/C/CursorMoveEvent.hpp"
#include "RE/D/DeviceConnectEvent.hpp"
#include "RE/K/KinectEvent.hpp"
#include "RE/M/MouseMoveEvent.hpp"
#include "RE/T/ThumbstickEvent.hpp"

namespace RE
{
	class InputEvent;

	class BSInputEventQueue : public BSTSingletonSDM<BSInputEventQueue> // 0x00
	{
	public:
		[[nodiscard]]
		static auto GetSingleton() noexcept -> BSInputEventQueue*
		{
			static const auto SINGLETON = REL::Relocation<BSInputEventQueue**>(ID::BSInputEventQueue::Singleton);
			return *SINGLETON;
		}

		// members
		std::array<ButtonEvent, 30> buttonEvents;			   // 0x008
		std::array<CharacterEvent, 15> charEvents;			   // 0x788
		std::array<MouseMoveEvent, 3> mouseEvents;			   // 0xA58
		std::array<CursorMoveEvent, 3> cursorEvents;		   // 0xB18
		std::array<ThumbstickEvent, 6> thumbstickEvents;	   // 0xBD8
		std::array<DeviceConnectEvent, 3> deviceConnectEvents; // 0xD88
		std::array<KinectEvent, 3> kinectEvents;			   // 0xE18
		mutable BSReadWriteLock inputLock;					   // 0xED8
		InputEvent* queueHead;								   // 0xEE0
		InputEvent* queueTail;								   // 0xEE8
		std::uint32_t eventTimeCount;						   // 0xEF0
	};

	static_assert(sizeof(BSInputEventQueue) == 0xEF8);
}
