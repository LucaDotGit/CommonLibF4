#pragma once

#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/B/BSSimpleList.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/T/TESBoundObject.hpp"

namespace RE
{
	class __declspec(novtable) BGSStaticCollection :
		public TESBoundObject,		// 0x00
		public BGSModelMaterialSwap // 0x68
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSStaticCollection;
		inline static constexpr const auto& VTABLE = VTABLE::BGSStaticCollection;
		inline static constexpr auto FORM_TYPE = FormType::StaticCollection;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				NonOccluder = 1 << 4,
				Deleted = 1 << 5,
				HiddenFromLocalMap = 1 << 9,
				Loadscreen = 1 << 10,
				UsedAsPlatform = 1 << 11,
				Ignored = 1 << 12,
				HasDistantLOD = 1 << 15,
				Obstacle = 1 << 25,
				NavMeshGeneration_Filter = 1 << 26,
				NavMeshGeneration_BoundingBox = 1 << 27,
				NavMeshGeneration_Ground = 1 << 30
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		class REF_COL_DATA
		{
		public:
			// members
			NiPoint3 location;	// 0x00
			NiPoint3 angle;		// 0x0C
			REX::Float32 scale; // 0x18
		};

		static_assert(sizeof(REF_COL_DATA) == 0x1C);

		// members
		BSTHashMap<TESBoundObject*, BSSimpleList<BGSStaticCollection::REF_COL_DATA>*>* dataMap; // 0xA8
	};

	static_assert(sizeof(BGSStaticCollection) == 0xB0);
}
