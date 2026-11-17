#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class BGSLoadGameBuffer;
	class BGSSaveGameBuffer;
	class NiAVObject;
	class NiNode;
	class NiPoint3;
	class ReferenceEffect;

	class __declspec(novtable) ReferenceEffectController
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ReferenceEffectController;
		inline static constexpr const auto& VTABLE = VTABLE::ReferenceEffectController;

		virtual ~ReferenceEffectController(); // 0x00

		// add
		virtual void HandleEvent(const BSFixedString& a_event); // 0x01 - { return; }
		virtual auto GetElapsedTime() -> REX::Float32;			// 0x02 - { return static_cast<REX::Float32>(0.0); }
		virtual auto GetScale() -> REX::Float32;				// 0x03 - { return static_cast<REX::Float32>(1.0); }
		virtual void SwitchAttachedRoot(NiNode* a_root, NiNode* a_attachRoot); // 0x04 - { return; }
		virtual auto GetSourcePosition() -> const NiPoint3&;				   // 0x05 - { return NiPoint3(); }
		virtual auto GetUseSourcePosition() -> bool;						   // 0x06 - { return true; }
		virtual auto GetNoInitialFlare() -> bool;							   // 0x07 - { return false; }
		virtual auto GetEffectPersists() -> bool;							   // 0x08 - { return true; }
		virtual auto GetGoryVisuals() -> bool;								   // 0x09 - { return false; }
		virtual void RemoveHitEffect(ReferenceEffect* a_refEffect);			   // 0x0A - { return; }
		virtual auto GetTargetReference() -> TESObjectREFR* = 0;			   // 0x0B
		virtual auto GetHitEffectArt() -> BGSArtObject* = 0;				   // 0x0C
		virtual auto GetHitEffectShader() -> TESEffectShader* = 0;			   // 0x0D
		virtual auto GetManagerHandlesSaveLoad() -> bool = 0;				   // 0x0E
		virtual auto GetAttachRoot()
			-> NiAVObject*; // 0x0F - { auto ref = GetTargetReference(); return ref ? ref->Get3D() : 0;
							// }
		virtual auto GetParticleAttachExtent() -> REX::Float32; // 0x10 - { return static_cast<REX::Float32>(0.0); }
		virtual auto GetUseParticleAttachExtent() -> bool;		// 0x11 - { return false; }
		virtual auto GetDoParticles() -> bool;					// 0x12 - { return true; }
		virtual auto GetParticlesUseLocalSpace() -> bool;		// 0x13 - { return false; }
		virtual auto GetUseRootWorldRotate() -> bool;			// 0x14 - { return false; }
		virtual auto GetIsRootActor() -> bool; // 0x15 - { auto ref = GetTargetReference(); return ref ? ref->formType =
											   // FormType::ActorCharacter : false; }
		virtual auto GetClearWhenCellIsUnloaded() -> bool;	// 0x16 - { return false; }
		virtual auto EffectShouldFaceTarget() -> bool;		// 0x17 - { return false; }
		virtual auto GetFacingTarget() -> TESObjectREFR*;	// 0x18 - { return 0; }
		virtual auto GetShaderUseParentCell() -> bool;		// 0x19 - { return true; }
		virtual auto EffectAttachesToCamera() -> bool;		// 0x1A - { return false; }
		virtual auto EffectRotatesWithCamera() -> bool;		// 0x1B - { return false; }
		virtual auto GetAllowTargetRoot() -> bool;			// 0x1C - { return true; }
		virtual auto IsReadyForAttach() -> bool;			// 0x1D - { return true; }
		virtual void SetWindPoint(const NiPoint3& a_point); // 0x1E - { return; }
		virtual auto GetWindPoint() -> const NiPoint3&;		// 0x1F - { return NiPoint3(); }
		virtual auto GetAllowNo3D() -> bool;				// 0x20 - { return false; }
		virtual void SaveGame(BGSSaveGameBuffer* a_buffer); // 0x21 - { return; }
		virtual void LoadGame(BGSLoadGameBuffer* a_buffer); // 0x22 - { return; }
	};

	static_assert(sizeof(ReferenceEffectController) == 0x08);
}
