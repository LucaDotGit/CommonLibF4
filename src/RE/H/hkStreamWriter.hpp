#pragma once

#include "RE/H/hkReferencedObject.hpp"
#include "RE/H/hkResult.hpp"
#include "RE/H/hkSeekableStreamReader.hpp"

namespace RE
{
	class __declspec(novtable) hkStreamWriter : public hkReferencedObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hkStreamWriter;
		inline static constexpr const auto& VTABLE = VTABLE::hkStreamWriter;

		using SeekWhence = hkSeekableStreamReader::SeekWhence;

		// add
		virtual auto IsOk() -> bool = 0;													   // 0x04
		virtual auto Write(const void* a_buffer, std::int32_t a_numBytes) -> std::int32_t = 0; // 0x05
		virtual void Flush();																   // 0x06 - { return; }
		virtual auto SeekTellSupported() -> bool; // 0x07 - { return false; }
		virtual auto Seek(std::int32_t a_offset, SeekWhence a_whence)
			-> hkResult;					 // 0x08 - { return hkResult::Failure; }
		virtual auto Tell() -> std::int32_t; // 0x09 - { return -1; }
		virtual auto IsBuffered() -> bool;	 // 0x10 - { return false; }
	};

	static_assert(sizeof(hkStreamWriter) == 0x10);
}
