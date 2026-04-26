#pragma once

#include "RE/U/UIMessage.hpp"

namespace RE
{
	class __declspec(novtable) IUIMessageData
		: public UIMessage // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::IUIMessageData };
		inline static constexpr auto VTABLE{ VTABLE::IUIMessageData };

		IUIMessageData(BSFixedString a_menuName, UI_MESSAGE_TYPE a_type)
			: UIMessage(std::move(a_menuName), a_type)
		{
			REL::EmplaceVtable(this);
		}

		~IUIMessageData() override = default; // 00

		// override (UIMessage)
		IUIMessageData* QData() override { return this; }			  // 01
		const IUIMessageData* QData() const override { return this; } // 02
	};
	static_assert(sizeof(IUIMessageData) == 0x18);
}
