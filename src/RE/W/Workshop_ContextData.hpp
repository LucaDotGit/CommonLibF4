#pragma once

#include "RE/A/Actor.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/T/TESObjectCELL.hpp"

namespace RE::Workshop
{
	class ContextData
	{
	public:
		ContextData(Actor* a_actor) :
			zAngle(a_actor->data.angle.z),
			parentCell(a_actor->parentCell),
			worldSpace(a_actor->parentCell->worldSpace)
		{
			// lookDir.y = static_cast<REX::Float32>(1.0);
			a_actor->GetEyeVector(lookPos, lookDir, false);
		}

		~ContextData() noexcept = default;

		ContextData(const ContextData&) = default;
		ContextData(ContextData&&) noexcept = default;

		auto operator=(const ContextData&) -> ContextData& = default;
		auto operator=(ContextData&&) noexcept -> ContextData& = default;

		// members
		NiPoint3 lookPos;		   // 0x00
		NiPoint3 lookDir;		   // 0x0C
		REX::Float32 zAngle;	   // 0x18
		TESObjectCELL* parentCell; // 0x20
		TESWorldSpace* worldSpace; // 0x28
	};

	static_assert(sizeof(ContextData) == 0x30);
}
