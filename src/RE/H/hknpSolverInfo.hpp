#pragma once

#include "RE/H/hkSimdFloat32.hpp"
#include "RE/H/hkVector4.hpp"

namespace RE
{
	class hknpSolverInfo
	{
	public:
		// members
		REX::Float32 tau;								   // 0x000
		REX::Float32 frictionTau;						   // 0x004
		hkSimdFloat32 damping;							   // 0x010
		hkSimdFloat32 deltaTime;						   // 0x020
		hkSimdFloat32 invDeltaTime;						   // 0x030
		hkSimdFloat32 subStepDeltaTime;					   // 0x040
		hkSimdFloat32 subStepInvDeltaTime;				   // 0x050
		hkSimdFloat32 distanceToLinearTim;				   // 0x060
		hkSimdFloat32 linearTimToDistance;				   // 0x070
		hkSimdFloat32 collisionTolerance;				   // 0x080
		hkSimdFloat32 unitScale;						   // 0x090
		hkSimdFloat32 collisionAccuracy;				   // 0x0A0
		REX::Float32 maxApproachSpeedForHighQualitySolver; // 0x0B0
		std::int32_t numSteps;							   // 0x0B4
		REX::Float32 invNumSteps;						   // 0x0B8
		std::int32_t numMicroSteps;						   // 0x0BC
		REX::Float32 invNumMicroSteps;					   // 0x0C0
		REX::Float32 nominalGravityLength;				   // 0x0C4
		REX::Float32 expectedDeltaTime;					   // 0x0C8
		std::uint32_t stepSolveCount;					   // 0x0CC
		hkVector4 globalAccelerationPerSubStep;			   // 0x0D0
		hkVector4 globalAccelerationPerStep;			   // 0x0E0
		hkVector4 integrateVelocityFactor;				   // 0x0F0
		hkVector4 invIntegrateVelocityFactor;			   // 0x100
		hkSimdFloat32 rhsFactor;						   // 0x110
		hkSimdFloat32 frictionRhsFactor;				   // 0x120
		REX::Float32 dampDivTau;						   // 0x130
		REX::Float32 tauDivDamp;						   // 0x134
		REX::Float32 dampDivFrictionTau;				   // 0x138
		REX::Float32 frictionTauDivDamp;				   // 0x13C
	};

	static_assert(sizeof(hknpSolverInfo) == 0x140);
}
