#pragma once

namespace RE::PackageNS
{
	enum class CRIME_TYPE : std::int32_t
	{
		kSteal = 0,
		kPickpocket = 1,
		kTrespass = 2,
		kAttack = 3,
		kMurder = 4,
		kEscape = 5,
		kUnused = 6
	};
}
