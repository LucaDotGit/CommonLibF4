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
		inline static constexpr const auto& RTTI = RTTI::BSInputEventUser;
		inline static constexpr const auto& VTABLE = VTABLE::BSInputEventUser;

		virtual ~BSInputEventUser() = default; // 0x00

		// add
		virtual auto ShouldHandleEvent([[maybe_unused]] const InputEvent* a_event) -> bool // 0x01
		{
			return false;
		}

		virtual void OnKinectEvent([[maybe_unused]] const KinectEvent* a_event) // 0x02
		{
			return;
		}

		virtual void OnDeviceConnectEvent([[maybe_unused]] const DeviceConnectEvent* a_event) // 0x03
		{
			return;
		}

		virtual void OnThumbstickEvent([[maybe_unused]] const ThumbstickEvent* a_event) // 0x04
		{
			return;
		}

		virtual void OnCursorMoveEvent([[maybe_unused]] const CursorMoveEvent* a_event) // 0x05
		{
			return;
		}

		virtual void OnMouseMoveEvent([[maybe_unused]] const MouseMoveEvent* a_event) // 0x06
		{
			return;
		}

		virtual void OnCharacterEvent([[maybe_unused]] const CharacterEvent* a_event) // 0x07
		{
			return;
		}

		virtual void OnButtonEvent([[maybe_unused]] const ButtonEvent* a_event) // 0x08
		{
			return;
		}

		GAME_HEAP_REDEFINE_NEW(BSInputEventUser);

		// members
		bool inputEventHandlingEnabled{true}; // 0x08
	};

	static_assert(sizeof(BSInputEventUser) == 0x10);
}
