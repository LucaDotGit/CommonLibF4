#pragma once

#include "RE/H/hkPtrAndInt.hpp"
#include "RE/H/hkSlot.hpp"

namespace RE
{
	class hkSignal
	{
	public:
		// members
		hkPtrAndInt<hkSlot, std::uint32_t, 3> slots; // 00
	};
	static_assert(sizeof(hkSignal) == 0x08);

	class hkSignal0
		: public hkSignal // 00
	{
	public:
	};
	static_assert(sizeof(hkSignal0) == 0x08);

	template <class T>
	class hkSignal1
		: public hkSignal // 00
	{
	public:
	};
	static_assert(sizeof(hkSignal1<std::any>) == 0x08);

	template <class T, class U>
	class hkSignal2
		: public hkSignal // 00
	{
	public:
	};
	static_assert(sizeof(hkSignal2<std::any, std::any>) == 0x08);

	template <class T, class U, class V>
	class hkSignal3
		: public hkSignal // 00
	{
	public:
	};
	static_assert(sizeof(hkSignal3<std::any, std::any, std::any>) == 0x08);
}
