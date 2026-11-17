#include "RE/M/MessageMenuManager.hpp"

#include "RE/B/BSReadWriteLock.hpp"

namespace RE
{
	auto MessageMenuManager::GetSingleton() noexcept -> MessageMenuManager*
	{
		static const auto SINGLETON = REL::Relocation<MessageMenuManager**>(ID::MessageMenuManager::Singleton);
		return *SINGLETON;
	}

	void MessageMenuManager::CreateOKMessage(
		const char* a_bodyText,
		const BSTSmartPointer<IMessageBoxCallback>& a_callback,
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
		const BSTSmartPointer<IMessageBoxCallback>& a_callback,
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
		const BSTSmartPointer<IMessageBoxCallback>& a_callback,
		BSTArray<BSString> a_buttons,
		WARNING_TYPES a_warningContext,
		bool a_ensureUnique)
	{
		const auto messageLock = BSAutoWriteLock(messageRWLock);

		CreateMessage(a_bodyText, a_callback, nullptr, nullptr, nullptr, nullptr, a_warningContext, a_ensureUnique);

		const auto messageDataIt = std::ranges::find_if(
			messages | std::views::reverse,
			[a_callback](const MessageBoxData* a_messageData) noexcept -> bool {
				return a_messageData && a_messageData->callback == a_callback.get();
			});

		if (messageDataIt == messages.rend() || (*messageDataIt)->callback != a_callback) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		auto& messageButtons = (*messageDataIt)->buttonText;

		if (a_buttons.empty()) {
			messageButtons.emplace_back(OK_TRANSLATION_KEY);
			return;
		}

		if (a_buttons.size() > MAX_BUTTON_COUNT) {
			a_buttons.resize(MAX_BUTTON_COUNT);
		}

		messageButtons = std::move(a_buttons);
	}

	void MessageMenuManager::CreateMessage(
		const char* a_bodyText,
		const BSTSmartPointer<IMessageBoxCallback>& a_callback,
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
			a_callback.get(),
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
		static const auto FUNC = REL::Relocation<FuncType>(ID::MessageMenuManager::ShowMessages);
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
		static const auto FUNC = REL::Relocation<FuncType>(ID::MessageMenuManager::CreateImpl);
		std::invoke(
			FUNC,
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
