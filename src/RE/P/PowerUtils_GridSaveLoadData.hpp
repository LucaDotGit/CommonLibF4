#pragma once

#include "RE/P/PowerUtils_GridConnection.hpp"

namespace RE::PowerUtils
{
	class GridSaveLoadData
	{
	public:
		// members
		std::uint32_t node;		   // 0x00
		GridConnection connection; // 0x04
	};

	static_assert(sizeof(GridSaveLoadData) == 0x0C);
}
