#pragma once

#include "RE/A/ACTOR_LOS_LOCATION.hpp"
#include "RE/A/AITimeStamp.hpp"

namespace RE
{
	class DetectionFormulaData
	{
	public:
		// members
		REX::Enum<ACTOR_LOS_LOCATION, std::int32_t> losLocation; // 0x00
		AITimeStamp timeStamp;									 // 0x04
		std::uint32_t ambush;									 // 0x08
		std::uint32_t targetRaceSize;							 // 0x0C
		std::uint32_t targetActionSound;						 // 0x10
		REX::Float32 lightLevel;								 // 0x14
		REX::Float32 modifiedLightLevel;						 // 0x18
		REX::Float32 visualDetectionDistance;					 // 0x1C
		REX::Float32 soundDetectionDistance;					 // 0x20
		REX::Float32 perception;								 // 0x24
		REX::Float32 basePerception;							 // 0x28
		REX::Float32 blindness;									 // 0x2C
		REX::Float32 deafness;									 // 0x30
		REX::Float32 targetDistance;							 // 0x34
		REX::Float32 targetAngle;								 // 0x38
		REX::Float32 targetVerticalAngle;						 // 0x3C
		REX::Float32 targetAgility;								 // 0x40
		REX::Float32 targetSneakSkill;							 // 0x44
		REX::Float32 targetBaseStealth;							 // 0x48
		REX::Float32 targetEquippedWeight;						 // 0x4C
		REX::Float32 targetMovementNoiseMult;					 // 0x50
		REX::Float32 targetStealth;								 // 0x54
		REX::Float32 targetVisibility;							 // 0x58
		REX::Float32 visualDetectionLevel;						 // 0x5C
		REX::Float32 soundDetectionLevel;						 // 0x60
		bool los;												 // 0x64
		bool los360;											 // 0x65
		bool exterior;											 // 0x66
		bool alert;												 // 0x67
		bool sleeping;											 // 0x68
		bool nightEye;											 // 0x69
		bool targetMoving;										 // 0x6A
		bool targetRunning;										 // 0x6B
		bool targetSneaking;									 // 0x6C
		bool targetInvisible;									 // 0x6D
		bool targetInCover;										 // 0x6E
		bool targetObserved;									 // 0x6F
		bool combatTarget;										 // 0x70
		bool flying;											 // 0x71
	};

	static_assert(sizeof(DetectionFormulaData) == 0x74);
}
