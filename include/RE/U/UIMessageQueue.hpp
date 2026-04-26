#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/U/UIMessage.hpp"

#include "msvc/memory.hpp"

namespace RE
{
	class IMenu;
}

namespace RE::Impl
{
	template <class T>
	concept UIMessageConstraint =
		std::derived_from<T, IMenu> &&
		!std::is_pointer_v<T> &&
		!std::is_reference_v<T> &&
		std::same_as<std::remove_cv_t<decltype(T::MENU_NAME)>, std::string_view>;
}

namespace RE
{
	enum class UI_MESSAGE_TYPE : std::int32_t;

	class UIMessageQueue
		: public BSTSingletonSDM<UIMessageQueue> // 00
	{
	public:
		[[nodiscard]] static UIMessageQueue* GetSingleton();

		bool HasMessage(const BSFixedString& a_menuName) const;
		void AddMessage(const BSFixedString& a_menuName, UI_MESSAGE_TYPE a_type);

		template <Impl::UIMessageConstraint T>
		void HasMessage() const
		{
			HasMessage(BSFixedString(T::MENU_NAME));
		}

		template <Impl::UIMessageConstraint T>
		void AddMessage(UI_MESSAGE_TYPE a_type)
		{
			AddMessage(BSFixedString(T::MENU_NAME), a_type);
		}

		// members
		BSTSmallArray<msvc::unique_ptr<UIMessage>, 64> messages; // 008
		mutable BSSpinLock messagesLock;						 // 218
	};
	static_assert(sizeof(UIMessageQueue) == 0x220);
}
