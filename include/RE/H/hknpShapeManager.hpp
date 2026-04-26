#pragma once

#include "RE/H/hkArray.hpp"
#include "RE/H/hknpBodyId.hpp"
#include "RE/H/hknpShapeSignals.hpp"

namespace RE
{
	class hknpShape;

	class hknpShapeManager
	{
	public:
		class MutableShapeInfo
		{
		public:
			// members
			hknpShapeManager* shapeManager;											   // 00
			hknpShape* shape;														   // 08
			hkArray<hknpBodyId> bodyIds;											   // 10
			REX::EnumSet<hknpShapeSignals::MutationFlagsEnum, std::uint8_t> mutations; // 20
		};
		static_assert(sizeof(MutableShapeInfo) == 0x28);

		// members
		hkArray<MutableShapeInfo*> mutableShapeInfos;	  // 00
		hkArray<MutableShapeInfo*> freeMutableShapeInfos; // 10
		bool isAnyShapeMutated;							  // 20
	};
	static_assert(sizeof(hknpShapeManager) == 0x28);
}
