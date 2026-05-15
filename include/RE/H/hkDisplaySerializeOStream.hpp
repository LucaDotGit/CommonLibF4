#pragma once

#include "RE/H/hkOArchive.hpp"

namespace RE
{
	class __declspec(novtable) hkDisplaySerializeOStream
		: public hkOArchive // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hkDisplaySerializeOStream };
		inline static constexpr auto VTABLE{ VTABLE::hkDisplaySerializeOStream };

		~hkDisplaySerializeOStream() override; // 00
	};
	static_assert(sizeof(hkDisplaySerializeOStream) == 0x20);
}
