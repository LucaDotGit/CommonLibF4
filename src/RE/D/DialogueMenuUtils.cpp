#include "RE/D/DialogueMenuUtils.hpp"

namespace RE::DialogueMenuUtils
{
	void OpenMenu()
	{
		using FuncType = decltype(&DialogueMenuUtils::OpenMenu);
		static const auto FUNC = REL::Relocation<FuncType>(ID::DialogueMenuUtils::OpenMenu);
		std::invoke(FUNC);
	}

	void CloseMenu()
	{
		using FuncType = decltype(&DialogueMenuUtils::CloseMenu);
		static const auto FUNC = REL::Relocation<FuncType>(ID::DialogueMenuUtils::CloseMenu);
		std::invoke(FUNC);
	}

	void ShowButtons()
	{
		using FuncType = decltype(&DialogueMenuUtils::ShowButtons);
		static const auto FUNC = REL::Relocation<FuncType>(ID::DialogueMenuUtils::ShowButtons);
		std::invoke(FUNC);
	}

	void ShowSpeechChallengeAnim()
	{
		using FuncType = decltype(&DialogueMenuUtils::ShowSpeechChallengeAnim);
		static const auto FUNC = REL::Relocation<FuncType>(ID::DialogueMenuUtils::ShowSpeechChallengeAnim);
		std::invoke(FUNC);
	}
}
