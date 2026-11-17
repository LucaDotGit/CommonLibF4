#pragma once

#include "RE/B/BSGFxShaderFXTarget.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/D/DisableHeavyItemsFunc.hpp"
#include "RE/G/GameMenuBase.hpp"
#include "RE/I/Inventory3DManager.hpp"
#include "RE/I/InventoryUserUIInterface.hpp"
#include "RE/R/Rumble.hpp"
#include "msvc/memory.hpp"

namespace RE
{
	enum class QuickContainerMode : std::int32_t;

	class MenuOpenCloseEvent;

	class __declspec(novtable) ContainerMenuBase :
		public GameMenuBase,							   // 0x000
		public BSTEventSink<InvInterfaceStateChangeEvent>, // 0x0E0
		public BSTEventSink<MenuOpenCloseEvent>			   // 0x0E8
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ContainerMenuBase;
		inline static constexpr const auto& VTABLE = VTABLE::ContainerMenuBase;

		class __declspec(novtable) FXQuantityMenu : public BSGFxShaderFXTarget // 0x00
		{
		public:
			~FXQuantityMenu() override; // 0x00

			// members
			BSGFxShaderFXTarget label;				   // 0x0B0
			BSGFxShaderFXTarget value;				   // 0x160
			BSGFxShaderFXTarget quantityBracketHolder; // 0x210
		};

		static_assert(sizeof(FXQuantityMenu) == 0x2C0);

		class ItemSorter
		{
		public:
			enum class SORT_ON_FIELD : std::int32_t
			{
				Alphabetical = 0,
				Damage = 1,
				RateOfFire = 2,
				Range = 3,
				Accuracy = 4,
				Value = 5,
				Weight = 6
			};

			void IncrementSort()
			{
				using FuncType = decltype(&ItemSorter::IncrementSort);
				static const auto FUNC = REL::Relocation<FuncType>(ID::ContainerMenuBase::ItemSorter::IncrementSort);
				std::invoke(FUNC, this);
			}

			void SetTab(std::uint32_t a_tab)
			{
				currentTab = a_tab;
			}

			// members
			std::array<REX::Enum<SORT_ON_FIELD, std::int32_t>, 14> currentSort; // 0x00
			std::uint32_t currentTab;											// 0x38
		};

		static_assert(sizeof(ItemSorter) == 0x3C);

		~ContainerMenuBase() override; // 0x00

		// override (GameMenuBase)
		void Call(const Params& a_params) override;							   // 0x01
		void MapCodeObjectFunctions() override;								   // 0x02
		void AdvanceMovie(DeltaTime a_deltaTime, std::time_t a_time) override; // 0x04
		void PreDisplay() override;											   // 0x05

		// add
		virtual void ConfirmInvestment(); // 0x14 - { return; }
		virtual void DoItemTransfer(std::uint32_t a_itemIndex, std::uint32_t a_count, bool a_fromContainer) = 0; // 0x15
		virtual auto GetDisplayBarterValues() -> bool;										 // 0x16 - { return false; }
		virtual auto GetCanEquipItem(std::uint32_t a_itemIndex, bool a_inContainer) -> bool; // 0x17 - { return false; }
		virtual auto GetIsItemEquipped(std::uint32_t a_itemIndex, bool a_inContainer)
			-> bool;																	// 0x18 - { return false; }
		virtual void ToggleItemEquipped(std::uint32_t a_itemIndex, bool a_inContainer); // 0x19 - { return; }
		virtual auto GetItemValue(std::uint32_t a_itemIndex, bool a_inContainer) -> std::uint32_t; // 0x1A
		virtual auto GetInventoryItemByListIndex(
			bool a_inContainer,
			std::uint32_t a_index) -> const InventoryUserUIInterfaceEntry*; // 0x1B
		virtual void PopulateMenuObj(
			ObjectRefHandle a_inventoryRef,
			const InventoryUserUIInterfaceEntry& a_entry,
			Scaleform::GFx::Value& a_menuObj) = 0;													// 0x1C
		virtual void SetMenuSuppressed(bool a_suppressed);											// 0x1D
		virtual void UpdateEncumbranceAndCaps(bool a_inContainer, std::int32_t a_capsDifferential); // 0x1E
		virtual void UpdateItemPickpocketInfo(
			std::int32_t a_index,
			bool a_inContainer,
			std::int32_t a_count);						 // 0x1F - { return; }
		virtual void UpdateList(bool a_inContainer) = 0; // 0x20

		void SetMessageBoxMode(bool a_messageBoxMode)
		{
			constexpr auto MEMBER_VAR_PATH = "messageBoxIsActive"sv;

			if (menuObj.IsAnyObject() && menuObj.HasMember(MEMBER_VAR_PATH.data())) {
				menuObj.SetMember(MEMBER_VAR_PATH.data(), Scaleform::GFx::Value(a_messageBoxMode));
			}
		}

		// members
		ItemSorter containerItemSorter;										// 0x0F0
		ItemSorter playerItemSorter;										// 0x12C
		msvc::unique_ptr<BSGFxShaderFXTarget> playerBracketBackgroundMc;	// 0x168
		msvc::unique_ptr<BSGFxShaderFXTarget> containerBracketBackgroundMc; // 0x170
		msvc::unique_ptr<BSGFxShaderFXTarget> containerListMc;				// 0x178
		msvc::unique_ptr<BSGFxShaderFXTarget> playerInventoryMc;			// 0x180
		msvc::unique_ptr<BSGFxShaderFXTarget> containerInventoryMc;			// 0x188
		msvc::unique_ptr<BSGFxShaderFXTarget> itemCardMc;					// 0x190
		msvc::unique_ptr<FXQuantityMenu> quantityMenuMc;					// 0x198
		InventoryUserUIInterface playerInv;									// 0x1A0
		InventoryUserUIInterface containerInv;								// 0x220
		Inventory3DManager inv3DModelManager;								// 0x2A0
		BSTArray<const TESBoundObject*> partialPlayerUpdateList;			// 0x3E0
		BSTArray<const TESBoundObject*> partialContainerUpdateList;			// 0x3F8
		REX::Enum<QuickContainerMode, std::int32_t> menuMode;				// 0x410
		Rumble::AutoRumblePause autoRumblePause;							// 0x414
		DisableHeavyItemsFunc disableHeavyFunc;								// 0x418
		ObjectRefHandle containerRef;										// 0x428
		bool suppressed;													// 0x42C
		bool menuOpening;													// 0x42D
	};

	static_assert(sizeof(ContainerMenuBase) == 0x430);
}
