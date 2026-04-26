#pragma once

#include "Scaleform/P/Ptr.hpp"

namespace RE
{
	class IMenu;
	class UIMessage;

	class UIMenuEntry
	{
	public:
		using CreateType = IMenu*(const UIMessage& a_message);
		using StaticUpdateType = void();

		// members
		::Scaleform::Ptr<IMenu> menu;	// 00
		CreateType* create;				// 08
		StaticUpdateType* staticUpdate; // 10
	};
	static_assert(sizeof(UIMenuEntry) == 0x18);
}
