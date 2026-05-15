#pragma once

#include "RE/H/hkQuaternionf.hpp"
#include "RE/H/hkVector4.hpp"
#include "RE/H/hknpMotionPropertiesId.hpp"

namespace RE
{
	class hkLocalFrame;
	class hknpBodyCinfo;

	class hknpMotionCinfo
	{
	public:
		// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
		hknpMotionCinfo()
		{
			using FuncType = void(hknpMotionCinfo*);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::hknpMotionCinfo::ctor };
			std::invoke(FUNC, this);
		}

		void InitializeAsKeyFramed(hknpBodyCinfo* a_cInfos, std::uint32_t a_cInfosNum)
		{
			using FuncType = void(hknpMotionCinfo*, hknpBodyCinfo*, std::uint32_t);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::hknpMotionCinfo::InitializeAsKeyFramed };
			std::invoke(FUNC, this, a_cInfos, a_cInfosNum);
		}

		// members
		hknpMotionPropertiesId motionPropertiesId;		   // 00
		bool enableDeactivation;						   // 02
		REX::Float32 inverseMass;						   // 04
		REX::Float32 massFactor;						   // 08
		REX::Float32 maxLinearAccelerationDistancePerStep; // 0C
		REX::Float32 maxRotationToPreventTunneling;		   // 10
		hkVector4 inverseInertiaLocal;					   // 20
		hkVector4 centerOfMassWorld;					   // 30
		hkQuaternionf orientation;						   // 40
		hkVector4 linearVelocity;						   // 50
		hkVector4 angularVelocity;						   // 60
	};
	static_assert(sizeof(hknpMotionCinfo) == 0x70);
}
