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
	class __declspec(novtable) TESObjectACTI :
		public TESBoundAnimObject,		  // 0x000
		public TESFullName,				  // 0x068
		public BGSModelMaterialSwap,	  // 0x078
		public TESMagicTargetForm,		  // 0x120
		public BGSDestructibleObjectForm, // 0x0B8
		public BGSOpenCloseForm,		  // 0x0C8
		public BGSKeywordForm,			  // 0x0D0
		public BGSPropertySheet,		  // 0x0F0
		public BGSForcedLocRefType,		  // 0x100
		public BGSNativeTerminalForm,	  // 0x110
		public BGSNavmeshableObject		  // 0x120
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESObjectACTI;
		inline static constexpr const auto& VTABLE = VTABLE::TESObjectACTI;
		inline static constexpr auto FORM_TYPE = FormType::Activator;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				NeverFades = 1 << 2,
				NonOccluder = 1 << 4,
				Deleted = 1 << 5,
				HasTreeLOD = 1 << 6,
				HeadingMarker = 1 << 7,
				MustUpdateAnims = 1 << 8,
				HiddenFromLocalMap = 1 << 9,
				HeadtrackMarker = 1 << 10,
				UsedAsPlatform = 1 << 11,
				Ignored = 1 << 12,
				PackInUseOnly = 1 << 13,
				HasDistantLOD = 1 << 15,
				RandomAnimStart = 1 << 16,
				Dangerous = 1 << 17,
				IgnoresObjectInteraction = 1 << 20,
				IsMarker = 1 << 23,
				Obstacle = 1 << 25,
				NavMeshGeneration_Filter = 1 << 26,
				NavMeshGeneration_BoundingBox = 1 << 27,
				ChildCanUse = 1 << 29,
				NavMeshGeneration_Ground = 1 << 30
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint16_t
		{
			None = 0,
			NoDisplacement = 1 << 0,
			IgnoredBySandbox = 1 << 1,
			IsProceduralWater = 1 << 2,
			IsLODWater = 1 << 3,
			IsRadio = 1 << 4
		};

		~TESObjectACTI() override; // 0x00

		// members
		BGSSoundDescriptorForm* soundLoop;		  // 0x128
		BGSSoundDescriptorForm* soundActivate;	  // 0x130
		TESWaterForm* waterForm;				  // 0x138
		REX::EnumSet<Flags, std::uint16_t> flags; // 0x140
	};

	static_assert(sizeof(TESObjectACTI) == 0x148);
}
