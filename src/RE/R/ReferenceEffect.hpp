#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTempEffect.hpp"

namespace RE
{
	class NiAVObject;
	class ReferenceEffectController;

	class __declspec(novtable) ReferenceEffect : public BSTempEffect // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ReferenceEffect;
		inline static constexpr const auto& VTABLE = VTABLE::ReferenceEffect;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::ReferenceEffect;
		inline static constexpr auto EFFECT_TYPE = TEMP_EFFECT_TYPE::RefDefault;

		~ReferenceEffect() override; // 0x00

		// add
		virtual auto Init() -> bool;					   // 0x37
		virtual void Suspend();							   // 0x38
		virtual void Resume();							   // 0x39
		virtual void Update3D();						   // 0x3A
		virtual void ClearTarget();						   // 0x3B
		virtual void UpdateParentCell(NiAVObject* a_root); // 0x3C
		virtual void UpdatePosition();					   // 0x3D
		virtual auto GetAttachRoot() -> NiAVObject*;	   // 0x3E
		virtual auto GetAttached() -> bool;				   // 0x3F
		virtual void DetachImpl();						   // 0x40

		// members
		ReferenceEffectController* controller; // 0x30
		ObjectRefHandle target;				   // 0x38
		ObjectRefHandle aimAtTarget;		   // 0x3C
		bool finished;						   // 0x40
		bool ownController;					   // 0x41
	};

	static_assert(sizeof(ReferenceEffect) == 0x48);
}
