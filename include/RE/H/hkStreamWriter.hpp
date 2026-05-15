#pragma once

#include "RE/H/hkReferencedObject.hpp"
#include "RE/H/hkResult.hpp"
#include "RE/H/hkSeekableStreamReader.hpp"

namespace RE
{
	class __declspec(novtable) hkStreamWriter
		: public hkReferencedObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hkStreamWriter };
		inline static constexpr auto VTABLE{ VTABLE::hkStreamWriter };

		using SeekWhence = hkSeekableStreamReader::SeekWhence;

		// add
		virtual bool IsOk() = 0;													   // 04
		virtual std::int32_t Write(const void* a_buffer, std::int32_t a_numBytes) = 0; // 05
		virtual void Flush();														   // 06 - { return; }
		virtual bool SeekTellSupported();											   // 07 - { return false; }
		virtual hkResult Seek(std::int32_t a_offset, SeekWhence a_whence);			   // 08 - { return hkResult::kFailure; }
		virtual std::int32_t Tell();												   // 09 - { return -1; }
		virtual bool IsBuffered();													   // 10 - { return false; }
	};
	static_assert(sizeof(hkStreamWriter) == 0x10);
}
