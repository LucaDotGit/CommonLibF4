#pragma once

#include "RE/I/InventoryUserUIInterface.hpp"

namespace RE
{
	class __declspec(novtable) BarterMenuTentativeInventoryUIInterface : public InventoryUserUIInterface // 0x00
	{
	public:
	};

	static_assert(sizeof(BarterMenuTentativeInventoryUIInterface) == 0x80);
}
