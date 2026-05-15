#pragma once

#include "RE/H/hkReferencedObject.hpp"

namespace RE
{
	class hkSeekableStreamReader;

	class __declspec(novtable) hkStreamReader
		: public hkReferencedObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hkStreamReader };
		inline static constexpr auto VTABLE{ VTABLE::hkStreamReader };

		// add
		virtual bool IsOk() = 0;												// 04
		virtual std::int32_t Read(void* a_buffer, std::int32_t a_numBytes) = 0; // 05
		virtual std::int32_t Skip(std::int32_t a_numBytes);						// 06 - { return -1; }
		virtual std::int32_t Peek(void* a_buffer, std::int32_t a_numBytes);		// 07 - { return -1; }
		virtual hkSeekableStreamReader* IsSeekTellSupported();					// 08 - { return nullptr; }
	};
	static_assert(sizeof(hkStreamReader) == 0x10);
}
