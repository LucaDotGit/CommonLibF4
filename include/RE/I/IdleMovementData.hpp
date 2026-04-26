#pragma once

#include "RE/N/NiPoint.hpp"

namespace RE
{
	class IdleMovementData
	{
	public:
		// members
		NiPoint3A translation;								  // 00
		NiPoint3A rotation;									  // 10
		NiPoint3A startVelocity;							  // 20
		NiPoint3A endVelocity;								  // 30
		NiPoint3A startRotSpeed;							  // 40
		NiPoint3A endRotSpeed;								  // 50
		NiPoint3A averageRotSpeed;							  // 60
		NiPoint3A translationUntilAllowRotation;			  // 70
		NiPoint3A velocityAtAllowRotation;					  // 80
		NiPoint3A rotSpeedAtAllowRotation;					  // 90
		REX::Float32 duration{ 0.0_f32 };					  // A0
		REX::Float32 tweenStart{ 0.0_f32 };					  // A4
		REX::Float32 tweenEnd{ 0.0_f32 };					  // A8
		REX::Float32 rotationTweenStart{ 0.0_f32 };			  // AC
		REX::Float32 rotationTweenEnd{ 0.0_f32 };			  // B0
		std::array<REX::Float32, 4> syncAnimTimes{ 0.0_f32 }; // B4
		bool usesAllowRotation{ false };					  // C4
	};
	static_assert(sizeof(IdleMovementData) == 0xD0);
}
