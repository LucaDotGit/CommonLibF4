#pragma once

#include "RE/H/hkRefPtr.hpp"
#include "RE/H/hkReferencedObject.hpp"
#include "RE/H/hkStreamReader.hpp"

namespace RE
{
	class __declspec(novtable) hkIArchive
		: public hkReferencedObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hkIArchive };
		inline static constexpr auto VTABLE{ VTABLE::hkIArchive };

		~hkIArchive() override; // 00

		[[nodiscard]] bool IsOk() const noexcept { return reader && reader->IsOk(); }

		// members
		hkRefPtr<hkStreamReader> reader; // 10
		bool byteSwap;					 // 18
	};
	static_assert(sizeof(hkIArchive) == 0x20);
}
