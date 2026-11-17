#pragma once

namespace RE
{
	enum class hknpShapeType : std::int32_t
	{
		Convex = 0,
		ConvexPolytope = 1,
		Sphere = 2,
		Capsule = 3,
		Triangle = 4,
		CompressedMesh = 5,
		ExternMesh = 6,
		StaticCompound = 7,
		DynamicCompound = 8,
		HeightField = 9,
		CompressedHeightField = 10,
		ScaledConvex = 11,
		Masked = 12,
		MaskedCompound = 13,
		LOD = 14,
		Dummy = 15,
		User0 = 16,
		User1 = 17,
		User2 = 18,
		User3 = 19,

		_Count = 20,

		Invalid = 21
	};
}
