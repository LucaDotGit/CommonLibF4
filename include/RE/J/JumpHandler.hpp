#pragma once

#include "RE/P/PlayerInputHandler.hpp"

namespace RE
{
	class __declspec(novtable) JumpHandler
		: public PlayerInputHandler // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::JumpHandler };
		inline static constexpr auto VTABLE{ VTABLE::JumpHandler };

		explicit JumpHandler(PlayerControlsData& a_data) noexcept
			: PlayerInputHandler(a_data)
		{
		}

		// members
		bool debounceAlternateExit{ false }; // 20
	};
	static_assert(sizeof(JumpHandler) == 0x28);
}
