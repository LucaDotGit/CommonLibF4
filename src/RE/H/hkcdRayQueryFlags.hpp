#pragma once

namespace RE
{
	class hkcdRayQueryFlags
	{
	public:
		enum class Enum : std::uint8_t
		{
			None = 0,
			DisableBackFacingTriangleHits = 1 << 0,
			DisableFrontFacingTriangleHits = 1 << 1,
			EnableInsideHits = 1 << 2,
			EnableExtraTriangleBevelplanes = 1 << 3
		};
	};

	static_assert(std::is_empty_v<hkcdRayQueryFlags>);
}
