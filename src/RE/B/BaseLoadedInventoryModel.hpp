#pragma once

#include "RE/B/BGSCreatedObjectManager.hpp"
#include "RE/N/NiPoint2.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiAVObject;

	class BaseLoadedInventoryModel
	{
	public:
		// members
		CreatedObjectPointer<TESForm> itemBase; // 0x00
		TESBoundObject* modelObj;				// 0x08
		NiPointer<NiAVObject> model;			// 0x10
		NiPoint2 panMinima;						// 0x18
		NiPoint2 panMaxima;						// 0x20
		REX::Float32 initialDistance;			// 0x28
		REX::Float32 boundRadius;				// 0x2C
		REX::Float32 horizontalBound;			// 0x30
		REX::Float32 verticalBound;				// 0x34
		REX::Float32 verticalBoundOffset;		// 0x38
	};

	static_assert(sizeof(BaseLoadedInventoryModel) == 0x40);
}
