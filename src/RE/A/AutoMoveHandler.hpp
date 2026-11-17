#pragma once

#include "RE/P/PlayerInputHandler.hpp"

namespace RE
{
	class __declspec(novtable) AutoMoveHandler : public PlayerInputHandler // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::AutoMoveHandler;
		inline static constexpr const auto& VTABLE = VTABLE::AutoMoveHandler;

		explicit AutoMoveHandler(PlayerControlsData& a_data) noexcept :
			PlayerInputHandler(a_data)
		{
			REL::EmplaceVtable(this);
		}

		~AutoMoveHandler() override; // 0x00
	};

	static_assert(sizeof(AutoMoveHandler) == 0x20);
}
