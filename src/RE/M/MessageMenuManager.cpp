#include "RE/M/MessageMenuManager.hpp"

namespace RE
{
	static constexpr auto OK_TRANSLATION_KEY = "$OK"sv;
	static constexpr auto YES_TRANSLATION_KEY = "$Yes"sv;
	static constexpr auto NO_TRANSLATION_KEY = "$No"sv;

	MessageMenuManager* MessageMenuManager::GetSingleton()
	{
		static const auto SINGLETON = REL::Relocation<MessageMenuManager**>{ ID::MessageMenuManager::Singleton };
		return *SINGLETON;
	}

	void MessageMenuManager::CreateOKMessage(
		const char* a_bodyText,
		IMessageBoxCallback* a_callback,
		WARNING_TYPES a_warningContext,
		bool a_ensureUnique)
	{
		CreateMessage(
			a_bodyText,
			a_callback,
			OK_TRANSLATION_KEY.data(),
			nullptr,
			nullptr,
			nullptr,
			a_warningContext,
			a_ensureUnique);
	}

	void MessageMenuManager::CreateYesNoMessage(
		const char* a_bodyText,
		IMessageBoxCallback* a_callback,
		WARNING_TYPES a_warningContext,
		bool a_ensureUnique)
	{
		CreateMessage(
			a_bodyText,
			a_callback,
			YES_TRANSLATION_KEY.data(),
			NO_TRANSLATION_KEY.data(),
			nullptr,
			nullptr,
			a_warningContext,
			a_ensureUnique);
	}

	void MessageMenuManager::CreateCustomMessage(
		const char* a_bodyText,
		IMessageBoxCallback* a_callback,
		BSTArray<BSString> a_buttons,
		WARNING_TYPES a_warningContext,
		bool a_ensureUnique)
	{
		const auto messageLock = BSAutoWriteLock(messageRWLock);

		CreateMessage(
			a_bodyText,
			a_callback,
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			a_warningContext,
			a_ensureUnique);

		auto* messageData = messages.back();
		if (!messageData || messageData->callback != a_callback) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		auto& messageButtons = messageData->buttonText;
		if (a_buttons.empty()) {
			messageButtons.emplace_back(OK_TRANSLATION_KEY);
			return;
		}

		a_buttons.resize(std::min(a_buttons.size(), MAX_BUTTON_COUNT));
		messageButtons = std::move(a_buttons);
	}

	void MessageMenuManager::CreateMessage(
		const char* a_bodyText,
		IMessageBoxCallback* a_callback,
		const char* a_buttonText01,
		const char* a_buttonText02,
		const char* a_buttonText03,
		const char* a_buttonText04,
		WARNING_TYPES a_warningContext,
		bool a_ensureUnique)
	{
		CreateImpl(
			nullptr,
			a_bodyText,
			a_callback,
			a_warningContext,
			a_buttonText01,
			a_buttonText02,
			a_buttonText03,
			a_buttonText04,
			a_ensureUnique);
	}

	void MessageMenuManager::ShowMessages()
	{
		using FuncType = decltype(&MessageMenuManager::ShowMessages);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::MessageMenuManager::ShowMessages };
		std::invoke(FUNC, this);
	}

	void MessageMenuManager::CreateImpl(
		const char* a_headerText,
		const char* a_bodyText,
		IMessageBoxCallback* a_callback,
		WARNING_TYPES a_warningContext,
		const char* a_buttonText01,
		const char* a_buttonText02,
		const char* a_buttonText03,
		const char* a_buttonText04,
		bool a_ensureUnique)
	{
		using FuncType = decltype(&MessageMenuManager::CreateImpl);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::MessageMenuManager::CreateImpl };
		std::invoke(FUNC,
			this,
			a_headerText,
			a_bodyText,
			a_callback,
			a_warningContext,
			a_buttonText01,
			a_buttonText02,
			a_buttonText03,
			a_buttonText04,
			a_ensureUnique);
	}
}
