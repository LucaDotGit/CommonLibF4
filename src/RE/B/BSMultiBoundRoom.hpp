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

	class __declspec(novtable) BSMultiBoundRoom : public BSMultiBoundNode // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSMultiBoundRoom;
		inline static constexpr const auto& VTABLE = VTABLE::BSMultiBoundRoom;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSMultiBoundRoom;

		// members
		NiTPointerList<BSPortal*> portalList;						   // 0x150
		NiTPointerList<BSOcclusionShape*> occluderList;				   // 0x168
		NiTPointerList<NiPointer<BSMultiBound>*> joinedMultiBoundList; // 0x180
		BSTArray<BSLight*> lights;									   // 0x198
	};

#if (COMMONLIB_RUNTIME_VR == 0)
	static_assert(sizeof(BSMultiBoundRoom) == 0x1B0);
#else
	static_assert(sizeof(BSMultiBoundRoom) == 0x190);
#endif
}
