#pragma once

#include "RE/B/BSMultiBoundShape.hpp"
#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class NiPlane;

	class __declspec(novtable) BSMultiBoundAABB : public BSMultiBoundShape // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSMultiBoundAABB;
		inline static constexpr const auto& VTABLE = VTABLE::BSMultiBoundAABB;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSMultiBoundAABB;

		// add
		virtual auto IntersectPlane(const NiPlane* a_plane) -> bool; // 0x32

		// members
		NiPoint3A center;	   // 0x20
		NiPoint3A halfExtents; // 0x30
	};

	static_assert(sizeof(BSMultiBoundAABB) == 0x40);
}
