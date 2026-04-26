#pragma once

#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BarterMenuTentativeInventoryUIInterface.hpp"
#include "RE/C/ContainerMenuBase.hpp"

#include "msvc/memory.hpp"

namespace RE
{
	class __declspec(novtable) BarterMenu
		: public ContainerMenuBase // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BarterMenu };
		inline static constexpr auto VTABLE{ VTABLE::BarterMenu };
		inline static constexpr auto MENU_NAME{ "BarterMenu"sv };
		inline static constexpr auto MENU_DEPTH{ UI_DEPTH_PRIORITY::kBarterMenu };

		class ItemBarterData
		{
		public:
			// members
			BSTHashMap<std::uint32_t, std::int32_t> stackQuantityMap; // 00
			std::uint32_t capsOwedByPlayer;							  // 30
		};
		static_assert(sizeof(ItemBarterData) == 0x38);

		// override (ContainerMenuBase)
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;																				 // 03
		bool OnButtonEventRelease(const BSFixedString& a_eventName) override;																			 // 0F
		void ConfirmInvestment() override;																												 // 14
		void DoItemTransfer(std::uint32_t a_itemIndex, std::uint32_t a_count, bool a_fromContainer) override;											 // 15
		bool GetDisplayBarterValues() override;																											 // 16
		std::uint32_t GetItemValue(std::uint32_t a_itemIndex, bool a_inContainer) override;																 // 1A
		const InventoryUserUIInterfaceEntry* GetInventoryItemByListIndex(bool a_inContainer, std::uint32_t a_index) override;							 // 1B
		void PopulateMenuObj(ObjectRefHandle a_inventoryRef, const InventoryUserUIInterfaceEntry& a_entry, ::Scaleform::GFx::Value& a_menuObj) override; // 1C
		void SetMenuSuppressed(bool a_suppressed) override;																								 // 1D
		void UpdateEncumbranceAndCaps(bool a_inContainer, std::int32_t a_capsDifferential) override;													 // 1E
		void UpdateList(bool a_inContainer) override;																									 // 20

		void ClearTradingData()
		{
			using FuncType = decltype(&BarterMenu::ClearTradingData);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BarterMenu::ClearTradingData };
			FUNC(this);
		}

		void CompleteTrade()
		{
			using FuncType = decltype(&BarterMenu::CompleteTrade);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BarterMenu::CompleteTrade };
			FUNC(this);
		}

		[[nodiscard]] std::int64_t GetCapsOwedByPlayer()
		{
			using FuncType = decltype(&BarterMenu::GetCapsOwedByPlayer);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BarterMenu::GetCapsOwedByPlayer };
			return std::invoke(FUNC, this);
		}

		// members
		BSTHashMap<InventoryInterface::Handle*, ItemBarterData*> barteredItems; // 430
		msvc::unique_ptr<BSGFxShaderFXTarget> capsTransferInfo_mc;				// 460
		msvc::unique_ptr<BSGFxShaderFXTarget> capsTransferBackground_mc;		// 468
		ObjectRefHandle vendorChestRef;											// 470
		ObjectRefHandle vendorActor;											// 474
		BarterMenuTentativeInventoryUIInterface playerTentativeInv;				// 478
		BarterMenuTentativeInventoryUIInterface containerTentativeInv;			// 4F8
		bool confirmingTrade;													// 578
	};
	static_assert(sizeof(BarterMenu) == 0x580);
}
