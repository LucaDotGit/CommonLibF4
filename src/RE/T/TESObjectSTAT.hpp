#pragma once

#include "RE/B/BGSForcedLocRefType.hpp"
#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/B/BGSNavmeshableObject.hpp"
#include "RE/B/BGSPropertySheet.hpp"
#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESObjectSTATData.hpp"

namespace RE
{
	class __declspec(novtable) TESObjectSTAT :
		public TESBoundObject,		 // 0x00
		public BGSModelMaterialSwap, // 0x68
		public BGSPropertySheet,	 // 0xA8
		public BGSForcedLocRefType,	 // 0xB8
		public BGSNavmeshableObject	 // 0xC8
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESObjectSTAT;
		inline static constexpr const auto& VTABLE = VTABLE::TESObjectSTAT;
		inline static constexpr auto FORM_TYPE = FormType::Static;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				NeverFades = 1 << 2,
				Deleted = 1 << 5,
				IsSkyObject = Deleted,
				HasTreeLOD = 1 << 6,
				AddOnLODObject = 1 << 7,
				HiddenFromLocalMap = 1 << 9,
				HasDistantLOD = 1 << 15,
				UsesHDLODTexture = 1 << 17,
				HasCurrents = 1 << 19,
				IsMarker = 1 << 23,
				Obstacle = 1 << 25,
				NavMeshGeneration_Filter = 1 << 26,
				NavMeshGeneration_BoundingBox = 1 << 27,
				ShowInWorldMap = 1 << 28,
				NavMeshGeneration_Ground = 1 << 30
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		// members
		TESObjectSTATData data; // 0xD0
	};

	static_assert(sizeof(TESObjectSTAT) == 0xE8);
}
