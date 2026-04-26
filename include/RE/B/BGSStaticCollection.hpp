#pragma once

#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/B/BSSimpleList.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/T/TESBoundObject.hpp"

namespace RE
{
	class __declspec(novtable) BGSStaticCollection
		: public TESBoundObject,	  // 00
		  public BGSModelMaterialSwap // 68
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSStaticCollection };
		inline static constexpr auto VTABLE{ VTABLE::BGSStaticCollection };
		inline static constexpr auto FORM_TYPE{ FormType::kStaticCollection };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kNonOccluder = 1 << 4,
				kDeleted = 1 << 5,
				kHiddenFromLocalMap = 1 << 9,
				kLoadscreen = 1 << 10,
				kUsedAsPlatform = 1 << 11,
				kIgnored = 1 << 12,
				kHasDistantLOD = 1 << 15,
				kObstacle = 1 << 25,
				kNavMeshGeneration_Filter = 1 << 26,
				kNavMeshGeneration_BoundingBox = 1 << 27,
				kNavMeshGeneration_Ground = 1 << 30
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		class REF_COL_DATA
		{
		public:
			// members
			NiPoint3 location;	// 00
			NiPoint3 angle;		// 0C
			REX::Float32 scale; // 18
		};
		static_assert(sizeof(REF_COL_DATA) == 0x1C);

		// members
		BSTHashMap<TESBoundObject*, BSSimpleList<BGSStaticCollection::REF_COL_DATA>*>* dataMap; // A8
	};
	static_assert(sizeof(BGSStaticCollection) == 0xB0);
}
