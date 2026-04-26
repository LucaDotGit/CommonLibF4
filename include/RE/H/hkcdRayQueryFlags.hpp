#pragma once

namespace RE
{
	class hkcdRayQueryFlags
	{
	public:
		enum class Enum : std::uint32_t
		{
			kNone = 0,
			kDisableBackFacingTriangleHits = 1 << 0,
			kDisableFrontFacingTriangleHits = 1 << 1,
			kEnableInsideHits = 1 << 2,
			kEnableExtraTriangleBevelplanes = 1 << 3
		};
	};
	static_assert(std::is_empty_v<hkcdRayQueryFlags>);
}
