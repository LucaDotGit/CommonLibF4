#include "RE/E/ExamineConfirmMenu.hpp"

#include "RE/M/MessageMenuManager.hpp"

namespace RE
{
	auto ExamineConfirmMenu::InitDataRepairFailure::GetDefaultButtonLabel() -> BSFixedStringCS
	{
		return BSFixedStringCS(MessageMenuManager::OK_TRANSLATION_KEY);
	}

	auto ExamineConfirmMenu::GetCannotRepairMessageSetting() -> Setting&
	{
		static auto* CannotRepairMessage = GetINISetting("sCannotRepairMessage:Interface"sv);
		REX::Assert(CannotRepairMessage != nullptr);
		return *CannotRepairMessage;
	}

	auto ExamineConfirmMenu::GetCannotRepairMessage() -> BSFixedStringCS
	{
		const auto& cannotRepairMessageSetting = GetCannotRepairMessageSetting();
		if (!cannotRepairMessageSetting.IsString()) [[unlikely]] {
			REX::Assert(false);
			return {};
		}

		return {cannotRepairMessageSetting.GetString()};
	}
}
