#pragma once

#include "RE/H/hkReferencedObject.hpp"

namespace RE
{
	class hkSeekableStreamReader;

	class __declspec(novtable) hkStreamReader : public hkReferencedObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hkStreamReader;
		inline static constexpr const auto& VTABLE = VTABLE::hkStreamReader;

		// add
		virtual auto IsOk() -> bool = 0;												// 0x04
		virtual auto Read(void* a_buffer, std::int32_t a_numBytes) -> std::int32_t = 0; // 0x05
		virtual auto Skip(std::int32_t a_numBytes) -> std::int32_t;						// 0x06 - { return -1; }
		virtual auto Peek(void* a_buffer, std::int32_t a_numBytes) -> std::int32_t;		// 0x07 - { return -1; }
		virtual auto IsSeekTellSupported() -> hkSeekableStreamReader*;					// 0x08 - { return nullptr; }
	};

	static_assert(sizeof(hkStreamReader) == 0x10);
}
