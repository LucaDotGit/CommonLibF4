#pragma once

#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/NetImmerse/NiObject.hpp"

namespace RE
{
	class __declspec(novtable) NiExtraData
		: public NiObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiExtraData };
		inline static constexpr auto VTABLE{ VTABLE::NiExtraData };
		inline static constexpr auto Ni_RTTI{ Ni_RTTI::NiExtraData };

		// add
		virtual bool KeepForExport() const { return false; }	   // 28
		virtual bool KeepForExporterOnly() const { return false; } // 29
		virtual bool IsStreamable() const { return true; }		   // 2A
		virtual bool IsCloneable() const { return true; }		   // 2B

		// members
		BSFixedString name; // 10
	};
	static_assert(sizeof(NiExtraData) == 0x18);
}
