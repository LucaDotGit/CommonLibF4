#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class ButtonEvent;
	class CharacterEvent;
	class CursorMoveEvent;
	class DeviceConnectEvent;
	class InputEvent;
	class MouseMoveEvent;
	class KinectEvent;
	class ThumbstickEvent;

	class __declspec(novtable) BSInputEventUser
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSInputEventUser };
		inline static constexpr auto VTABLE{ VTABLE::BSInputEventUser };

		virtual ~BSInputEventUser() = default; // 00

		// add
		virtual bool ShouldHandleEvent([[maybe_unused]] const InputEvent* a_event) { return false; }	  // 01
		virtual void OnKinectEvent([[maybe_unused]] const KinectEvent* a_event) { return; }				  // 02
		virtual void OnDeviceConnectEvent([[maybe_unused]] const DeviceConnectEvent* a_event) { return; } // 03
		virtual void OnThumbstickEvent([[maybe_unused]] const ThumbstickEvent* a_event) { return; }		  // 04
		virtual void OnCursorMoveEvent([[maybe_unused]] const CursorMoveEvent* a_event) { return; }		  // 05
		virtual void OnMouseMoveEvent([[maybe_unused]] const MouseMoveEvent* a_event) { return; }		  // 06
		virtual void OnCharacterEvent([[maybe_unused]] const CharacterEvent* a_event) { return; }		  // 07
		virtual void OnButtonEvent([[maybe_unused]] const ButtonEvent* a_event) { return; }				  // 08

		GAME_HEAP_REDEFINE_NEW(BSInputEventUser);

		// members
		bool inputEventHandlingEnabled{ true }; // 08
	};
	static_assert(sizeof(BSInputEventUser) == 0x10);
}
