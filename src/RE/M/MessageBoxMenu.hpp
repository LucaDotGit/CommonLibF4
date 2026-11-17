#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/G/GameMenuBase.hpp"
#include "RE/U/UI_DEPTH_PRIORITY.hpp"

namespace RE
{
	class MenuModeChangeEvent;
	class MessageBoxData;

	class __declspec(novtable) MessageBoxMenu :
		public GameMenuBase,					 // 0x00
		public BSTEventSink<MenuModeChangeEvent> // 0xE0
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::MessageBoxMenu;
		inline static constexpr const auto& VTABLE = VTABLE::MessageBoxMenu;
		inline static constexpr auto MENU_NAME = "MessageBoxMenu"sv;
		inline static constexpr auto MENU_DEPTH = UI_DEPTH_PRIORITY::MessageBoxMenu;

		~MessageBoxMenu() override; // 0x00

		// override (GameMenuBase)
		void Call(const Params& a_params) override;								  // 0x01
		void MapCodeObjectFunctions() override;									  // 0x02
		auto ProcessMessage(UIMessage& a_message) -> UI_MESSAGE_RESULTS override; // 0x03

		// override (BSTEventSink<MenuModeChangeEvent>)
		auto ProcessEvent(const MenuModeChangeEvent& a_event, BSTEventSource<MenuModeChangeEvent>* a_eventSource)
			-> BSEventNotifyControl override;

		void ShowMessage()
		{
			using FuncType = decltype(&MessageBoxMenu::ShowMessage);
			static const auto FUNC = REL::Relocation<FuncType>(ID::MessageBoxMenu::ShowMessage);
			std::invoke(FUNC, this);
		}

		// members
		MessageBoxData* currentMessage; // 0xE8
	};

	static_assert(sizeof(MessageBoxMenu) == 0xF0);
}
