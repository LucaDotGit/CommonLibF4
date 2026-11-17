#pragma once

#include "RE/R/ReferenceEffectController.hpp"

namespace RE
{
	class __declspec(novtable) SkyEffectController : public ReferenceEffectController // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::SkyEffectController;
		inline static constexpr const auto& VTABLE = VTABLE::SkyEffectController;

		// override (ReferenceEffectController)
		void RemoveHitEffect(ReferenceEffect* a_refEffect) override; // 0x0A - { return; }
		auto GetTargetReference() -> TESObjectREFR* override;		 // 0x0B - { return g_thePlayer; }
		auto GetHitEffectArt() -> BGSArtObject* override;			 // 0x0C - { return GetSkyReferenceEffectArt(); }
		auto GetHitEffectShader() -> TESEffectShader* override;		 // 0x0D - { return 0; }
		auto GetManagerHandlesSaveLoad() -> bool override;			 // 0x0E - { return 0; }
		auto GetAttachRoot() -> NiAVObject* override;				 // 0x0F
		auto EffectAttachesToCamera() -> bool override;				 // 0x1A - { return true; }
		auto EffectRotatesWithCamera() -> bool override;			 // 0x1B
	};

	static_assert(sizeof(SkyEffectController) == 0x08);
}
