#pragma once

#include "RE/B/BGSDestructibleObjectForm.hpp"
#include "RE/B/BGSForcedLocRefType.hpp"
#include "RE/B/BGSKeywordForm.hpp"
#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/B/BGSNativeTerminalForm.hpp"
#include "RE/B/BGSOpenCloseForm.hpp"
#include "RE/B/BGSPropertySheet.hpp"
#include "RE/C/CONT_DATA.hpp"
#include "RE/T/TESBoundAnimObject.hpp"
#include "RE/T/TESContainer.hpp"
#include "RE/T/TESFullName.hpp"
#include "RE/T/TESMagicCasterForm.hpp"
#include "RE/T/TESMagicTargetForm.hpp"
#include "RE/T/TESWeightForm.hpp"

namespace RE
{
	class __declspec(novtable) TESObjectCONT
		: public TESBoundAnimObject,		// 000
		  public TESContainer,				// 068
		  public TESFullName,				// 080
		  public BGSModelMaterialSwap,		// 090
		  public TESWeightForm,				// 0D0
		  public TESMagicCasterForm,		// 148
		  public TESMagicTargetForm,		// 148
		  public BGSDestructibleObjectForm, // 0E0
		  public BGSOpenCloseForm,			// 0F0
		  public BGSKeywordForm,			// 0F8
		  public BGSForcedLocRefType,		// 118
		  public BGSPropertySheet,			// 128
		  public BGSNativeTerminalForm		// 138
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESObjectCONT };
		inline static constexpr auto VTABLE{ VTABLE::TESObjectCONT };
		inline static constexpr auto FORM_TYPE{ FormType::kContainer };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kHasDistantLOD = 1 << 15,
				kRandomAnimStart = 1 << 16,
				kObstacle = 1 << 25,
				kNavMeshGeneration_Filter = 1 << 26,
				kNavMeshGeneration_BoundingBox = 1 << 27,
				kNavMeshGeneration_Ground = 1 << 30
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		// members
		CONT_DATA data;						  // 149
		BGSSoundDescriptorForm* openSound;	  // 150
		BGSSoundDescriptorForm* closeSound;	  // 158
		BGSSoundDescriptorForm* takeAllSound; // 160
		BGSListForm* containsOnlyList;		  // 168
	};
	static_assert(sizeof(TESObjectCONT) == 0x170);
}
