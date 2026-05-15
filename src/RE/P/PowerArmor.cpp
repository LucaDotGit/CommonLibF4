#include "RE/P/PowerArmor.hpp"

#include "RE/P/PlayerCharacter.hpp"
#include "RE/S/Setting.hpp"
#include "RE/S/SettingUtil.hpp"

namespace RE::PowerArmor
{
	bool ActorInPowerArmor(const Actor& a_actor)
	{
		using FuncType = decltype(&PowerArmor::ActorInPowerArmor);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::PowerArmor::ActorInPowerArmor };
		return std::invoke(FUNC, a_actor);
	}

	bool PlayerInPowerArmor()
	{
		const auto* player = PlayerCharacter::GetSingleton();
		if (!player) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		return ActorInPowerArmor(*player);
	}

	BGSKeyword* GetArmorKeyword()
	{
		using FuncType = decltype(&PowerArmor::GetArmorKeyword);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::PowerArmor::GetArmorKeyword };
		return std::invoke(FUNC);
	}

	BGSKeyword* GetBatteryKeyword()
	{
		using FuncType = decltype(&PowerArmor::GetBatteryKeyword);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::PowerArmor::GetBatteryKeyword };
		return std::invoke(FUNC);
	}

	TESAmmo* GetDefaultBatteryObject()
	{
		using FuncType = decltype(&PowerArmor::GetDefaultBatteryObject);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::PowerArmor::GetDefaultBatteryObject };
		return std::invoke(FUNC);
	}

	bool IsPowerArmorBattery(const TESBoundObject* a_itemData)
	{
		using FuncType = decltype(&PowerArmor::IsPowerArmorBattery);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::PowerArmor::IsPowerArmorBattery };
		return std::invoke(FUNC, a_itemData);
	}

	void SyncFurnitureVisualsToInventory(TESObjectREFR* a_furniture, bool a_force3DUpdate, BGSInventoryItem* a_tempItemToAdd, bool a_hideCore)
	{
		using FuncType = decltype(&PowerArmor::SyncFurnitureVisualsToInventory);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::PowerArmor::SyncFurnitureVisualsToInventory };
		std::invoke(FUNC, a_furniture, a_force3DUpdate, a_tempItemToAdd, a_hideCore);
	}

	Setting& GetNewBatteryCapacity()
	{
		static auto* NewBatteryCapacity = GetGameSetting("fNewBatteryCapacity"sv);
		return *NewBatteryCapacity;
	}
}
