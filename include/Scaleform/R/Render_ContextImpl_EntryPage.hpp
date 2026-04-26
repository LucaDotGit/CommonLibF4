#pragma once

#include "Scaleform/R/Render_ContextImpl_Entry.hpp"
#include "Scaleform/R/Render_ContextImpl_EntryPageBase.hpp"

namespace Scaleform::Render::ContextImpl
{
	class EntryPage
		: public EntryPageBase // 00
	{
	public:
		// members
		std::array<Entry, 72> entries; // 038
	};
	static_assert(sizeof(EntryPage) == 0xFF8);
}
