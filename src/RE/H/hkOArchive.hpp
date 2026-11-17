#pragma once

#include "RE/H/hkRefPtr.hpp"
#include "RE/H/hkReferencedObject.hpp"
#include "RE/H/hkStreamWriter.hpp"

namespace RE
{
	class __declspec(novtable) hkOArchive : public hkReferencedObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hkOArchive;
		inline static constexpr const auto& VTABLE = VTABLE::hkOArchive;

		~hkOArchive() override; // 0x00

		[[nodiscard]]
		auto IsOk() const noexcept -> bool
		{
			return writer && writer->IsOk();
		}

		// members
		hkRefPtr<hkStreamWriter> writer; // 0x10
		bool byteSwap;					 // 0x18
	};

	static_assert(sizeof(hkOArchive) == 0x20);
}
