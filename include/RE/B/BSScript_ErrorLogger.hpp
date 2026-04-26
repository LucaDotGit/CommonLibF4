#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTHashMap.hpp"

namespace RE::BSScript
{
	class ICachedErrorMessage;
	class LogEvent;

	class __declspec(novtable) ErrorLogger
		: public BSTEventSource<LogEvent> // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__ErrorLogger };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__ErrorLogger };

		enum class Severity : std::int32_t
		{
			kInfo = 0,
			kWarning = 1,
			kError = 2,
			kFatal = 3,

			kTotal = 4
		};

		class PerThreadErrorCounts
		{
		public:
			// members
			std::uint32_t fatalCount;	// 00
			std::uint32_t errorCount;	// 04
			std::uint32_t warningCount; // 08
		};
		static_assert(sizeof(PerThreadErrorCounts) == 0x0C);

		virtual ~ErrorLogger(); // 00

		// add
		virtual void PostErrorImpl(const ICachedErrorMessage* a_errMsg, Severity a_severity) = 0; // 01
		virtual void ResetImpl();																  // 02 - { return; }

		// members
		BSFixedString logName;												// 60
		mutable BSSpinLock dataLock;										// 68
		BSTHashMap<REX::W32::THREAD_ID, PerThreadErrorCounts> threadErrors; // 70
	};
	static_assert(sizeof(ErrorLogger) == 0xA0);
}
