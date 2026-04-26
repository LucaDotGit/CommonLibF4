#pragma once

#include "RE/B/BSEventFlag.hpp"
#include "RE/B/BSTAtomicValue.hpp"
#include "RE/B/BSThread.hpp"

namespace RE
{
	class __declspec(novtable) BSTaskThread
		: public BSThread // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSTaskThread };
		inline static constexpr auto VTABLE{ VTABLE::BSTaskThread };

		~BSTaskThread() override; // 00

		std::uint32_t ThreadProc() override; // 01

		// members
		std::array<std::byte, 0x80 - 0x50> pad50;		  // 50
		BSTAtomicValue<std::uint32_t> pauseResumeRequest; // 80
		BSEventFlag taskEvent;							  // 88
		bool exit;										  // 90
		std::array<std::byte, 0xC0 - 0x91> pad91;		  // 91
	};
	static_assert(sizeof(BSTaskThread) == 0xC0);
}
