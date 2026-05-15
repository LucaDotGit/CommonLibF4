#pragma once

#include "RE/B/BSSoundHandle.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/G/GameMenuBase.hpp"

namespace RE
{
	class MenuOpenCloseEvent;

	class __declspec(novtable) HolotapeMenu
		: public GameMenuBase,					  // 00
		  public BSTEventSink<MenuOpenCloseEvent> // E0
	{
	public:
		inline static constexpr auto RTTI{ RTTI::HolotapeMenu };
		inline static constexpr auto VTABLE{ VTABLE::HolotapeMenu };
		inline static constexpr auto MENU_NAME{ "HolotapeMenu"sv };

		~HolotapeMenu() override; // 00

		// override (GameMenuBase)
		void Call(const Params& a_params) override;							  // 01
		void MapCodeObjectFunctions() override;								  // 02
		bool CanHandleWhenDisabled(const ButtonEvent* a_event) override;	  // 0E
		bool OnButtonEventRelease(const BSFixedString& a_eventName) override; // 0F

		// add
		virtual void ProcessCancel() = 0;				// 14
		virtual void ProcessChatterImpl(const Params&); // 15

		// override (BSInputEventUser)
		bool ShouldHandleEvent(const InputEvent* a_event) override;		 // 01
		void OnThumbstickEvent(const ThumbstickEvent* a_event) override; // 04

		// override (BSTEventSink)
		BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent& a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource) override; // 01

		static void ShowHolotapeInPipboy(const BSFixedString& a_holotapePath)
		{
			using FuncType = decltype(&HolotapeMenu::ShowHolotapeInPipboy);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::HolotapeMenu::ShowHolotapeInPipboy };
			std::invoke(FUNC, a_holotapePath);
		}

		static void ShowHolotapeInTerminal(const BSFixedString& a_holotapePath)
		{
			using FuncType = decltype(&HolotapeMenu::ShowHolotapeInTerminal);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::HolotapeMenu::ShowHolotapeInTerminal };
			std::invoke(FUNC, a_holotapePath);
		}

		// members
		BSTArray<BSSoundHandle> registeredSounds; // 0E8
		bool useOwnCursor;						  // 100
		bool isMinigame;						  // 101
	};
	static_assert(sizeof(HolotapeMenu) == 0x108);
}
