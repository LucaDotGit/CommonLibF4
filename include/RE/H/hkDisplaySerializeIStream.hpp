#pragma once

#include "RE/H/hkIArchive.hpp"

namespace RE
{
	class __declspec(novtable) hkDisplaySerializeIStream
		: public hkIArchive // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hkDisplaySerializeIStream };
		inline static constexpr auto VTABLE{ VTABLE::hkDisplaySerializeIStream };

		~hkDisplaySerializeIStream() override; // 00
	};
	static_assert(sizeof(hkDisplaySerializeIStream) == 0x20);
}
