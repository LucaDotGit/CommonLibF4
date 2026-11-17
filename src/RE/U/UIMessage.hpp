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
		inline static constexpr const auto& RTTI = RTTI::UIMessage;
		inline static constexpr const auto& VTABLE = VTABLE::UIMessage;

		UIMessage(BSFixedString a_menuName, UI_MESSAGE_TYPE a_type) :
			menuName(std::move(a_menuName)),
			type(a_type)
		{
			REL::EmplaceVtable(this);
		}

		virtual ~UIMessage() = default; // 0x00

		// add
		virtual auto QData() -> IUIMessageData* // 0x01
		{
			return nullptr;
		}

		virtual auto QData() const -> const IUIMessageData* // 0x02
		{
			return nullptr;
		}

		GAME_HEAP_REDEFINE_NEW(UIMessage);

		// members
		BSFixedString menuName;													// 0x08
		REX::Enum<UI_MESSAGE_TYPE, std::int32_t> type{UI_MESSAGE_TYPE::_Count}; // 0x10
	};

	static_assert(sizeof(UIMessage) == 0x18);
}
