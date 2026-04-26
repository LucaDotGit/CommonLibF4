#pragma once

#include "RE/B/BSMultiBoundNode.hpp"
#include "RE/B/BSPortal.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiTPointerList.hpp"

namespace RE
{
	class BSLight;
	class BSOcclusionShape;

	class __declspec(novtable) BSMultiBoundRoom
		: public BSMultiBoundNode // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSMultiBoundRoom };
		inline static constexpr auto VTABLE{ VTABLE::BSMultiBoundRoom };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::BSMultiBoundRoom };

		// members
		NiTPointerList<BSPortal*> portalList;						   // 150
		NiTPointerList<BSOcclusionShape*> occluderList;				   // 168
		NiTPointerList<NiPointer<BSMultiBound>*> joinedMultiBoundList; // 180
		BSTArray<BSLight*> lights;									   // 198
	};
	static_assert(sizeof(BSMultiBoundRoom) == 0x1B0);
}
