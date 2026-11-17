#pragma once

namespace RE
{
	class MiddleLowProcessData
	{
	public:
		// members
		std::int32_t hourPackageEvaluated; // 0x00
	};

	static_assert(sizeof(MiddleLowProcessData) == 0x04);
}
