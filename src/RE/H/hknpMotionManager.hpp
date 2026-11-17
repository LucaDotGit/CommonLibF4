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
			hkArray<hknpMotionId> solverIdToMotionId; // 0x10
		};

		static_assert(sizeof(CellData) == 0x10);

		// members
		hknpBodyManager* _bodyManager;		 // 0x00
		hkArray<hknpMotion> _motions;		 // 0x08
		bool _motionBufferIsUserOwned;		 // 0x18
		hknpMotionId _firstFreeMotionId;	 // 0x1C
		hknpMotionId _firstMarkedMotionId;	 // 0x20
		std::uint32_t _numAllocatedMotions;	 // 0x24
		std::uint32_t _numMarkedMotions;	 // 0x28
		std::uint32_t _peakMotionIndex;		 // 0x2C
		hkArray<CellData> _activeMotionGrid; // 0x30
		bool _isLocked;						 // 0x40
	};

	static_assert(sizeof(hknpMotionManager) == 0x48);
}
