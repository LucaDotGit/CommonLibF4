#pragma once

namespace RE
{
	class SetCullMarkersFunctor
	{
	public:
		// members
		bool cull; // 0x00
	};

	static_assert(sizeof(SetCullMarkersFunctor) == 0x01);
}
