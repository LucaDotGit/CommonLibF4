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
	class __declspec(novtable) TESObjectCONT :
		public TESBoundAnimObject,		  // 0x000
		public TESContainer,			  // 0x068
		public TESFullName,				  // 0x080
		public BGSModelMaterialSwap,	  // 0x090
		public TESWeightForm,			  // 0x0D0
		public TESMagicCasterForm,		  // 0x148
		public TESMagicTargetForm,		  // 0x148
		public BGSDestructibleObjectForm, // 0x0E0
		public BGSOpenCloseForm,		  // 0x0F0
		public BGSKeywordForm,			  // 0x0F8
		public BGSForcedLocRefType,		  // 0x118
		public BGSPropertySheet,		  // 0x128
		public BGSNativeTerminalForm	  // 0x138
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESObjectCONT;
		inline static constexpr const auto& VTABLE = VTABLE::TESObjectCONT;
		inline static constexpr auto FORM_TYPE = FormType::Container;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12,
				HasDistantLOD = 1 << 15,
				RandomAnimStart = 1 << 16,
				Obstacle = 1 << 25,
				NavMeshGeneration_Filter = 1 << 26,
				NavMeshGeneration_BoundingBox = 1 << 27,
				NavMeshGeneration_Ground = 1 << 30
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		~TESObjectCONT() override; // 0x00

		// members
		CONT_DATA data;						  // 0x149
		BGSSoundDescriptorForm* openSound;	  // 0x150
		BGSSoundDescriptorForm* closeSound;	  // 0x158
		BGSSoundDescriptorForm* takeAllSound; // 0x160
		BGSListForm* containsOnlyList;		  // 0x168
	};

	static_assert(sizeof(TESObjectCONT) == 0x170);
}
