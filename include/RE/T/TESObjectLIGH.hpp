#pragma once

#include "RE/B/BGSDestructibleObjectForm.hpp"
#include "RE/B/BGSEquipType.hpp"
#include "RE/B/BGSKeywordForm.hpp"
#include "RE/B/BGSMessageIcon.hpp"
#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/B/BGSOpenCloseForm.hpp"
#include "RE/B/BGSPropertySheet.hpp"
#include "RE/N/NiColor.hpp"
#include "RE/O/OBJ_LIGH.hpp"
#include "RE/T/TESBoundAnimObject.hpp"
#include "RE/T/TESIcon.hpp"
#include "RE/T/TESTexture.hpp"
#include "RE/T/TESValueForm.hpp"
#include "RE/T/TESWeightForm.hpp"

namespace RE
{
	class __declspec(novtable) TESObjectLIGH
		: public TESBoundAnimObject,		// 000
		  public BGSModelMaterialSwap,		// 068
		  public TESIcon,					// 0A8
		  public BGSMessageIcon,			// 0B8
		  public TESWeightForm,				// 0D0
		  public TESValueForm,				// 0E0
		  public BGSDestructibleObjectForm, // 0F0
		  public BGSEquipType,				// 100
		  public BGSPropertySheet,			// 110
		  public BGSOpenCloseForm,			// 120
		  public BGSKeywordForm				// 128
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESObjectLIGH };
		inline static constexpr auto VTABLE{ VTABLE::TESObjectLIGH };
		inline static constexpr auto FORM_TYPE{ FormType::kLight };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kHasDistantLOD = 1 << 15,
				kRandomAnimStart = 1 << 16,
				kObstacle = 1 << 25,
				kPortalStrict = 1 << 28
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		// members
		OBJ_LIGH data;				   // 148
		REX::Float32 fade;			   // 180
		BGSSoundDescriptorForm* sound; // 188
		TESTexture goboTexture;		   // 190
		NiColor emittanceColor;		   // 1A0
		BGSLensFlare* lensFlare;	   // 1B0
		BGSGodRays* godRays;		   // 1B8
	};
	static_assert(sizeof(TESObjectLIGH) == 0x1C0);
}
