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
			kNoOp = 0,
			kEOL = 1,
			kEOLPass = 2,
			kEOLFail = 3,
			kGroupIntersection = 4,
			kGroupUnion = 5,
			kGroupEnd = 6,
			kPortal = 7,
			kOcclusion = 8,
			kOcclusionBox = 9
		};

		class FunctionOp
		{
		public:
			// members
			std::int32_t op; // 00
			std::int32_t jp; // 04
			std::int32_t jf; // 08
		};
		static_assert(sizeof(FunctionOp) == 0x0C);

		// members
		BSTArray<NiFrustumPlanes> planes;		 // 00
		BSTArray<FunctionOp> functionOperators;	 // 18
		NiFrustumPlanes viewFrustum;			 // 30
		NiPoint3 viewPosition;					 // A0
		NiCamera* camera;						 // B0
		BSCoreUtils::BSCPUFeatures* cpuFeatures; // B8
		std::uint32_t freePlane;				 // C0
		std::uint32_t freeOp;					 // C4
		std::uint32_t firstOp;					 // C8
		bool skipViewFrustum;					 // CC
		bool preThreaded;						 // CD
	};
	static_assert(sizeof(BSCompoundFrustum) == 0xD0);
}
