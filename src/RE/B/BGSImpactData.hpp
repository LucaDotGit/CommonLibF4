#pragma once

#include "RE/D/DecalData.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESModel.hpp"

namespace RE
{
	enum class SOUND_LEVEL : std::int32_t;

	class __declspec(novtable) BGSImpactData :
		public TESForm, // 0x00
		public TESModel // 0x20
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSImpactData;
		inline static constexpr const auto& VTABLE = VTABLE::BGSImpactData;
		inline static constexpr auto FORM_TYPE = FormType::ImpactData;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class ORIENTATION : std::int32_t
		{
			SurfaceNormal = 0,
			ProjVector = 1,
			ProjReflect = 2
		};

		class IMPACT_DATA_DATA
		{
		public:
			// members
			REX::Float32 effectDuration;					 // 0x00
			REX::Enum<ORIENTATION, std::int32_t> orient;	 // 0x04
			REX::Float32 angleThreshold;					 // 0x08
			REX::Float32 placementRadius;					 // 0x0C
			REX::Enum<SOUND_LEVEL, std::int32_t> soundLevel; // 0x10
			std::int8_t flags;								 // 0x14
			std::int8_t resultOverride;						 // 0x15
		};

		static_assert(sizeof(IMPACT_DATA_DATA) == 0x18);

		// members
		IMPACT_DATA_DATA data;				  // 0x50
		BGSTextureSet* decalTextureSet;		  // 0x68
		BGSTextureSet* decalTextureSet2;	  // 0x70
		BGSSoundDescriptorForm* sound01;	  // 0x78
		BGSSoundDescriptorForm* sound02;	  // 0x80
		BGSExplosion* explosion;			  // 0x88
		BGSHazard* hazard;					  // 0x90
		DecalData decalData;				  // 0x98
		REX::Float32 maxFootstepParticleDist; // 0xBC
	};

	static_assert(sizeof(BGSImpactData) == 0xC0);
}
