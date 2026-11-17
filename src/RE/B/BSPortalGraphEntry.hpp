#pragma once

#include "RE/B/BSCompoundFrustum.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BSMultiBoundRoom;
	class BSPortalGraph;

	class __declspec(novtable) BSPortalGraphEntry : public NiRefObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSPortalGraphEntry;
		inline static constexpr const auto& VTABLE = VTABLE::BSPortalGraphEntry;

		enum class PGE_ROOTVIS : std::int32_t
		{
			Frustum = 0,
			Sphere = 1,
			HemiSphere = 2
		};

		// members
		BSPortalGraph* portalGraph;									   // 0x010
		BSTArray<NiPointer<BSMultiBoundRoom>> multiboundRoomAccumList; // 0x018
		NiPointer<BSMultiBoundRoom> multiBoundRoomRoot;				   // 0x030
		BSTHashMap<const void*, BSCompoundFrustum*> visibilityMap;	   // 0x038
		BSCompoundFrustum compoundFrustum;							   // 0x068
		bool visibleUnboundSpace;									   // 0x138
		bool enableAccumulation;									   // 0x139
		PGE_ROOTVIS rootVisibilityType;								   // 0x13C
		std::uint32_t worldID;										   // 0x140
	};

	static_assert(sizeof(BSPortalGraphEntry) == 0x148);
}
