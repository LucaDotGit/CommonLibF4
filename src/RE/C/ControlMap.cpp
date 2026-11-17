#include "RE/C/ControlMap.hpp"

namespace RE
{
	static_assert(INPUT_DEVICE::None < static_cast<INPUT_DEVICE>(0));
	static_assert(UserEvents::INPUT_CONTEXT_ID::None > UserEvents::INPUT_CONTEXT_ID::_Count);

	auto ControlMap::GetSingleton() noexcept -> ControlMap*
	{
		static const auto SINGLETON = REL::Relocation<ControlMap**>(ID::ControlMap::Singleton);
		return *SINGLETON;
	}

	auto ControlMap::ContainsControlName(
		const BSFixedString& a_controlName,
		INPUT_DEVICE a_deviceType,
		INPUT_CONTEXT a_inputContext) const -> bool
	{
		if ((a_deviceType <= INPUT_DEVICE::None || a_deviceType >= INPUT_DEVICE::Supported) ||
			(a_inputContext < static_cast<INPUT_CONTEXT>(0) || a_inputContext >= INPUT_CONTEXT::_Count)) {
			return false;
		}

		const auto* controlMap = controlMaps[REX::ToUnsigned(std::to_underlying(a_inputContext))];
		if (!controlMap) {
			return false;
		}

		const auto& deviceMappings = controlMap->deviceMappings[REX::ToUnsigned(std::to_underlying(a_deviceType))];
		return std::ranges::any_of(
			deviceMappings,
			[&a_controlName](const UserEventMapping& a_eventMapping) noexcept -> bool {
				return a_eventMapping.eventID == a_controlName;
			});
	}

	auto ControlMap::GetControlNameByKeyCode(
		std::uint32_t a_keyCode,
		INPUT_DEVICE a_deviceType,
		INPUT_CONTEXT a_inputContext) const -> std::optional<BSFixedString>
	{
		if ((a_deviceType <= INPUT_DEVICE::None || a_deviceType >= INPUT_DEVICE::Supported) ||
			(a_inputContext < static_cast<INPUT_CONTEXT>(0) || a_inputContext >= INPUT_CONTEXT::_Count)) {
			return std::nullopt;
		}

		const auto* controlMap = controlMaps[REX::ToUnsigned(std::to_underlying(a_inputContext))];
		if (!controlMap) {
			return std::nullopt;
		}

		const auto& deviceMappings = controlMap->deviceMappings[REX::ToUnsigned(std::to_underlying(a_deviceType))];
		for (const auto& mapping : deviceMappings) {
			if (std::cmp_equal(mapping.inputKey, a_keyCode)) {
				return mapping.eventID;
			}
		}

		return std::nullopt;
	}

	auto ControlMap::GetKeyCodeByControlName(
		const BSFixedString& a_controlName,
		INPUT_DEVICE a_deviceType,
		INPUT_CONTEXT a_inputContext) const -> std::optional<std::uint32_t>
	{
		if ((a_deviceType <= INPUT_DEVICE::None || a_deviceType >= INPUT_DEVICE::Supported) ||
			(a_inputContext < static_cast<INPUT_CONTEXT>(0) || a_inputContext >= INPUT_CONTEXT::_Count)) {
			return std::nullopt;
		}

		const auto* controlMap = controlMaps[REX::ToUnsigned(std::to_underlying(a_inputContext))];
		if (!controlMap) {
			return std::nullopt;
		}

		const auto& deviceMappings = controlMap->deviceMappings[REX::ToUnsigned(std::to_underlying(a_deviceType))];
		for (const auto& mapping : deviceMappings) {
			if (mapping.eventID == a_controlName) {
				return mapping.inputKey;
			}
		}

		return std::nullopt;
	}

	auto ControlMap::PopInputContext(INPUT_CONTEXT a_inputContext) -> bool
	{
		using FuncType = decltype(&ControlMap::PopInputContext);
		static const auto FUNC = REL::Relocation<FuncType>(ID::ControlMap::PopInputContext);
		return std::invoke(FUNC, this, a_inputContext);
	}

	void ControlMap::PushInputContext(INPUT_CONTEXT a_inputContext)
	{
		using FuncType = decltype(&ControlMap::PushInputContext);
		static const auto FUNC = REL::Relocation<FuncType>(ID::ControlMap::PushInputContext);
		std::invoke(FUNC, this, a_inputContext);
	}

	auto ControlMap::RemapButton(const BSFixedString& a_id, INPUT_DEVICE a_deviceType, std::int32_t a_buttonID) -> bool
	{
		using FuncType = decltype(&ControlMap::RemapButton);
		static const auto FUNC = REL::Relocation<FuncType>(ID::ControlMap::RemapButton);
		return std::invoke(FUNC, this, a_id, a_deviceType, a_buttonID);
	}

	void ControlMap::SaveRemappings()
	{
		using FuncType = decltype(&ControlMap::SaveRemappings);
		static const auto FUNC = REL::Relocation<FuncType>(ID::ControlMap::SaveRemappings);
		std::invoke(FUNC, this);
	}

	void ControlMap::SetTextEntryMode(bool a_enable)
	{
		using FuncType = decltype(&ControlMap::SetTextEntryMode);
		static const auto FUNC = REL::Relocation<FuncType>(ID::ControlMap::SetTextEntryMode);
		std::invoke(FUNC, this, a_enable);
	}
}
