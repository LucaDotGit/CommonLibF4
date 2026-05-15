#include "RE/U/UIMessageQueue.hpp"

namespace RE
{
	UIMessageQueue* UIMessageQueue::GetSingleton()
	{
		static const auto SINGLETON = REL::Relocation<UIMessageQueue**>{ ID::UIMessageQueue::Singleton };
		return *SINGLETON;
	}

	bool UIMessageQueue::HasMessage(const BSFixedString& a_menuName) const
	{
		const auto messageLock = BSAutoLock(messagesLock);
		return std::ranges::any_of(messages, [&a_menuName](const msvc::unique_ptr<UIMessage>& a_message) -> bool {
			return a_message && a_message->menuName == a_menuName;
		});
	}

	void UIMessageQueue::AddMessage(const BSFixedString& a_menuName, UI_MESSAGE_TYPE a_type)
	{
		const auto messageLock = BSAutoLock(messagesLock);
		messages.push_back(msvc::make_unique<UIMessage>(a_menuName, a_type));
	}
}
