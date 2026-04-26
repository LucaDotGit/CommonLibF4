#pragma once

#include "RE/P/PlayerInputHandler.hpp"

namespace RE
{
	class __declspec(novtable) LookHandler
		: public PlayerInputHandler // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::LookHandler };
		inline static constexpr auto VTABLE{ VTABLE::LookHandler };

		explicit LookHandler(PlayerControlsData& a_data) noexcept
			: PlayerInputHandler(a_data)
		{
		}

		// members
		REX::Float32 thumbstickMaxedSec{ 0.0_f32 }; // 20
	};
	static_assert(sizeof(LookHandler) == 0x28);
}
