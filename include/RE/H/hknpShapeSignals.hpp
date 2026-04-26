#pragma once

#include "RE/H/hkSignal.hpp"

namespace RE
{
	class hknpShapeSignals
	{
	public:
		enum class MutationFlagsEnum : std::uint8_t
		{
			kNone = 0,
			kAABBChanged = 1 << 0,
			kUpdateCollisionCaches = 1 << 1,
			kRebuildCollisionCaches = 1 << 2
		};

		class ShapeDestroyedSignal
			: public hkSignal0 // 00
		{
		public:
		};
		static_assert(sizeof(ShapeDestroyedSignal) == 0x08);

		class ShapeMutatedSignal
			: public hkSignal1<std::uint8_t>
		{
		public:
		};
		static_assert(sizeof(ShapeMutatedSignal) == 0x08);

		// members
		ShapeMutatedSignal shapeMutated;	 // 00
		ShapeDestroyedSignal shapeDestroyed; // 08
	};
	static_assert(sizeof(hknpShapeSignals) == 0x10);
}
