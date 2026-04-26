#pragma once

#include "RE/B/BGSForcedLocRefType.hpp"
#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/B/BGSNavmeshableObject.hpp"
#include "RE/B/BGSPropertySheet.hpp"
#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESObjectSTATData.hpp"

namespace RE
{
	class __declspec(novtable) TESObjectSTAT
		: public TESBoundObject,	   // 00
		  public BGSModelMaterialSwap, // 68
		  public BGSPropertySheet,	   // A8
		  public BGSForcedLocRefType,  // B8
		  public BGSNavmeshableObject  // C8
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESObjectSTAT };
		inline static constexpr auto VTABLE{ VTABLE::TESObjectSTAT };
		inline static constexpr auto FORM_TYPE{ FormType::kStatic };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kNeverFades = 1 << 2,
				kDeleted = 1 << 5,
				kIsSkyObject = kDeleted,
				kHasTreeLOD = 1 << 6,
				kAddOnLODObject = 1 << 7,
				kHiddenFromLocalMap = 1 << 9,
				kHasDistantLOD = 1 << 15,
				kUsesHDLODTexture = 1 << 17,
				kHasCurrents = 1 << 19,
				kIsMarker = 1 << 23,
				kObstacle = 1 << 25,
				kNavMeshGeneration_Filter = 1 << 26,
				kNavMeshGeneration_BoundingBox = 1 << 27,
				kShowInWorldMap = 1 << 28,
				kNavMeshGeneration_Ground = 1 << 30
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		// members
		TESObjectSTATData data; // D0
	};
	static_assert(sizeof(TESObjectSTAT) == 0xE8);
}
