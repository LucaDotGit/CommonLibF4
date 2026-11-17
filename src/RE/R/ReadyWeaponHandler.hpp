#pragma once

#include "RE/P/PlayerInputHandler.hpp"

namespace RE
{
	class __declspec(novtable) ReadyWeaponHandler : public PlayerInputHandler // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ReadyWeaponHandler;
		inline static constexpr const auto& VTABLE = VTABLE::ReadyWeaponHandler;

		explicit ReadyWeaponHandler(PlayerControlsData& a_data) noexcept :
			PlayerInputHandler(a_data)
		{
			REL::EmplaceVtable(this);
		}

		~ReadyWeaponHandler() override; // 0x00

		// members
		bool actionTaken{false}; // 0x20
	};

	static_assert(sizeof(ReadyWeaponHandler) == 0x28);
}
