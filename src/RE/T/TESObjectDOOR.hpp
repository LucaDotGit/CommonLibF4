#pragma once

#include "RE/B/BGSDestructibleObjectForm.hpp"
#include "RE/B/BGSKeywordForm.hpp"
#include "RE/B/BGSLocalizedString.hpp"
#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/B/BGSNativeTerminalForm.hpp"
#include "RE/B/BGSOpenCloseForm.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/T/TESBoundAnimObject.hpp"
#include "RE/T/TESFullName.hpp"
#include "RE/T/TESMagicCasterForm.hpp"
#include "RE/T/TESMagicTargetForm.hpp"

namespace RE
{
	class __declspec(novtable) TESObjectDOOR :
		public TESBoundAnimObject,		  // 0x000
		public TESFullName,				  // 0x068
		public BGSModelMaterialSwap,	  // 0x078
		public TESMagicCasterForm,		  // 0x100
		public TESMagicTargetForm,		  // 0x100
		public BGSDestructibleObjectForm, // 0x0B8
		public BGSOpenCloseForm,		  // 0x0C8
		public BGSKeywordForm,			  // 0x0D0
		public BGSNativeTerminalForm	  // 0x0F0
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESObjectDOOR;
		inline static constexpr const auto& VTABLE = VTABLE::TESObjectDOOR;
		inline static constexpr auto FORM_TYPE = FormType::Door;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12,
				HasDistantLOD = 1 << 15,
				RandomAnimStart = 1 << 16,
				IsMarker = 1 << 23
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint8_t
		{
			None = 0,
			Automatic = 1 << 1,
			Hidden = 1 << 2,
			MinimalUse = 1 << 3,
			Sliding = 1 << 4,
			DoNotOpenInCombatSearch = 1 << 5,
			NoToText = 1 << 6
		};

		~TESObjectDOOR() override; // 0x00

		// members
		BGSLocalizedString altOpenText;			 // 0x108
		BGSLocalizedString altCloseText;		 // 0x110
		BGSSoundDescriptorForm* openSound;		 // 0x118
		BGSSoundDescriptorForm* closeSound;		 // 0x120
		BGSSoundDescriptorForm* loopSound;		 // 0x128
		REX::EnumSet<Flags, std::uint8_t> flags; // 0x130
		BSTArray<TESForm*> randomTeleports;		 // 0x138
	};

	static_assert(sizeof(TESObjectDOOR) == 0x150);
}
