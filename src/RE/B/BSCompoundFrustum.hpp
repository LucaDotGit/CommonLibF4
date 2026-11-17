#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/N/NiCamera.hpp"
#include "RE/N/NiFrustumPlanes.hpp"

namespace RE::BSCoreUtils
{
	class BSCPUFeatures;
}

namespace RE
{
	class BSCompoundFrustum
	{
	public:
		enum class Operator : std::int32_t
		{
			NoOp = 0,
			EOL = 1,
			EOLPass = 2,
			EOLFail = 3,
			GroupIntersection = 4,
			GroupUnion = 5,
			GroupEnd = 6,
			Portal = 7,
			Occlusion = 8,
			OcclusionBox = 9
		};

		class FunctionOp
		{
		public:
			// members
			std::int32_t op; // 0x00
			std::int32_t jp; // 0x04
			std::int32_t jf; // 0x08
		};

		static_assert(sizeof(FunctionOp) == 0x0C);

		// members
		BSTArray<NiFrustumPlanes> planes;		 // 0x00
		BSTArray<FunctionOp> functionOperators;	 // 0x18
		NiFrustumPlanes viewFrustum;			 // 0x30
		NiPoint3 viewPosition;					 // 0xA0
		NiCamera* camera;						 // 0xB0
		BSCoreUtils::BSCPUFeatures* cpuFeatures; // 0xB8
		std::uint32_t freePlane;				 // 0xC0
		std::uint32_t freeOp;					 // 0xC4
		std::uint32_t firstOp;					 // 0xC8
		bool skipViewFrustum;					 // 0xCC
		bool preThreaded;						 // 0xCD
	};

	static_assert(sizeof(BSCompoundFrustum) == 0xD0);
}
