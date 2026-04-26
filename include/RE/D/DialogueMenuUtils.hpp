#pragma once

namespace RE::DialogueMenuUtils
{
	inline void OpenMenu()
	{
		using FuncType = decltype(&DialogueMenuUtils::OpenMenu);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::DialogueMenuUtils::OpenMenu };
		FUNC();
	}

	inline void CloseMenu()
	{
		using FuncType = decltype(&DialogueMenuUtils::CloseMenu);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::DialogueMenuUtils::CloseMenu };
		FUNC();
	}

	inline void ShowSpeechChallengeAnim()
	{
		using FuncType = decltype(&DialogueMenuUtils::ShowSpeechChallengeAnim);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::DialogueMenuUtils::ShowSpeechChallengeAnim };
		FUNC();
	}
}
