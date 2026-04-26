#pragma once

namespace RE
{
	class BGSInventoryItem;
	class Setting;
}

namespace RE::PowerArmor
{
	[[nodiscard]] bool ActorInPowerArmor(const Actor& a_actor);
	[[nodiscard]] bool PlayerInPowerArmor();
	[[nodiscard]] BGSKeyword* GetArmorKeyword();
	[[nodiscard]] BGSKeyword* GetBatteryKeyword();
	[[nodiscard]] TESAmmo* GetDefaultBatteryObject();
	[[nodiscard]] bool IsPowerArmorBattery(const TESBoundObject* a_itemData);
	void SyncFurnitureVisualsToInventory(TESObjectREFR* a_furniture, bool a_force3DUpdate, BGSInventoryItem* a_tempItemToAdd, bool a_hideCore);
	[[nodiscard]] Setting& GetNewBatteryCapacity();
}
