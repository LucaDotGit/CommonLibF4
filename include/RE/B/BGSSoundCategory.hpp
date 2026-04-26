#pragma once

#include "RE/B/BSISoundCategory.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESFullName.hpp"

namespace RE
{
	class __declspec(novtable) BGSSoundCategory
		: public TESForm,		  // 00
		  public TESFullName,	  // 20
		  public BSISoundCategory // 30
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSSoundCategory };
		inline static constexpr auto VTABLE{ VTABLE::BGSSoundCategory };
		inline static constexpr auto FORM_TYPE{ FormType::kSoundCategory };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kMuteWhenSubmerged = 1 << 0,
			kShouldAppearOnMenu = 1 << 1,
			kImmuneToTimeSpeedup = 1 << 2,
			kPauseDuringMenus_Immed = 1 << 3,
			kPauseDuringMenus_Faded = 1 << 4,
			kExcludeFromPlayerOPMOverride = 1 << 5,
			kPauseDuringStartMenu = 1 << 6
		};

		// members
		BGSSoundCategory* parentCategory;			 // 38
		BGSSoundCategory* sliderCategory;			 // 40
		REX::Float32 volumeMult;					 // 48
		REX::Float32 snapshotMult;					 // 4C
		REX::Float32 currCompressionMult;			 // 50
		REX::Float32 fullyCompressedMult;			 // 54
		REX::Float32 frequencyMult;					 // 58
		REX::Float32 minFrequencyMult;				 // 5C
		REX::EnumSet<Flags, std::uint32_t> appFlags; // 60
		std::array<std::uint16_t, 6> attenuation;	 // 64
		std::uint16_t stateFlags;					 // 70
		std::uint16_t staticMult;					 // 72
		std::uint16_t defaultMenuValue;				 // 74
	};
	static_assert(sizeof(BGSSoundCategory) == 0x78);
}
