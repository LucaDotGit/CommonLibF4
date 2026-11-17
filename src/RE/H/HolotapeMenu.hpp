#pragma once

#include "RE/B/BSSoundHandle.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/G/GameMenuBase.hpp"

namespace RE
{
	class MenuOpenCloseEvent;

	class __declspec(novtable) HolotapeMenu :
		public GameMenuBase,					// 0x00
		public BSTEventSink<MenuOpenCloseEvent> // 0xE0
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::HolotapeMenu;
		inline static constexpr const auto& VTABLE = VTABLE::HolotapeMenu;
		inline static constexpr auto MENU_NAME = "HolotapeMenu"sv;

		~HolotapeMenu() override; // 0x00

		// override (GameMenuBase)
		void Call(const Params& a_params) override;									  // 0x01
		void MapCodeObjectFunctions() override;										  // 0x02
		auto CanHandleWhenDisabled(const ButtonEvent* a_event) -> bool override;	  // 0x0E
		auto OnButtonEventRelease(const BSFixedString& a_eventName) -> bool override; // 0x0F

		// add
		virtual void ProcessCancel() = 0;				// 0x14
		virtual void ProcessChatterImpl(const Params&); // 0x15

		// override (BSInputEventUser)
		auto ShouldHandleEvent(const InputEvent* a_event) -> bool override; // 0x01
		void OnThumbstickEvent(const ThumbstickEvent* a_event) override;	// 0x04

		// override (BSTEventSink)
		auto ProcessEvent(
			const MenuOpenCloseEvent& a_event,
			BSTEventSource<MenuOpenCloseEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		static void ShowHolotapeInPipboy(const BSFixedString& a_holotapePath)
		{
			using FuncType = decltype(&HolotapeMenu::ShowHolotapeInPipboy);
			static const auto FUNC = REL::Relocation<FuncType>(ID::HolotapeMenu::ShowHolotapeInPipboy);
			std::invoke(FUNC, a_holotapePath);
		}

		static void ShowHolotapeInTerminal(const BSFixedString& a_holotapePath)
		{
			using FuncType = decltype(&HolotapeMenu::ShowHolotapeInTerminal);
			static const auto FUNC = REL::Relocation<FuncType>(ID::HolotapeMenu::ShowHolotapeInTerminal);
			std::invoke(FUNC, a_holotapePath);
		}

		// members
		BSTArray<BSSoundHandle> registeredSounds; // 0x0E8
		bool useOwnCursor;						  // 0x100
		bool isMinigame;						  // 0x101
	};

	static_assert(sizeof(HolotapeMenu) == 0x108);
}
