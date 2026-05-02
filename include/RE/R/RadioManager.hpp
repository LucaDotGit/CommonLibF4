#pragma once

namespace RE::RadioManager
{
	inline REX::Float32 QCurrentPlayerFreq()
	{
		using FuncType = decltype(&RadioManager::QCurrentPlayerFreq);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::RadioManager::QCurrentPlayerFreq };
		return std::invoke(FUNC);
	}

	inline void EnablePlayerRadio(bool a_enable, bool a_playOnOffSound)
	{
		using FuncType = decltype(&RadioManager::EnablePlayerRadio);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::RadioManager::EnablePlayerRadio };
		FUNC(a_enable, a_playOnOffSound);
	}

	inline bool QPlayerRadioEnabled()
	{
		using FuncType = decltype(&RadioManager::QPlayerRadioEnabled);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::RadioManager::QPlayerRadioEnabled };
		return std::invoke(FUNC);
	}
}
