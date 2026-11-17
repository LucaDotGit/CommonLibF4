#pragma once

#include "RE/C/ContainerMenuBase.hpp"
#include "RE/U/UI_DEPTH_PRIORITY.hpp"
#include "msvc/memory.hpp"

namespace RE
{
	class __declspec(novtable) ContainerMenu : public ContainerMenuBase // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ContainerMenu;
		inline static constexpr const auto& VTABLE = VTABLE::ContainerMenu;
		inline static constexpr auto MENU_NAME = "ContainerMenu"sv;
		inline static constexpr auto MENU_DEPTH = UI_DEPTH_PRIORITY::ContainerMenu;

		// override (ContainerMenuBase)
		auto ProcessMessage(UIMessage& a_message) -> UI_MESSAGE_RESULTS override;							  // 0x03
		void DoItemTransfer(std::uint32_t a_itemIndex, std::uint32_t a_count, bool a_fromContainer) override; // 0x15
		auto GetCanEquipItem(std::uint32_t a_itemIndex, bool a_inContainer) -> bool override;				  // 0x17
		auto GetIsItemEquipped(std::uint32_t a_itemIndex, bool a_inContainer) -> bool override;				  // 0x18
		void ToggleItemEquipped(std::uint32_t a_itemIndex, bool a_inContainer) override;					  // 0x19
		void PopulateMenuObj(
			ObjectRefHandle a_inventoryRef,
			const InventoryUserUIInterfaceEntry& a_entry,
			Scaleform::GFx::Value& a_menuObj) override;															// 0x22
		void UpdateItemPickpocketInfo(std::int32_t a_index, bool a_inContainer, std::int32_t a_count) override; // 0x25
		void UpdateList(bool a_inContainer) override;															// 0x26

		void TakeAllItems()
		{
			using FuncType = decltype(&ContainerMenu::TakeAllItems);
			static const auto FUNC = REL::Relocation<FuncType>(ID::ContainerMenu::TakeAllItems);
			std::invoke(FUNC, this);
		}

		// members
		msvc::unique_ptr<BSGFxShaderFXTarget> pickpocketInfoMc; // 0x430
		std::uint32_t valueStolenFromContainer;					// 0x438
		bool containerAccessed;									// 0x43C
		bool addedTempItems;									// 0x43D
		bool plantedExplosiveWeapon;							// 0x43E
		bool containerIsAnimatingOpen;							// 0x43F
	};

	static_assert(sizeof(ContainerMenu) == 0x440);
}
