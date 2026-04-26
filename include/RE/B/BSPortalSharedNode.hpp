#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/N/NiNode.hpp"

namespace RE
{
	class BSLight;
	class BSPortal;

	class __declspec(novtable) BSPortalSharedNode
		: public NiNode // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSPortalSharedNode };
		inline static constexpr auto VTABLE{ VTABLE::BSPortalSharedNode };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::BSPortalSharedNode };

		~BSPortalSharedNode() override; // 00

		// members
		BSTArray<BSLight*> lights; // 140
		BSPortal* portal;		   // 158
	};
	static_assert(sizeof(BSPortalSharedNode) == 0x160);
}
