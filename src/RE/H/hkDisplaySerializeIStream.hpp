#pragma once

#include "RE/H/hkIArchive.hpp"

namespace RE
{
	class __declspec(novtable) hkDisplaySerializeIStream : public hkIArchive // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hkDisplaySerializeIStream;
		inline static constexpr const auto& VTABLE = VTABLE::hkDisplaySerializeIStream;

		~hkDisplaySerializeIStream() override; // 0x00
	};

	static_assert(sizeof(hkDisplaySerializeIStream) == 0x20);
}
