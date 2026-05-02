#pragma once

#include "RE/A/ACTOR_LOS_LOCATION.hpp"
#include "RE/A/AITimeStamp.hpp"

namespace RE
{
	class DetectionFormulaData
	{
	public:
		// members
		REX::Enum<ACTOR_LOS_LOCATION, std::int32_t> losLocation; // 00
		AITimeStamp timeStamp;									 // 04
		std::uint32_t ambush;									 // 08
		std::uint32_t targetRaceSize;							 // 0C
		std::uint32_t targetActionSound;						 // 10
		REX::Float32 lightLevel;								 // 14
		REX::Float32 modifiedLightLevel;						 // 18
		REX::Float32 visualDetectionDistance;					 // 1C
		REX::Float32 soundDetectionDistance;					 // 20
		REX::Float32 perception;								 // 24
		REX::Float32 basePerception;							 // 28
		REX::Float32 blindness;									 // 2C
		REX::Float32 deafness;									 // 30
		REX::Float32 targetDistance;							 // 34
		REX::Float32 targetAngle;								 // 38
		REX::Float32 targetVerticalAngle;						 // 3C
		REX::Float32 targetAgility;								 // 40
		REX::Float32 targetSneakSkill;							 // 44
		REX::Float32 targetBaseStealth;							 // 48
		REX::Float32 targetEquippedWeight;						 // 4C
		REX::Float32 targetMovementNoiseMult;					 // 50
		REX::Float32 targetStealth;								 // 54
		REX::Float32 targetVisibility;							 // 58
		REX::Float32 visualDetectionLevel;						 // 5C
		REX::Float32 soundDetectionLevel;						 // 60
		bool los;												 // 64
		bool los360;											 // 65
		bool exterior;											 // 66
		bool alert;												 // 67
		bool sleeping;											 // 68
		bool nightEye;											 // 69
		bool targetMoving;										 // 6A
		bool targetRunning;										 // 6B
		bool targetSneaking;									 // 6C
		bool targetInvisible;									 // 6D
		bool targetInCover;										 // 6E
		bool targetObserved;									 // 6F
		bool combatTarget;										 // 70
		bool flying;											 // 71
	};
	static_assert(sizeof(DetectionFormulaData) == 0x74);
}
