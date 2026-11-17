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
	class __declspec(novtable) TESObjectLIGH :
		public TESBoundAnimObject,		  // 0x000
		public BGSModelMaterialSwap,	  // 0x068
		public TESIcon,					  // 0x0A8
		public BGSMessageIcon,			  // 0x0B8
		public TESWeightForm,			  // 0x0D0
		public TESValueForm,			  // 0x0E0
		public BGSDestructibleObjectForm, // 0x0F0
		public BGSEquipType,			  // 0x100
		public BGSPropertySheet,		  // 0x110
		public BGSOpenCloseForm,		  // 0x120
		public BGSKeywordForm			  // 0x128
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESObjectLIGH;
		inline static constexpr const auto& VTABLE = VTABLE::TESObjectLIGH;
		inline static constexpr auto FORM_TYPE = FormType::Light;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12,
				HasDistantLOD = 1 << 15,
				RandomAnimStart = 1 << 16,
				Obstacle = 1 << 25,
				PortalStrict = 1 << 28
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		~TESObjectLIGH() override; // 0x00

		// members
		OBJ_LIGH data;				   // 0x148
		REX::Float32 fade;			   // 0x180
		BGSSoundDescriptorForm* sound; // 0x188
		TESTexture goboTexture;		   // 0x190
		NiColor emittanceColor;		   // 0x1A0
		BGSLensFlare* lensFlare;	   // 0x1B0
		BGSGodRays* godRays;		   // 0x1B8
	};

	static_assert(sizeof(TESObjectLIGH) == 0x1C0);
}
