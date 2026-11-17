#pragma once

#include "RE/P/PlayerInputHandler.hpp"

namespace RE
{
	class __declspec(novtable) LookHandler : public PlayerInputHandler // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::LookHandler;
		inline static constexpr const auto& VTABLE = VTABLE::LookHandler;

		explicit LookHandler(PlayerControlsData& a_data) noexcept :
			PlayerInputHandler(a_data)
		{
			REL::EmplaceVtable(this);
		}

		~LookHandler() override; // 0x00

		// members
		REX::Float32 thumbstickMaxedSec{static_cast<REX::Float32>(0.0)}; // 0x20
	};

	static_assert(sizeof(LookHandler) == 0x28);
}
