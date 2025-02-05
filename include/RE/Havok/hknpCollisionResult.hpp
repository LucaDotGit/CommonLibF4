#pragma once

#include "RE/Havok/hkBaseTypes.hpp"
#include "RE/Havok/hkVector4.hpp"
#include "RE/Havok/hknpBodyId.hpp"
#include "RE/Havok/hknpMaterialId.hpp"

namespace RE
{
	struct hknpCollisionQueryType
	{
	public:
		enum class Enum;
	};

	struct hknpCollisionResult
	{
	public:
		struct BodyInfo
		{
		public:
			// members
			hknpBodyId m_bodyId;								// 00
			hknpMaterialId m_shapeMaterialId;					// 04
			hkPadSpu<std::uint32_t> m_shapeKey;					// 08
			hkPadSpu<std::uint32_t> m_shapeCollisionFilterInfo; // 0C
			hkPadSpu<std::size_t> m_shapeUserData;				// 10
		};
		static_assert(sizeof(BodyInfo) == 0x18);

		// members
		hkVector4f position;										   // 00
		hkVector4f normal;											   // 10
		hkPadSpu<float> fraction;									   // 20
		BodyInfo queryBodyInfo;										   // 28
		BodyInfo hitBodyInfo;										   // 40
		hkEnum<hknpCollisionQueryType::Enum, std::uint32_t> queryType; // 58
		hkPadSpu<std::uint32_t> hitResult;							   // 5C
	};
	static_assert(sizeof(hknpCollisionResult) == 0x60);
}
