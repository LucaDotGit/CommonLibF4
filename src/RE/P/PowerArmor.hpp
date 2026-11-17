#pragma once

namespace RE
{
	class BGSInventoryItem;
	class Setting;
}

namespace RE::PowerArmor
{
	[[nodiscard]]
	auto ActorInPowerArmor(const Actor& a_actor) -> bool;
	[[nodiscard]]
	auto GetArmorKeyword() -> BGSKeyword*;
	[[nodiscard]]
	auto GetBatteryKeyword() -> BGSKeyword*;
	[[nodiscard]]
	auto GetDefaultBatteryObject() -> TESAmmo*;
	[[nodiscard]]
	auto IsPowerArmorBattery(const TESBoundObject* a_itemData) -> bool;
	void SyncFurnitureVisualsToInventory(
		TESObjectREFR* a_furniture,
		bool a_force3DUpdate,
		BGSInventoryItem* a_tempItemToAdd,
		bool a_hideCore);

	[[nodiscard]]
	auto GetNewBatteryCapacitySetting() -> Setting&;
	[[nodiscard]]
	auto GetNewBatteryCapacity() -> REX::Float32;
	void SetNewBatteryCapacity(REX::Float32 a_value);
}
