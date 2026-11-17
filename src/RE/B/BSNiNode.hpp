#pragma once

#include "RE/N/NiNode.hpp"

namespace RE
{
	class __declspec(novtable) BSNiNode : public NiNode // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSNiNode;
		inline static constexpr const auto& VTABLE = VTABLE::BSNiNode;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSNiNode;
	};

#if (COMMONLIB_RUNTIME_VR == 0)
	static_assert(sizeof(BSNiNode) == 0x140);
#else
	static_assert(sizeof(BSNiNode) == 0x120);
#endif
}
