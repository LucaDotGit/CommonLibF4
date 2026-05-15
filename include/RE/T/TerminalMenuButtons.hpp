#pragma once

#include "RE/G/GameMenuBase.hpp"
#include "RE/U/UI_DEPTH_PRIORITY.hpp"

namespace RE
{
	class __declspec(novtable) TerminalMenuButtons
		: public GameMenuBase // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TerminalMenuButtons };
		inline static constexpr auto VTABLE{ VTABLE::TerminalMenuButtons };
		inline static constexpr auto MENU_NAME{ "TerminalMenuButtons"sv };
		inline static constexpr auto MENU_DEPTH{ UI_DEPTH_PRIORITY::kTerminalMenuButtons };

		~TerminalMenuButtons() override; // 00

		// override (GameMenuBase)
		void Call(const Params& a_params) override;						  // 01
		void MapCodeObjectFunctions() override;							  // 02
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override; // 03
	};
	static_assert(sizeof(TerminalMenuButtons) == 0xE0);
}
