#pragma once

#include "RE/U/UIMessage.hpp"

namespace RE
{
	class __declspec(novtable) IUIMessageData : public UIMessage // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::IUIMessageData;
		inline static constexpr const auto& VTABLE = VTABLE::IUIMessageData;

		IUIMessageData(BSFixedString a_menuName, UI_MESSAGE_TYPE a_type) :
			UIMessage(std::move(a_menuName), a_type)
		{
			REL::EmplaceVtable(this);
		}

		~IUIMessageData() override = default; // 0x00

		// override (UIMessage)
		auto QData() -> IUIMessageData* override // 0x01
		{
			return this;
		}

		auto QData() const -> const IUIMessageData* override // 0x02
		{
			return this;
		}
	};

	static_assert(sizeof(IUIMessageData) == 0x18);
}
