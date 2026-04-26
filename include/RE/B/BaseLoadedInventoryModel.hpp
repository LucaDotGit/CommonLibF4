#pragma once

#include "RE/B/BGSCreatedObjectManager.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiAVObject;

	class BaseLoadedInventoryModel
	{
	public:
		// members
		CreatedObjPtr<TESForm> itemBase;  // 00
		TESBoundObject* modelObj;		  // 08
		NiPointer<NiAVObject> model;	  // 10
		NiPoint2 panMinima;				  // 18
		NiPoint2 panMaxima;				  // 20
		REX::Float32 initialDistance;	  // 28
		REX::Float32 boundRadius;		  // 2C
		REX::Float32 horizontalBound;	  // 30
		REX::Float32 verticalBound;		  // 34
		REX::Float32 verticalBoundOffset; // 38
	};
	static_assert(sizeof(BaseLoadedInventoryModel) == 0x40);
}
