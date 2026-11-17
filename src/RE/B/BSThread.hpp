#pragma once

#include "RE/B/BSCriticalSection.hpp"

namespace RE
{
	class __declspec(novtable) BSThread
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSThread;
		inline static constexpr const auto& VTABLE = VTABLE::BSThread;

		virtual ~BSThread(); // 0x00

		// add
		virtual auto ThreadProc() -> std::uint32_t; // 0x01

		// members
		mutable BSCriticalSection criticalSection; // 0x08
		REX::W32::HANDLE threadHandle;			   // 0x30
		REX::W32::HANDLE parentHandle;			   // 0x38
		REX::W32::THREAD_ID threadID;			   // 0x40
		REX::W32::THREAD_ID parentID;			   // 0x44
		volatile bool threadIsActive;			   // 0x48
	};

	static_assert(sizeof(BSThread) == 0x50);
}
