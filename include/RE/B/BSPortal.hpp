#pragma once

#include "RE/B/BSOcclusionPlane.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BSMultiBoundRoom;
	class BSPortalSharedNode;

	class __declspec(novtable) BSPortal
		: public BSOcclusionPlane // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSPortal };
		inline static constexpr auto VTABLE{ VTABLE::BSPortal };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::BSPortal };

		~BSPortal() override; // 00

		// members
		std::array<BSMultiBoundRoom*, 2> multiboundRoom; // 130
		NiPointer<BSPortalSharedNode> sharedGeometry;	 // 140
	};
	static_assert(sizeof(BSPortal) == 0x150);
}
