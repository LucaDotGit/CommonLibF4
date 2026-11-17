#pragma once

namespace RE::BSGraphics
{
	enum class SetRenderTargetMode : std::int32_t
	{
		Clear = 0,
		ClearDepth = 1,
		ClearStencil = 2,
		NoClear = 3,
		Restore = 3,
		ForceCopyRestore = 4,
		Init = 5
	};
}
