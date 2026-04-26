#pragma once

namespace RE
{
	enum class MENU_RENDER_CONTEXT : std::int32_t
	{
		kMenuDelete = 0,
		kPreDisplay = 1,
		kRenderScreenspace = 2,
		kRenderCopyQuads = 3,
		kRenderImagespace = 4,
		kEnsureDisplayMenuCalled = 5,
		kPostDisplay = 6
	};
}
