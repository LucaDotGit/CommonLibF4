#pragma once

#include "RE/P/PlayerInputHandler.hpp"

namespace RE
{
	class __declspec(novtable) ReadyWeaponHandler
		: public PlayerInputHandler // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ReadyWeaponHandler };
		inline static constexpr auto VTABLE{ VTABLE::ReadyWeaponHandler };

		explicit ReadyWeaponHandler(PlayerControlsData& a_data) noexcept
			: PlayerInputHandler(a_data)
		{
		}

		// members
		bool actionTaken{ false }; // 20
	};
	static_assert(sizeof(ReadyWeaponHandler) == 0x28);
}
