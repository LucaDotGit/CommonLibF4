#pragma once

#include "RE/H/hkResult.hpp"
#include "RE/H/hkStreamReader.hpp"

namespace RE
{
	class __declspec(novtable) hkSeekableStreamReader
		: public hkStreamReader // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hkSeekableStreamReader };
		inline static constexpr auto VTABLE{ VTABLE::hkSeekableStreamReader };

		enum class SeekWhence : std::int32_t
		{
			kSet = 0,
			kCur = 1,
			kEnd = 2
		};

		// add
		virtual hkResult Seek(std::int32_t a_numBytes, SeekWhence a_whence) = 0; // 09
		virtual std::int32_t Tell() = 0;										 // 10
	};
	static_assert(sizeof(hkSeekableStreamReader) == 0x10);
}
