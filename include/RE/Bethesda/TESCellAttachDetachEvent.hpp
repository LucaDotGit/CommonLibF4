#pragma once

#include "RE/Bethesda/BSTEvent.hpp"
#include "RE/Bethesda/TESObjectREFRs.hpp"
#include "RE/NetImmerse/NiSmartPointer.hpp"

namespace RE
{
	class TESObjectCELL;

	struct TESCellAttachDetachEvent
	{
		NiPointer<TESObjectREFR> reference; // 00
		bool attached;						// 08	- 01 - attached, 00 - detached
	};

	inline void RegisterForCellAttachDetach(BSTEventSink<TESCellAttachDetachEvent>* a_sink)
	{
		using func_t = decltype(&RegisterForCellAttachDetach);
		static REL::Relocation<func_t> func{ REL::RelocationID(409767, 2201568) };
		return func(a_sink);
	}
	static_assert(sizeof(TESCellAttachDetachEvent) == 0x10);
}
