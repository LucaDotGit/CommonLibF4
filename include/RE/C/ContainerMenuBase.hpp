#pragma once

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

	class __declspec(novtable) ContainerMenuBase
		: public GameMenuBase,								 // 000
		  public BSTEventSink<InvInterfaceStateChangeEvent>, // 0E0
		  public BSTEventSink<MenuOpenCloseEvent>			 // 0E8
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ContainerMenuBase };
		inline static constexpr auto VTABLE{ VTABLE::ContainerMenuBase };

		class __declspec(novtable) FXQuantityMenu
			: public BSGFxShaderFXTarget // 00
		{
		public:
			// members
			BSGFxShaderFXTarget label;				   // 0B0
			BSGFxShaderFXTarget value;				   // 160
			BSGFxShaderFXTarget quantityBracketHolder; // 210
		};
		static_assert(sizeof(FXQuantityMenu) == 0x2C0);

		class ItemSorter
		{
		public:
			enum class SORT_ON_FIELD : std::int32_t
			{
				kAlphabetical = 0,
				kDamage = 1,
				kRateOfFire = 2,
				kRange = 3,
				kAccuracy = 4,
				kValue = 5,
				kWeight = 6
			};

			void IncrementSort()
			{
				using FuncType = decltype(&ItemSorter::IncrementSort);
				static const auto FUNC = REL::Relocation<FuncType>{ ID::ContainerMenuBase::ItemSorter::IncrementSort };
				std::invoke(FUNC, this);
			}

			void SetTab(std::uint32_t a_tab)
			{
				currentTab = a_tab;
			}

			// members
			std::array<REX::Enum<SORT_ON_FIELD, std::int32_t>, 14> currentSort; // 00
			std::uint32_t currentTab;											// 38
		};
		static_assert(sizeof(ItemSorter) == 0x3C);

		~ContainerMenuBase() override; // 00

		// override (GameMenuBase)
		void Call(const Params& a_params) override;									// 01
		void MapCodeObjectFunctions() override;										// 02
		void AdvanceMovie(REX::Float32 a_timeDelta, std::uint64_t a_time) override; // 04
		void PreDisplay() override;													// 05

		// add
		virtual void ConfirmInvestment();																													// 14 - { return; }
		virtual void DoItemTransfer(std::uint32_t a_itemIndex, std::uint32_t a_count, bool a_fromContainer) = 0;											// 15
		virtual bool GetDisplayBarterValues();																												// 16 - { return false; }
		virtual bool GetCanEquipItem(std::uint32_t a_itemIndex, bool a_inContainer);																		// 17 - { return false; }
		virtual bool GetIsItemEquipped(std::uint32_t a_itemIndex, bool a_inContainer);																		// 18 - { return false; }
		virtual void ToggleItemEquipped(std::uint32_t a_itemIndex, bool a_inContainer);																		// 19 - { return; }
		virtual std::uint32_t GetItemValue(std::uint32_t a_itemIndex, bool a_inContainer);																	// 1A
		virtual const InventoryUserUIInterfaceEntry* GetInventoryItemByListIndex(bool a_inContainer, std::uint32_t a_index);								// 1B
		virtual void PopulateMenuObj(ObjectRefHandle a_inventoryRef, const InventoryUserUIInterfaceEntry& a_entry, ::Scaleform::GFx::Value& a_menuObj) = 0; // 1C
		virtual void SetMenuSuppressed(bool a_suppressed);																									// 1D
		virtual void UpdateEncumbranceAndCaps(bool a_inContainer, std::int32_t a_capsDifferential);															// 1E
		virtual void UpdateItemPickpocketInfo(std::int32_t a_index, bool a_inContainer, std::int32_t a_count);												// 1F - { return; }
		virtual void UpdateList(bool a_inContainer) = 0;																									// 20

		void SetMessageBoxMode(bool a_messageBoxMode)
		{
			constexpr auto MEMBER_VAR_PATH = "messageBoxIsActive"sv;

			if (menuObj.IsAnyObject() && menuObj.HasMember(MEMBER_VAR_PATH.data())) {
				menuObj.SetMember(MEMBER_VAR_PATH.data(), ::Scaleform::GFx::Value(a_messageBoxMode));
			}
		}

		// members
		ItemSorter containerItemSorter;										 // 0F0
		ItemSorter playerItemSorter;										 // 12C
		msvc::unique_ptr<BSGFxShaderFXTarget> playerBracketBackground_mc;	 // 168
		msvc::unique_ptr<BSGFxShaderFXTarget> containerBracketBackground_mc; // 170
		msvc::unique_ptr<BSGFxShaderFXTarget> containerList_mc;				 // 178
		msvc::unique_ptr<BSGFxShaderFXTarget> playerInventory_mc;			 // 180
		msvc::unique_ptr<BSGFxShaderFXTarget> containerInventory_mc;		 // 188
		msvc::unique_ptr<BSGFxShaderFXTarget> itemCard_mc;					 // 190
		msvc::unique_ptr<FXQuantityMenu> quantityMenu_mc;					 // 198
		InventoryUserUIInterface playerInv;									 // 1A0
		InventoryUserUIInterface containerInv;								 // 220
		Inventory3DManager inv3DModelManager;								 // 2A0
		BSTArray<const TESBoundObject*> partialPlayerUpdateList;			 // 3E0
		BSTArray<const TESBoundObject*> partialContainerUpdateList;			 // 3F8
		REX::Enum<QuickContainerMode, std::int32_t> menuMode;				 // 410
		Rumble::AutoRumblePause autoRumblePause;							 // 414
		DisableHeavyItemsFunc disableHeavyFunc;								 // 418
		ObjectRefHandle containerRef;										 // 428
		bool suppressed;													 // 42C
		bool menuOpening;													 // 42D
	};
	static_assert(sizeof(ContainerMenuBase) == 0x430);
}
