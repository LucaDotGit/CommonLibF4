#include "RE/B/BSInputDevice.hpp"

namespace RE
{
	bool BSInputDevice::ContainsButtonID(ButtonID a_buttonID) const
	{
		return deviceButtons.contains(a_buttonID);
	}

	bool BSInputDevice::ContainsButtonName(const BSFixedStringCS& a_name) const
	{
		return buttonNameIDMap.contains(a_name);
	}

	auto BSInputDevice::GetButtonInfoByName(const BSFixedStringCS& a_name) const -> std::optional<std::pair<ButtonID, InputButton*>>
	{
		const auto buttonIDIt = buttonNameIDMap.find(a_name);
		if (buttonIDIt == buttonNameIDMap.end()) {
			return std::nullopt;
		}

		const auto buttonIt = deviceButtons.find(buttonIDIt->second);
		if (buttonIt == deviceButtons.end()) {
			return std::nullopt;
		}

		return std::make_pair(buttonIDIt->second, buttonIt->second);
	}

	auto BSInputDevice::GetButtonInfoByID(ButtonID a_buttonID) const -> std::optional<std::pair<ButtonID, InputButton*>>
	{
		const auto buttonIt = deviceButtons.find(a_buttonID);
		if (buttonIt == deviceButtons.end()) {
			return std::nullopt;
		}

		return std::make_pair(buttonIt->first, buttonIt->second);
	}

	void BSInputDevice::CreateButtonEvent(ButtonID a_buttonID, REX::Float32 a_deltaTime, bool a_prevPressed, bool a_currPressed)
	{
		using FuncType = decltype(&BSInputDevice::CreateButtonEvent);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSInputDevice::CreateButtonEvent };
		FUNC(this, a_buttonID, a_deltaTime, a_prevPressed, a_currPressed);
	}
}
