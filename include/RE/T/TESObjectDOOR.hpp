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
	class __declspec(novtable) TESObjectDOOR
		: public TESBoundAnimObject,		// 000
		  public TESFullName,				// 068
		  public BGSModelMaterialSwap,		// 078
		  public TESMagicCasterForm,		// 100
		  public TESMagicTargetForm,		// 100
		  public BGSDestructibleObjectForm, // 0B8
		  public BGSOpenCloseForm,			// 0C8
		  public BGSKeywordForm,			// 0D0
		  public BGSNativeTerminalForm		// 0F0
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESObjectDOOR };
		inline static constexpr auto VTABLE{ VTABLE::TESObjectDOOR };
		inline static constexpr auto FORM_TYPE{ FormType::kDoor };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kHasDistantLOD = 1 << 15,
				kRandomAnimStart = 1 << 16,
				kIsMarker = 1 << 23
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint8_t
		{
			kNone = 0,
			kAutomatic = 1 << 1,
			kHidden = 1 << 2,
			kMinimalUse = 1 << 3,
			kSliding = 1 << 4,
			kDoNotOpenInCombatSearch = 1 << 5,
			kNoToText = 1 << 6
		};

		// members
		BGSLocalizedString altOpenText;			 // 108
		BGSLocalizedString altCloseText;		 // 110
		BGSSoundDescriptorForm* openSound;		 // 118
		BGSSoundDescriptorForm* closeSound;		 // 120
		BGSSoundDescriptorForm* loopSound;		 // 128
		REX::EnumSet<Flags, std::uint8_t> flags; // 130
		BSTArray<TESForm*> randomTeleports;		 // 138
	};
	static_assert(sizeof(TESObjectDOOR) == 0x150);
}
