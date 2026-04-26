#pragma once

#include "RE/N/NiColor.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESFullName.hpp"
#include "RE/T/TESTexture.hpp"
#include "RE/W/WaterShaderData.hpp"

namespace RE
{
	class BSWaterShaderMaterial;
	class NiTexture;

	class __declspec(novtable) TESWaterForm
		: public TESForm,	 // 000
		  public TESFullName // 020
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESWaterForm };
		inline static constexpr auto VTABLE{ VTABLE::TESWaterForm };
		inline static constexpr auto FORM_TYPE{ FormType::kWaterType };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint8_t
		{
			kNone = 0,
			kCauseDamage = 1 << 0,
			kDirectionalSounds = 1 << 2,
			kEnableFlowmap = 1 << 3,
			kBlendNormals = 1 << 4
		};

		[[nodiscard]] static TESWaterForm* GetDefaultWater()
		{
			static const auto DEFAULT_WATER = REL::Relocation<TESWaterForm**>{ ID::TESWaterForm::DefaultWater };
			return *DEFAULT_WATER;
		}

		// members
		bool needUpdate;								  // 030
		NiColorA texScroll00;							  // 034
		NiColorA texScroll01;							  // 044
		NiColorA texScroll02;							  // 054
		TESTexture noiseTexture00;						  // 068
		TESTexture noiseTexture01;						  // 078
		TESTexture noiseTexture02;						  // 088
		std::int8_t alpha;								  // 098
		REX::EnumSet<Flags, std::uint8_t> flags;		  // 099
		BGSMaterialType* materialType;					  // 0A0
		BGSSoundDescriptorForm* waterSound;				  // 0A8
		WaterShaderData data;							  // 0B0
		std::array<TESWaterForm*, 3> waterWeatherControl; // 180
		std::int32_t currentTextureSelect01;			  // 198
		std::int32_t currentTextureSelect02;			  // 19C
		std::uint32_t frequencyX;						  // 1A0
		std::uint32_t frequencyY;						  // 1A4
		std::int32_t octaves;							  // 1A8
		REX::Float32 amplitude;							  // 1AC
		REX::Float32 lacunarity;						  // 1B0
		REX::Float32 bias;								  // 1B4
		REX::Float32 gain;								  // 1B8
		SpellItem* consumeSpell;						  // 1C0
		SpellItem* contactSpell;						  // 1C8
		NiPointer<NiTexture> niNoiseTexture00;			  // 1D0
		NiPointer<NiTexture> niNoiseTexture01;			  // 1D8
		NiPointer<NiTexture> niNoiseTexture02;			  // 1E0
		TESObjectACTI* placeableAutoWater;				  // 1E8
		TESObjectACTI* placeableLODWater;				  // 1F0
		BSWaterShaderMaterial* waterShaderMaterial;		  // 1F8
		bool resetNoiseTextures;						  // 200
		TESImageSpace* imageSpace;						  // 208
		NiPoint3 linearVelocity;						  // 210
		NiPoint3 angularVelocity;						  // 21C
	};
	static_assert(sizeof(TESWaterForm) == 0x228);
}
