#pragma once

#include "RE/B/BSCompoundFrustum.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BSMultiBoundRoom;
	class BSPortalGraph;

	class __declspec(novtable) BSPortalGraphEntry
		: public NiRefObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSPortalGraphEntry };
		inline static constexpr auto VTABLE{ VTABLE::BSPortalGraphEntry };

		enum class PGE_ROOTVIS : std::int32_t
		{
			kFrustum = 0,
			kSphere = 1,
			kHemiSphere = 2
		};

		// members
		BSPortalGraph* portalGraph;									   // 010
		BSTArray<NiPointer<BSMultiBoundRoom>> multiboundRoomAccumList; // 018
		NiPointer<BSMultiBoundRoom> multiBoundRoomRoot;				   // 030
		BSTHashMap<const void*, BSCompoundFrustum*> visibilityMap;	   // 038
		BSCompoundFrustum compoundFrustum;							   // 068
		bool visibleUnboundSpace;									   // 138
		bool enableAccumulation;									   // 139
		PGE_ROOTVIS rootVisibilityType;								   // 13C
		std::uint32_t worldID;										   // 140
	};
	static_assert(sizeof(BSPortalGraphEntry) == 0x148);
}
