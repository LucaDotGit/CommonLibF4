#pragma once

#include "RE/B/ButtonEvent.hpp"
#include "RE/P/PlayerInputHandler.hpp"

namespace RE
{
	class __declspec(novtable) HeldStateHandler
		: public PlayerInputHandler // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::HeldStateHandler };
		inline static constexpr auto VTABLE{ VTABLE::HeldStateHandler };

		explicit HeldStateHandler(PlayerControlsData& a_data) noexcept
			: PlayerInputHandler(a_data)
		{
			// REL::EmplaceVtable(this);
		}

		~HeldStateHandler() override = default; // 00

		// add
		virtual void UpdateHeldStateActive(const ButtonEvent* a_event) { heldStateActive = a_event && (a_event->value != 0.0_f32 || a_event->heldDownSecs < 0.0_f32); } // 10
		virtual void SetHeldStateActive(bool a_set) { heldStateActive = a_set; }																						// 11

		// members
		bool heldStateActive{ false };	   // 20
		bool triggerReleaseEvent{ false }; // 21
	};
	static_assert(sizeof(HeldStateHandler) == 0x28);
}
