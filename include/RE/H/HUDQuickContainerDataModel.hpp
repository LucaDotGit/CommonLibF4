#pragma once

#include "RE/B/BSInputEventUser.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTOptional.hpp"
#include "RE/B/BlockPipboyOpeningEvent.hpp"
#include "RE/H/HUDModes.hpp"
#include "RE/I/InventoryUserUIInterface.hpp"
#include "RE/I/IsPipboyActiveEvent.hpp"
#include "RE/N/nsUIDebug_UIDebugLogger_NoOp.hpp"
#include "RE/Q/QuickContainerStateEvent.hpp"
#include "RE/R/RolloverSuppressedEvent.hpp"
#include "RE/V/ViewCasterUpdateEvent.hpp"

namespace RE
{
	class ClearQuickContainerEvent;
	class HUDModeEvent;
	class MenuModeChangeEvent;
	class MenuOpenCloseEvent;
	class OpenContainerMenuEventData;
	class TESContainerChangedEvent;

	class __declspec(novtable) HUDQuickContainerDataModel
		: public BSInputEventUser,						   // 000
		  public BSTEventSink<MenuOpenCloseEvent>,		   // 010
		  public BSTEventSink<HUDModeEvent>,			   // 018
		  public BSTEventSink<OpenContainerMenuEventData>, // 020
		  public BSTEventSink<TESContainerChangedEvent>,   // 028
		  public BSTEventSink<ClearQuickContainerEvent>,   // 030
		  public BSTEventSink<MenuModeChangeEvent>,		   // 038
		  public nsUIDebug::UIDebugLogger_NoOp			   // 040
	{
	public:
		inline static constexpr auto RTTI{ RTTI::HUDQuickContainerDataModel };
		inline static constexpr auto VTABLE{ VTABLE::HUDQuickContainerDataModel };

		~HUDQuickContainerDataModel() override; // 00

		// override (BSInputEventUser)
		bool ShouldHandleEvent(const InputEvent* a_event) override; // 01
		void OnButtonEvent(const ButtonEvent* a_event) override;	// 08

		// override (BSTEventSink<MenuOpenCloseEvent>)
		BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent& a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<HUDModeEvent>)
		BSEventNotifyControl ProcessEvent(const HUDModeEvent& a_event, BSTEventSource<HUDModeEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<OpenContainerMenuEventData>)
		BSEventNotifyControl ProcessEvent(const OpenContainerMenuEventData& a_event, BSTEventSource<OpenContainerMenuEventData>* a_eventSource) override; // 01

		// override (BSTEventSink<TESContainerChangedEvent>)
		BSEventNotifyControl ProcessEvent(const TESContainerChangedEvent& a_event, BSTEventSource<TESContainerChangedEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<ClearQuickContainerEvent>)
		BSEventNotifyControl ProcessEvent(const ClearQuickContainerEvent& a_event, BSTEventSource<ClearQuickContainerEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<MenuModeChangeEvent>)
		BSEventNotifyControl ProcessEvent(const MenuModeChangeEvent& a_event, BSTEventSource<MenuModeChangeEvent>* a_eventSource) override; // 01

		void TakeSelectedItem()
		{
			using FuncType = decltype(&HUDQuickContainerDataModel::TakeSelectedItem);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::HUDQuickContainerDataModel::TakeSelectedItem };
			FUNC(this);
		}

		// members
		BSTValueEventSource<QuickContainerStateEvent> quickContainerState; // 040
		BSTValueEventSource<RolloverSuppressedEvent> rolloverSuppressed;   // 110
		BSTValueEventSource<BlockPipboyOpeningEvent> blockPipboyOpening;   // 128
		BSTValueEventSink<ViewCasterUpdateEvent> viewCasterEvent;		   // 140
		BSTValueEventSink<IsPipboyActiveEvent> isPipboyActive;			   // 198
		InventoryUserUIInterface invInterface;							   // 1B0
		HUDModes validHUDModes;											   // 230
		BSTArray<BSFixedString> overridingMenus;						   // 250
		BSTOptional<REX::Float32> lastRepeatTime;						   // 268
		std::int32_t topItemIndex;										   // 270
		std::int32_t selectedItemIndex;									   // 274
		std::int32_t totalItemCount;									   // 278
		std::int32_t excludingMenusOpenCounter;							   // 27C
		bool refreshContainerSize;										   // 280
		bool receivedActivatePress;										   // 281
		bool nextContainerActivated;									   // 282
	};
	static_assert(sizeof(HUDQuickContainerDataModel) == 0x288);
}
