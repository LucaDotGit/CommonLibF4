#pragma once

#include "RE/H/hkOArchive.hpp"

namespace RE
{
	class __declspec(novtable) hkDisplaySerializeOStream : public hkOArchive // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hkDisplaySerializeOStream;
		inline static constexpr const auto& VTABLE = VTABLE::hkDisplaySerializeOStream;

		~hkDisplaySerializeOStream() override; // 0x00
	};

	static_assert(sizeof(hkDisplaySerializeOStream) == 0x20);
}
