#pragma once

#include "RE/H/hkVector4.hpp"

namespace RE
{
	class hknpCharacterSurfaceInfo
	{
	public:
		enum class SupportedState : std::int8_t; // To-Do

		// members
		bool isSurfaceDynamic;								   // 0x00
		REX::Enum<SupportedState, std::int8_t> supportedState; // 0x01
		REX::Float32 surfaceDistanceExcess;					   // 0x04
		hkVector4 surfaceNormal;							   // 0x10
		hkVector4 surfaceVelocity;							   // 0x20
	};

	static_assert(sizeof(hknpCharacterSurfaceInfo) == 0x30);
}
