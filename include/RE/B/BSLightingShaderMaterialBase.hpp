#pragma once

#include "RE/B/BSShaderMaterial.hpp"
#include "RE/B/BSSpinLock.hpp"
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

	class __declspec(novtable) BSLightingShaderMaterialBase
		: public BSShaderMaterial // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSLightingShaderMaterialBase };
		inline static constexpr auto VTABLE{ VTABLE::BSLightingShaderMaterialBase };

		// add
		virtual const BSLightingShaderMaterialEnvmap* IsLightingShaderMaterialEnvmap();		   // 09
		virtual void ClearTextures();														   // 0A
		virtual std::uint32_t GetTextures(NiTexture** a_textures, std::uint32_t a_arraySize);  // 0B
		virtual void SaveBinary(NiStream* a_stream);										   // 0C
		virtual void LoadBinary(NiStream* a_stream);										   // 0D
		virtual void OnPrefetchTextures(void* a_outHandles, const BSTextureSet* a_textureSet); // 0E - TextureDB::Handle
		virtual void OnLoadTextureSet1(const BSTextureSet* a_textureSet, void* a_inHandles);   // 0F - TextureDB::Handle
		virtual void OnLoadTextureSet2(const BSTextureSet* a_textureSet);					   // 10
		virtual void DoReceiveValuesFromRootMaterial(const BSShaderData& a_rootData);		   // 11

		void OnLoadTextureSet(const BSTextureSet* a_textureSet, void* a_inHandles) // TextureDB::Handle
		{
			return OnLoadTextureSet1(a_textureSet, a_inHandles);
		}

		void OnLoadTextureSet(const BSTextureSet* a_textureSet)
		{
			return OnLoadTextureSet2(a_textureSet);
		}

		// members
		NiColor specularColor;							   // 38
		NiPointer<NiTexture> diffuseTexture;			   // 40
		NiPointer<NiTexture> normalTexture;				   // 48
		NiPointer<NiTexture> rimSoftLightingTexture;	   // 50
		NiPointer<NiTexture> smoothnessSpecMaskTexture;	   // 58
		NiPointer<NiTexture> lookupTexture;				   // 60
		BSGraphics::TextureAddressMode textureClampMode;   // 68
		NiPointer<BSTextureSet> textureSet;				   // 70
		REX::Float32 materialAlpha;						   // 74
		REX::Float32 refractionPower;					   // 78
		REX::Float32 smoothness;						   // 7C
		REX::Float32 specularColorScale;				   // 80
		REX::Float32 fresnelPower;						   // 84
		REX::Float32 wetnessControl_SpecScale;			   // 88
		REX::Float32 wetnessControl_SpecPowerScale;		   // 8C
		REX::Float32 wetnessControl_SpecMin;			   // 90
		REX::Float32 wetnessControl_EnvMapScale;		   // 94
		REX::Float32 wetnessControl_FresnelPower;		   // 98
		REX::Float32 wetnessControl_Metalness;			   // 9C
		REX::Float32 subSurfaceLightRolloff;			   // A0
		REX::Float32 rimLightPower;						   // A4
		REX::Float32 backLightPower;					   // A8
		REX::Float32 lookupScale;						   // AC
		mutable BSNonReentrantSpinLock loadTextureSetLock; // B0
	};
	static_assert(sizeof(BSLightingShaderMaterialBase) == 0xC0);
}
