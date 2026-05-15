#pragma once

#include "RE/H/hkRefPtr.hpp"
#include "RE/H/hkReferencedObject.hpp"
#include "RE/H/hkStreamWriter.hpp"

namespace RE
{
	class __declspec(novtable) hkOArchive
		: public hkReferencedObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hkOArchive };
		inline static constexpr auto VTABLE{ VTABLE::hkOArchive };

		~hkOArchive() override; // 00

		[[nodiscard]] bool IsOk() const noexcept { return writer && writer->IsOk(); }

		// members
		hkRefPtr<hkStreamWriter> writer; // 10
		bool byteSwap;					 // 18
	};
	static_assert(sizeof(hkOArchive) == 0x20);
}
