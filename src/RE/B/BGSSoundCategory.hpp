#pragma once

#include "RE/B/BSISoundCategory.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESFullName.hpp"

namespace RE
{
	class __declspec(novtable) BGSSoundCategory :
		public TESForm,			// 0x00
		public TESFullName,		// 0x20
		public BSISoundCategory // 0x30
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSSoundCategory;
		inline static constexpr const auto& VTABLE = VTABLE::BGSSoundCategory;
		inline static constexpr auto FORM_TYPE = FormType::SoundCategory;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t
		{
			None = 0,
			MuteWhenSubmerged = 1 << 0,
			ShouldAppearOnMenu = 1 << 1,
			ImmuneToTimeSpeedup = 1 << 2,
			PauseDuringMenus_Immed = 1 << 3,
			PauseDuringMenus_Faded = 1 << 4,
			ExcludeFromPlayerOPMOverride = 1 << 5,
			PauseDuringStartMenu = 1 << 6
		};

		~BGSSoundCategory() override; // 0x00

		// members
		BGSSoundCategory* parentCategory;			 // 0x38
		BGSSoundCategory* sliderCategory;			 // 0x40
		REX::Float32 volumeMult;					 // 0x48
		REX::Float32 snapshotMult;					 // 0x4C
		REX::Float32 currCompressionMult;			 // 0x50
		REX::Float32 fullyCompressedMult;			 // 0x54
		REX::Float32 frequencyMult;					 // 0x58
		REX::Float32 minFrequencyMult;				 // 0x5C
		REX::EnumSet<Flags, std::uint32_t> appFlags; // 0x60
		std::array<std::uint16_t, 6> attenuation;	 // 0x64
		std::uint16_t stateFlags;					 // 0x70
		std::uint16_t staticMult;					 // 0x72
		std::uint16_t defaultMenuValue;				 // 0x74
	};

	static_assert(sizeof(BGSSoundCategory) == 0x78);
}
