#pragma once

#include "RE/B/BGSTerminal.hpp"
#include "RE/B/BSScaleformExternalTexture.hpp"
#include "RE/B/BSSoundHandle.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/G/GameMenuBase.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE::REFREventCallbacks
{
	class IEventCallback;
}

namespace RE
{
	class NiAVObject;

	class __declspec(novtable) TerminalMenu
		: public GameMenuBase // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TerminalMenu };
		inline static constexpr auto VTABLE{ VTABLE::TerminalMenu };
		inline static constexpr auto MENU_NAME{ "TerminalMenu"sv };
		inline static constexpr auto MENU_DEPTH{ UI_DEPTH_PRIORITY::kTerminalMenu };

		enum class Mode : std::int32_t
		{
			kInit = 0,
			kHack = 1,
			kLogin = 2,
			kList = 3,
			kText = 4,
			kImage = 5,
			kHolotape = 6,
			kWaitingForPapyrus = 7
		};

		class ListItem
		{
		public:
			// members
			BGSTerminal::MenuItem* menuItem{ nullptr }; // 00
			BGSTerminal* terminal{ nullptr };			// 08
		};
		static_assert(sizeof(ListItem) == 0x10);

		~TerminalMenu() override; // 00

		// override (GameMenuBase)
		void Call(const Params& a_params) override;									// 01
		void MapCodeObjectFunctions() override;										// 02
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;			// 03
		void AdvanceMovie(REX::Float32 a_timeDelta, std::uint64_t a_time) override; // 04
		bool CanHandleWhenDisabled(const ButtonEvent* a_event) override;			// 0E
		bool OnButtonEventRelease(const BSFixedString& a_eventName) override;		// 0F

		// override (BSInputEventUser)
		bool ShouldHandleEvent(const InputEvent* a_event) override; // 01
		void OnButtonEvent(const ButtonEvent* a_event) override;	// 08

		// members
		std::array<::Scaleform::GFx::Value, 6> menuElements;							// 0E0
		BSTArray<ListItem> menuItemList;												// 1A0
		BSTArray<NiPointer<NiAVObject>> culledObjects;									// 1B8
		BSTArray<BGSTerminal*> history;													// 1D0
		BSTHashMap<void*, std::uint32_t> lastSelectionMap;								// 1E8
		BSTSmartPointer<REFREventCallbacks::IEventCallback> terminalRunResultsCallback; // 218
		BSScaleformExternalTexture displayImage;										// 220
		BSSoundHandle charScrollLoop;													// 238
		REX::Enum<Mode, std::int32_t> mode;												// 240
		std::uint64_t soundMark;														// 248
		std::uint64_t responseTextTimeout;												// 250
		std::uint64_t loginTextTimeout;													// 258
		bool autoEjectHolotapeOnExit;													// 260
		bool cancelPressRegistered;														// 261
		bool autoLoadHolotape;															// 262
	};
	static_assert(sizeof(TerminalMenu) == 0x268);
}
