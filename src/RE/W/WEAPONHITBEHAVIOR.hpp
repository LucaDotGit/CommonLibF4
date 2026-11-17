#pragma once

namespace RE
{
	enum class WEAPONHITBEHAVIOR : std::int32_t
	{
		Normal = 0,
		DismemberOnly = 1,
		ExplodeOnly = 2,
		NoDismemberOrExplode = 3
	};
}
