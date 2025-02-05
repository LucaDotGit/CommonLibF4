#pragma once

#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSLock.hpp"
#include "RE/Bethesda/BSTArray.hpp"
#include "RE/Bethesda/BSTSingleton.hpp"
#include "RE/Bethesda/UIMessage.hpp"

namespace RE
{
	class UIMessageQueue
		: public BSTSingletonSDM<UIMessageQueue> // 000
	{
	public:
		[[nodiscard]] static UIMessageQueue* GetSingleton()
		{
			static REL::Relocation<UIMessageQueue**> singleton{ REL::RelocationID(82123, 2689091) };
			return *singleton;
		}

		void AddMessage(const BSFixedString& a_menu, UI_MESSAGE_TYPE a_type)
		{
			using func_t = decltype(&UIMessageQueue::AddMessage);
			static REL::Relocation<func_t> func{ REL::RelocationID(1182019, 2284929) };
			return func(this, a_menu, a_type);
		}

		// members
		BSTSmallArray<msvc::unique_ptr<UIMessage>, 64> messages; // 008
		mutable BSSpinLock uiMessagesLock;						 // 218
	};
	static_assert(sizeof(UIMessageQueue) == 0x220);
}
