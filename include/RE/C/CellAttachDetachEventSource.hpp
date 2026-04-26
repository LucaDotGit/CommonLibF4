#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSingleton.hpp"

namespace RE
{
	class CellAttachDetachEvent;
}

namespace RE::CellAttachDetachEventSource
{
	class CellAttachDetachEventSourceSingleton
		: public BSTSingletonImplicit<CellAttachDetachEventSourceSingleton> // 00
	{
	public:
		[[nodiscard]] static CellAttachDetachEventSourceSingleton& GetSingleton()
		{
			using FuncType = decltype(&CellAttachDetachEventSourceSingleton::GetSingleton);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::CellAttachDetachEvent::Singleton };
			return std::invoke(FUNC);
		}

		// members
		BSTEventSource<CellAttachDetachEvent> source; // 00
	};
	static_assert(sizeof(CellAttachDetachEventSourceSingleton) == 0x58);
}
