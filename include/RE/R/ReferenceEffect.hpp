#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTempEffect.hpp"

namespace RE
{
	class NiAVObject;
	class ReferenceEffectController;

	class __declspec(novtable) ReferenceEffect
		: public BSTempEffect // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ReferenceEffect };
		inline static constexpr auto VTABLE{ VTABLE::ReferenceEffect };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::ReferenceEffect };
		inline static constexpr auto EFFECT_TYPE{ TEMP_EFFECT_TYPE::kRefDefault };

		~ReferenceEffect() override; // 00

		// add
		virtual bool Init();							   // 37
		virtual void Suspend();							   // 38
		virtual void Resume();							   // 39
		virtual void Update3D();						   // 3A
		virtual void ClearTarget();						   // 3B
		virtual void UpdateParentCell(NiAVObject* a_root); // 3C
		virtual void UpdatePosition();					   // 3D
		virtual NiAVObject* GetAttachRoot();			   // 3E
		virtual bool GetAttached();						   // 3F
		virtual void DetachImpl();						   // 40

		// members
		ReferenceEffectController* controller; // 30
		ObjectRefHandle target;				   // 38
		ObjectRefHandle aimAtTarget;		   // 3C
		bool finished;						   // 40
		bool ownController;					   // 41
	};
	static_assert(sizeof(ReferenceEffect) == 0x48);
}
