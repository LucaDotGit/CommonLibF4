#pragma once

#include "RE/B/BSMagicShaderParticles.hpp"
#include "RE/B/BSSoundHandle.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/R/ReferenceEffect.hpp"

namespace RE
{
	class BSEffectShaderData;
	class NiAVObject;
	class NiSourceTexture;
	class NiTexture;

	class __declspec(novtable) ShaderReferenceEffect : public ReferenceEffect // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ShaderReferenceEffect;
		inline static constexpr const auto& VTABLE = VTABLE::ShaderReferenceEffect;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::ShaderReferenceEffect;
		inline static constexpr auto EFFECT_TYPE = TEMP_EFFECT_TYPE::RefShader;

		enum class Flags : std::int32_t
		{
			ThirdPerson = 0,
			InterfaceEffect = 1,
			Restart = 2,
			AllTexturesAvailable = 3,
			ParticleShadersStarted = 4,
			Suspended = 5,
			DisallowTargetRoot = 6
		};

		~ShaderReferenceEffect() override; // 0x00

		// members
		BSMagicShaderParticles particles; // 0x048
		BSTArray<BSTPair<void*, NiPointer<NiTexture>*>>
			textureRequests; // 0x068 - To-Do: `BSTArray<BSTPair<TextureDB::Handle, NiPointer<NiTexture>*>>`
		BSTArray<NiPointer<NiAVObject>> addOnObjects;	   // 0x080
		BSTArray<void*> modelHandles;					   // 0x098 - To-Do: `BSTArray<BSModelDB::Handle>`
		BSTArray<NiPointer<NiAVObject>> targetArray;	   // 0x0B0
		BSSoundHandle soundHandle;						   // 0x0C8
		NiPointer<NiSourceTexture> textureShaderTexture;   // 0x0D0
		NiPointer<NiSourceTexture> textureBlockOutTexture; // 0x0D8
		NiPointer<NiSourceTexture> texturePaletteTexture;  // 0x0E0
		TESBoundObject* wornObject;						   // 0x0E8
		TESEffectShader* effectData;					   // 0x0F0
		BSEffectShaderData* effectShaderData;			   // 0x0F8
		NiPointer<NiAVObject> lastRootNode;				   // 0x100
		REX::Float32 alphaTimer;						   // 0x104
		REX::Float32 addonAlpha;						   // 0x108
		REX::Float32 addonScale;						   // 0x10C
		REX::Float32 effectShaderAge;					   // 0x110
		REX::Enum<Flags, std::int32_t> flags;			   // 0x114
		std::uint32_t pushCount;						   // 0x118
	};

	static_assert(sizeof(ShaderReferenceEffect) == 0x120);
}
