#pragma once

namespace RE::RadioManager
{
	inline auto QCurrentPlayerFreq() -> REX::Float32
	{
		using FuncType = decltype(&RadioManager::QCurrentPlayerFreq);
		static const auto FUNC = REL::Relocation<FuncType>(ID::RadioManager::QCurrentPlayerFreq);
		return std::invoke(FUNC);
	}

	inline void EnablePlayerRadio(bool a_enable, bool a_playOnOffSound)
	{
		using FuncType = decltype(&RadioManager::EnablePlayerRadio);
		static const auto FUNC = REL::Relocation<FuncType>(ID::RadioManager::EnablePlayerRadio);
		std::invoke(FUNC, a_enable, a_playOnOffSound);
	}

	inline auto QPlayerRadioEnabled() -> bool
	{
		using FuncType = decltype(&RadioManager::QPlayerRadioEnabled);
		static const auto FUNC = REL::Relocation<FuncType>(ID::RadioManager::QPlayerRadioEnabled);
		return std::invoke(FUNC);
	}
}
