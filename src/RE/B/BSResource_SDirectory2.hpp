#pragma once

#include "RE/B/BSResource_Archive2_Index.hpp"

namespace RE::BSResource::SDirectory2
{
	class Cursor : public Archive2::Index::CursorWithEntry // 0x00
	{
	public:
		// members
		Archive2::Index* index; // 0x170
	};

	static_assert(sizeof(Cursor) == 0x178);
}
