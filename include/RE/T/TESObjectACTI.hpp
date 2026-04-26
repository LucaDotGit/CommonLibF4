#pragma once

#include "RE/B/BGSDestructibleObjectForm.hpp"
#include "RE/B/BGSForcedLocRefType.hpp"
#include "RE/B/BGSKeywordForm.hpp"
#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/B/BGSNativeTerminalForm.hpp"
#include "RE/B/BGSNavmeshableObject.hpp"
#include "RE/B/BGSOpenCloseForm.hpp"
#include "RE/B/BGSPropertySheet.hpp"
#include "RE/T/TESBoundAnimObject.hpp"
#include "RE/T/TESFullName.hpp"
#include "RE/T/TESMagicTargetForm.hpp"

namespace RE
{
	class __declspec(novtable) TESObjectACTI
		: public TESBoundAnimObject,		// 000
		  public TESFullName,				// 068
		  public BGSModelMaterialSwap,		// 078
		  public TESMagicTargetForm,		// 120
		  public BGSDestructibleObjectForm, // 0B8
		  public BGSOpenCloseForm,			// 0C8
		  public BGSKeywordForm,			// 0D0
		  public BGSPropertySheet,			// 0F0
		  public BGSForcedLocRefType,		// 100
		  public BGSNativeTerminalForm,		// 110
		  public BGSNavmeshableObject		// 120
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESObjectACTI };
		inline static constexpr auto VTABLE{ VTABLE::TESObjectACTI };
		inline static constexpr auto FORM_TYPE{ FormType::kActivator };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kNeverFades = 1 << 2,
				kNonOccluder = 1 << 4,
				kDeleted = 1 << 5,
				kHasTreeLOD = 1 << 6,
				kHeadingMarker = 1 << 7,
				kMustUpdateAnims = 1 << 8,
				kHiddenFromLocalMap = 1 << 9,
				kHeadtrackMarker = 1 << 10,
				kUsedAsPlatform = 1 << 11,
				kIgnored = 1 << 12,
				kPackInUseOnly = 1 << 13,
				kHasDistantLOD = 1 << 15,
				kRandomAnimStart = 1 << 16,
				kDangerous = 1 << 17,
				kIgnoresObjectInteraction = 1 << 20,
				kIsMarker = 1 << 23,
				kObstacle = 1 << 25,
				kNavMeshGeneration_Filter = 1 << 26,
				kNavMeshGeneration_BoundingBox = 1 << 27,
				kChildCanUse = 1 << 29,
				kNavMeshGeneration_Ground = 1 << 30
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint16_t
		{
			kNone = 0,
			kNoDisplacement = 1 << 0,
			kIgnoredBySandbox = 1 << 1,
			kIsProceduralWater = 1 << 2,
			kIsLODWater = 1 << 3,
			kIsRadio = 1 << 4
		};

		// members
		BGSSoundDescriptorForm* soundLoop;		  // 128
		BGSSoundDescriptorForm* soundActivate;	  // 130
		TESWaterForm* waterForm;				  // 138
		REX::EnumSet<Flags, std::uint16_t> flags; // 140
	};
	static_assert(sizeof(TESObjectACTI) == 0x148);
}
