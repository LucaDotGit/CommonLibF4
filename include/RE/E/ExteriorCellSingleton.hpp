#pragma once

#include "RE/B/BSTSingleton.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class bhkWorldM;

	class ExteriorCellSingleton
		: public BSTSingletonExplicit<ExteriorCellSingleton>
	{
	public:
		[[nodiscard]] static ExteriorCellSingleton* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<ExteriorCellSingleton**>{ ID::ExteriorCellSingleton::Singleton };
			return *SINGLETON;
		}

		// members
		NiPointer<bhkWorldM> exteriorWorld;
	};
	static_assert(sizeof(ExteriorCellSingleton) == 0x08);
}
