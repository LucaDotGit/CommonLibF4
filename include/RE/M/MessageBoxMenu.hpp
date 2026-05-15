#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/G/GameMenuBase.hpp"
#include "RE/U/UI_DEPTH_PRIORITY.hpp"

namespace RE
{
	class MenuModeChangeEvent;
	class MessageBoxData;

	class __declspec(novtable) MessageBoxMenu
		: public GameMenuBase,					   // 00
		  public BSTEventSink<MenuModeChangeEvent> // E0
	{
	public:
		inline static constexpr auto RTTI{ RTTI::MessageBoxMenu };
		inline static constexpr auto VTABLE{ VTABLE::MessageBoxMenu };
		inline static constexpr auto MENU_NAME{ "MessageBoxMenu"sv };
		inline static constexpr auto MENU_DEPTH{ UI_DEPTH_PRIORITY::kMessageBoxMenu };

		~MessageBoxMenu() override; // 00

		// override (GameMenuBase)
		void Call(const Params& a_params) override;						  // 01
		void MapCodeObjectFunctions() override;							  // 02
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override; // 03

		// override (BSTEventSink<MenuModeChangeEvent>)
		BSEventNotifyControl ProcessEvent(const MenuModeChangeEvent& a_event, BSTEventSource<MenuModeChangeEvent>* a_eventSource) override;

		void ShowMessage()
		{
			using FuncType = decltype(&MessageBoxMenu::ShowMessage);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::MessageBoxMenu::ShowMessage };
			std::invoke(FUNC, this);
		}

		// members
		MessageBoxData* currentMessage; // E8
	};
	static_assert(sizeof(MessageBoxMenu) == 0xF0);
}
