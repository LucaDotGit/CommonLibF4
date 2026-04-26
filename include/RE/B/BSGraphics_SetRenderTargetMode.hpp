#pragma once

namespace RE::BSGraphics
{
	enum class SetRenderTargetMode : std::int32_t
	{
		kClear = 0,
		kClearDepth = 1,
		kClearStencil = 2,
		kNoClear = 3,
		kRestore = 3,
		kForceCopyRestore = 4,
		kInit = 5
	};
}
