#pragma once

#include "RE/H/hkRefPtr.hpp"
#include "RE/H/hkReferencedObject.hpp"
#include "RE/H/hkStreamReader.hpp"

namespace RE
{
	class __declspec(novtable) hkIArchive : public hkReferencedObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hkIArchive;
		inline static constexpr const auto& VTABLE = VTABLE::hkIArchive;

		~hkIArchive() override; // 0x00

		[[nodiscard]]
		auto IsOk() const noexcept -> bool
		{
			return reader && reader->IsOk();
		}

		// members
		hkRefPtr<hkStreamReader> reader; // 0x10
		bool byteSwap;					 // 0x18
	};

	static_assert(sizeof(hkIArchive) == 0x20);
}
