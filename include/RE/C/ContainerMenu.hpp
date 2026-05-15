#pragma once

#include "RE/C/ContainerMenuBase.hpp"
#include "RE/U/UI_DEPTH_PRIORITY.hpp"

#include "msvc/memory.hpp"

namespace RE
{
	class __declspec(novtable) ContainerMenu
		: public ContainerMenuBase // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ContainerMenu };
		inline static constexpr auto VTABLE{ VTABLE::ContainerMenu };
		inline static constexpr auto MENU_NAME{ "ContainerMenu"sv };
		inline static constexpr auto MENU_DEPTH{ UI_DEPTH_PRIORITY::kContainerMenu };

		// override (ContainerMenuBase)
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;																				 // 03
		void DoItemTransfer(std::uint32_t a_itemIndex, std::uint32_t a_count, bool a_fromContainer) override;											 // 15
		bool GetCanEquipItem(std::uint32_t a_itemIndex, bool a_inContainer) override;																	 // 17
		bool GetIsItemEquipped(std::uint32_t a_itemIndex, bool a_inContainer) override;																	 // 18
		void ToggleItemEquipped(std::uint32_t a_itemIndex, bool a_inContainer) override;																 // 19
		void PopulateMenuObj(ObjectRefHandle a_inventoryRef, const InventoryUserUIInterfaceEntry& a_entry, ::Scaleform::GFx::Value& a_menuObj) override; // 22
		void UpdateItemPickpocketInfo(std::int32_t a_index, bool a_inContainer, std::int32_t a_count) override;											 // 25
		void UpdateList(bool a_inContainer) override;																									 // 26

		void TakeAllItems()
		{
			using FuncType = decltype(&ContainerMenu::TakeAllItems);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::ContainerMenu::TakeAllItems };
			std::invoke(FUNC, this);
		}

		// members
		msvc::unique_ptr<BSGFxShaderFXTarget> pickpocketInfo_mc; // 430
		std::uint32_t valueStolenFromContainer;					 // 438
		bool containerAccessed;									 // 43C
		bool addedTempItems;									 // 43D
		bool plantedExplosiveWeapon;							 // 43E
		bool containerIsAnimatingOpen;							 // 43F
	};
	static_assert(sizeof(ContainerMenu) == 0x440);
}
