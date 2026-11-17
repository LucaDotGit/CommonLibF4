#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/N/NiNode.hpp"

namespace RE
{
	class BSLight;
	class BSPortal;

	class __declspec(novtable) BSPortalSharedNode : public NiNode // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSPortalSharedNode;
		inline static constexpr const auto& VTABLE = VTABLE::BSPortalSharedNode;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSPortalSharedNode;

		~BSPortalSharedNode() override; // 0x00

		// members
		BSTArray<BSLight*> lights; // 0x140
		BSPortal* portal;		   // 0x158
	};

#if (COMMONLIB_RUNTIME_VR == 0)
	static_assert(sizeof(BSPortalSharedNode) == 0x160);
#else
	static_assert(sizeof(BSPortalSharedNode) == 0x140);
#endif
}
