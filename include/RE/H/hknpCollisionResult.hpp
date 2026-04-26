#pragma once

#include "RE/C/CFilter.hpp"
#include "RE/H/hkPadSpu.hpp"
#include "RE/H/hkVector4f.hpp"
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
			hknpBodyId bodyId;							// 00
			hknpMaterialId shapeMaterialId;				// 04
			hkPadSpu<std::uint32_t> shapeKey;			// 08
			hkPadSpu<CFilter> shapeCollisionFilterInfo; // 0C
			hkPadSpu<std::uint64_t> shapeUserData;		// 10
		};
		static_assert(sizeof(BodyInfo) == 0x18);

		// members
		hkVector4f position;											 // 00
		hkVector4f normal;												 // 10
		hkPadSpu<REX::Float32> fraction;								 // 20
		BodyInfo queryBodyInfo;											 // 28
		BodyInfo hitBodyInfo;											 // 40
		REX::Enum<hknpCollisionQueryType::Enum, std::int32_t> queryType; // 58
		hkPadSpu<std::uint32_t> hitResult;								 // 5C
	};
	static_assert(sizeof(hknpCollisionResult) == 0x60);
}
