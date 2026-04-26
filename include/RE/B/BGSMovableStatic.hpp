#pragma once

#include "RE/B/BGSDestructibleObjectForm.hpp"
#include "RE/B/BGSKeywordForm.hpp"
#include "RE/M/MOVABLE_STATIC_DATA.hpp"
#include "RE/T/TESObjectSTAT.hpp"

namespace RE
{
	class __declspec(novtable) BGSMovableStatic
		: public TESObjectSTAT,				// 000
		  public BGSDestructibleObjectForm, // 0E8
		  public BGSKeywordForm				// 0F8
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSMovableStatic };
		inline static constexpr auto VTABLE{ VTABLE::BGSMovableStatic };
		inline static constexpr auto FORM_TYPE{ FormType::kMovableStatic };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kMustUpdateAnims = 1 << 8,
				kHiddenFromLocalMap = 1 << 9,
				kIgnored = 1 << 12,
				kHasDistantLOD = 1 << 15,
				kRandomAnimStart = 1 << 16,
				kHasCurrents = 1 << 19,
				kObstacle = 1 << 25,
				kNavMeshGeneration_Filter = 1 << 26,
				kNavMeshGeneration_BoundingBox = 1 << 27,
				kNavMeshGeneration_Ground = 1 << 30
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		// members
		BGSSoundDescriptorForm* soundLoop; // 118
		MOVABLE_STATIC_DATA data;		   // 120
	};
	static_assert(sizeof(BGSMovableStatic) == 0x128);
}
