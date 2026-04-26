#pragma once

#include "RE/B/BSInputEventUser.hpp"
#include "RE/B/BSSpinLock.hpp"
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

	class BSInputEventQueue
		: public BSTSingletonSDM<BSInputEventQueue> // 00
	{
	public:
		[[nodiscard]] static BSInputEventQueue* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<BSInputEventQueue**>{ ID::BSInputEventQueue::Singleton };
			return *SINGLETON;
		}

		// members
		std::array<ButtonEvent, 30> buttonEvents;			   // 008
		std::array<CharacterEvent, 15> charEvents;			   // 788
		std::array<MouseMoveEvent, 3> mouseEvents;			   // A58
		std::array<CursorMoveEvent, 3> cursorEvents;		   // B18
		std::array<ThumbstickEvent, 6> thumbstickEvents;	   // BD8
		std::array<DeviceConnectEvent, 3> deviceConnectEvents; // D88
		std::array<KinectEvent, 3> kinectEvents;			   // E18
		mutable BSReadWriteLock inputLock;					   // ED8
		InputEvent* queueHead;								   // EE0
		InputEvent* queueTail;								   // EE8
		std::uint32_t eventTimeCount;						   // EF0
	};
	static_assert(sizeof(BSInputEventQueue) == 0xEF8);
}
