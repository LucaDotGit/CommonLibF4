#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/R/ReferenceEffectController.hpp"

namespace RE
{
	class __declspec(novtable) ActiveEffectReferenceEffectController : public ReferenceEffectController // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ActiveEffectReferenceEffectController;
		inline static constexpr const auto& VTABLE = VTABLE::ActiveEffectReferenceEffectController;

		// override (ReferenceEffectController)
		void HandleEvent(const BSFixedString& a_event) override; // 0x01 - return { effect->HandleEvent(a_event); }
		auto GetElapsedTime() -> REX::Float32 override;			 // 0x02 - return { effect->elapsedSeconds; }
		auto GetScale() -> REX::Float32 override;				 // 0x03
		void SwitchAttachedRoot(NiNode* a_root, NiNode* a_attachRoot)
			override; // 0x04 - return { effect->SwitchAttachedRoot(a_root, a_attachRoot); }
		auto GetSourcePosition() -> const NiPoint3& override;		 // 0x05
		auto GetUseSourcePosition() -> bool override;				 // 0x06
		auto GetNoInitialFlare() -> bool override;					 // 0x07
		auto GetEffectPersists() -> bool override;					 // 0x08
		auto GetGoryVisuals() -> bool override;						 // 0x09
		void RemoveHitEffect(ReferenceEffect* a_refEffect) override; // 0x0A
		auto GetTargetReference() -> TESObjectREFR* override;		 // 0x0B
		auto GetHitEffectArt() -> BGSArtObject* override;			 // 0x0C
		auto GetHitEffectShader() -> TESEffectShader* override;		 // 0x0D
		auto GetManagerHandlesSaveLoad() -> bool override;			 // 0x0E - { return false; }
		auto EffectShouldFaceTarget() -> bool override;				 // 0x17
		auto GetFacingTarget() -> TESObjectREFR* override;			 // 0x18
		void SetWindPoint(const NiPoint3& a_point) override;		 // 0x1E - { windPoint = a_point; }
		auto GetWindPoint() -> const NiPoint3& override;			 // 0x1F - { return windPoint; }
		auto GetAllowNo3D() -> bool override;						 // 0x20
		void SaveGame(BGSSaveGameBuffer* a_buffer) override;		 // 0x21
		void LoadGame(BGSLoadGameBuffer* a_buffer) override;		 // 0x22

		// members
		ActiveEffect* effect;	// 0x08
		NiPoint3 windPoint;		// 0x10
		ObjectRefHandle target; // 0x18
	};

	static_assert(sizeof(ActiveEffectReferenceEffectController) == 0x20);
}
