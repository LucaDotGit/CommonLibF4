#pragma once

#include "RE/P/PlayerInputHandler.hpp"

namespace RE
{
	class __declspec(novtable) SneakHandler
		: public PlayerInputHandler // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::SneakHandler };
		inline static constexpr auto VTABLE{ VTABLE::SneakHandler };

		explicit SneakHandler(PlayerControlsData& a_data) noexcept
			: PlayerInputHandler(a_data)
		{
		}
	};
	static_assert(sizeof(SneakHandler) == 0x20);
}
