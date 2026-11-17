#pragma once

#include "RE/P/PlayerInputHandler.hpp"

namespace RE
{
	class __declspec(novtable) JumpHandler : public PlayerInputHandler // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::JumpHandler;
		inline static constexpr const auto& VTABLE = VTABLE::JumpHandler;

		explicit JumpHandler(PlayerControlsData& a_data) noexcept :
			PlayerInputHandler(a_data)
		{
			REL::EmplaceVtable(this);
		}

		~JumpHandler() override; // 0x00

		// members
		bool debounceAlternateExit{false}; // 0x20
	};

	static_assert(sizeof(JumpHandler) == 0x28);
}
