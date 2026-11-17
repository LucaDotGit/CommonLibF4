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
			hknpShapeManager* shapeManager;											   // 0x00
			hknpShape* shape;														   // 0x08
			hkArray<hknpBodyId> bodyIds;											   // 0x10
			REX::EnumSet<hknpShapeSignals::MutationFlagsEnum, std::uint8_t> mutations; // 0x20
		};

		static_assert(sizeof(MutableShapeInfo) == 0x28);

		// members
		hkArray<MutableShapeInfo*> mutableShapeInfos;	  // 0x00
		hkArray<MutableShapeInfo*> freeMutableShapeInfos; // 0x10
		bool isAnyShapeMutated;							  // 0x20
	};

	static_assert(sizeof(hknpShapeManager) == 0x28);
}
