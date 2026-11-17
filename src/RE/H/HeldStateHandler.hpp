#pragma once

#include "RE/B/ButtonEvent.hpp"
#include "RE/P/PlayerInputHandler.hpp"

namespace RE
{
	class __declspec(novtable) HeldStateHandler : public PlayerInputHandler // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::HeldStateHandler;
		inline static constexpr const auto& VTABLE = VTABLE::HeldStateHandler;

		explicit HeldStateHandler(PlayerControlsData& a_data) noexcept :
			PlayerInputHandler(a_data)
		{
			REL::EmplaceVtable(this);
		}

		~HeldStateHandler() override; // 0x00

		// add
		virtual void UpdateHeldStateActive(const ButtonEvent* a_event) // 0x10
		{
			heldStateActive = a_event && (a_event->value != static_cast<REX::Float32>(0.0) ||
										  a_event->heldDownSecs < static_cast<REX::Float32>(0.0));
		}

		virtual void SetHeldStateActive(bool a_set) // 0x11
		{
			heldStateActive = a_set;
		}

		// members
		bool heldStateActive{false};	 // 0x20
		bool triggerReleaseEvent{false}; // 0x21
	};

	static_assert(sizeof(HeldStateHandler) == 0x28);
}
