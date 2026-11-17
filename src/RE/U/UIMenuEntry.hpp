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
		Scaleform::Ptr<IMenu> menu;		// 0x00
		CreateType* create;				// 0x08
		StaticUpdateType* staticUpdate; // 0x10
	};

	static_assert(sizeof(UIMenuEntry) == 0x18);
}
