#pragma once

namespace RE
{
	enum class MENU_RENDER_CONTEXT : std::int32_t
	{
		MenuDelete = 0,
		PreDisplay = 1,
		RenderScreenspace = 2,
		RenderCopyQuads = 3,
		RenderImagespace = 4,
		EnsureDisplayMenuCalled = 5,
		PostDisplay = 6
	};
}
