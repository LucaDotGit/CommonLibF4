#pragma once

namespace RE
{
	enum class WEAPONHITBEHAVIOR : std::int32_t
	{
		kNormal = 0,
		kDismemberOnly = 1,
		kExplodeOnly = 2,
		kNoDismemberOrExplode = 3
	};
}
