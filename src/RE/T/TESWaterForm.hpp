#pragma once

#include "RE/N/NiColorA.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESFullName.hpp"
#include "RE/T/TESTexture.hpp"
#include "RE/W/WaterShaderData.hpp"

namespace RE
{
	class BSWaterShaderMaterial;
	class NiTexture;

	class __declspec(novtable) TESWaterForm :
		public TESForm,	   // 0x000
		public TESFullName // 0x020
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESWaterForm;
		inline static constexpr const auto& VTABLE = VTABLE::TESWaterForm;
		inline static constexpr auto FORM_TYPE = FormType::WaterType;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint8_t
		{
			None = 0,
			CauseDamage = 1 << 0,
			DirectionalSounds = 1 << 2,
			EnableFlowmap = 1 << 3,
			BlendNormals = 1 << 4
		};

		[[nodiscard]]
		static auto GetDefaultWater() -> TESWaterForm*
		{
			static const auto DEFAULT_WATER = REL::Relocation<TESWaterForm**>(ID::TESWaterForm::DefaultWater);
			return *DEFAULT_WATER;
		}

		// members
		bool needUpdate;								  // 0x030
		NiColorA texScroll00;							  // 0x034
		NiColorA texScroll01;							  // 0x044
		NiColorA texScroll02;							  // 0x054
		TESTexture noiseTexture00;						  // 0x068
		TESTexture noiseTexture01;						  // 0x078
		TESTexture noiseTexture02;						  // 0x088
		std::int8_t alpha;								  // 0x098
		REX::EnumSet<Flags, std::uint8_t> flags;		  // 0x099
		BGSMaterialType* materialType;					  // 0x0A0
		BGSSoundDescriptorForm* waterSound;				  // 0x0A8
		WaterShaderData data;							  // 0x0B0
		std::array<TESWaterForm*, 3> waterWeatherControl; // 0x180
		std::int32_t currentTextureSelect01;			  // 0x198
		std::int32_t currentTextureSelect02;			  // 0x19C
		std::uint32_t frequencyX;						  // 0x1A0
		std::uint32_t frequencyY;						  // 0x1A4
		std::int32_t octaves;							  // 0x1A8
		REX::Float32 amplitude;							  // 0x1AC
		REX::Float32 lacunarity;						  // 0x1B0
		REX::Float32 bias;								  // 0x1B4
		REX::Float32 gain;								  // 0x1B8
		SpellItem* consumeSpell;						  // 0x1C0
		SpellItem* contactSpell;						  // 0x1C8
		NiPointer<NiTexture> niNoiseTexture00;			  // 0x1D0
		NiPointer<NiTexture> niNoiseTexture01;			  // 0x1D8
		NiPointer<NiTexture> niNoiseTexture02;			  // 0x1E0
		TESObjectACTI* placeableAutoWater;				  // 0x1E8
		TESObjectACTI* placeableLODWater;				  // 0x1F0
		BSWaterShaderMaterial* waterShaderMaterial;		  // 0x1F8
		bool resetNoiseTextures;						  // 0x200
		TESImageSpace* imageSpace;						  // 0x208
		NiPoint3 linearVelocity;						  // 0x210
		NiPoint3 angularVelocity;						  // 0x21C
	};

	static_assert(sizeof(TESWaterForm) == 0x228);
}
