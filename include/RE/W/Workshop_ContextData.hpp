#pragma once

#include "RE/A/Actor.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/T/TESObjectCELL.hpp"

namespace RE::Workshop
{
	class ContextData
	{
	public:
		ContextData(Actor* a_actor)
			: zAngle(a_actor->data.angle.z),
			  parentCell(a_actor->parentCell),
			  worldSpace(a_actor->parentCell->worldSpace)
		{
			// lookDir.y = 1.0_f32;
			a_actor->GetEyeVector(lookPos, lookDir, false);
		}

		~ContextData() noexcept = default;

		ContextData(const ContextData&) = default;
		ContextData(ContextData&&) noexcept = default;

		ContextData& operator=(const ContextData&) = default;
		ContextData& operator=(ContextData&&) noexcept = default;

		// members
		NiPoint3 lookPos;		   // 00
		NiPoint3 lookDir;		   // 0C
		REX::Float32 zAngle;	   // 18
		TESObjectCELL* parentCell; // 20
		TESWorldSpace* worldSpace; // 28
	};
	static_assert(sizeof(ContextData) == 0x30);
}
