#include "RE/U/UIMessageQueue.hpp"

#include "RE/B/BSSpinLock.hpp"

namespace RE
{
	auto UIMessageQueue::GetSingleton() noexcept -> UIMessageQueue*
	{
		static const auto SINGLETON = REL::Relocation<UIMessageQueue**>(ID::UIMessageQueue::Singleton);
		return *SINGLETON;
	}

	auto UIMessageQueue::HasMessage(const BSFixedString& a_menuName) const noexcept -> bool
	{
		const auto messageLock = BSAutoSpinLock(messagesLock);
		return std::ranges::any_of(
			messages,
			[&a_menuName](const msvc::unique_ptr<UIMessage>& a_message) noexcept -> bool {
				return a_message && a_message->menuName == a_menuName;
			});
	}

	void UIMessageQueue::AddMessage(const BSFixedString& a_menuName, UI_MESSAGE_TYPE a_type)
	{
		const auto messageLock = BSAutoSpinLock(messagesLock);
		messages.push_back(msvc::make_unique<UIMessage>(a_menuName, a_type));
	}
}
