#pragma once

#include "RE/B/BSCriticalSection.hpp"

namespace RE
{
	class __declspec(novtable) BSThread
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSThread };
		inline static constexpr auto VTABLE{ VTABLE::BSThread };

		virtual ~BSThread(); // 00

		// add
		virtual std::uint32_t ThreadProc(); // 01

		// members
		mutable BSCriticalSection criticalSection; // 08
		REX::W32::HANDLE threadHandle;			   // 30
		REX::W32::HANDLE parentHandle;			   // 38
		REX::W32::THREAD_ID threadID;			   // 40
		REX::W32::THREAD_ID parentID;			   // 44
		volatile bool threadIsActive;			   // 48
	};
	static_assert(sizeof(BSThread) == 0x50);
}
