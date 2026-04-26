#pragma once

#include "RE/H/hkArray.hpp"
#include "RE/H/hknpMotionId.hpp"

namespace RE
{
	class hknpBodyManager;
	class hknpMotion;

	class hknpMotionManager
	{
	public:
		class CellData
		{
		public:
			// members
			hkArray<hknpMotionId> solverIdToMotionId; // 10
		};
		static_assert(sizeof(CellData) == 0x10);

		// members
		hknpBodyManager* _bodyManager;		 // 00
		hkArray<hknpMotion> _motions;		 // 08
		bool _motionBufferIsUserOwned;		 // 18
		hknpMotionId _firstFreeMotionId;	 // 1C
		hknpMotionId _firstMarkedMotionId;	 // 20
		std::uint32_t _numAllocatedMotions;	 // 24
		std::uint32_t _numMarkedMotions;	 // 28
		std::uint32_t _peakMotionIndex;		 // 2C
		hkArray<CellData> _activeMotionGrid; // 30
		bool _isLocked;						 // 40
	};
	static_assert(sizeof(hknpMotionManager) == 0x48);
}
