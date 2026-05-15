#pragma once

namespace RE
{
	class HUDModeType;
}

namespace RE::SendHUDMessage
{
	inline void PopHUDMode(const HUDModeType& a_hudMode)
	{
		using FuncType = decltype(&SendHUDMessage::PopHUDMode);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::SendHUDMessage::PopHUDMode };
		std::invoke(FUNC, a_hudMode);
	}

	inline void PushHUDMode(const HUDModeType& a_hudMode)
	{
		using FuncType = decltype(&SendHUDMessage::PushHUDMode);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::SendHUDMessage::PushHUDMode };
		std::invoke(FUNC, a_hudMode);
	}

	inline void SetPowerArmorMode(bool a_inPowerArmor)
	{
		using FuncType = decltype(&SendHUDMessage::SetPowerArmorMode);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::SendHUDMessage::SetPowerArmorMode };
		std::invoke(FUNC, a_inPowerArmor);
	}

	inline void ShowHUDMessage(const char* a_message, const char* a_sound = nullptr, bool a_throttle = false, bool a_warning = false)
	{
		using FuncType = decltype(&SendHUDMessage::ShowHUDMessage);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::SendHUDMessage::ShowHUDMessage };
		std::invoke(FUNC, a_message, a_sound, a_throttle, a_warning);
	}
}
