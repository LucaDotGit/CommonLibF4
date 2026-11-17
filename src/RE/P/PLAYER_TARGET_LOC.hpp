#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class DoorTeleportData;

	class PLAYER_TARGET_LOC
	{
	public:
		using ArrivalFuncType = void(void*);

		// members
		TESWorldSpace* world;			  // 0x00
		TESObjectCELL* interior;		  // 0x08
		DoorTeleportData* transitionTel;  // 0x10
		NiPoint3 location;				  // 0x18
		NiPoint3 angle;					  // 0x24
		TESObjectREFR* walkThroughDoor;	  // 0x30
		ArrivalFuncType* arrivalFunc;	  // 0x38
		void* arrivalFuncData;			  // 0x40
		ObjectRefHandle furnitureRef;	  // 0x48
		ObjectRefHandle fastTravelMarker; // 0x4C
		REX::Float32 fastTravelDist;	  // 0x50
		bool resetWeather;				  // 0x54
		bool allowAutoSave;				  // 0x55
		bool preventLoadMenu;			  // 0x56
		bool skyTransition;				  // 0x57
		bool isValid;					  // 0x58
	};

	static_assert(sizeof(PLAYER_TARGET_LOC) == 0x60);
}
