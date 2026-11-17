#pragma once

namespace RE::PackageNS
{
	enum class CRIME_TYPE : std::int32_t
	{
		Steal = 0,
		Pickpocket = 1,
		Trespass = 2,
		Attack = 3,
		Murder = 4,
		Escape = 5,
		Unused = 6
	};
}
