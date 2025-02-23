#pragma once

#include "RE/Bethesda/BSStorage.hpp"

namespace RE::BSScript
{
	struct __declspec(novtable) IHandleReaderWriter
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__IHandleReaderWriter };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__IHandleReaderWriter };

		virtual ~IHandleReaderWriter(); // 00

		// add
		virtual std::uint16_t GetHandleVersion() const = 0;									// 01
		virtual bool WriteHandle(BSStorage& storage, std::uint64_t) const = 0;				// 02
		virtual bool ReadHandle(BSStorage const& storage, std::uint64_t&) const = 0;		// 03
		virtual bool ReadHandleNoRemap(BSStorage const& storage, std::uint64_t&) const = 0; // 04
	};
	static_assert(sizeof(IHandleReaderWriter) == 0x8);
}
