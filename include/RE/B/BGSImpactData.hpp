#pragma once

#include "RE/D/DecalData.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESModel.hpp"

namespace RE
{
	enum class SOUND_LEVEL : std::int32_t;

	class __declspec(novtable) BGSImpactData
		: public TESForm, // 00
		  public TESModel // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSImpactData };
		inline static constexpr auto VTABLE{ VTABLE::BGSImpactData };
		inline static constexpr auto FORM_TYPE{ FormType::kImpactData };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class ORIENTATION : std::int32_t
		{
			kSurfaceNormal = 0,
			kProjVector = 1,
			kProjReflect = 2
		};

		class IMPACT_DATA_DATA
		{
		public:
			// members
			REX::Float32 effectDuration;					 // 00
			REX::Enum<ORIENTATION, std::int32_t> orient;	 // 04
			REX::Float32 angleThreshold;					 // 08
			REX::Float32 placementRadius;					 // 0C
			REX::Enum<SOUND_LEVEL, std::int32_t> soundLevel; // 10
			std::int8_t flags;								 // 14
			std::int8_t resultOverride;						 // 15
		};
		static_assert(sizeof(IMPACT_DATA_DATA) == 0x18);

		// members
		IMPACT_DATA_DATA data;				  // 50
		BGSTextureSet* decalTextureSet;		  // 68
		BGSTextureSet* decalTextureSet2;	  // 70
		BGSSoundDescriptorForm* sound01;	  // 78
		BGSSoundDescriptorForm* sound02;	  // 80
		BGSExplosion* explosion;			  // 88
		BGSHazard* hazard;					  // 90
		DecalData decalData;				  // 98
		REX::Float32 maxFootstepParticleDist; // BC
	};
	static_assert(sizeof(BGSImpactData) == 0xC0);
}
