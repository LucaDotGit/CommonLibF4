#pragma once

#include "RE/P/PlayerInputHandler.hpp"

namespace RE
{
	class __declspec(novtable) AutoMoveHandler
		: public PlayerInputHandler // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::AutoMoveHandler };
		inline static constexpr auto VTABLE{ VTABLE::AutoMoveHandler };

		explicit AutoMoveHandler(PlayerControlsData& a_data) noexcept
			: PlayerInputHandler(a_data)
		{
		}
	};
	static_assert(sizeof(AutoMoveHandler) == 0x20);
}
