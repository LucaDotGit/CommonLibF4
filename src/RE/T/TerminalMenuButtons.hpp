#pragma once

#include "RE/G/GameMenuBase.hpp"
#include "RE/U/UI_DEPTH_PRIORITY.hpp"

namespace RE
{
	class __declspec(novtable) TerminalMenuButtons : public GameMenuBase // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TerminalMenuButtons;
		inline static constexpr const auto& VTABLE = VTABLE::TerminalMenuButtons;
		inline static constexpr auto MENU_NAME = "TerminalMenuButtons"sv;
		inline static constexpr auto MENU_DEPTH = UI_DEPTH_PRIORITY::TerminalMenuButtons;

		~TerminalMenuButtons() override; // 0x00

		// override (GameMenuBase)
		void Call(const Params& a_params) override;								  // 0x01
		void MapCodeObjectFunctions() override;									  // 0x02
		auto ProcessMessage(UIMessage& a_message) -> UI_MESSAGE_RESULTS override; // 0x03
	};

	static_assert(sizeof(TerminalMenuButtons) == 0xE0);
}
