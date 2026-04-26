#include "RE/C/ControlMap.hpp"

namespace RE
{
	static_assert(INPUT_DEVICE::kNone < static_cast<INPUT_DEVICE>(0));
	static_assert(UserEvents::INPUT_CONTEXT_ID::kNone > UserEvents::INPUT_CONTEXT_ID::kTotal);

	ControlMap* ControlMap::GetSingleton()
	{
		static const auto SINGLETON = REL::Relocation<ControlMap**>{ ID::ControlMap::Singleton };
		return *SINGLETON;
	}

	bool ControlMap::ContainsControlName(const BSFixedString& a_controlName, INPUT_DEVICE a_deviceType, INPUT_CONTEXT a_inputContext) const
	{
		if ((a_deviceType <= INPUT_DEVICE::kNone || a_deviceType >= INPUT_DEVICE::kSupported) ||
			(a_inputContext < static_cast<INPUT_CONTEXT>(0) || a_inputContext >= INPUT_CONTEXT::kTotal)) {
			return false;
		}

		const auto* controlMap = controlMaps[std::to_underlying(a_inputContext)];
		if (!controlMap) {
			return false;
		}

		const auto& deviceMappings = controlMap->deviceMappings[std::to_underlying(a_deviceType)];
		return std::ranges::any_of(deviceMappings, [&a_controlName](const UserEventMapping& a_eventMapping) {
			return a_eventMapping.eventID == a_controlName;
		});
	}

	auto ControlMap::GetControlNameByKeyCode(std::uint32_t a_keyCode, INPUT_DEVICE a_deviceType, INPUT_CONTEXT a_inputContext) const
		-> std::optional<BSFixedString>
	{
		if ((a_deviceType <= INPUT_DEVICE::kNone || a_deviceType >= INPUT_DEVICE::kSupported) ||
			(a_inputContext < static_cast<INPUT_CONTEXT>(0) || a_inputContext >= INPUT_CONTEXT::kTotal)) {
			return std::nullopt;
		}

		const auto* controlMap = controlMaps[std::to_underlying(a_inputContext)];
		if (!controlMap) {
			return std::nullopt;
		}

		const auto& deviceMappings = controlMap->deviceMappings[std::to_underlying(a_deviceType)];
		for (const auto& mapping : deviceMappings) {
			if (std::cmp_equal(mapping.inputKey, a_keyCode)) {
				return mapping.eventID;
			}
		}

		return std::nullopt;
	}

	auto ControlMap::GetKeyCodeByControlName(const BSFixedString& a_controlName, INPUT_DEVICE a_deviceType, INPUT_CONTEXT a_inputContext) const
		-> std::optional<std::uint32_t>
	{
		if ((a_deviceType <= INPUT_DEVICE::kNone || a_deviceType >= INPUT_DEVICE::kSupported) ||
			(a_inputContext < static_cast<INPUT_CONTEXT>(0) || a_inputContext >= INPUT_CONTEXT::kTotal)) {
			return std::nullopt;
		}

		const auto* controlMap = controlMaps[std::to_underlying(a_inputContext)];
		if (!controlMap) {
			return std::nullopt;
		}

		const auto& deviceMappings = controlMap->deviceMappings[std::to_underlying(a_deviceType)];
		for (const auto& mapping : deviceMappings) {
			if (mapping.eventID == a_controlName) {
				return mapping.inputKey;
			}
		}

		return std::nullopt;
	}

	bool ControlMap::PopInputContext(INPUT_CONTEXT a_inputContext)
	{
		using FuncType = decltype(&ControlMap::PopInputContext);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::ControlMap::PopInputContext };
		return std::invoke(FUNC, this, a_inputContext);
	}

	void ControlMap::PushInputContext(INPUT_CONTEXT a_inputContext)
	{
		using FuncType = decltype(&ControlMap::PushInputContext);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::ControlMap::PushInputContext };
		FUNC(this, a_inputContext);
	}

	bool ControlMap::RemapButton(const BSFixedString& a_id, INPUT_DEVICE a_deviceType, std::int32_t a_buttonID)
	{
		using FuncType = decltype(&ControlMap::RemapButton);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::ControlMap::RemapButton };
		return std::invoke(FUNC, this, a_id, a_deviceType, a_buttonID);
	}

	void ControlMap::SaveRemappings()
	{
		using FuncType = decltype(&ControlMap::SaveRemappings);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::ControlMap::SaveRemappings };
		FUNC(this);
	}

	void ControlMap::SetTextEntryMode(bool a_enable)
	{
		using FuncType = decltype(&ControlMap::SetTextEntryMode);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::ControlMap::SetTextEntryMode };
		FUNC(this, a_enable);
	}
}
