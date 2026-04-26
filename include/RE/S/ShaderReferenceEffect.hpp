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

	class __declspec(novtable) ShaderReferenceEffect
		: public ReferenceEffect // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ShaderReferenceEffect };
		inline static constexpr auto VTABLE{ VTABLE::ShaderReferenceEffect };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::ShaderReferenceEffect };
		inline static constexpr auto EFFECT_TYPE{ TEMP_EFFECT_TYPE::kRefShader };

		enum class Flags : std::int32_t
		{
			kThirdPerson = 0,
			kInterfaceEffect = 1,
			kRestart = 2,
			kAllTexturesAvailable = 3,
			kParticleShadersStarted = 4,
			kSuspended = 5,
			kDisallowTargetRoot = 6
		};

		~ShaderReferenceEffect() override;

		// members
		BSMagicShaderParticles particles;								 // 048
		BSTArray<BSTPair<void*, NiPointer<NiTexture>*>> textureRequests; // 068 - TODO: `TextureDB::Handle`
		BSTArray<NiPointer<NiAVObject>> addOnObjects;					 // 080
		BSTArray<void*> modelHandles;									 // 098 - TODO: `BSModelDB::Handle`
		BSTArray<NiPointer<NiAVObject>> targetArray;					 // 0B0
		BSSoundHandle soundHandle;										 // 0C8
		NiPointer<NiSourceTexture> textureShaderTexture;				 // 0D0
		NiPointer<NiSourceTexture> textureBlockOutTexture;				 // 0D8
		NiPointer<NiSourceTexture> texturePaletteTexture;				 // 0E0
		TESBoundObject* wornObject;										 // 0E8
		TESEffectShader* effectData;									 // 0F0
		BSEffectShaderData* effectShaderData;							 // 0F8
		NiPointer<NiAVObject> lastRootNode;								 // 100
		REX::Float32 alphaTimer;										 // 104
		REX::Float32 addonAlpha;										 // 108
		REX::Float32 addonScale;										 // 10C
		REX::Float32 effectShaderAge;									 // 110
		REX::Enum<Flags, std::int32_t> flags;							 // 114
		std::uint32_t pushCount;										 // 118
	};
	static_assert(sizeof(ShaderReferenceEffect) == 0x120);
}
