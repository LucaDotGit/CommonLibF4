#pragma once

namespace RE
{
	enum class hknpShapeType : std::int32_t
	{
		kConvex = 0,
		kConvexPolytope = 1,
		kSphere = 2,
		kCapsule = 3,
		kTriangle = 4,
		kCompressedMesh = 5,
		kExternMesh = 6,
		kStaticCompound = 7,
		kDynamicCompound = 8,
		kHeightField = 9,
		kCompressedHeightField = 10,
		kScaledConvex = 11,
		kMasked = 12,
		kMaskedCompound = 13,
		kLOD = 14,
		kDummy = 15,
		kUser0 = 16,
		kUser1 = 17,
		kUser2 = 18,
		kUser3 = 19,

		kTotal = 20,

		kInvalid = 21
	};
}
