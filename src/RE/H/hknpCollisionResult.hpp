#pragma once

#include "RE/C/CFilter.hpp"
#include "RE/H/hkPadSpu.hpp"
#include "RE/H/hkVector4.hpp"
#include "RE/H/hknpBodyId.hpp"
#include "RE/H/hknpCollisionQueryType.hpp"
#include "RE/H/hknpMaterialId.hpp"

namespace RE
{
	class hknpCollisionResult
	{
	public:
		class BodyInfo
		{
		public:
			// members
			hknpBodyId bodyId;							// 0x00
			hknpMaterialId shapeMaterialId;				// 0x04
			hkPadSpu<std::uint32_t> shapeKey;			// 0x08
			hkPadSpu<CFilter> shapeCollisionFilterInfo; // 0x0C
			hkPadSpu<std::uint64_t> shapeUserData;		// 0x10
		};

		static_assert(sizeof(BodyInfo) == 0x18);

		// members
		hkVector4 position;												 // 0x00
		hkVector4 normal;												 // 0x10
		hkPadSpu<REX::Float32> fraction;								 // 0x20
		BodyInfo queryBodyInfo;											 // 0x28
		BodyInfo hitBodyInfo;											 // 0x40
		REX::Enum<hknpCollisionQueryType::Enum, std::int32_t> queryType; // 0x58
		hkPadSpu<std::uint32_t> hitResult;								 // 0x5C
	};

	static_assert(sizeof(hknpCollisionResult) == 0x60);
}
