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
			static const auto FUNC = REL::Relocation<FuncType>(ID::hknpBodyCinfo::ctor);
			std::invoke(FUNC, this);
		}

		// members
		hknpShape* shape;											 // 0x00
		hknpBodyId reservedBodyId;									 // 0x08
		hknpMotionId motionId;										 // 0x0C
		hknpBodyQualityId qualityId;								 // 0x10
		hknpMaterialId materialId;									 // 0x12
		std::uint32_t collisionFilterInfo;							 // 0x14
		REX::EnumSet<hknpCollisionFlags, std::uint32_t> flags;		 // 0x18
		REX::Float32 collisionLookAheadDistance;					 // 0x1C
		hkStringPtr name;											 // 0x20
		std::uintptr_t userData;									 // 0x28
		hkVector4 position;											 // 0x30
		hkQuaternionf orientation;									 // 0x40
		REX::EnumSet<hknpBody::SpuFlagsEnum, std::uint8_t> spuFlags; // 0x50
		hkRefPtr<hkLocalFrame> localFrame;							 // 0x58
	};

	static_assert(sizeof(hknpBodyCinfo) == 0x60);
}
