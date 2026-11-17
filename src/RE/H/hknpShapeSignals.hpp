#pragma once

#include "RE/H/hkSignal.hpp"

namespace RE
{
	class hknpShapeSignals
	{
	public:
		enum class MutationFlagsEnum : std::uint8_t
		{
			None = 0,
			AABBChanged = 1 << 0,
			UpdateCollisionCaches = 1 << 1,
			RebuildCollisionCaches = 1 << 2
		};

		class ShapeDestroyedSignal : public hkSignal0 // 0x00
		{
		public:
		};

		static_assert(sizeof(ShapeDestroyedSignal) == 0x08);

		class ShapeMutatedSignal : public hkSignal1<std::uint8_t>
		{
		public:
		};

		static_assert(sizeof(ShapeMutatedSignal) == 0x08);

		// members
		ShapeMutatedSignal shapeMutated;	 // 0x00
		ShapeDestroyedSignal shapeDestroyed; // 0x08
	};

	static_assert(sizeof(hknpShapeSignals) == 0x10);
}
