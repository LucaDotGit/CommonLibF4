#pragma once

#include "RE/P/PlayerInputHandler.hpp"

namespace RE
{
	class __declspec(novtable) SneakHandler : public PlayerInputHandler // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::SneakHandler;
		inline static constexpr const auto& VTABLE = VTABLE::SneakHandler;

		explicit SneakHandler(PlayerControlsData& a_data) noexcept :
			PlayerInputHandler(a_data)
		{
			REL::EmplaceVtable(this);
		}

		~SneakHandler() override; // 0x00
	};

	static_assert(sizeof(SneakHandler) == 0x20);
}
