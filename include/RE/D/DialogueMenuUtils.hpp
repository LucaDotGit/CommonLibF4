#pragma once

namespace RE::DialogueMenuUtils
{
	inline void OpenMenu()
	{
		using FuncType = decltype(&DialogueMenuUtils::OpenMenu);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::DialogueMenuUtils::OpenMenu };
		std::invoke(FUNC);
	}

	inline void CloseMenu()
	{
		using FuncType = decltype(&DialogueMenuUtils::CloseMenu);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::DialogueMenuUtils::CloseMenu };
		std::invoke(FUNC);
	}

	inline void ShowSpeechChallengeAnim()
	{
		using FuncType = decltype(&DialogueMenuUtils::ShowSpeechChallengeAnim);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::DialogueMenuUtils::ShowSpeechChallengeAnim };
		std::invoke(FUNC);
	}
}
