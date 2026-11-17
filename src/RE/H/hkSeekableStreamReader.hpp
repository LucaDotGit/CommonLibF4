#pragma once

#include "RE/H/hkResult.hpp"
#include "RE/H/hkStreamReader.hpp"

namespace RE
{
	class __declspec(novtable) hkSeekableStreamReader : public hkStreamReader // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hkSeekableStreamReader;
		inline static constexpr const auto& VTABLE = VTABLE::hkSeekableStreamReader;

		enum class SeekWhence : std::int32_t
		{
			Set = 0,
			Cur = 1,
			End = 2
		};

		// add
		virtual auto Seek(std::int32_t a_numBytes, SeekWhence a_whence) -> hkResult = 0; // 0x09
		virtual auto Tell() -> std::int32_t = 0;										 // 0x10
	};

	static_assert(sizeof(hkSeekableStreamReader) == 0x10);
}
