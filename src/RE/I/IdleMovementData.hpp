#pragma once

#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class IdleMovementData
	{
	public:
		// members
		NiPoint3A translation;													   // 0x00
		NiPoint3A rotation;														   // 0x10
		NiPoint3A startVelocity;												   // 0x20
		NiPoint3A endVelocity;													   // 0x30
		NiPoint3A startRotSpeed;												   // 0x40
		NiPoint3A endRotSpeed;													   // 0x50
		NiPoint3A averageRotSpeed;												   // 0x60
		NiPoint3A translationUntilAllowRotation;								   // 0x70
		NiPoint3A velocityAtAllowRotation;										   // 0x80
		NiPoint3A rotSpeedAtAllowRotation;										   // 0x90
		REX::Float32 duration{static_cast<REX::Float32>(0.0)};					   // 0xA0
		REX::Float32 tweenStart{static_cast<REX::Float32>(0.0)};				   // 0xA4
		REX::Float32 tweenEnd{static_cast<REX::Float32>(0.0)};					   // 0xA8
		REX::Float32 rotationTweenStart{static_cast<REX::Float32>(0.0)};		   // 0xAC
		REX::Float32 rotationTweenEnd{static_cast<REX::Float32>(0.0)};			   // 0xB0
		std::array<REX::Float32, 4> syncAnimTimes{static_cast<REX::Float32>(0.0)}; // 0xB4
		bool usesAllowRotation{false};											   // 0xC4
	};

	static_assert(sizeof(IdleMovementData) == 0xD0);
}
