#pragma once

#include "Scaleform/R/Render_TreeContainer.hpp"

namespace Scaleform::Render
{
	class TreeRoot
		: public TreeContainer // 00
	{
	public:
	};
	static_assert(sizeof(TreeRoot) == 0x38);
}
