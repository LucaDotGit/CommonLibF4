#pragma once

#include "RE/N/NiNode.hpp"

namespace RE
{
	class __declspec(novtable) BSNiNode
		: public NiNode // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSNiNode };
		inline static constexpr auto VTABLE{ VTABLE::BSNiNode };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::BSNiNode };
	};
	static_assert(sizeof(BSNiNode) == 0x140);
}
