#include "RE/P/PowerArmor.hpp"

#include "RE/S/Setting.hpp"
#include "RE/S/SettingUtil.hpp"

namespace RE::PowerArmor
{
	auto ActorInPowerArmor(const Actor& a_actor) -> bool
	{
		using FuncType = decltype(&PowerArmor::ActorInPowerArmor);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PowerArmor::ActorInPowerArmor);
		return std::invoke(FUNC, a_actor);
	}

	auto GetArmorKeyword() -> BGSKeyword*
	{
		using FuncType = decltype(&PowerArmor::GetArmorKeyword);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PowerArmor::GetArmorKeyword);
		return std::invoke(FUNC);
	}

	auto GetBatteryKeyword() -> BGSKeyword*
	{
		using FuncType = decltype(&PowerArmor::GetBatteryKeyword);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PowerArmor::GetBatteryKeyword);
		return std::invoke(FUNC);
	}

	auto GetDefaultBatteryObject() -> TESAmmo*
	{
		using FuncType = decltype(&PowerArmor::GetDefaultBatteryObject);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PowerArmor::GetDefaultBatteryObject);
		return std::invoke(FUNC);
	}

	auto IsPowerArmorBattery(const TESBoundObject* a_itemData) -> bool
	{
		using FuncType = decltype(&PowerArmor::IsPowerArmorBattery);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PowerArmor::IsPowerArmorBattery);
		return std::invoke(FUNC, a_itemData);
	}

	void SyncFurnitureVisualsToInventory(
		TESObjectREFR* a_furniture,
		bool a_force3DUpdate,
		BGSInventoryItem* a_tempItemToAdd,
		bool a_hideCore)
	{
		using FuncType = decltype(&PowerArmor::SyncFurnitureVisualsToInventory);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PowerArmor::SyncFurnitureVisualsToInventory);
		std::invoke(FUNC, a_furniture, a_force3DUpdate, a_tempItemToAdd, a_hideCore);
	}

	auto GetNewBatteryCapacitySetting() -> Setting&
	{
		static auto* NewBatteryCapacity = GetGameSetting("fNewBatteryCapacity"sv);
		REX::Assert(NewBatteryCapacity != nullptr);
		return *NewBatteryCapacity;
	}

	auto GetNewBatteryCapacity() -> REX::Float32
	{
		const auto& setting = GetNewBatteryCapacitySetting();
		if (!setting.IsFloat()) [[unlikely]] {
			REX::Assert(false);
			return static_cast<REX::Float32>(0.0);
		}

		return setting.GetFloat();
	}

	void SetNewBatteryCapacity(REX::Float32 a_value)
	{
		auto& setting = GetNewBatteryCapacitySetting();
		if (!setting.IsFloat()) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		setting.SetFloat(a_value);
	}
}
