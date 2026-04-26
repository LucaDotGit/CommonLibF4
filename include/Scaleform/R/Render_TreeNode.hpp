#pragma once

#include "Scaleform/R/Render_ContextImpl_Entry.hpp"

namespace Scaleform::Render
{
	class TreeNode
		: public ContextImpl::Entry // 00
	{
	public:
	};
	static_assert(sizeof(TreeNode) == 0x38);
}
