#pragma once

#include "Scaleform/R/Render_ContextImpl_Entry.hpp"
#include "Scaleform/R/Render_ContextImpl_EntryPageBase.hpp"

namespace Scaleform::Render::ContextImpl
{
	class EntryPage : public EntryPageBase // 0x00
	{
	public:
		// members
		std::array<Entry, 72> entries; // 0x038
	};

	static_assert(sizeof(EntryPage) == 0xFF8);
}
