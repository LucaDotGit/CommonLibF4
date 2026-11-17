#pragma once

#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BarterMenuTentativeInventoryUIInterface.hpp"
#include "RE/C/ContainerMenuBase.hpp"
#include "RE/U/UI_DEPTH_PRIORITY.hpp"
#include "msvc/memory.hpp"

namespace RE
{
	class __declspec(novtable) BarterMenu : public ContainerMenuBase // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BarterMenu;
		inline static constexpr const auto& VTABLE = VTABLE::BarterMenu;
		inline static constexpr auto MENU_NAME = "BarterMenu"sv;
		inline static constexpr auto MENU_DEPTH = UI_DEPTH_PRIORITY::BarterMenu;

		class ItemBarterData
		{
		public:
			// members
			BSTHashMap<std::uint32_t, std::int32_t> stackQuantityMap; // 0x00
			std::uint32_t capsOwedByPlayer;							  // 0x30
		};

		static_assert(sizeof(ItemBarterData) == 0x38);

		// override (ContainerMenuBase)
		auto ProcessMessage(UIMessage& a_message) -> UI_MESSAGE_RESULTS override;							  // 0x03
		auto OnButtonEventRelease(const BSFixedString& a_eventName) -> bool override;						  // 0x0F
		void ConfirmInvestment() override;																	  // 0x14
		void DoItemTransfer(std::uint32_t a_itemIndex, std::uint32_t a_count, bool a_fromContainer) override; // 0x15
		auto GetDisplayBarterValues() -> bool override;														  // 0x16
		auto GetItemValue(std::uint32_t a_itemIndex, bool a_inContainer) -> std::uint32_t override;			  // 0x1A
		auto GetInventoryItemByListIndex(bool a_inContainer, std::uint32_t a_index)
			-> const InventoryUserUIInterfaceEntry* override; // 0x1B
		void PopulateMenuObj(
			ObjectRefHandle a_inventoryRef,
			const InventoryUserUIInterfaceEntry& a_entry,
			Scaleform::GFx::Value& a_menuObj) override;												 // 0x1C
		void SetMenuSuppressed(bool a_suppressed) override;											 // 0x1D
		void UpdateEncumbranceAndCaps(bool a_inContainer, std::int32_t a_capsDifferential) override; // 0x1E
		void UpdateList(bool a_inContainer) override;												 // 0x20

		void ClearTradingData()
		{
			using FuncType = decltype(&BarterMenu::ClearTradingData);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BarterMenu::ClearTradingData);
			std::invoke(FUNC, this);
		}

		void CompleteTrade()
		{
			using FuncType = decltype(&BarterMenu::CompleteTrade);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BarterMenu::CompleteTrade);
			std::invoke(FUNC, this);
		}

		[[nodiscard]]
		auto GetCapsOwedByPlayer() -> std::int64_t
		{
			using FuncType = decltype(&BarterMenu::GetCapsOwedByPlayer);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BarterMenu::GetCapsOwedByPlayer);
			return std::invoke(FUNC, this);
		}

		// members
		BSTHashMap<InventoryInterface::Handle*, ItemBarterData*> barteredItems; // 0x430
		msvc::unique_ptr<BSGFxShaderFXTarget> capsTransferInfoMc;				// 0x460
		msvc::unique_ptr<BSGFxShaderFXTarget> capsTransferBackgroundMc;			// 0x468
		ObjectRefHandle vendorChestRef;											// 0x470
		ObjectRefHandle vendorActor;											// 0x474
		BarterMenuTentativeInventoryUIInterface playerTentativeInv;				// 0x478
		BarterMenuTentativeInventoryUIInterface containerTentativeInv;			// 0x4F8
		bool confirmingTrade;													// 0x578
	};

	static_assert(sizeof(BarterMenu) == 0x580);
}
