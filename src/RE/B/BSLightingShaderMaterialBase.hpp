#pragma once

#include "RE/B/BSNonReentrantSpinLock.hpp"
#include "RE/B/BSShaderMaterial.hpp"
#include "RE/N/NiColor.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE::BSGraphics
{
	enum class TextureAddressMode : std::int32_t;
}

namespace RE
{
	class BSLightingShaderMaterialEnvmap;
	class BSShaderData;
	class BSTextureSet;
	class NiTexture;
	class NiStream;

	class __declspec(novtable) BSLightingShaderMaterialBase : public BSShaderMaterial // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSLightingShaderMaterialBase;
		inline static constexpr const auto& VTABLE = VTABLE::BSLightingShaderMaterialBase;

		// add
		virtual auto IsLightingShaderMaterialEnvmap() -> const BSLightingShaderMaterialEnvmap*;		  // 0x09
		virtual void ClearTextures();																  // 0x0A
		virtual auto GetTextures(NiTexture** a_textures, std::uint32_t a_arraySize) -> std::uint32_t; // 0x0B
		virtual void SaveBinary(NiStream* a_stream);												  // 0x0C
		virtual void LoadBinary(NiStream* a_stream);												  // 0x0D
		virtual void OnPrefetchTextures(
			void* a_outHandles,
			const BSTextureSet* a_textureSet);												 // 0x0E - TextureDB::Handle
		virtual void OnLoadTextureSet1(const BSTextureSet* a_textureSet, void* a_inHandles); // 0x0F - TextureDB::Handle
		virtual void OnLoadTextureSet2(const BSTextureSet* a_textureSet);					 // 0x10
		virtual void DoReceiveValuesFromRootMaterial(const BSShaderData& a_rootData);		 // 0x11

		void OnLoadTextureSet(const BSTextureSet* a_textureSet, void* a_inHandles) // TextureDB::Handle
		{
			OnLoadTextureSet1(a_textureSet, a_inHandles);
		}

		void OnLoadTextureSet(const BSTextureSet* a_textureSet)
		{
			OnLoadTextureSet2(a_textureSet);
		}

		// members
		NiColor specularColor;							   // 0x38
		NiPointer<NiTexture> diffuseTexture;			   // 0x40
		NiPointer<NiTexture> normalTexture;				   // 0x48
		NiPointer<NiTexture> rimSoftLightingTexture;	   // 0x50
		NiPointer<NiTexture> smoothnessSpecMaskTexture;	   // 0x58
		NiPointer<NiTexture> lookupTexture;				   // 0x60
		BSGraphics::TextureAddressMode textureClampMode;   // 0x68
		NiPointer<BSTextureSet> textureSet;				   // 0x70
		REX::Float32 materialAlpha;						   // 0x74
		REX::Float32 refractionPower;					   // 0x78
		REX::Float32 smoothness;						   // 0x7C
		REX::Float32 specularColorScale;				   // 0x80
		REX::Float32 fresnelPower;						   // 0x84
		REX::Float32 wetnessControl_SpecScale;			   // 0x88
		REX::Float32 wetnessControl_SpecPowerScale;		   // 0x8C
		REX::Float32 wetnessControl_SpecMin;			   // 0x90
		REX::Float32 wetnessControl_EnvMapScale;		   // 0x94
		REX::Float32 wetnessControl_FresnelPower;		   // 0x98
		REX::Float32 wetnessControl_Metalness;			   // 0x9C
		REX::Float32 subSurfaceLightRolloff;			   // 0xA0
		REX::Float32 rimLightPower;						   // 0xA4
		REX::Float32 backLightPower;					   // 0xA8
		REX::Float32 lookupScale;						   // 0xAC
		mutable BSNonReentrantSpinLock loadTextureSetLock; // 0xB0
	};

	static_assert(sizeof(BSLightingShaderMaterialBase) == 0xC0);
}
