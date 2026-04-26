#pragma once

#include "RE/P/PowerUtils_GridConnection.hpp"

namespace RE::PowerUtils
{
	class GridSaveLoadData
	{
	public:
		// members
		std::uint32_t node;		   // 00
		GridConnection connection; // 04
	};
	static_assert(sizeof(GridSaveLoadData) == 0x0C);
}
