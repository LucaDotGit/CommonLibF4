#pragma once

#include "RE/B/BSOcclusionPlane.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BSMultiBoundRoom;
	class BSPortalSharedNode;

	class __declspec(novtable) BSPortal : public BSOcclusionPlane // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSPortal;
		inline static constexpr const auto& VTABLE = VTABLE::BSPortal;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSPortal;

		~BSPortal() override; // 0x00

		// members
		std::array<BSMultiBoundRoom*, 2> multiboundRoom; // 0x130
		NiPointer<BSPortalSharedNode> sharedGeometry;	 // 0x140
	};

	static_assert(sizeof(BSPortal) == 0x150);
}
