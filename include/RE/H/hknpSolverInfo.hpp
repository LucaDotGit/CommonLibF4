#pragma once

#include "RE/H/hkSimdFloat32.hpp"
#include "RE/H/hkVector4.hpp"

namespace RE
{
	class hknpSolverInfo
	{
	public:
		// members
		REX::Float32 tau;								   // 000
		REX::Float32 frictionTau;						   // 004
		hkSimdFloat32 damping;							   // 010
		hkSimdFloat32 deltaTime;						   // 020
		hkSimdFloat32 invDeltaTime;						   // 030
		hkSimdFloat32 subStepDeltaTime;					   // 040
		hkSimdFloat32 subStepInvDeltaTime;				   // 050
		hkSimdFloat32 distanceToLinearTim;				   // 060
		hkSimdFloat32 linearTimToDistance;				   // 070
		hkSimdFloat32 collisionTolerance;				   // 080
		hkSimdFloat32 unitScale;						   // 090
		hkSimdFloat32 collisionAccuracy;				   // 0A0
		REX::Float32 maxApproachSpeedForHighQualitySolver; // 0B0
		std::int32_t numSteps;							   // 0B4
		REX::Float32 invNumSteps;						   // 0B8
		std::int32_t numMicroSteps;						   // 0BC
		REX::Float32 invNumMicroSteps;					   // 0C0
		REX::Float32 nominalGravityLength;				   // 0C4
		REX::Float32 expectedDeltaTime;					   // 0C8
		std::uint32_t stepSolveCount;					   // 0CC
		hkVector4 globalAccelerationPerSubStep;			   // 0D0
		hkVector4 globalAccelerationPerStep;			   // 0E0
		hkVector4 integrateVelocityFactor;				   // 0F0
		hkVector4 invIntegrateVelocityFactor;			   // 100
		hkSimdFloat32 rhsFactor;						   // 110
		hkSimdFloat32 frictionRhsFactor;				   // 120
		REX::Float32 dampDivTau;						   // 130
		REX::Float32 tauDivDamp;						   // 134
		REX::Float32 dampDivFrictionTau;				   // 138
		REX::Float32 frictionTauDivDamp;				   // 13C
	};
	static_assert(sizeof(hknpSolverInfo) == 0x140);
}
