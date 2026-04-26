#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/U/UI_MESSAGE_TYPE.hpp"

namespace RE
{
	class IUIMessageData;

	class __declspec(novtable) UIMessage
	{
	public:
		inline static constexpr auto RTTI{ RTTI::UIMessage };
		inline static constexpr auto VTABLE{ VTABLE::UIMessage };

		UIMessage(BSFixedString a_menuName, UI_MESSAGE_TYPE a_type)
			: menuName(std::move(a_menuName)),
			  type(a_type)
		{
			REL::EmplaceVtable(this);
		}

		virtual ~UIMessage() = default; // 00

		// add
		virtual IUIMessageData* QData() { return nullptr; }				// 01
		virtual const IUIMessageData* QData() const { return nullptr; } // 02

		GAME_HEAP_REDEFINE_NEW(UIMessage);

		// members
		BSFixedString menuName;													  // 08
		REX::Enum<UI_MESSAGE_TYPE, std::int32_t> type{ UI_MESSAGE_TYPE::kTotal }; // 10
	};
	static_assert(sizeof(UIMessage) == 0x18);
}
