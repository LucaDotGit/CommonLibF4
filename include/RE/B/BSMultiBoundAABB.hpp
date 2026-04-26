#pragma once

#include "RE/B/BSMultiBoundShape.hpp"
#include "RE/N/NiPoint.hpp"

namespace RE
{
	class NiPlane;

	class __declspec(novtable) BSMultiBoundAABB
		: public BSMultiBoundShape // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSMultiBoundAABB };
		inline static constexpr auto VTABLE{ VTABLE::BSMultiBoundAABB };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::BSMultiBoundAABB };

		// add
		virtual bool IntersectPlane(const NiPlane* a_plane); // 32

		// members
		NiPoint3A center;	   // 20
		NiPoint3A halfExtents; // 30
	};
	static_assert(sizeof(BSMultiBoundAABB) == 0x40);
}
