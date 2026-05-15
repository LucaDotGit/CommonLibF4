#pragma once

#include "RE/H/hkVector4.hpp"

namespace RE
{
	class hknpCharacterSurfaceInfo
	{
	public:
		enum class SupportedState : std::int8_t; // TODO

		// members
		bool isSurfaceDynamic;								   // 00
		REX::Enum<SupportedState, std::int8_t> supportedState; // 01
		REX::Float32 surfaceDistanceExcess;					   // 04
		hkVector4 surfaceNormal;							   // 10
		hkVector4 surfaceVelocity;							   // 20
	};
	static_assert(sizeof(hknpCharacterSurfaceInfo) == 0x30);
}
