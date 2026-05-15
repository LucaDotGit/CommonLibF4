#pragma once

#include "RE/H/hkLocalFrame.hpp"
#include "RE/H/hkQuaternionf.hpp"
#include "RE/H/hkRefPtr.hpp"
#include "RE/H/hkStringPtr.hpp"
#include "RE/H/hkVector4.hpp"
#include "RE/H/hknpBody.hpp"

namespace RE
{
	class hkLocalFrame;

	class hknpBodyCinfo
	{
	public:
		// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
		hknpBodyCinfo()
		{
			using FuncType = void (hknpBodyCinfo::*)();
			static const auto FUNC = REL::Relocation<FuncType>{ ID::hknpBodyCinfo::ctor };
			std::invoke(FUNC, this);
		}

		// members
		hknpShape* shape;											 // 00
		hknpBodyId reservedBodyId;									 // 08
		hknpMotionId motionId;										 // 0C
		hknpBodyQualityId qualityId;								 // 10
		hknpMaterialId materialId;									 // 12
		std::uint32_t collisionFilterInfo;							 // 14
		REX::EnumSet<hknpCollisionFlags, std::uint32_t> flags;		 // 18
		REX::Float32 collisionLookAheadDistance;					 // 1C
		hkStringPtr name;											 // 20
		std::uintptr_t userData;									 // 28
		hkVector4 position;											 // 30
		hkQuaternionf orientation;									 // 40
		REX::EnumSet<hknpBody::SpuFlagsEnum, std::uint8_t> spuFlags; // 50
		hkRefPtr<hkLocalFrame> localFrame;							 // 58
	};
	static_assert(sizeof(hknpBodyCinfo) == 0x60);
}
