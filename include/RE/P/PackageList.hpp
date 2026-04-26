#pragma once

#include "RE/B/BSSimpleList.hpp"

namespace RE
{
	class PackageList
	{
	public:
		// members
		BSSimpleList<TESPackage*> listPackages; // 00
	};
	static_assert(sizeof(PackageList) == 0x10);
}
