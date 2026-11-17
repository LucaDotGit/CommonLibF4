#pragma once

#include "RE/B/BGSTerminal.hpp"
#include "RE/B/BSScaleformExternalTexture.hpp"
#include "RE/B/BSSoundHandle.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/G/GameMenuBase.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/U/UI_DEPTH_PRIORITY.hpp"

namespace RE::REFREventCallbacks
{
	class IEventCallback;
}

namespace RE
{
	class NiAVObject;

	class __declspec(novtable) TerminalMenu : public GameMenuBase // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TerminalMenu;
		inline static constexpr const auto& VTABLE = VTABLE::TerminalMenu;
		inline static constexpr auto MENU_NAME = "TerminalMenu"sv;
		inline static constexpr auto MENU_DEPTH = UI_DEPTH_PRIORITY::TerminalMenu;

		enum class Mode : std::int32_t
		{
			Init = 0,
			Hack = 1,
			Login = 2,
			List = 3,
			Text = 4,
			Image = 5,
			Holotape = 6,
			WaitingForPapyrus = 7
		};

		class ListItem
		{
		public:
			// members
			BGSTerminal::MenuItem* menuItem{nullptr}; // 0x00
			BGSTerminal* terminal{nullptr};			  // 0x08
		};

		static_assert(sizeof(ListItem) == 0x10);

		~TerminalMenu() override; // 0x00

		// override (GameMenuBase)
		void Call(const Params& a_params) override;									  // 0x01
		void MapCodeObjectFunctions() override;										  // 0x02
		auto ProcessMessage(UIMessage& a_message) -> UI_MESSAGE_RESULTS override;	  // 0x03
		void AdvanceMovie(DeltaTime a_deltaTime, std::time_t a_time) override;		  // 0x04
		auto CanHandleWhenDisabled(const ButtonEvent* a_event) -> bool override;	  // 0x0E
		auto OnButtonEventRelease(const BSFixedString& a_eventName) -> bool override; // 0x0F

		// override (BSInputEventUser)
		auto ShouldHandleEvent(const InputEvent* a_event) -> bool override; // 0x01
		void OnButtonEvent(const ButtonEvent* a_event) override;			// 0x08

		// members
		std::array<Scaleform::GFx::Value, 6> menuElements;								// 0x0E0
		BSTArray<ListItem> menuItemList;												// 0x1A0
		BSTArray<NiPointer<NiAVObject>> culledObjects;									// 0x1B8
		BSTArray<BGSTerminal*> history;													// 0x1D0
		BSTHashMap<void*, std::uint32_t> lastSelectionMap;								// 0x1E8
		BSTSmartPointer<REFREventCallbacks::IEventCallback> terminalRunResultsCallback; // 0x218
		BSScaleformExternalTexture displayImage;										// 0x220
		BSSoundHandle charScrollLoop;													// 0x238
		REX::Enum<Mode, std::int32_t> mode;												// 0x240
		std::uint64_t soundMark;														// 0x248
		std::uint64_t responseTextTimeout;												// 0x250
		std::uint64_t loginTextTimeout;													// 0x258
		bool autoEjectHolotapeOnExit;													// 0x260
		bool cancelPressRegistered;														// 0x261
		bool autoLoadHolotape;															// 0x262
	};

	static_assert(sizeof(TerminalMenu) == 0x268);
}
