#include "RE/P/PerkUtilities.hpp"

namespace RE::PerkUtilities
{
	void RemoveGrenadeTrajectory()
	{
		using FuncType = decltype(&PerkUtilities::RemoveGrenadeTrajectory);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::PerkUtilities::RemoveGrenadeTrajectory };
		FUNC();
	}
}
