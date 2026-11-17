#pragma once

namespace Scaleform::GFx
{
	class ResourceId
	{
	public:
		// members
		std::uint32_t id; // 0x00
	};

	static_assert(sizeof(ResourceId) == 0x04);
}
