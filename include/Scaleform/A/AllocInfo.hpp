#pragma once

namespace Scaleform
{
	class AllocInfo
	{
	public:
		// members
		std::uint32_t statID;
	};
	static_assert(sizeof(AllocInfo) == 0x04);
}
