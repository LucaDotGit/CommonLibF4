#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/N/NiObject.hpp"

namespace RE
{
	class __declspec(novtable) NiExtraData
		: public NiObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiExtraData };
		inline static constexpr auto VTABLE{ VTABLE::NiExtraData };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::NiExtraData };

		NiExtraData()
		{
			REL::EmplaceVtable(this);
		}

		explicit NiExtraData(BSFixedString a_name)
			: name(std::move(a_name))
		{
			REL::EmplaceVtable(this);
		}

		~NiExtraData() override = default; // 00

		// add
		virtual bool KeepForExport() const;		  // 28 - { return false; }
		virtual bool KeepForExporterOnly() const; // 29 - { return false; }
		virtual bool IsStreamable() const;		  // 2A - { return true; }
		virtual bool IsCloneable() const;		  // 2B - { return true; }

		// members
		BSFixedString name; // 10
	};
	static_assert(sizeof(NiExtraData) == 0x18);
}
